#include <Arduino.h>
#include "lcd_wrapper.h"
#include "mastermind.h"

boolean is_duplicat(char code[])
{ // https://qna.habr.com/q/473022
  char *first_ch;
  char *second_ch;
  for (int x = 0; x < sizeof(code) / sizeof(code[0]); x++)
  {                                     // this gives us a length (16/4)
    first_ch = strchr(code, code[x]);   // first found char or NULL
    second_ch = strrchr(code, code[x]); // last found char or NULL
    if (second_ch != 0 && first_ch != second_ch)
    {
      return true;
    }
  }
  return false;
}

char *generate_code(bool repeat, int length)
{
  if (length < 1)
  {
    return NULL;
  }
  if (repeat == true && length > 10)
  {
    return NULL;
  }

  char code[length + 1];
  int x = 0;
  while (x < length)
  {
    code[x] = random(10) + 48; // or + '0' turn it to a char
    x++;
  }
  code[length] = '\0';
  char *first_ch;
  char *second_ch;
  while (repeat == false && is_duplicat(code))
  {
    for (int y = 0; y < length; y++)
    {

      first_ch = strchr(code, code[y]);   // first found char or NULL
      second_ch = strrchr(code, code[y]); // last found char or NULL

      if (second_ch != 0 && first_ch != second_ch)
      {
        code[y] = random(10) + 48;
      }
    }
  }

  char *result = (char *)calloc(length + 1, sizeof(char));
  memcpy(result, code, length + 1);

  return result;
}

void get_score(const char *secret, const char *guess, int *peg_a, int *peg_b)
{
  if (secret == NULL || guess == NULL)
  {
    return;
  }
  String player = String(guess); // make type String so we can use length() and indexOf() function
  String arduino = String(secret);

  if (player.length() != arduino.length())
  {
    return;
  }

  int x = 0;
  int idx_pos;
  while (x < player.length())
  {                                       // returns length without \0
    idx_pos = arduino.indexOf(player[x]); // returns position of value or -1
    if (idx_pos != -1)
    {
      if (idx_pos == x)
      {
        *peg_a += 1;            // first of all we need to find all digits in the same positions
        arduino[idx_pos] = ' '; // so next time function indexOf() won't return this position
      }
    }
    x += 1;
  }
  x = 0;
  while (x < player.length())
  {                                       // returns length without \0
    idx_pos = arduino.indexOf(player[x]); // returns position of value or -1
    if (idx_pos != -1)
    {
      *peg_b += 1;
      arduino[idx_pos] = ' '; // so next time function indexOf() won't return this position
    }
    x += 1;
  }
}

void turn_off_leds()
{
  digitalWrite(LED_BLUE_1, LOW);
  digitalWrite(LED_RED_1, LOW);
  digitalWrite(LED_BLUE_2, LOW);
  digitalWrite(LED_RED_2, LOW);
  digitalWrite(LED_BLUE_3, LOW);
  digitalWrite(LED_RED_3, LOW);
  digitalWrite(LED_BLUE_4, LOW);
  digitalWrite(LED_RED_4, LOW);
}

void render_leds(const int peg_a, const int peg_b)
{
  if (peg_a > 4 || peg_b > 4)
  {
    return;
  }

  char red_led[] = {LED_RED_1, LED_RED_2, LED_RED_3, LED_RED_4};
  char blue_led[] = {LED_BLUE_1, LED_BLUE_2, LED_BLUE_3, LED_BLUE_4};
  int idx = 0;
  if (peg_a > 0)
  {
    while (idx < peg_a)
    {
      digitalWrite(red_led[idx], HIGH);
      idx++;
    }
  }
  if (peg_b > 0)
  {
    idx = 0;
    while (idx < peg_b)
    {
      digitalWrite(blue_led[idx], HIGH);
      idx++;
    }
  }
}

void render_history(char *secret, char **history, const int entry_nr)
{
  char count[][3] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10"};
  char score[] = {65, 48, 66, 48, '\0'};
  int peg_a = 0, peg_b = 0;

  turn_off_leds();
  lcd_print_at(0, 0, count[entry_nr]);
  lcd_print_at(2, 0, ":");
  lcd_print_at(4, 0, history[entry_nr]);
  get_score(secret, history[entry_nr], &peg_a, &peg_b);
  score[1] = peg_a + '0';
  score[3] = peg_b + '0';
  lcd_set_cursor(9, 0);
  lcd_print(score);
  render_leds(peg_a, peg_b);
}

