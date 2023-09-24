#include "Snowflake.h"
#include <Adafruit_SSD1306.h>
#include "Arduino.h"

Snowflake::Snowflake(boolean ** grid, int xPos1, int yPos1, int snowflakeHeight1, int snowflakeWidth1, unsigned long spawnTime) {
  pixelGrid = grid;
  snowflakeHeight = snowflakeHeight1;
  snowflakeWidth = snowflakeWidth1;
  xPos = xPos1;
  yPos = yPos1;
  xVel = 0;
  yVel = 6;
  timeAtLastMove = spawnTime;
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