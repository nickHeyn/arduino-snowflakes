#include "Snowflake.h"
#include <Adafruit_SSD1306.h>
#include "Arduino.h"

Snowflake::Snowflake() {
  Serial.println("Starting snowflake build");
  for(int row = 0; row < SNOWFLAKE_QUADRANT_HEIGHT; row++) {
    for(int col = 0; col < SNOWFLAKE_QUADRANT_WIDTH; col++) {
      if(col == 0 || row == SNOWFLAKE_QUADRANT_HEIGHT) {
        snowflakeQuadrant[row][col] = 0xff;
      }
      else {
        snowflakeQuadrant[row][col] = 0x00;
      }
    }
  }
  xPos = 30;
  yPos = 30;
};

void Snowflake::drawSnowflake(Adafruit_SSD1306 display) {
  unsigned char** fullSnowflake = generateFullSnowflake();
  display.clearDisplay();
  //display.drawBitmap(0, 0, fullSnowflake, 17, 17, 1);
  //display.drawRect(30, 30, 17, 17, 1);
  int count = 0;
  for(int row = 0; row < SNOWFLAKE_FULL_HEIGHT; row++) {
    for(int col = 0; col < SNOWFLAKE_FULL_WIDTH; col++) {
        display.drawPixel(yPos+row, xPos+col, 1);
        count++;
    }
  }
  Serial.println(count);
  display.display();
};

unsigned char ** Snowflake::generateFullSnowflake() {
  unsigned char ** result = 0;
  result = new unsigned char* [SNOWFLAKE_FULL_HEIGHT];

  for(int row = 0; row < SNOWFLAKE_FULL_HEIGHT; row++) {
    result[row] = new unsigned char[SNOWFLAKE_FULL_WIDTH];
    for(int col = 0; col < SNOWFLAKE_FULL_WIDTH; col++) {
      result[row][col] = 0xff;
    }
  }

  return result;
};