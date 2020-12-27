/*
 * eps_convert.c
 *
 * Copyright 2020 Mike Evans <mikee@saxicola.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *

 Derived from http://tuxfrank.altervista.org/GTR300print/index.html
 Take an input file destined for an Epson type  dot matrix printer and
 turn it into a an .fodt file which can be opened in LibreOfffice for printing
 or converting to a pdf.

 *
 */

#include "./Runprinter.h"

#define TABSZ 20
#define TABSTRSZ 132
#define NEWFILESZ 500000


// Simple message display.
static void DEBUG(char * msg)
{
    printf("%s", msg);
}

void eps_convert (uint8_t* Data, int dsize)
{
    char filenm[FILENMSZ];
    FILE *fid;
    char tabstr[TABSTRSZ];
    int tabstrsize;
    char timestr[TABSTRSZ];
    int timestrsize;
    int fptr, j;
    char newdata[NEWFILESZ];
    int newptr;
    char newtabdata[NEWFILESZ];
    int newtabptr;
    int tabid;
    time_t timer;
    struct tm *timestruct;
    int tabid_i;
    int prevdatanull;
    int nullcounter;
    int onelinedoublewidth;
    int condensed,doublewidth;



    fptr=0;
    newptr=0;
    tabid=0;
    newtabptr=0;
    prevdatanull=0;
    nullcounter=0;
    onelinedoublewidth=0;
    condensed=0;
    doublewidth=0;


    //Make sure to skip initial garbage (search an ESC character to start with)
    for (j=0; j<8; j++)
    {
      if (Data[j]==27)
      {
        fptr=j;
        break;
      }
    }
    //printf("dsize=%i\n",dsize);fflush(stdout);
    for (;;)
    {
        if (fptr==dsize) break;
        if (nullcounter==4) break;
        switch(Data[fptr])
        {
/*            case 179:                  //Table geometry
                newdata[newptr]=124;
                newptr++;
                break;
*/
            case 9:                             //Horizontal tab
                strcpy(&(newdata[newptr]),"<text:tab/>");
                newptr=newptr+11;
                break;
            case 10:                            //Line Feed
                if (onelinedoublewidth==1)
                {
                  sprintf(&(newdata[newptr]),"</text:span></text:p>\n   <text:p text:style-name=\"P%i\">",tabid+1);
                  newptr=newptr+54;
                  onelinedoublewidth=0;
                }
                else
                {
                  sprintf(&(newdata[newptr]),"</text:p>\n   <text:p text:style-name=\"P%i\">",tabid+1);
                  newptr=newptr+42;
                }
                break;
            case 14:                            //Select double width for one line
                strcpy(&(newdata[newptr]),"<text:span text:style-name=\"T1\">");
                newptr=newptr+32;
                onelinedoublewidth=1;
                break;
            case 15:                            //Select condensed width
                strcpy(&(newdata[newptr]),"<text:span text:style-name=\"T2\">");
                newptr=newptr+32;
                condensed=1;
                break;
            case 18:                            //Cancel condensed width
                if (condensed==1)
                {
                  condensed=0;
                  strcpy(&(newdata[newptr]),"</text:span>");
                  newptr=newptr+12;
                }
                break;
            case 20:                            //Cancel one line double width mode
                strcpy(&(newdata[newptr]),"</text:span>");
                newptr=newptr+12;
                onelinedoublewidth=0;
                break;
            case 24:                            //CAN
                break;
            case 27:
                fptr++;
                switch(Data[fptr])
                {
                    case 14:                            //Select double width for one line
                        strcpy(&(newdata[newptr]),"<text:span text:style-name=\"T1\">");
                        newptr=newptr+32;
                        onelinedoublewidth=1;
                        break;
                    case 15:                            //Select condensed width
                        strcpy(&(newdata[newptr]),"<text:span text:style-name=\"T2\">");
                        newptr=newptr+32;
                        break;
                    case 50:                    //Select 6 lines per inch
                    case 56:                    //Disable paper out sensor
                    case 60:                    //Select unidirectional mode for one line
                    case 70:                    //Cancel emphasized mode
                    case 72:                    //Cancel double strike mode
                    case 79:                    //Cancel skip over perforation
                    case 84:                    //Cancel superscript/subscript
                        break;
                    case 45:                    //Cancel underlining
                    case 85:                    //Cancel unidirectional mode
                    case 87:                    //Cancel double width mode
                        fptr++;
                        switch(Data[fptr])
                        {
                            case 48:            //Cancel double width mode
                                if (doublewidth==1)
                                {
                                  doublewidth=0;
                                  strcpy(&(newdata[newptr]),"</text:span>");
                                  newptr=newptr+12;
                                }
                                break;
                        }
                        break;
                    case 83:                    //Select subscript
                        fptr++;
                        switch(Data[fptr])
                        {
                            case 49:
                                break;
                        }
                        break;
                    case 68:                    //Tab definition
                        fptr++;
                        tabstrsize=sprintf(tabstr,"  <style:style style:name=\"P%i\" style:family=\"paragraph\" style:parent-style-name=\"Standard\">\n",tabid+2);
                        strcpy(&(newtabdata[newtabptr]),tabstr);
                        newtabptr=newtabptr+tabstrsize;
                        tabstrsize=sprintf(tabstr,"   <style:paragraph-properties>\n");
                        strcpy(&(newtabdata[newtabptr]),tabstr);
                        newtabptr=newtabptr+tabstrsize;
                        tabstrsize=sprintf(tabstr,"    <style:tab-stops>\n");
                        strcpy(&(newtabdata[newtabptr]),tabstr);
                        newtabptr=newtabptr+tabstrsize;
                        while(Data[fptr]!=0)
                        {
                            tabstrsize=sprintf(tabstr,"     <style:tab-stop style:position=\"%1.1fpt\"/>\n",Data[fptr]*5.4);
                            strcpy(&(newtabdata[newtabptr]),tabstr);
                            newtabptr=newtabptr+tabstrsize;
                            fptr++;
                        }
                        tabstrsize=sprintf(tabstr,"    </style:tab-stops>\n");
                        strcpy(&(newtabdata[newtabptr]),tabstr);
                        newtabptr=newtabptr+tabstrsize;
                        tabstrsize=sprintf(tabstr,"   </style:paragraph-properties>\n");
                        strcpy(&(newtabdata[newtabptr]),tabstr);
                        newtabptr=newtabptr+tabstrsize;
                        tabstrsize=sprintf(tabstr,"   <style:text-properties style:font-name=\"Liberation Mono\" />\n");
                        strcpy(&(newtabdata[newtabptr]),tabstr);
                        newtabptr=newtabptr+tabstrsize;
                        tabstrsize=sprintf(tabstr,"  </style:style>\n");
                        strcpy(&(newtabdata[newtabptr]),tabstr);
                        newtabptr=newtabptr+tabstrsize;
                        tabid++;
                        sprintf(&(newdata[newptr]),"</text:p><text:p text:style-name=\"P%i\">",tabid+1);
                        newptr=newptr+38;
                        break;
                }
                break;
// Special text
            case 39:                             //Apostrophe
                strcpy(&(newdata[newptr]),"&apos;");
                newptr=newptr+6;
                break;
            case 34:        // Double quote
                strcpy(&(newdata[newptr]),"&quot;");
                newptr=newptr+6;
                break;
            case 60:
                strcpy(&(newdata[newptr]),"&lt;");
                newptr=newptr+4;
                break;
            case 62:
                strcpy(&(newdata[newptr]),"&gt;");
                newptr=newptr+4;
                break;
            case 218:                            //Left top corner
                newdata[newptr]=226;
                newptr=newptr+1;
                newdata[newptr]=148;
                newptr=newptr+1;
                newdata[newptr]=140;
                newptr=newptr+1;
                break;
            case 196:                            //Horizontal line
                newdata[newptr]=226;
                newptr=newptr+1;
                newdata[newptr]=148;
                newptr=newptr+1;
                newdata[newptr]=128;
                newptr=newptr+1;
                break;
            case 191:                            //Right top corner
                newdata[newptr]=226;
                newptr=newptr+1;
                newdata[newptr]=148;
                newptr=newptr+1;
                newdata[newptr]=144;
                newptr=newptr+1;
                break;
            case 179:                            //Vertical line
                newdata[newptr]=226;
                newptr=newptr+1;
                newdata[newptr]=148;
                newptr=newptr+1;
                newdata[newptr]=130;
                newptr=newptr+1;
                break;
            case 192:                            //Left bottom corner
                newdata[newptr]=226;
                newptr=newptr+1;
                newdata[newptr]=148;
                newptr=newptr+1;
                newdata[newptr]=148;
                newptr=newptr+1;
                break;
            case 217:                            //Right bottom corner
                newdata[newptr]=226;
                newptr=newptr+1;
                newdata[newptr]=148;
                newptr=newptr+1;
                newdata[newptr]=152;
                newptr=newptr+1;
                break;
            case 248:                            //Degrees
                newdata[newptr]=194;
                newptr=newptr+1;
                newdata[newptr]=176;
                newptr=newptr+1;
                break;
            case 130:                            // é
                newdata[newptr]=195;
                newptr=newptr+1;
                newdata[newptr]=169;
                newptr=newptr+1;
                break;
// Default text
            default:
                {
                    if (Data[fptr]>125)         //Text
                    {
                    }
                    else if (Data[fptr]>32)         //Text
                    {
                        newdata[newptr]=Data[fptr];
                        printf("%c", Data[fptr]);
                        newptr++;
                    }
                    else if (Data[fptr]==32)         //Text      Space
                    {
                        strcpy(&(newdata[newptr]),"<text:s/>");
                        newptr=newptr+9;
                    }
/*                    else if (Data[fptr]==0)         //Text
                    {
                        newdata[newptr]=124;        // |
                        newptr++;
                    }
*/

                }

        }

        if (Data[fptr]==0)
        {
          if (prevdatanull==1)
          {
            nullcounter++;
          }
          prevdatanull=1;
        }
        else
        {
          prevdatanull=0;
          nullcounter=0;
        }
        fptr++;

    }
    printf("\n");
    printf("%s\n",newdata);

    printf("%i,%i\n",Data[fptr-1],Data[fptr]);fflush(stdout);

    for (;;)
    {
        if (Data[fptr-1]==10)
        {
            fptr--;
            //printf("%i,%i\n",Data[fptr-1],Data[fptr]);fflush(stdout);
            newptr=newptr-42;
            //printf("%i\n",newptr);fflush(stdout);
        }
        else
        {
            break;
        }
    }

// add vogels
/*
    strcpy(&(newdata[newptr]),"</text:p>\n   <text:p text:style-name=\"P1\">");
    newptr=newptr+42;
    strcpy(&(newdata[newptr]),"</text:p>\n   <text:p text:style-name=\"P1\">");
    newptr=newptr+42;
    strcpy(&(newdata[newptr]),"</text:p>\n   <text:p text:style-name=\"P1\">");
    newptr=newptr+42;
    strcpy(&(newdata[newptr]),"<text:tab/><text:tab/>Autobedrijf Vogels Gemert");
    newptr=newptr+47;
    strcpy(&(newdata[newptr]),"</text:p>\n   <text:p text:style-name=\"P1\">");
    newptr=newptr+42;
    strcpy(&(newdata[newptr]),"<text:tab/><text:tab/>");
    newptr=newptr+22;
    time(&timer);
    timestruct=localtime(&timer);
    timestrsize=sprintf(timestr,"Date: %04i-%02i-%02i, time: %02i:%02i:%02i",
            timestruct->tm_year+1900,
            timestruct->tm_mon+1,
            timestruct->tm_mday,
            timestruct->tm_hour,
            timestruct->tm_min,
            timestruct->tm_sec);
    strcpy(&(newdata[newptr]), timestr);
    newptr=newptr+timestrsize;

*/
    strcpy(filenm,"tempres1.txt");
    fid=fopen(filenm,"w");
    dsize=fwrite(newtabdata,1,newtabptr,fid);
    fclose(fid);

    strcpy(filenm,"tempres2.txt");
    fid=fopen(filenm,"w");
    dsize=fwrite(newdata,1,newptr,fid);
    fclose(fid);



    system("cat part1.prn tempres1.txt part2.prn tempres2.txt part3.prn > printfile.fodt");

//STRACE LOWRITER
//system("/usr/bin/strace -o /tmp/strace-f.log -f /usr/bin/lowriter --headless -p printfile.fodt > lowriter.log 2> lowriter.err");
    //system("HOME=/root USERNAME=root USER=root LOGNAME=root /usr/bin/lowriter --headless -p /tmp/printfile.fodt > /tmp/lowriter.log 2> /tmp/lowriter.err");
    return;
}

/******************************************************************************************

******************************************************************************************/
int main()
{

    uint8_t *data;
    uint16_t count = 0;
    char *filenm = "cutecom.log";
    FILE *fid;
    uint32_t file_len;

    printf("Reading file: %s\n", filenm);
    fid = fopen(filenm, "rb");
    fseek(fid, 0, SEEK_END);
    file_len = ftell(fid);
    rewind(fid);
    printf("Size of file = %d bytes\n", file_len);
    data = (uint8_t*)malloc(file_len+1 * sizeof(uint8_t));
    count = fread(data, sizeof(uint8_t), file_len,  fid);
    printf("Size of data read = %d bytes\n", count);
    fclose(fid);
    for(uint16_t i = 0; i < count; i++)
    {
        printf("%x", data[i]);
    }
    printf("\n");
    eps_convert ("", 0);
    eps_convert (data, count);

    fid = NULL;
    free(data);

}
