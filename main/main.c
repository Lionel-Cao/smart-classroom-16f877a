#include <16F877A.h>
#device ADC=10

#FUSES NOWDT                    
#FUSES NOBROWNOUT               
#FUSES NOLVP                    

#use delay(crystal=1000000)
#include <DS1307.h>
#include <lcd.h>

#define     MENU     input(PIN_E0)
#define     TANG     input(PIN_E1)
#define     GIAM     input(PIN_E2)

float LM35,AS;
int i, nhiet;
void nhietdo();
void anhsang();
void main()
{
   unsigned char* Time;
   unsigned char* Date;
   signed char Gio,Phut,Giay;
   signed char Ngay,Thang,Thu;
   const char ThuNgay[7][6]={"CN","T2","T3","T4","T5","T6","T7"};
   SETUP_ADC(ADC_CLOCK_DIV_32);
   SETUP_ADC_PORTS(ALL_ANALOG);
   lcd_init();
   lcd_putc('\f');
   
   while(TRUE)
   {
      Time = Get_DS1307_RTC_Time();
      Gio = Time[2];
      Phut = Time[1];
      Giay = Time[0];
   
      Date = Get_DS1307_RTC_Date();
      Thu = Date[0];
      Ngay = Date[1];
      Thang = Date[2];
      delay_ms(50);
      anhsang();
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02u:%02u:%02u",Gio,Phut,Giay);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%02s-%02u-%02u",ThuNgay[Thu-1],Ngay,Thang);  
      nhietdo();
      lcd_gotoxy(10,1);
      printf(lcd_putc,"%d",nhiet);
      lcd_putc(223);
      lcd_putc("C");
      
      delay_ms(50);
   }
}
void nhietdo()
{
    SET_ADC_CHANNEL(0);
    LM35=0;
    for(i=0; i<=100; i++)
      {
         LM35 =LM35 + read_adc();
      }
    nhiet=LM35/100/2.046;
    if(nhiet>=27)
      {
         lcd_gotoxy(10,2);
         printf(lcd_putc,"FAN:ON ");
         output_high(PIN_E0);
      }
      else if(nhiet<=24)
      {
         lcd_gotoxy(10,2);
         printf(lcd_putc,"FAN:OFF");
         output_low(PIN_E0);
      }
}
void anhsang()
{
   SET_ADC_CHANNEL(1);
   AS=read_ADC();
   if(AS>930)
   {
      lcd_gotoxy(15,1);
         printf(lcd_putc,"0");
         output_high(PIN_E1);
   }
   else if(AS<=930)
   {
      lcd_gotoxy(15,1);
         printf(lcd_putc,"F");
         output_low(PIN_E1);
   }    
}
   
   
