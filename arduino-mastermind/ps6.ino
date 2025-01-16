#include "mastermind.h"
#include "lcd_wrapper.h"

void setup()
{
  // initialize the lcd
  Serial.begin(9600);
  // Print a message to the LCD.
  lcd_init();
  randomSeed(analogRead(1));
  pinMode(LED_BLUE_1, OUTPUT);
  pinMode(LED_BLUE_2, OUTPUT);
  pinMode(LED_BLUE_3, OUTPUT);
  pinMode(LED_BLUE_4, OUTPUT);
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_RED_3, OUTPUT);
  pinMode(LED_RED_4, OUTPUT);

  pinMode(BTN_1_PIN, INPUT);
  pinMode(BTN_2_PIN, INPUT);
  pinMode(BTN_3_PIN, INPUT);
  pinMode(BTN_4_PIN, INPUT);
  pinMode(BTN_ENTER_PIN, INPUT);
}

void loop()
{
  char *str = generate_code(false, 4);
  Serial.println(str);

  play_game(str);

  free(str);
}
