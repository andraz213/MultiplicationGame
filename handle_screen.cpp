#include "handle_screen.h"
#include "handle_spiffs.h"
#include "game_logic.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void init_screen(){
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

    display.display();

}



void show_eqq(int x, int y, int ans1, int ans2, int ans3, int ans4){
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.println(String(get_score_fs()));

display.setTextSize(2); // Draw 2X-scale text
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 20);

display.println(String(ans1));
display.setCursor(15, 48);
display.println(String(ans2));

int x_off = 100;
if(ans4 < 10){
  x_off += 12;
}
if(ans4 == 100){
  x_off -= 12;
}
display.setCursor(x_off, 20);
display.println(String(ans4));

x_off = 85;
if(ans3 < 10){
  x_off += 12;
}
if(ans3 == 100){
  x_off -= 12;
}

display.setCursor(x_off, 48);
display.println(String(ans3));

x_off = 46;
if(x == 10){
  x_off -= 12;
}
display.setCursor(x_off, 0);
display.println(String(x) + " " + String(y));

display.fillCircle(62, 7, 2, SSD1306_WHITE);

display.display();
}
