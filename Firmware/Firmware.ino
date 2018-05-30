/*
 * Wires:
 *    Scale:
 *      GND   => GND
 *      DT    => A1
 *      SCK   => A0
 *      VCC   => 5v
 *    4-digit 7-segment: (top left to top right, bottom left to bottom right):
 *      1 =>  1k res  => 7
 *      2 =>  2
 *      3 =>  12
 *      4 => 1k res => 8
 *      5 => 1k res => 9
 *      6 => 3
 *      7 => 11
 *      8 => 5
 *      9 => 6
 *      10 => 4
 *      11 => 13
 *      12 => 1k res => 10
 *    button:
 *      1 => 5v
 *      2 => A2
 *      2 => 10k res => gnd (parallel)
 *      
 */



// Include Libraries
#include "Arduino.h"
#include "SevSeg.h"
#include "hx711.h"
#include "Button.h"

// Pin Definitions
#define BUTTON_PIN A2
#define SCALE_SCK  A0
#define SCALE_DT  A1
#define SEG7_A	2
#define SEG7_B	3
#define SEG7_C	4
#define SEG7_D	5
#define SEG7_E	11
#define SEG7_F	12
#define SEG7_G	13
#define SEG7_DECIMAL	6
#define SEG7_DIG1	7
#define SEG7_DIG2	8
#define SEG7_DIG3	9
#define SEG7_DIG4	10

// Global variables and defines
#define GLOBAL_OFFSET 15117660
#define GLOBAL_RATIO 1102
int temp_grams_offset = 0;

// object initialization
SevSeg sevseg; //Initiate a seven segment controller object
Hx711 scale(SCALE_DT, SCALE_SCK);
Button pushButton(BUTTON_PIN);

void setup() {
    Serial.begin(9600);

    byte numDigits = 4;
    byte digitPins[] = {SEG7_DIG1, SEG7_DIG2, SEG7_DIG3, SEG7_DIG4};
    byte segmentPins[] = {SEG7_A, SEG7_B, SEG7_C, SEG7_D, SEG7_E, SEG7_F, SEG7_G, SEG7_DECIMAL};
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
    sevseg.setBrightness(90);

    // recorder 0kg: offset = 15117660
    // recorded 1kg: w      = 16219895
    // ratio = (w - offset) / 1000 = 1102.235
    scale.setOffset(GLOBAL_OFFSET);
    scale.setScale(GLOBAL_RATIO);

    pushButton.init();
}

void loop() {

    // read scale
    //Serial.print(F("Reading scale: grams: "));
    int grams_read = scale.getGram();
    int grams = grams_read - temp_grams_offset;
    if (grams > -4 && grams < 4) {
      grams = 0;
    }
    //Serial.println(grams);

    // loop in loop - to reduce reading scale
    for (int i=0; i<20000; i++) {
      // display grams
      sevseg.setNumber(grams, 3);
      sevseg.refreshDisplay(); // Must run repeatedly

      // check buttons
      bool pushButtonVal = pushButton.read();
      if (pushButtonVal == true) {
          //Serial.println(F("push button clicked"));
          temp_grams_offset = grams_read;
          delay(300);
      }
    }
}
