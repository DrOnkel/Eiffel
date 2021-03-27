// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DIVIDER  100

#include "LedControl.h"

int ii,jj;

 int  Minutes, Hours;
unsigned long MinTimer;
// pin 12 is connected to the DataIn 
// pin 11 is connected to the CLK 
// pin 10 is connected to LOAD 
byte NofTextes=1;

#define VOLUME  31
 
LedControl lc = LedControl(12, 11, 10, 1);

byte MuteCount;
int MinTime;

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS     72

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS+10, PIN, NEO_GRB + NEO_KHZ800);
byte iRL;
byte LightMode;

int delayval = 10,SCounter,tTurn; // delay for half a second
void _test(void);


  void PlayText(byte NofSound);
void PlayMusic(byte NofSound);


void ShowDisplay()
{

pinMode(3,INPUT_PULLUP);

  //N2Show -  value to show

  lc.clearDisplay(0);
  lc.setDigit(0, 1, (Minutes) / 10, false);
  lc.setDigit(0, 0, (Minutes) % 10, false);
  //lc.setDigit(0, 5, (NofCamera+1) / 10, false);
  lc.setDigit(0, 3, (Hours) % 10, false);

  
    lc.setChar(0, 5, ' ', false);
  lc.setChar(0, 6, ' ', false);
    lc.setChar(0, 7, ' ', false);
 lc.setChar(0, 2, ' ', false);

  // lc.setDigit(0,3,i,false);
  lc.setDigit(0, 4, Hours / 10, false);
  //lc.setDigit(0, 1, (N2Show / 10) % 10, false);
  //lc.setDigit(0, 0, N2Show % 10, false);

Serial.print("  h  ");

}














void setup() {

  pinMode(4, INPUT_PULLUP);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
Serial.begin(9600);
Serial.print("Hello it is Eiffel011 Light  Clock  MP3");
  _test();


  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);
delay(1000);


delayMicroseconds(10);
Serial.write(0x7E);
Serial.write(0xFF);
Serial.write(0x06);
Serial.write(0x06);
Serial.write(0x01);
Serial.write(0x00);
Serial.write(VOLUME);
Serial.write(0xFE);
Serial.write(0xF4-VOLUME);

Serial.write(0xEF);
Serial.end();

  ShowDisplay() ;
  
}

void loop() {
switch(LightMode)
{
 

case '0':
for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(10,10,10));
break;
case 'A':
for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(63,0,0));
break;


case 'B':
for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(0,63,0));
break;

case 'C':
for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(0,0,63));
break;

case 'D':
for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(63,63,63));
break;

case 'E':
 
pixels.setPixelColor(iRL++ , pixels.Color(0, 0,0));

iRL =iRL %NUMPIXELS;
pixels.setPixelColor(iRL , pixels.Color(0, 0,63));
Serial.println("iRL=");
Serial.println(iRL);
break;








}
// if(digitalRead(4) == HIGH)
   pixels.show(); 

delay(10);
// Serial.println(LightMode);

if(Serial.available())  
{
   byte tSR =Serial.read();
   if (tSR != 10)
  LightMode = tSR;
Serial.write(LightMode);
SCounter=0;
}


if(millis()-MinTimer >200)//1000

{
MinTimer=millis();
if((Minutes%20) ==0)
{
if(digitalRead(4) == HIGH)
 PlayMusic(++NofTextes);


}
 if (Minutes++>58)

{
Minutes=0;
if(Hours++>22)
Hours=0;

 
  
}
 
  // if(digitalRead(4) == HIGH)
  ShowDisplay() ;
Serial.println(Hours*100+Minutes);
MinTime=(Hours*60+Minutes)%DIVIDER;


  
}

 

 if (  MinTime<5                  )
 {
LightMode=0;

for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(250,2,10));
  
 }



 else if ( MinTime<10)                  
 {
LightMode=0;

for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(10,250,10));
  
 }



  else if ( MinTime<15                   )
 {
LightMode=0;

for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(15,15,250));
  
 
 }


