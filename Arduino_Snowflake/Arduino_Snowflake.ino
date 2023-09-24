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
#define MAX_NUM_SNOWFLAKES 1
#define STARTING_Y_POS_WINDOW 8
#define SNOWFLAKE_QUADRANT_HEIGHT 9
#define SNOWFLAKE_QUADRANT_WIDTH 9
#define SNOWFLAKE_FULL_HEIGHT SNOWFLAKE_QUADRANT_HEIGHT * 2 - 1 // 17
#define SNOWFLAKE_FULL_WIDTH SNOWFLAKE_QUADRANT_WIDTH * 2 - 1 //17

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SnowflakeFactory factory(SNOWFLAKE_QUADRANT_WIDTH, SNOWFLAKE_QUADRANT_HEIGHT);
std::vector<Snowflake> snowflakes;
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
}

void loop() {
  // put your main code here, to run repeatedly:
  moveSnowflakes();
  removeOutOfBoundsSnowflakes();
  spawnSnowflakes();
  drawSnowlakes();
  count++;
}

void drawSnowlakes() {
  display.clearDisplay();
  for(int snowflakeIndex = 0; snowflakeIndex < snowflakes.size(); snowflakeIndex++) {
    snowflakes[snowflakeIndex].drawSnowflake(&display, SCREEN_HEIGHT, SCREEN_WIDTH);
  }
  display.display();
}

void moveSnowflakes() {
  for(int snowflakeIndex = 0; snowflakeIndex < snowflakes.size(); snowflakeIndex++) {
    snowflakes[snowflakeIndex].moveSnowflake(millis());
  }
}

void removeOutOfBoundsSnowflakes() {
  for(int snowflakeIndex = 0; snowflakeIndex < snowflakes.size(); snowflakeIndex++) {
    Snowflake* snowflake = &snowflakes[snowflakeIndex];
    if(snowflake->getYPos() > SCREEN_HEIGHT) {
      snowflakes.erase(snowflakes.begin() + snowflakeIndex);
      snowflake->deletePixelGrid();
      delete snowflake;
      snowflakeIndex--;
    }
  }
}

void spawnSnowflakes() {
  if(snowflakes.size() < MAX_NUM_SNOWFLAKES) {
    int startingXPos = random(0, SCREEN_WIDTH - SNOWFLAKE_FULL_WIDTH);
    int startingYPos = random(-SNOWFLAKE_FULL_HEIGHT - 1 - STARTING_Y_POS_WINDOW, -SNOWFLAKE_FULL_HEIGHT - 1);
    snowflakes.push_back(*(factory.generateSnowflake(startingXPos, startingYPos)));
  }

}
