#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int bikeX = 0; 

void setup() {
  // Initialize the display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  
  display.clearDisplay();
  display.display();
}

void drawGrass(int x, int y) {
  // Draw simple grass shapes
  for (int i = 0; i < SCREEN_WIDTH; i += 4) {
    display.drawLine(i, y, i + 2, y - 4, SSD1306_WHITE); 
    display.drawLine(i + 2, y - 4, i + 4, y, SSD1306_WHITE); 
  }
}

void drawAdvancedBicycle(int x, int y, int pedalAngle) {
  display.drawCircle(x, y, 10, SSD1306_WHITE);
  display.drawCircle(x + 30, y, 10, SSD1306_WHITE);
  display.drawLine(x, y, x + 15, y - 10, SSD1306_WHITE); 
  display.drawLine(x + 15, y - 10, x + 30, y, SSD1306_WHITE); 
  display.drawLine(x + 15, y - 10, x + 15, y - 20, SSD1306_WHITE); 
  display.drawLine(x + 15, y - 20, x + 5, y - 15, SSD1306_WHITE); 
  display.drawLine(x + 5, y - 15, x + 15, y - 10, SSD1306_WHITE); 
  display.drawLine(x + 30, y, x + 35, y - 10, SSD1306_WHITE);
  display.drawLine(x + 35, y - 10, x + 30, y - 20, SSD1306_WHITE);
  int pedalX = x + 15 + 5 * cos(pedalAngle * PI / 180);
  int pedalY = y - 10 + 5 * sin(pedalAngle * PI / 180);
  display.drawLine(x + 15, y - 10, pedalX, pedalY, SSD1306_WHITE);
  pedalX = x + 15 + 5 * cos((pedalAngle + 180) * PI / 180);
  pedalY = y - 10 + 5 * sin((pedalAngle + 180) * PI / 180);
  display.drawLine(x + 15, y - 10, pedalX, pedalY, SSD1306_WHITE);
  display.drawCircle(x + 15, y - 30, 3, SSD1306_WHITE); // Head
  display.drawLine(x + 15, y - 27, x + 15, y - 20, SSD1306_WHITE); 
  display.drawLine(x + 15, y - 25, x + 35, y - 15, SSD1306_WHITE); 
  display.drawLine(x + 15, y - 25, x + 35, y - 10, SSD1306_WHITE); 
  int leftLegX = x + 15 + 5 * cos((pedalAngle + 90) * PI / 180);
  int leftLegY = y - 10 + 5 * sin((pedalAngle + 90) * PI / 180);
  int rightLegX = x + 15 + 5 * cos((pedalAngle + 270) * PI / 180);
  int rightLegY = y - 10 + 5 * sin((pedalAngle + 270) * PI / 180);
  display.drawLine(x + 15, y - 20, leftLegX, leftLegY, SSD1306_WHITE);
  display.drawLine(x + 15, y - 20, rightLegX, rightLegY, SSD1306_WHITE); 

void loop() {
  for (int pedalAngle = 0; pedalAngle < 360; pedalAngle += 10) {
    display.clearDisplay();
    drawGrass(0, 63);
    drawAdvancedBicycle(bikeX, 40, pedalAngle);
    display.display();
    delay(100); 
    
    bikeX += 2; 
    if (bikeX > SCREEN_WIDTH) { 
      bikeX = -30; 
    }
  }
}

