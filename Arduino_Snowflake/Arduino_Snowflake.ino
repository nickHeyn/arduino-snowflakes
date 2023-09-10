#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Snowflake.h"
#include "SnowflakeFactory.h"


// pin settings
#define LED_PIN 2
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1

// Snowflake settings
#define SNOWFLAKE_QUADRANT_HEIGHT 9
#define SNOWFLAKE_QUADRANT_WIDTH 9
#define SNOWFLAKE_FULL_HEIGHT SNOWFLAKE_QUADRANT_HEIGHT * 2 - 1 // 17
#define SNOWFLAKE_FULL_WIDTH SNOWFLAKE_QUADRANT_WIDTH * 2 - 1 //17

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(A0));
  Serial.begin(115200);
  SnowflakeFactory factory(SNOWFLAKE_QUADRANT_WIDTH, SNOWFLAKE_QUADRANT_HEIGHT);
  Snowflake snowflake1 = factory.generateSnowflake();

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

  // show snowflake
  snowflake1.drawSnowflake(display);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
