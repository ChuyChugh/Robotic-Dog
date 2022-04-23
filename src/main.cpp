#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ODriveArduino.h>
#include <ODriveEnums.h>
#include <math.h>
#include <string.h>

#define l1 207.5
#define l2 80
#define cpr 8192
#define ratio 10.0f
#define up_x_position 200 //use millimeters as unit
#define up_y_position 400
#define down_x_position 40
#define down_y_position 40

template<class T> inline Print& operator <<(Print &obj,     T arg) { obj.print(arg);    return obj; }
template<>        inline Print& operator <<(Print &obj, float arg) { obj.print(arg, 4); return obj; }

SoftwareSerial odrive1_serial(8,9);
ODriveArduino odrive1(odrive1_serial);

String choice;

enum class SPEED{
  SLOW,
  FAST
};
SPEED speed;
namespace Axis{
  float set_axis0(double x, double y){
    float numerator = square(l1)+square(x) +square(y)-square(l2), denominator = 2 * l1 * hypot(x,y), result = 0;
    return (acos(x/hypot(x,y)) - acos(numerator/denominator))/2/PI * cpr * ratio;
  }
  float set_axis1(double x, double y){
    float numerator = square(l1)-square(x) -square(y)+square(l2), denominator = 2 * l1 * l2, result = 0;
    return PI/2 - acos((numerator/denominator)) /2/PI * cpr * ratio;
  }
}

void setup() {
  odrive1_serial.begin(115200);
  Serial.begin(115200);


  while(!Serial){
    Serial.println("ODriveArduino");
    Serial.println("Setting parameters...");
    Serial.println("Hello. Type a command to choose the setup/position control and speed");
    Serial.println("Make sure you type to integers that go from 0 to 1");
  }
  Serial.println("Ready!");
    Serial.println("Send the character '0' or '1' to calibrate respective motor (you must do this before you can command movement)");
    Serial.println("Send the character 's' to exectue test move");
    Serial.println("Send the character 'b' to read bus voltage");
    Serial.println("Send the character 'p' to do a spinning test");
}
void loop(){
    
    char character = Serial.read();

    if(character == '0' || character == 'l'){
      int num = (int)character;
      int requested_state = AXIS_STATE_MOTOR_CALIBRATION;
      Serial << "Axis" << character << ": Requesting state " << requested_state << '\n';
      if(!odrive1.run_state(num, requested_state, true)) return;

      requested_state = AXIS_STATE_ENCODER_OFFSET_CALIBRATION;
      Serial << "Axis" << character << ": Requesting state " << requested_state << '\n';
      if(!odrive1.run_state(num, requested_state, true, 25.0f)) return;

      requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL;
      Serial << "Axis" << character << ": Requesting state " << requested_state << '\n';
      if(!odrive1.run_state(num, requested_state, false /*don't wait*/)) return;
    }

    if(character == 'b'){
      odrive1_serial  << "r vbus_voltage\n";
      Serial << "VBus Voltage for ODrive1: " << odrive1.readFloat() << '\n';
    }

    if(character == 'p'){
      float pos_m0 = 81920.0f;
      odrive1.SetPosition(0, pos_m0);
      delay(5000);
      pos_m0 = 0.0f;
      odrive1.SetPosition(0, pos_m0);
      delay(5000);
    }
  }

