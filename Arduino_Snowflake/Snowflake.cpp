#include "Snowflake.h"
#include <Adafruit_SSD1306.h>
#include "Arduino.h"

Snowflake::Snowflake(boolean ** grid, int snowflakeHeight1, int snowflakeWidth1) {
  pixelGrid = grid;
  snowflakeHeight = snowflakeHeight1;
  snowflakeWidth = snowflakeWidth1;
  xPos = 30;
  yPos = 30;
};

void Snowflake::drawSnowflake(Adafruit_SSD1306 display) {
  display.clearDisplay();
  int count = 0;
  for(int row = 0; row < snowflakeHeight; row++) {
    for(int col = 0; col < snowflakeWidth; col++) {
        if(pixelGrid[row][col]) {
          display.drawPixel(xPos+col, yPos+row, 1);
        }
        
        count++;
    }
  }
  Serial.println(count);
  display.display();
};