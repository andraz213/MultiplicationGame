#include "handle_neopix.h"

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#define PIN       0

#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool inited_neo = false;

float pixs[8][2][3];



void init_neo(){
  if(!inited_neo){

    pixels.begin();
    inited_neo = true;

    for(int i = 0; i<8; i++){
      pixs[i][0][0] = 0.0;
      pixs[i][0][1] = 0.0;
      pixs[i][0][2] = 0.0;
      pixs[i][1][0] = 0.0;
      pixs[i][1][1] = 0.0;
      pixs[i][1][2] = 0.0;

    }
  }
}


void correct_neo(){
   pixels.clear();
  for(int i = 0; i<8; i++){
    pixels.setPixelColor(i, pixels.Color(0, 100, 0));
    delay(50);
    pixels.show();
  }

  delay(100);

}


void resetting_pix(){
pixels.clear();
 for(int i = 0; i<8; i++){
   if(i % 2 == 0){
     pixels.setPixelColor(i, pixels.Color(100, 0, 0));
   }else{
     pixels.setPixelColor(i, pixels.Color(0, 100, 0));
   }
 }
 pixels.show();

}

void wrong_neo(){
   pixels.clear();
  for(int i = 0; i<8; i++){
    pixels.setPixelColor(i, pixels.Color(100, 0, 0));
    delay(50);
    pixels.show();
  }

  delay(100);

}





void updat_pix(){

  pixels.clear();

  for(int i = 0; i<8; i++){
    float d = abs(pixs[i][0][0] - pixs[i][1][0]);
    d += abs(pixs[i][0][1] - pixs[i][1][1]);
    d += abs(pixs[i][0][2] - pixs[i][1][2]);


    if(abs(d) < 4.0){

      int r = random(25);
      int g = random(25);
      int b = random(25);

      int avg = (r + g + b)/3;
      int delta = abs(avg - r) + abs(avg - g) + abs(avg - b);
      while(delta < 40 || avg > 20){

        r = random(25);
        g = random(25);
        b = random(25);

        avg = (r + g + b)/3;
        delta = abs(avg - r) + abs(avg - r) + abs(avg - r);
      }

      pixs[i][1][0] = r;
      pixs[i][1][1] = g;
      pixs[i][1][2] = b;

    }

    float fak = (float)(random(10) + 10)/1000.0;
    if(fak < 0.01){
      fak = 0.01;
    }

    pixs[i][0][0] += fak * (pixs[i][1][0] - pixs[i][0][0]);
    pixs[i][0][1] += fak * (pixs[i][1][1] - pixs[i][0][1]);
    pixs[i][0][2] += fak * (pixs[i][1][2] - pixs[i][0][2]);


    pixels.setPixelColor(i, pixels.Color((int)pixs[i][0][0], (int)pixs[i][0][1], (int)pixs[i][0][2]));

  }
  pixels.show();

}
