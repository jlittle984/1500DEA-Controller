/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution

// To show the display buffer on the hardware.
   NOTE: You _must_ call display using [display.display();] after making any drawing commands
   to make them visible on the display hardware!
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FreeSansBold9pt7b.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

//Set Pushbutton variable:
// variables will change:

int buttonState = 0;         // variable for reading the pushbutton status
const int LED = 12;


void setup()   {  

///////////////////////////////////////////////////////////////////////
/////////initial boot screen setup
//////////////////////////////////////////////////////////////////////
  
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();

  // Set Font with Font library included above//
  display.setFont(&FreeSansBold9pt7b);
  
////////////////////////////////////////////////////////////////
/////////////////Address Digital Pins/////////////////////////
//////////////////////////////////////////////////////////////


//Relay Board 1 Outputs
pinMode(2, OUTPUT);
digitalWrite(2, HIGH);
pinMode(3, OUTPUT);
digitalWrite(3, HIGH);
pinMode(4, OUTPUT);
digitalWrite(4, HIGH);
pinMode(5, OUTPUT);
digitalWrite(5, HIGH);

//Relay Board 2 Outputs
pinMode(6, OUTPUT);
digitalWrite(6, HIGH);
pinMode(7, OUTPUT);
digitalWrite(7, HIGH);   
pinMode(8, OUTPUT);
digitalWrite(8, HIGH);
pinMode(9, OUTPUT);
digitalWrite(9, HIGH);


// initialize the pushbutton pin as an input:
pinMode(11,  INPUT_PULLUP);
digitalWrite(11, HIGH);
pinMode(12,  OUTPUT);
digitalWrite(12, LOW);

////////////////////////////////////////////////////////////////////////////
///////Intro Text/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(40,20);
  display.println("System");
   display.setCursor(30,40);
  display.println("Powerup");
  display.display();
  delay(3000);
  
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(40,20);
  display.println("Please");
  display.setCursor(30,40);
  display.println("Stand By");
  display.display();
  delay(3000);
    
  display.clearDisplay();
  display.display();
  

}

////////////////////////////////////////////////////////
////////LOOP AREA BEGIN
////////////////////////////////////////////////////////


