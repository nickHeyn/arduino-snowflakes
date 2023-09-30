#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>
#include "Snowflake.h"
#include "SnowflakeFactory.h"


// pin settings
#define LED_PIN 2
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1

// Snowflake settings
#define MAX_NUM_SNOWFLAKES 4
#define STARTING_Y_POS_WINDOW 50
#define SNOWFLAKE_QUADRANT_HEIGHT 9
#define SNOWFLAKE_QUADRANT_WIDTH 9
#define SNOWFLAKE_FULL_HEIGHT SNOWFLAKE_QUADRANT_HEIGHT * 2 - 1
#define SNOWFLAKE_FULL_WIDTH SNOWFLAKE_QUADRANT_WIDTH * 2 - 1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SnowflakeFactory factory(SNOWFLAKE_QUADRANT_WIDTH, SNOWFLAKE_QUADRANT_HEIGHT);
Snowflake snowflakes[MAX_NUM_SNOWFLAKES];
unsigned int count = 0;


void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(A0));
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  Serial.println("Starting");
   // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  pinMode(LED_PIN, OUTPUT);

  for(int i = 0; i < MAX_NUM_SNOWFLAKES; i++) {
    int startingXPos = random(0, SCREEN_WIDTH - SNOWFLAKE_FULL_WIDTH);
    int startingYPos = random(-SNOWFLAKE_FULL_HEIGHT - 1 - STARTING_Y_POS_WINDOW, -SNOWFLAKE_FULL_HEIGHT - 1);
    snowflakes[i] = factory.generateSnowflake(startingXPos, startingYPos);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  moveSnowflakes();
  respawnSnowflakes();
  drawSnowlakes();
  count++;
}

void drawSnowlakes() {
  display.clearDisplay();
  for(int snowflakeIndex = 0; snowflakeIndex < MAX_NUM_SNOWFLAKES; snowflakeIndex++) {
    snowflakes[snowflakeIndex].drawSnowflake(&display, SCREEN_HEIGHT, SCREEN_WIDTH);
  }
  display.display();
}

void moveSnowflakes() {
  for(int snowflakeIndex = 0; snowflakeIndex < MAX_NUM_SNOWFLAKES; snowflakeIndex++) {
    snowflakes[snowflakeIndex].moveSnowflake(millis());
  }
}

void respawnSnowflakes() {
for(int snowflakeIndex = 0; snowflakeIndex < MAX_NUM_SNOWFLAKES; snowflakeIndex++) {
    Snowflake snowflake = snowflakes[snowflakeIndex];
    if(snowflake.getYPos() > SCREEN_HEIGHT) {
      // snowflake is out of bounds. Need to reset its position and grid
      snowflake.deletePixelGrid();

      int startingXPos = random(0, SCREEN_WIDTH - SNOWFLAKE_FULL_WIDTH);
      int startingYPos = random(-SNOWFLAKE_FULL_HEIGHT - 1 - STARTING_Y_POS_WINDOW, -SNOWFLAKE_FULL_HEIGHT - 1);
      snowflakes[snowflakeIndex] = factory.generateSnowflake(startingXPos, startingYPos);
    }
  }
}
