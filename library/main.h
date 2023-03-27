#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=4000000)
#include <DS1307.h>
#include <lcd.h>

#define     MENU     input(PIN_E0)
#define     TANG     input(PIN_E1)
#define     GIAM     input(PIN_E2)


