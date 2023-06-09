#include <16F877A.h>
#device ADC=10

#FUSES NOWDT                    
#FUSES NOBROWNOUT               
#FUSES NOLVP                    

#use delay(crystal=4000000)
#include <DS1307.h>
#include <lcd.h>

#define     MENU     input(PIN_D5)
#define     TANG     input(PIN_D2)
#define     GIAM     input(PIN_D3)
#define     CAIDAT   input(PIN_D4)

float LM35,AS,RL,V, dosang, setas=100;
int i, nhiet,nhieton=27, nhietoff=20, chedo,next;
   unsigned char* Time;
   unsigned char* Date;
   signed char Gio,Phut,Giay;
   signed char Ngay,Thang,Nam,Thu;
   const char ThuNgay[7][6]={"CN","T2","T3","T4","T5","T6","T7"};
void nhietdo();
void set_time();
void cai_dat();
void anhsang();
void ScanDelay10ms(unsigned int16 Dem);
void main()
{
   SETUP_ADC(ADC_CLOCK_DIV_32);
   SETUP_ADC_PORTS(ALL_ANALOG);
   lcd_init();
   lcd_gotoxy(3,1);
   printf(lcd_putc,"CAO TRONG KY");
   lcd_gotoxy(5,2);
   printf(lcd_putc,"41801155");
   delay_ms(2000);
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
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02u:%02u:%02u",Gio,Phut,Giay);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%02s-%02u-%02u",ThuNgay[Thu-1],Ngay,Thang);  
      anhsang();
      nhietdo();
      cai_dat();
      lcd_gotoxy(10,2);
      printf(lcd_putc,"%3.0f",dosang);
      lcd_gotoxy(13,2);
      printf(lcd_putc,"LUX");
      if(nhiet>=nhieton)
      {
         output_high(PIN_E0);
      }
      else if(nhiet<=nhietoff)
      {
         output_low(PIN_E0);
      }
      lcd_gotoxy(10,1);
      printf(lcd_putc,"%d",nhiet);
      lcd_putc(223);
      lcd_putc("C");
      set_time();
      ScanDelay10ms(20);
    }  
}
void set_time()
{
next=0;
          if(CAIDAT==0)
      {
         while(CAIDAT==0);
        next=next+1;
         if(next>3)
         {
           next=0;
         }
         lcd_putc('\f');
      }
     while(next==1)
      {
      lcd_gotoxy(3,1);
      printf(lcd_putc,"%02u:%02u:%02u",Gio,Phut,Giay);
      lcd_gotoxy(3,1);
      printf(lcd_putc,"__");
      lcd_gotoxy(3,2);
      printf(lcd_putc,"%02s-%02u-%02u",ThuNgay[Thu-1],Ngay,Thang); 
         if(TANG==0)
         {
            while(TANG==0);
            gio = gio+1;
            if (gio>23)
            gio=0;
         }
         else if(GIAM==0)
         {
            while(GIAM==0);
            gio = gio-1;
            if(gio<0)
            gio=23;
         }
         else if(CAIDAT==0)
         {
            while(CAIDAT==0);
           next =next+1;
            if(Next>6)
            {
              next =0;
            }
         }
     }
     while(next==2)
      {
      lcd_gotoxy(3,1);
      printf(lcd_putc,"%02u:%02u:%02u",Gio,Phut,Giay);
      lcd_gotoxy(6,1);
      printf(lcd_putc,"__");
      lcd_gotoxy(3,2);
      printf(lcd_putc,"%02s-%02u-%02u",ThuNgay[Thu-1],Ngay,Thang); 
         if(TANG==0)
         {
            while(TANG==0);
            phut = phut+1;
            if (phut>59)
            phut=0;
         }
         else if(GIAM==0)
         {
            while(GIAM==0);
            phut = phut-1;
            if (phut<0)
            phut=59;
         }
         else if(CAIDAT==0)
         {
            while(CAIDAT==0);
           next =next+1;
            if(Next>6)
            {
              next =0;
            }
         }
      }
      while(next==3)
      {
      lcd_gotoxy(3,1);
      printf(lcd_putc,"%02u:%02u:%02u",Gio,Phut,Giay);
      lcd_gotoxy(9,1);
      printf(lcd_putc,"__");
      lcd_gotoxy(3,2);
      printf(lcd_putc,"%02s-%02u-%02u",ThuNgay[Thu-1],Ngay,Thang); 
         if(TANG==0)
         {
            while(TANG==0);
            giay = giay+1;
            if (giay>59)
            giay=0;
         }
         else if(GIAM==0)
         {
            while(GIAM==0);
            giay = giay-1;
            if (giay<0)
            giay=59;
         }
          else if(CAIDAT==0)
         {
            while(CAIDAT==0);
           next =next+1;
            if(Next>6)
            {
              next =0;
            }
            Set_DS1307_RTC_Time(Gio,Phut,Giay);
         }
     }
     while(next==4)
      {
      lcd_gotoxy(3,1);
      printf(lcd_putc,"%02u:%02u:%02u",Gio,Phut,Giay);
      lcd_gotoxy(3,2);
      printf(lcd_putc,"%02s-%02u-%02u",ThuNgay[Thu-1],Ngay,Thang); 
      lcd_gotoxy(3,2);
      printf(lcd_putc,"__");
         if(TANG==0)
         {
            while(TANG==0);
            thu = thu+1;
            if (thu>7)
            thu=1;
         }
         else if(GIAM==0)
         {
            while(GIAM==0);
            thu = thu-1;
            if(thu<1)
            thu=7;
         }
         else if(CAIDAT==0)
         {
            while(CAIDAT==0);
           next =next+1;
            if(Next>6)
            {
              next =0;
            }
         }
     }
     while(next==5)
      {
      lcd_gotoxy(3,1);
      printf(lcd_putc,"%02u:%02u:%02u",Gio,Phut,Giay);
      lcd_gotoxy(3,2);
      printf(lcd_putc,"%02s-%02u-%02u",ThuNgay[Thu-1],Ngay,Thang); 
      lcd_gotoxy(6,2);
      printf(lcd_putc,"__");
         if(TANG==0)
         {
            while(TANG==0);
            ngay = ngay+1;
            if (ngay>31)
            ngay=1;
         }
         else if(GIAM==0)
         {
            while(GIAM==0);
            ngay = ngay-1;
            if (ngay<1)
            ngay=31;
         }
         else if(CAIDAT==0)
         {
            while(CAIDAT==0);
           next =next+1;
            if(Next>6)
            {
              next =0;
            }
         }
      }
      while(next==6)
      {
      lcd_gotoxy(3,1);
      printf(lcd_putc,"%02u:%02u:%02u",Gio,Giay,Giay);
      lcd_gotoxy(3,2);
      printf(lcd_putc,"%02s-%02u-%02u",ThuNgay[Thu-1],Ngay,Thang); 
      lcd_gotoxy(9,2);
      printf(lcd_putc,"__");
         if(TANG==0)
         {
            while(TANG==0);
            thang = thang+1;
            if (thang>12)
            thang=1;
         }
         else if(GIAM==0)
         {
            while(GIAM==0);
            thang = thang-1;
            if (thang<1)
            thang=12;
         }
          else if(CAIDAT==0)
         {
            while(CAIDAT==0);
           next =next+1;
            if(Next>6)
            {
              next =0;
            }
            Set_DS1307_RTC_Date(Ngay,Thang,Nam,Thu);
            lcd_putc('\f');
            lcd_gotoxy(5,1);
            printf(lcd_putc,"SETTIME");
            lcd_gotoxy(4,2);
            printf(lcd_putc,"COMPLETE");
            delay_ms(1000);
            lcd_putc('\f');
         }
     }
   }
