#include "Snowflake.h"
#include <Adafruit_SSD1306.h>
#include "Arduino.h"

Snowflake::Snowflake(boolean ** grid, int snowflakeHeight1, int snowflakeWidth1) {
  pixelGrid = grid;
  snowflakeHeight = snowflakeHeight1;
  snowflakeWidth = snowflakeWidth1;
  xPos = 30;
  yPos = 30;
  xVel = 0;
  yVel = 1;
};

void Snowflake::drawSnowflake(Adafruit_SSD1306* display, int displayHeight, int displayWidth) {
  for(int row = 0; row < snowflakeHeight; row++) {
    for(int col = 0; col < snowflakeWidth; col++) {
      int displayXPos = xPos + col;
      int displayYPos = yPos + row;
      if(pixelGrid[row][col] &&
         displayXPos >= 0 &&
         displayXPos < displayWidth &&
         displayYPos >= 0 &&
         displayYPos < displayHeight) {
        display->drawPixel(displayXPos, displayYPos, 1);
      }
    }
  }
};