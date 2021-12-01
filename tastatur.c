//
//  tastatur.c
//  Data_Teensy
//
//  Created by Ruedi Heimlicher on 01.12.2017.
//

#include "tastatur.h"

#define TASTATUR_KANAL  11

extern volatile uint8_t hoststatus;

extern volatile uint8_t Tastaturwert;
extern volatile uint16_t TastaturCount;
extern volatile uint8_t Menu_Ebene;
extern void manuellmessung_start(void);
extern void manuellmessung_stop(void);
/*
 */
//err_puthex(Tastenwert);

//         closeADC();

//uint8_t Taste=-1;
//      Tastenwert/=8;
//      Tastenwert*=3;
//      err_clr_line(1);
//      err_gotoxy(0,1);
//      err_puts("Taste \0");
//      err_putint(Taste);
//      delay_ms(200);


//err_puthex(Tastenwert);

//         closeADC();

//uint8_t Taste=-1;
//      Tastenwert/=8;
//      Tastenwert*=3;
//      err_clr_line(1);
//      err_gotoxy(0,1);
//      err_puts("Taste \0");
//      err_putint(Taste);
//      delay_ms(200);

uint8_t Tastenwahl(uint8_t Tastaturwert)
{
   if (Tastaturwert < TASTE1)
      return 1;
   if (Tastaturwert < TASTE2)
      return 2;
   if (Tastaturwert < TASTE3)
      return 3;
   if (Tastaturwert < TASTE4)
      return 4;
   if (Tastaturwert < TASTE5)
      return 5;
   if (Tastaturwert < TASTE6)
      return 6;
   if (Tastaturwert < TASTE7)
      return 7;
   if (Tastaturwert < TASTE8)
      return 8;
   if (Tastaturwert < TASTE9)
      return 9;
   if (Tastaturwert < TASTE_L)
      return 10;
   if (Tastaturwert < TASTE0)
      return 11; // entspricht 0
   if (Tastaturwert < TASTE_R)
      return 12;
   
   return -1;
}

