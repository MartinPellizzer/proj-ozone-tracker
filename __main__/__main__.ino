#include <SoftwareSerial.h>
#include <Nextion.h>

SoftwareSerial nextion(2, 3); // Nextion TX -> Pin 2 Arduino --- Nextion RX -> Pin 3 Arduino
Nextion myNextion(nextion, 9600);

typedef enum State {
  HOME_PAGE,
  CHART_PAGE,
  FUNC_PAGE,
  INFO_PAGE
} State;

typedef struct Fifo {
  int n;
  int *a;
} Fifo;

typedef struct Circ {
  int n;
  int i;
  int *a;
} Circ;

State state = HOME_PAGE;
State state_prev = HOME_PAGE;

Fifo f = {12, (int[12]) {0}};
bool is_f_updated = false;

Circ c_sec = {60, 0, (int[60]) {0}};
Circ c_min = {60, 0, (int[60]) {0}};

int sensor_val = 0;
int sensor_val_prev = -1;

unsigned long current_millis = 0;
unsigned long current_millis_zero = 0;

void setup() {
  Serial.begin(9600);
  myNextion.init();
}

void loop()
{
  ReadSensor();
  
  if ((millis() - current_millis_zero) >= 3000)
  {
    current_millis_zero = millis();
    sensor_val = 0;
  }
  
  NextionHandleInputs();
  NextionHandleOutputs();

  bool is_overflow = false;
  int _avg = 0;

  if ((millis() - current_millis) >= 1000)
  {
    current_millis = millis();
    
    is_overflow = CircInsert(&c_sec, sensor_val);
    
    if (is_overflow)
    {
      _avg = CircAvg(&c_sec);
      is_overflow = CircInsert(&c_min, _avg);

      if (is_overflow)
      {
        _avg = CircAvg(&c_min);
        FifoPush(&f, _avg);
        is_f_updated = true;
      }
    }
  }
}