else  if (   MinTime<20        )
 {
LightMode=0;

if (++jj >NUMPIXELS)
jj=0;

 pixels.setPixelColor((jj-1)%NUMPIXELS, pixels.Color(20,15,14));
pixels.setPixelColor((jj)%NUMPIXELS, pixels.Color(250,15,14));
  
 
 }
 
 else  if (   MinTime<25        )
 {
LightMode=0;

if (++jj >NUMPIXELS)
jj=0;

 pixels.setPixelColor((jj-1)%NUMPIXELS, pixels.Color(70,15,114));
pixels.setPixelColor((jj)%NUMPIXELS, pixels.Color(20,250,14));
pixels.setPixelColor((jj+1)%NUMPIXELS, pixels.Color(20,250,14));  
 pixels.setPixelColor((jj+2)%NUMPIXELS, pixels.Color(20,250,14));  
 }
 else  if (   MinTime<30        )
 {
LightMode=0;

if (++jj >250)
jj=0;

// pixels.setPixelColor((jj-1)%NUMPIXELS, pixels.Color(70,15,114));
pixels.setPixelColor((jj)%NUMPIXELS, pixels.Color(20,jj,14));
pixels.setPixelColor((jj+1)%NUMPIXELS, pixels.Color(20,250,jj));  
 pixels.setPixelColor((jj+2)%NUMPIXELS, pixels.Color(20,250,jj));  
 }
 else  if (   MinTime<250        )
 {
LightMode=0;

if (++jj >250)
jj=0;
for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(20,jj,255-jj));
  
 }


 else  if (  MinTime<50       )
 {
LightMode=0;

for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(20,250,20));
  
 
 }
 else  if (  MinTime<60       )
 {
LightMode=0;

for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(20,10,250));
  
 
 }

 else  if (  MinTime<70       )
 {
LightMode=0;

for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(250,10,20));
  
 
 }

 else  if (  MinTime<80       )
 {
LightMode=0;

for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(20,250,20));
  
 
 }
 else  if (  MinTime<90       )
 {
LightMode=0;

for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(20,10,250));
  
 
 }
 else   if (  MinTime<DIVIDER      )
 {
LightMode=0;

for(byte j=0;j<NUMPIXELS;j++)
pixels.setPixelColor(j, pixels.Color(250,250,250));
  
 
 }
if (MinTime==DIVIDER-2)
_test();

   
}


void _test(void)
{
// For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255,0 ,0)); // Moderately bright green color.
    if(i>0)
     pixels.setPixelColor(i-1, pixels.Color(5,0 ,0)); // Moderately bright green color.
     

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }

    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0 ,255)); // Moderately bright green color.
    if(i>0)
     pixels.setPixelColor(i-1, pixels.Color(0,0 ,5)); // Moderately bright green color.
     

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,255 ,0)); // Moderately bright green color.
    if(i>0)
     pixels.setPixelColor(i-1, pixels.Color(0,5 ,0)); // Moderately bright green color.
     

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    
     pixels.setPixelColor(i, pixels.Color(5,5 ,5)); // Moderately bright green color.
     

   

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
 pixels.show(); // This sends the updated pixel color to the hardware.
  
  }




  void PlayText(byte NofSound)
{
  digitalWrite(10, LOW);
  delay(1);
  
Serial.begin(9600);
Serial.write( 0x7E);
Serial.write( 0xFF);
Serial.write( 0x06);
Serial.write( 0x03);
Serial.write( 0x00);
Serial.write( 0x00);
Serial.write( NofSound);
Serial.write( 0xFE );
Serial.write( 0xF8-NofSound);
Serial.write( 0xEF);
Serial.println("");
Serial.print("NofS= ");
Serial.println(NofSound);

delay(12);
//return;
 Serial.end();
//DDRD &= ~0x02;
//if(NofSound !=96)
//CountForUS=millis();
//CountFromUS=CountForUS;
MuteCount=0;


} 



void PlayMusic(byte NofSound)
{
  digitalWrite(10, LOW);
  delay(1);
  
Serial.begin(9600);
Serial.write( 0x7E);
Serial.write( 0xFF);
Serial.write( 0x06);
Serial.write( 0x03);
Serial.write( 0x00);
Serial.write( 0x00);
Serial.write( NofSound+1);
Serial.write( 0xFE );
Serial.write( byte(0xF8-NofSound-1));
Serial.write( 0xEF);
Serial.println("");
Serial.print("NofS= ");

Serial.print(NofSound);

 





delay(12);
//return;
 Serial.end();
//DDRD &= ~0x02;
//if(NofSound !=96)
//CountForUS=millis();
//CountFromUS=CountForUS;
MuteCount=0;
delay(100);

} 
