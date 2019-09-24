#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#define RS PINB0
#define EN PINB2
void enable_pinini_degis(void);
void lcd_komut_yolla(uint8_t komut);
void lcd_basla(void);
void lcdHucreyeGit(unsigned int satir,unsigned int sutun);
void lcd_veri_yaz(unsigned char veri);


int main(void)
{

  DDRD=0xFF;
  DDRB=0xFF;
  PORTD=0x00;
  _delay_ms(50);
  PORTB &=~(1<<RS);//RS LOW
  PORTB &=~(1<<EN);//EN LOW

for(int i=0;i<2;i++)
{

   lcd_komut_yolla(0x03);
  _delay_ms(5);//4,1ms gerek
   
}

 lcd_komut_yolla(0x03);
_delay_us(150);
lcd_basla();
  
lcdHucreyeGit(1,1);
_delay_ms(1);//37 us diyor.
lcd_veri_yaz(0x45);
lcd_veri_yaz(0x46);
lcd_veri_yaz(0x47);
lcd_veri_yaz('T');
lcd_veri_yaz('T');

lcdHucreyeGit(2,1);
_delay_ms(1);//37 us diyor.

lcd_veri_yaz('T');
 
while(1);


}


  
void enable_pinini_degis()
{
  
  PORTB &=~(1<<EN);
  _delay_us(1);
  PORTB |=(1<<EN);
  _delay_us(1);
  PORTB &=~(1<<EN);
  _delay_us(100);

}
void lcd_komut_yolla(uint8_t komut)
{
  PORTD =komut;
  PORTB &=~(1<<RS);//RS LOW
  enable_pinini_degis();
  
  komut=komut<<4;

  PORTD=komut;
  PORTB &=~(1<<RS);//RS LOW
  enable_pinini_degis();

}
void lcd_basla()
{
  lcd_komut_yolla(0x02);
  _delay_ms(2);
  lcd_komut_yolla(0x28);
  _delay_ms(1);
  lcd_komut_yolla(0x0C);
  _delay_ms(1);
  lcd_komut_yolla(0x01);
  _delay_ms(1);
  lcd_komut_yolla(0x06);
  _delay_ms(1);

}
void lcdHucreyeGit(unsigned int satir,unsigned int sutun)
{
  if(satir==1)
  {
    sutun--;
    lcd_komut_yolla(0x80+sutun);
    
    
  }
  else if(satir==2)
  {
    sutun--;
    lcd_komut_yolla(0xC0+sutun);
    
  }
}

void lcd_veri_yaz(unsigned char veri)
{
  PORTB |=(1<<RS);//RS HIGH
  PORTD =veri;
  enable_pinini_degis();
  
  veri=veri<<4;

  PORTB |=(1<<RS);//RS HIGH
  PORTD=veri;
  enable_pinini_degis();
}
