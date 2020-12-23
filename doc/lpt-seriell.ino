
/********************************************************************************
 * PrinterCaptureInterrupt.ino
 * ------------------
 * Wiring Layout
 * -------------
 * 
 * Parallel Port Output               Arduino Input
 * --------------------               -------------
 * Name      Dir.   Pin                Name    Pin
 * ----      ----   ---                ----    ---
 * nSTROBE    >       1................INT0     2 (as interupt)
 * DATA BYTE  >     2-9....................     5,6,14-19    
 * nACK       <      10....................     3
 * BUSY       <      11....................     4
 * OutofPaper <      12................GND
 * Selected   <      13.................5v
 * GND        <>  18-25................GND
 *-------------------------------------------------------------------------------
 * 
 * CS:      pin 10 
 * MOSI:    pin 11
 * MISO:    pin 12 
 * SCK:     pin 13 
 *
 ********************************************************************************/
#define LEN 256

#define PWR_ON   7
#define PWR_STAT 8
#define LED_ON   9

#define SD_CS   10

#define Data0   5
#define Data1   6
#define Data2   14
#define Data3   15
#define Data4   16
#define Data5   17
#define Data6   18
#define Data7   19

#define nStrobe 2
#define nAck    3
#define Busy    4


#include <SPI.h>
#include <SD.h>
#include "TimerOne.h"  

enum States {
  READY,
  BUSY,
  ACK,
  STDBY
} State;

String Filename = "";
char buf[LEN];  
int bufx = 0;
int count = 0;
int toggle = LOW;
int adc;


void setup()
{
  //--------- Configure pins --------------

  pinMode(PWR_ON, OUTPUT);
  digitalWrite(PWR_ON,HIGH); // pin7 power-bridge ein; 
  pinMode(PWR_STAT, INPUT_PULLUP); // pin8 für status power-bridge
  pinMode(LED_ON, OUTPUT);
  digitalWrite(LED_ON,HIGH); // pin9 power Led ein; 
  
  pinMode(nStrobe, INPUT_PULLUP);
  
  for (int n = Data0; n < (Data7+1); n++)
    pinMode(n, INPUT_PULLUP);
  
  pinMode(nAck, OUTPUT);
  pinMode(Busy, OUTPUT);
  
  //Serial.begin(9600);
  //while (!Serial) { ; }
  
  attachInterrupt(0,DataReady,FALLING);
  State = STDBY;
  delay(100);
  //Serial.println("Pins Initialised");


  //-------- SD Karte einbinden -------------

  //Serial.println("Initializing SD Card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(SD_CS)) {
    //Serial.println("SD failed, or not present");
    // don't do anything more:
    delay(1000);
    digitalWrite(PWR_ON,LOW);    //Sleep -> pin7 bzw. power-bridge aussschalten 
    return;
  }
  //Serial.println("card initialized.");

  
  //-------- Dateinamen verwalten ------------

  if (!SD.exists("print")) 
  {
    Filename = "print";
    //Serial.println(Filename);
  }
  else
  {
    char text[10];
    String str; 

    for (int i=1; i < 1000; i++)
    {
       str= "print" + String(i); 
       str.toCharArray(text,10);
      
       if (!SD.exists(text)) 
       {
          Filename = String(text);
          //Serial.println(Filename);
          i=1000;
       }
    }
  }

  
  //-------- 1 sekunden timer einstellen -----------
  
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(sek);
  
}

 
void sek() 
{
  count++;
}

               
void loop()
{
  switch (State) {
    case READY:
      digitalWrite(Busy, LOW);
      digitalWrite(nAck,HIGH);
      break;
    case BUSY: // nStrobe signal received by interrupt handler
      digitalWrite(Busy, HIGH);
      ProcessChar();
      State = ACK;
      break;
    case ACK:
      digitalWrite(nAck,LOW);
      delayMicroseconds(10); // Specification minimum = 5 us       
      State = READY;
      break;
    case STDBY:
      //adc messen -> led blinken bei unterspannung akku
      adc = analogRead(7);
      if (adc<670) 
      {
        //Serial.println(adc);
        toggle = !toggle; 
        digitalWrite(LED_ON,toggle);
        delay(500);
      }
      break;  
  }   

  if ((State==READY) && (count==2))
  {
    SDsave(0);
  //  Serial.println("sd end");
    State = STDBY;
    digitalWrite(LED_ON,HIGH);
  }

  if (count>180) 
  {
  //  Serial.println("10 sekunden");   //im leerlauf etwa 80 mal pro sekunden aufgerufen
    digitalWrite(PWR_ON,LOW);    //Sleep -> pin7 bzw. power-bridge aussschalten 
    return;
  }
  
  if (digitalRead(PWR_STAT) && count>1)
  {
   // Serial.println("Power Off");
    digitalWrite(PWR_ON,LOW);    //Sleep -> pin7 bzw. power-bridge aussschalten 
    return;
  }
}


void DataReady()
{
  State = BUSY;
  count=0;
}


void ProcessChar()
{
  byte Char;
  
  Char =  digitalRead(Data0) +
         (digitalRead(Data1) << 1) +
         (digitalRead(Data2) << 2) +
         (digitalRead(Data3) << 3) +
         (digitalRead(Data4) << 4) +
         (digitalRead(Data5) << 5) +
         (digitalRead(Data6) << 6) +
         (digitalRead(Data7) << 7);
         
  //Serial.print((char)Char);
  buf[bufx]= Char;
  bufx++;
  
  if (bufx == LEN) 
  {
    SDsave(1); 
    bufx=0;
    //Serial.println("sd saving");
    toggle = !toggle;
    digitalWrite(LED_ON,toggle);   
  }
}

void SDsave(char mod)
{
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(Filename, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    if(mod) {
      dataFile.write(buf,LEN);
      dataFile.close();
    }
    else {
      dataFile.println(" ");
      dataFile.close();
    } 
  }
  // if the file isn't open, pop up an error:
  else {
    //Serial.println("error opening file");
  }
}



