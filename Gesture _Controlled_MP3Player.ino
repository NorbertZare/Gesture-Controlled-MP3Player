#include <Wire.h>
#include "paj7620.h"
#include <LiquidCrystal.h>
#include <Servo.h>


Servo servov; // showing volume
Servo servon; // for showing Previous & Next

/* 
Notice: When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
        You also can adjust the reaction time according to the actual circumstance.
*/
#define GES_REACTION_TIME		500				// You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME			800				// When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME			1000



const int rs = 0, en = 1, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int v=120;
int i;
int p=0;

    const int up = 8;    //for volume up button
    const int down = 9;  //for volume down button
    const int next = 10;  //for Next button
    const int pre = 11;   //for Previous button
    const int pp = 12;    //for Pause/Play button


void setup()
{
	uint8_t error = 0;

servov.attach(6);
servon.attach(7);

lcd.begin(16, 2);

lcd.clear();
lcd.print(" Gesture Control");
lcd.setCursor(0, 1);
lcd.print(" *  MP3 Player *");

    pinMode(up, OUTPUT);
    pinMode(down, OUTPUT);
    pinMode(next, OUTPUT);
    pinMode(pre, OUTPUT);
    pinMode(pp, OUTPUT);
    
    digitalWrite(up, HIGH);
    digitalWrite(down, HIGH);
    digitalWrite(next, HIGH);
    digitalWrite(pre, HIGH);
    digitalWrite(pp, HIGH);





	error = paj7620Init();			// initialize Paj7620 registers

  servov.write(v);
}

void loop()
{


lcd.clear();
lcd.print(" Gesture Control");
lcd.setCursor(0, 1);
lcd.print(" *  MP3 Player *");





  
	uint8_t data = 0, data1 = 0, error;
	
	error = paj7620ReadReg(0x43, 1, &data);				// Read Bank_0_Reg_0x43/0x44 for gesture result.
	if (!error) 
	{
		switch (data) 									// When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
		{
			case GES_RIGHT_FLAG:
				delay(GES_ENTRY_TIME);
				paj7620ReadReg(0x43, 1, &data);
				if(data == GES_FORWARD_FLAG) 
				{
           lcd.clear();
           if (p==0)
           {
           lcd.print(" Pause ||");
           p=1;
           }
           else if (p==1)
           {
           lcd.print(" Play >");
           p=0;
           }
          digitalWrite(pp, LOW);
          delay (500);
          digitalWrite(pp, HIGH);
          delay (500);
          
          
					delay(GES_QUIT_TIME);
      
				}
				else if(data == GES_BACKWARD_FLAG) 
				{
					delay(GES_QUIT_TIME);
				}
				else
				{

lcd.clear();
lcd.print(" Next >|");
          digitalWrite(next, LOW);
          delay (100);
          digitalWrite(next, HIGH);
          servon.write(1);
          delay(1000);
          servon.write(90);
				}          
				break;
			case GES_LEFT_FLAG: 
				delay(GES_ENTRY_TIME);
				paj7620ReadReg(0x43, 1, &data);
				if(data == GES_FORWARD_FLAG) 
				{

           lcd.clear();
           if (p==0)
           {
           lcd.print(" Pause ||");
           p=1;
           }
           else if (p==1)
           {
           lcd.print(" Play >");
           p=0;
           }
          digitalWrite(pp, LOW);
          delay (500);
          digitalWrite(pp, HIGH);
          delay (500);
					delay(GES_QUIT_TIME);
				}
				else if(data == GES_BACKWARD_FLAG) 
				{

					delay(GES_QUIT_TIME);
				}
				else
				{
lcd.clear();
lcd.print(" Previous |<");
          digitalWrite(pre, LOW);
          delay (100);
          digitalWrite(pre, HIGH);
          servon.write(179);
          delay(1000);
          servon.write(90);
          
				}          
				break;
			case GES_UP_FLAG:
				delay(GES_ENTRY_TIME);
				paj7620ReadReg(0x43, 1, &data);
				if(data == GES_FORWARD_FLAG) 
				{

           lcd.clear();
           if (p==0)
           {
           lcd.print(" Pause ||");
           p=1;
           }
          else if (p==1)
           {
           lcd.print(" Play >");
           p=0;
           }
          digitalWrite(pp, LOW);
          delay (500);
          digitalWrite(pp, HIGH);
          delay (500);
					delay(GES_QUIT_TIME);
				}
				else if(data == GES_BACKWARD_FLAG) 
				{
					delay(GES_QUIT_TIME);
				}
				else
				{
				}          
				break;
			case GES_DOWN_FLAG:
				delay(GES_ENTRY_TIME);
				paj7620ReadReg(0x43, 1, &data);
				if(data == GES_FORWARD_FLAG) 
				{

           lcd.clear();
           if (p==0)
           {
           lcd.print(" Pause ||");
           p=1;
           }
          else if (p==1)
           {
           lcd.print(" Play >");
           p=0;
           }
          digitalWrite(pp, LOW);
          delay (500);
          digitalWrite(pp, HIGH);
          delay (500);
					delay(GES_QUIT_TIME);
				}
				else if(data == GES_BACKWARD_FLAG) 
				{
					delay(GES_QUIT_TIME);
				}
				else
				{
				}          
				break;
			case GES_FORWARD_FLAG:

           lcd.clear();
           if (p==0)
           {
           lcd.print(" Pause ||");
           p=1;
           }
           else if (p==1)
           {
           lcd.print(" Play >");
           p=0;
           }
          digitalWrite(pp, LOW);
          delay (500);
          digitalWrite(pp, HIGH);
          delay (500);
				delay(GES_QUIT_TIME);
				break;
			case GES_BACKWARD_FLAG:		
				delay(GES_QUIT_TIME);
				break;
			case GES_CLOCKWISE_FLAG:

lcd.clear();
lcd.print(" volume up +");

 for (i = 1 ; i<=10 ; i++ )
    {
      
       v=v-1;
              if(v<0)
       {
        v=0;
       }
      servov.write(v);
      digitalWrite(up, LOW);
      delay(100);
      v=v-1;
      servov.write(v);
      delay(100);
      v=v-1;
      servov.write(v);
      delay(100);
      v=v-1;
      servov.write(v);
      delay(100);
      v=v-1;
      servov.write(v);
      digitalWrite(up, HIGH);
      delay(100);
    }
				break;
			case GES_COUNT_CLOCKWISE_FLAG:

lcd.clear();
lcd.print(" volume down -");

 for (i = 1 ; i<=10 ; i++ )
    {
      
       v=v+1;
              if(v>180)
       {
        v=180;
       }
      servov.write(v);
      digitalWrite(down, LOW);
      delay(100);
      v=v+1;
      servov.write(v);
      delay(100);
      v=v+1;
      servov.write(v);
      delay(100);
      v=v+1;
      servov.write(v);
      delay(100);
      v=v+1;
      servov.write(v);
      digitalWrite(down, HIGH);
      delay(100);
    }
				break;  
			default:
				paj7620ReadReg(0x44, 1, &data1);
				if (data1 == GES_WAVE_FLAG) 
				{
				}
				break;
		}
	}
	delay(100);

}