uint8_t tastencode(uint8_t tastaturkanal)
{
   uint16_t Tastenwert=0;
   
   //uint8_t TastaturCount=0;
   
   uint8_t Taste=0;
   
   Tastenwert=(adc_read(tastaturkanal)>>2);

   //lcd_gotoxy(7,2);
   //lcd_putc('T');
   //lcd_putint(Tastenwert);

   if (Tastenwert>5) // ca Minimalwert der Matrix
   {
      //         wdt_reset();
      /*
       0: Wochenplaninit
       1: IOW 8* 2 Bytes auf Bus laden
       2: Menu der aktuellen Ebene nach oben
       3: IOW 2 Bytes vom Bus in Reg laden
       4: Auf aktueller Ebene nach rechts (Heizung: Vortag lesen und anzeigen)                           
       5: Ebene tiefer
       6: Auf aktueller Ebene nach links (Heizung: Folgetag lesen und anzeigen)                           
       7: 
       8: Menu der aktuellen Ebene nach unten
       9: DCF77 lesen
       
       12: Ebene höher
       */
      TastaturCount++;
      if (TastaturCount>=2)   //   Prellen abgelaufen
      {
         
         //err_clr_line(1);
         //err_gotoxy(0,1);
         //err_puts("ADC:\0");
         //err_putint(Tastenwert);
         
         Taste=Tastenwahl(Tastenwert);
         
         //lcd_gotoxy(12,2);
         //lcd_puts("T:\0");
         //err_gotoxy(14,1);
         //lcd_putint(Tastenwert);
         //lcd_putc(' ');
         //lcd_putint2(Taste);
         /*
          lcd_putint2(Taste);
          //delay_ms(1200);
          //err_clr_line(1);
          */
         TastaturCount=0;
         Tastenwert=0x00;
         //            uint8_t i=0;
         
         //         uint8_t inByte0=0;
         //         uint8_t inByte1=0;
         
         uint8_t inBytes[4]={};
         //         uint8_t pos=0;
         //         lcd_gotoxy(12,0);
         //         lcd_put_wochentag(DCF77buffer[5]);
         //         lcd_gotoxy(15,0);
         //         lcd_put_zeit(DCF77buffer[0],DCF77buffer[1]);
         
         //         Taste=0xff;
         
         
         //Taste=4;
         
         switch (Taste)
         {
            case 0://
            { 
               break;
               // Blinken auf C2
               
            }
               break;
               
               
            case 1:
            {
               //
            }
               break;
               
            case 2:                                 //   Menu vorwaertsschalten   
            {
               //lcd_cls();
               /*
                err_gotoxy(0,1);
                err_puts("M:\0");
                err_putint2(Menu_Ebene & 0xF0);
                err_gotoxy(10,1);
                err_puts("T:\0");
                err_putint2(Taste);
                //               delay_ms(1000);
                */
               switch (Menu_Ebene & 0xF0)               //   Bits 7-4, Menu_Ebene
               {
                  case 0x00:                        //   oberste Ebene, Raeume
                  {
                  }
                     break;
                     
                  case 0x10:                        // erste Unterebene, Thema
                  {
                  }
                     break;
                  case    0x20:                        // zweite Unterebene
                  {
                     
                  }break;
               }//switch Menu_Ebene
               
            }
               break;
               
            case 3:   //
            {
               
            }break;
               
            case 4:   // Vortag
            {
               
               //err_clr_line(0);
               //err_gotoxy(0,0);
               //err_puts("Taste 4\0");
               //delay_ms(50);
               //err_clr_line(0);
               
               
               switch (Menu_Ebene & 0xF0)//Bits 7-4   
               {
                  case 0x00:   //oberste Ebene
                  {
                     //err_clr_line(0);
                     //err_puts("E0\0");
                     
                  }break;
                     
                  case 0x10: // erste Ebene
                  {
                     
                     
                  }break;
                     
                  case 0x20: // zweite Ebene, Plan
                  {
                  }break;   //   case 0x20
                     
                     
               }//switch Menu_Ebene & 0xF0
               
            } break; // case Vortag
               
               
            case 5:                        // Ebene tiefer
            {
               lcd_gotoxy(19,3);
               lcd_putc('M');
               hoststatus |= (1<<MANUELL_OK);
               manuellmessung_start();
               
               
               
               //Taste=99;
               //lcd_clr_line(1);
               //lcd_gotoxy(0,1);
               //lcd_puts("Taste 5\0");
               //delay_ms(200);
               //lcd_clr_line(1);
               //err_gotoxy(3,0);
               //err_puthex(DCF77daten[5]);
               Menu_Ebene &= 0xF0;                     //   Bits 7 - 4 behalten, Bits 3-0 loeschen
               if ((Menu_Ebene & 0xF0)<0x20)
               {
                  switch (Menu_Ebene & 0xF0)
                  {
                     case 0x00: // erste Ebene, Thema
                     {
                        Menu_Ebene = 0x10;
                     }break;
                        
                     case 0x10:
                     {
                        Menu_Ebene = 0x20;
                     }break;
                        
                        
                        
                        
                  }//switch Menu_Ebene
               }
            }            break;
               
            case 6: // Folgetag
            {
               /*
                err_clr_line(1);
                err_gotoxy(0,1);
                err_puts("Taste 6\0");
                delay_ms(50);
                err_clr_line(1);
                */
               
               switch (Menu_Ebene & 0xF0)//Bits 7-4   
               {
                  case 0x00:   //oberste Ebene
                  {
                  }                  break;
                     
                  case 0x10: // erste Ebene
                  {
                     
                     
                  }break;
                     
                  case 0x20: // zweite Ebene, Plan
                  {
                     
                  }break;   // case 0x20
                     
               } // Menu_Ebene & 0xF0
               
            } break; // case Folgetag
               
               //case 7:
               
               //   break;
               
               
            case 8:                                    //Menu rueckwaertsschalten
            {
               //err_gotoxy(0,1);
               //err_puts("M:\0");
               //err_putint2(Menu_Ebene & 0xF0);
               //err_gotoxy(10,1);
               //err_puts("T:\0");
               //err_putint2(Taste);
               //delay_ms(1000);
               
               switch (Menu_Ebene & 0xF0)//Bits 7-4            oberste Ebene, Raeume
               {
                  case 0x00:
                  {
                  }
                     break;
                     
                  case 0x10:                           // erste Unterebene, Thema
                  {
                     
                  }
                     break;
                     
               }// switch Menu_Ebene
               
            }
               break;
               
               case 10:
            {
               hoststatus &= ~(1<<MANUELL_OK); 
               manuellmessung_stop();
               lcd_gotoxy(19,3);
               lcd_putc(' ');

            } break;
               
               
            case 12:// Ebene hoeher
            {
               //Taste=99;
               
               //lcd_clr_line(1);
               //lcd_gotoxy(0,1);
               //lcd_puts("Taste 12\0");
               //delay_ms(100);
               //lcd_clr_line(1);
               switch (Menu_Ebene & 0xF0)
               {
                  case 0x00:
                  {
                     
                  }break;
                     
                  case 0x10:
                  {
                     Menu_Ebene = 0x00;                     //Ebene 0
                     
                  }break;
                  case 0x20:
                  {
                     Menu_Ebene = 0x10;                     //   Ebene 1
                     Menu_Ebene &= 0xF0;                     //   Bits 7 - 4 behalten, Bits 3-0 loeschen
                     
                     
                  }break;
                     
                     
               }//switch MenuEbene
               
               
            }break;
               
               
         }//switch Taste
         
      }
      
   }
   return Taste;
}// tastencode
