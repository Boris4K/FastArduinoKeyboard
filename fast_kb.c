#include <Keyboard.h>

#define BUTTONS 20

int keycode_arr[] =
{
  118,  // PIN0   'v'
  119,   // PIN1   'w'
  120,  // PIN2   'x'
  121,   // PIN3   'y'
  32,  // PIN4   space
  10,  // PIN5   enter

  215,  // PIN6   RIGHT
  217,  // PIN7   DOWN
  216,  // PIN8   LEFT
  218,  // PIN9   UP

  122,  // PIN10  Z
  176,  // PIN11  ENTER
  17,   // PIN12  CTRL
  204,  // PIN13  F11

  112,  // A0     PAUSE
  177,  // A1     ESC

  97,  // A2     'a'

  98,  // A3     'b'

  108,  // A4     (right shoulder - r)
  114   // A5     "l" - left shoulder
};

int key_state[BUTTONS];

void setup()
{
  PRR1 = PRR1 |
         (
           (1 << PRTIM2) |
           (1 << PRTIM3) |
           (1 << PRUSART1)
         );
  PRR0 = PRR0 |
         (
           (1 << PRTWI) |
           (1 << PRSPI) |
           (1 << PRTIM1) |
           (1 << PRADC)
         );

  DDRB = DDRB & ~
         (
           (1 << DDB1) |
           (1 << DDB2) |
           (1 << DDB3) |
           (1 << DDB4) |
           (1 << DDB5) |
           (1 << DDB6) |
           (1 << DDB7)
         );

  PORTB = PORTB |
          (
            (1 << PB1) |
            (1 << PB2) |
            (1 << PB3) |
            (1 << PB4) |
            (1 << PB5) |
            (1 << PB6) |
            (1 << PB7)
          );

  DDRC = DDRC & ~
         (
           (1 << DDC6) |
           (1 << DDC7)
         );
  PORTC = PORTC |
          (
            (1 << PC6) |
            (1 << PC7)
          );

  DDRD = DDRD & ~
         (
           (1 << DDD0) |
           (1 << DDD1) |
           (1 << DDD2) |
           (1 << DDD3) |
           (1 << DDD4) |
           (1 << DDD6) |
           (1 << DDD7)
         );
  PORTD = PORTD |
          (
            (1 << PD0) |
            (1 << PD1) |
            (1 << PD2) |
            (1 << PD3) |
            (1 << PD4) |
            (1 << PD6) |
            (1 << PD7)
          );

  DDRE = DDRE & ~ (1 << DDE6);
  PORTE = PORTE | (1 << PE6);

  DDRF = DDRF & ~
         (
           (1 << DDF0) |
           (1 << DDF1) |
           (1 << DDF4) |
           (1 << DDF5) |
           (1 << DDF6) |
           (1 << DDF7)
         );
  PORTF = PORTF |
          (
            (1 << PF0) |
            (1 << PF1) |
            (1 << PF4) |
            (1 << PF5) |
            (1 << PF6) |
            (1 << PF7)
          );

  Keyboard.begin();
  //Serial.begin(115200);
}

void loop()
{
  int port_b;
  int port_c;
  int port_d;
  int port_e;
  int port_f;

  port_b = PINB;
  port_c = PINC;
  port_d = PIND;
  port_e = PINE;
  port_f = PINF;

  key_state[0] = ((port_d & (1 << PD2)) == 0); // PIN0
  key_state[1] = ((port_d & (1 << PD3)) == 0); // PIN1
  key_state[2] = ((port_d & (1 << PD1)) == 0); // PIN2
  key_state[3] = ((port_d & (1 << PD0)) == 0); // PIN3
  key_state[4] = ((port_d & (1 << PD4)) == 0); // PIN4
  key_state[5] = ((port_c & (1 << PC6)) == 0); // PIN5
  key_state[6] = ((port_d & (1 << PD7)) == 0); // PIN6
  key_state[7] = ((port_e & (1 << PE6)) == 0); // PIN7
  key_state[8] = ((port_b & (1 << PB4)) == 0); // PIN8
  key_state[9] = ((port_b & (1 << PB5)) == 0); // PIN9
  key_state[10] = ((port_b & (1 << PB6)) == 0); // PIN10
  key_state[11] = ((port_b & (1 << PB7)) == 0); // PIN11
  key_state[12] = ((port_d & (1 << PD6)) == 0); // PIN12
  key_state[13] = ((port_c & (1 << PC7)) == 0); // PIN13
  key_state[14] = ((port_f & (1 << PF7)) == 0); // A0
  key_state[15] = ((port_f & (1 << PF6)) == 0); // A1
  key_state[16] = ((port_f & (1 << PF5)) == 0); // A2
  key_state[17] = ((port_f & (1 << PF4)) == 0); // A3
  key_state[18] = ((port_f & (1 << PF1)) == 0); // A4
  key_state[19] = ((port_f & (1 << PF0)) == 0); // A5

  //Serial.println(key_state[6]);

  for (int i = 0; i < BUTTONS; i++)
  {
    if (key_state[i] == 1)
    {
      //Serial.println(keycode_arr[i]);
      Keyboard.press(keycode_arr[i]);
    }
    else
    {
      Keyboard.release(keycode_arr[i]);
    }
  }
}
