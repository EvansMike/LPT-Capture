

/********************************************************************************
 * PrinterCaptureInterrupt.ino
 * ------------------
 * Wiring Layout
 * -------------
 *
 * Parallel Port Output               AVR Pins
 * --------------------               -------------
 * Name      Dir.   Pin                Name    Pin
 * ----      ----   ---                ----    ---
 * nSTROBE    >       1................INT0     2 (as interrupt)
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

enum States {
  READY,
  BUSY,
  ACK,
  STDBY
} State;






int main()
{


}