void anhsang()
{
   SET_ADC_CHANNEL(1);
   AS=read_ADC();
   V=(AS*5)/1023;
   RL=(10*V)/(5-V);
   dosang=500/RL;
    if(dosang<=setas)
   {
         output_high(PIN_D1);
   }
   else if(dosang>setas)
   {
         output_low(PIN_D1);
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
}
void cai_dat()
{
      chedo=0;
          if(MENU==0)
      {
         while(MENU==0);
         chedo=chedo+1;
         if(chedo>3)
         {
            chedo=0;
         }
         lcd_putc('\f');
      }
     while(chedo==1)
      {
         lcd_gotoxy(3,1);
         printf(lcd_putc,"       ");
         lcd_gotoxy(3,1);
         printf(lcd_putc,"FAN ON :%d",nhieton);
         lcd_putc(223);
         lcd_putc("C");
         lcd_gotoxy(3,2);
         printf(lcd_putc,"FAN OFF:%d",nhietoff);
         lcd_putc(223);
         lcd_putc("C");
         if(TANG==0)
         {
            while(TANG==0);
            nhieton = nhieton+1;
         }
         else if(GIAM==0)
         {
            while(GIAM==0);
            nhieton = nhieton-1;
         }
         else if(MENU==0)
         {
            while(MENU==0);
            CheDo = CheDo+1;
            if(CheDo>3)
            {
               CheDo =0;
            }
         }
     }
     while(chedo==2)
{
         lcd_gotoxy(3,2);
         printf(lcd_putc,"       ");
         lcd_gotoxy(3,1);
         printf(lcd_putc,"FAN ON :%d",nhieton);
         lcd_putc(223);
         lcd_putc("C");
         lcd_gotoxy(3,2);
         printf(lcd_putc,"FAN OFF:%d",nhietoff);
         lcd_putc(223);
         lcd_putc("C");
      {
         if(TANG==0)
         {
            while(TANG==0);
            nhietoff = nhietoff+1;
         }
         else if(GIAM==0)
         {
            while(GIAM==0);
            nhietoff = nhietoff-1;
         }
          else if(MENU==0)
         {
            while(MENU==0);
            CheDo = CheDo+1;
            if(CheDo>3)
            {
               CheDo =0;
            }
            lcd_putc('\f');
         }
     }
   }
   if(MENU==0)
      {
         while(MENU==0);
         chedo=chedo+1;
         if(chedo>3)
         {
            chedo=0;
         }
         lcd_putc('\f');
      }
     while(chedo==3)
      {
         lcd_gotoxy(1,1);
         printf(lcd_putc,"D0 SANG BAT DEN:");
         lcd_gotoxy(4,2);
         printf(lcd_putc,"%3.0f LUX",setas);
         if(TANG==0)
         {
            while(TANG==0);
            setas = setas+5;
         }
         else if(GIAM==0)
         {
            while(GIAM==0);
            {
            setas = setas-5;
            }
         }
         else if(MENU==0)
         {
            while(MENU==0);
            CheDo = CheDo+1;
            if(CheDo>3)
            {
               CheDo =0;
            }
            lcd_putc('\f');
            lcd_gotoxy(5,1);
            printf(lcd_putc,"SETUP");
            lcd_gotoxy(4,2);
            printf(lcd_putc,"COMPLETE");
            delay_ms(1000);
            lcd_putc('\f');
         }
      }
}

void ScanDelay10ms(unsigned int16 Dem)
{
   while(Dem>1)
   {
      Dem--;
      delay_ms(10);
      if( CAIDAT==0 || MENU==0 || TANG==0 || GIAM==0)
      {
         return;
      }
   }
}