void loop() {

// read the state of the pushbutton value:
  buttonState = digitalRead(11);

  // check if the pushbutton is pressed. If it is, the buttonState is LOW:
 
  if (buttonState == LOW) {
    digitalWrite(12, HIGH);
    // proceed:
    
    
    display.clearDisplay();
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(30,15);
    display.println("Beginning");
    display.setCursor(30,30);
    display.println("Cycle");
    display.display();
    delay(2000);
    
//drying sequence begin


////////////////////////////////////
///Left side of cycle///////////////
////////////////////////////////////

   //left side drying -close Right Inlet Valve (pin 4)
digitalWrite(4, LOW); 
  //Set left side inlet to open - it remains closed at the end of the loop
  digitalWrite(3, HIGH);

   
  display.clearDisplay();
  display.drawLine(2, 18, 126, 18, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println("SYS STATUS");
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,37);
  display.println("SW SIDES");
  display.display();
  delay(3000);



  display.clearDisplay();
  display.drawLine(2, 18, 126, 18, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println("SYS STATUS");
  display.display();
  display.setTextSize(1);
  delay(500);
  display.setTextColor(WHITE);
  display.setCursor(15,37);
  display.println("LT DRY");
  display.display();
  delay(3000);

// left side drying - open Right Exhaust Valve (pin 5)
  digitalWrite(5, LOW); 
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,60);
  display.println("RT DEPR");
  display.display();
  delay(6000);


  

/////Turn on right side heater - pin 8

  digitalWrite(8, LOW);
  
  display.clearDisplay();
  display.display();
  display.drawLine(2, 18, 126, 18, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println("SYS STATUS");
  display.display();
  display.setTextSize(1);
  delay(500);
  display.setTextColor(WHITE);
  display.setCursor(15,37);
  display.println("LT DRY");
  display.display();
  delay(1000);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,60);
  display.println("RT HEAT");
  display.display();
  delay(6000);
  
///SWEEP
/////Turn off right side heater - pin 8
  digitalWrite(8, HIGH);
  
  display.clearDisplay();
  display.drawLine(2, 18, 126, 18, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println("SYS STATUS");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,37);
  display.println("LT DRY");
  display.display();
  delay(500);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,60);
  display.println("RT SWEEP");
  display.display();
  delay(6000);

// Repressurization
 //close right side exhaust (pin 5)
  digitalWrite(5, HIGH); 
 // open repress valve (pin 6)
  digitalWrite(6, LOW);

  display.clearDisplay();
  display.drawLine(2, 18, 126, 18, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println("SYS STATUS");
  display.setTextSize(1);
  delay(500);
  display.setTextColor(WHITE);
  display.setCursor(15,37);
  display.println("REPRESS");
  display.display();
  delay(500);
  display.setCursor(5,60);
  display.println("UNDER WAY");
  display.display();
  delay(6000);

// close repress valve (pin 6)
  digitalWrite(6, HIGH);
 

  display.clearDisplay();
  display.drawLine(2, 18, 126, 18, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println("SYS STATUS");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,37);
  display.println("SW SIDES");
  display.display();
  delay(3000);

//inlet switchover
//close left inlet (pin 3) 

    digitalWrite(3, LOW); 
    delay(3000);
  
/////////////////////////////////////
///Right side of cycle///////////////
/////////////////////////////////////


//open right inlet - pin4   
    digitalWrite(4, HIGH); 
    delay(3000);

      


    display.clearDisplay();
    display.drawLine(2, 18, 126, 18, WHITE);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,15);
    display.println("SYS STATUS");
    display.display();
    display.setTextSize(1);
    delay(500);
    display.setTextColor(WHITE);
    display.setCursor(15,37);
    display.println("RT DRY");
    display.display();
    delay(3000);

// left side drying - open Left Exhaust Valve (pin 2)
    digitalWrite(2, LOW); 
 
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(15,60);
    display.println("LT DEPR");
    display.display();
    delay(6000);

/////Turn on right side heater - pin 7

  digitalWrite(7, LOW);
  
  display.clearDisplay();
  display.display();
  display.drawLine(2, 18, 126, 18, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println("SYS STATUS");
  display.display();
  display.setTextSize(1);
  delay(500);
  display.setTextColor(WHITE);
  display.setCursor(15,37);
  display.println("RT DRY");
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,60);
  display.println("LT HEAT");
  display.display();
  delay(6000);
  
///SWEEP
/////Turn off right side heater - pin 7

  digitalWrite(7, HIGH);
  display.clearDisplay();
  display.drawLine(2, 18, 126, 18, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println("SYS STATUS");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,37);
  display.println("RT DRY");
  display.display();
  delay(500);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,60);
  display.println("LT SWEEP");
  display.display();
  delay(6000);

// Repressurization
 //close left side exhaust (pin 5)
  digitalWrite(2, HIGH); 
 // open repress valve (pin 6)
  digitalWrite(6, LOW);

  display.clearDisplay();
  display.drawLine(2, 18, 126, 18, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println("SYS STATUS");
  display.setTextSize(1);
  delay(500);
  display.setTextColor(WHITE);
  display.setCursor(15,37);
  display.println("REPRESS");
  display.display();
  delay(500);
  display.setCursor(5,60);
  display.println("UNDER WAY");
  display.display();
  delay(6000);

// close repress valve (pin 6)
  digitalWrite(6, HIGH);








     
///////////////////////////////end of if/else statement          
          } else {
    
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(40,15);
  display.println("Press ");
  display.setCursor(40,35);
  display.println("Button");
  display.setCursor(30,55);
  display.println("to Begin");
  display.display();

// Flash LED waiting on input

{
  float in, out;
  
  for (in = 4.712; in < 10.995; in = in + 0.007)
  {
    out = sin(in) * 127.5 + 127.5;
    analogWrite(LED,out);
    delay(1);
  }
}
    
//Turn off all relays

    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);   
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    display.display();
    delay(1000);
    
    digitalWrite(12, LOW);

      }
  }
/*



    
  
      
 /

  

  
 


// Repressurization
//close left side exhaust (pin 2)
digitalWrite(2, HIGH); 
    delay(3000);

display.clearDisplay();
  display.display();   
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,15);
  display.println("repressurization");
  display.setCursor(15,25);
  display.println("in progress");
  display.display();
  
// open repress Valve (pin 6)
digitalWrite(6, LOW); 
  delay(6000);
// close repress valve (pin 6)
digitalWrite(6, HIGH);
  delay(3000);
  
  display.clearDisplay();
  display.display();
    
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,10);
  display.println("Switchover");
  display.display();
  delay(3000);


*/



//////////////////////////////////////////////////
////////functions related to display
//////////////////////////////////////////////////
