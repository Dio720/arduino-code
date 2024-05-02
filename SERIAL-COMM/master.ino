#include <SoftwareSerial.h>

SoftwareSerial ArduinoSlave(10,11);
String answer;
String message;
int int_value = 0, old_int_value = 0;
int button_pin = 7;
bool sensor_flag = false;

void setup() {
    Serial.begin(9600);
    Serial.println("ENTER Commands: ");
    pinMode(button_pin, INPUT);
    ArduinoSlave.begin(9600);
}

String bool_to_string(bool b) {
  if (b) {
    return "True";
  }
  return "False";
}

void loop() {
    // Read Sensor
    int_value = analogRead(A1);
    auto button_reading = digitalRead(button_pin);
    // Read answer from slave 
    readSlavePort();

    Serial.print("BUTTON READING: ");
    Serial.println(button_reading);
    sensor_flag = (button_reading == HIGH) ? !sensor_flag : sensor_flag;
    Serial.print("Sensor flag: ");
    Serial.println(bool_to_string(sensor_flag));

    // Send data to slave 
    if (old_int_value != int_value) {
        Serial.print("INT VALUE - before ternary: ");
        Serial.println(int_value);
        Serial.println("Master sent: ");
        int_value = (sensor_flag) ? 255 : int_value;
        Serial.println(int_value);
        ArduinoSlave.print(int_value);
        old_int_value = int_value;
    }
    // Send answer to monitor
    if (answer != "") {
        Serial.print("Slave LED PWM value: ");
        Serial.println(answer);
        answer = "";
    }
    Serial.println();
    delay(1000);
}

void readSlavePort() {
    while (ArduinoSlave.available()) {
        delay(10);
        if (ArduinoSlave.available() > 0) {
            char ch = ArduinoSlave.read(); // gets one byte from serial buffer
            answer += ch; // makes the string readString
        }
    }
}