void play_game(char *secret)
{

  int tried = 0;
  bool win = 0;
  int peg_a, peg_b;
  char guess[] = {48, 48, 48, 48, '\0'};
  char count[][3] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10"};
  char score[] = {65, 48, 66, 48, '\0'};
  char **history = calloc(10, sizeof(char *));

  for (int y = 0; y < 10; y++)
  {
    history[y] = calloc(5, sizeof(char));
  }

  lcd_clear();
  turn_off_leds();

  lcd_print_at(0, 0, "Welcome to");
  lcd_print_at(6, 1, "MasterMind");

  delay(3000);
  lcd_clear();

  lcd_print_at(0, 0, "Guess secret");
  lcd_print_at(11, 1, "code");

  delay(3000);
  lcd_clear();

  lcd_print_at(0, 0, "Try it now:");
  lcd_print_at(0, 1, "Your guess: 0000");

  while (tried < 10 && win == false)
  {
    if (digitalRead(BTN_1_PIN) == HIGH)
    {
      long milis = 0;
      int idx = tried - 1;
      while (digitalRead(BTN_1_PIN) == HIGH)
      {
        // milis++;
        if (digitalRead(BTN_2_PIN) == HIGH)
        {
          idx--;
          if (idx >= 0)
          {
            render_history(secret, history, idx);
          }
          else
          {
            idx = 0;
          }
          delay(350);
        }
        if (digitalRead(BTN_3_PIN) == HIGH)
        {
          idx++;
          if (tried > idx)
          {
            render_history(secret, history, idx);
          }
          else
          {
            idx = tried - 1;
          }
          delay(350);
        }
        milis++;
      }
      if (milis < 20000)
      {
        guess[0] = guess[0] != 57 ? guess[0] + 1 : 48; // we're using ternary operator; guess doesn't equal 9? if yes then guess + 1, if not than guess equal 0
        lcd_print_at(12, 1, guess);
      }
      while (digitalRead(BTN_1_PIN) == HIGH)
      {
        // do nothing
      }
      delay(250);
    }
    if (digitalRead(BTN_2_PIN) == HIGH)
    {
      guess[1] = guess[1] != 57 ? guess[1] + 1 : 48;
      lcd_print_at(12, 1, guess);
      while (digitalRead(BTN_2_PIN) == HIGH)
      {
        // do nothing
      }
      delay(250);
    }
    if (digitalRead(BTN_3_PIN) == HIGH)
    {
      guess[2] = guess[2] != 57 ? guess[2] + 1 : 48;
      lcd_print_at(12, 1, guess);
      while (digitalRead(BTN_3_PIN) == HIGH)
      {
        // do nothing
      }
      delay(250);
    }
    if (digitalRead(BTN_4_PIN) == HIGH)
    {
      guess[3] = guess[3] != 57 ? guess[3] + 1 : 48;
      lcd_print_at(12, 1, guess);
      while (digitalRead(BTN_4_PIN) == HIGH)
      {
        // do nothing
      }
      delay(250);
    }
    if (digitalRead(BTN_ENTER_PIN) == HIGH)
    {
      memcpy(history[tried], guess, 5 * sizeof(guess[0])); // copy blocks of memory
      lcd_clear();
      turn_off_leds();
      peg_a = 0;
      peg_b = 0;
      get_score(secret, guess, &peg_a, &peg_b);
      if (peg_a == 4)
      {
        win = true;
        break;
      }
      if (tried == 9)
      {
        break;
      }
      lcd_print_at(0, 0, count[tried]);
      lcd_print_at(2, 0, ":");
      lcd_print_at(4, 0, guess);
      for (int i = 0; i < 4; i++)
      {
        guess[i] = 48;
      }
      lcd_print_at(0, 1, "Your guess: 0000");
      score[1] = peg_a + '0';
      score[3] = peg_b + '0';
      lcd_set_cursor(9, 0);
      lcd_print(score);

      render_leds(peg_a, peg_b);
      while (digitalRead(BTN_ENTER_PIN) == HIGH)
      {
        // do nothing
      }
      delay(250);
      tried++;
    }
  }

  if (win == true)
  {
    lcd_clear();
    render_leds(4, 4);
    lcd_print_at(5, 0, "You win");
    lcd_print_at(1, 1, "At attempt:");
    lcd_print_at(13, 1, count[tried]);
  }
  else
  {
    lcd_clear();
    turn_off_leds();
    lcd_print_at(0, 0, "HA-HA-HA! LOSER!");
    lcd_print_at(0, 1, "Secret:");
    lcd_print_at(8, 1, secret);
  }
  delay(3000);
  for (int y = 0; y < 10; y++)
  {
    free(history[y]);
  }
  free(history);
}
