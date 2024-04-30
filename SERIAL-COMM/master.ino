#include <SoftwareSerial.h>

SoftwareSerial ArduinoSlave(10,11);
String answer;
String message;
int int_value = 0, old_int_value = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("ENTER Commands: ");
    ArduinoSlave.begin(9600);
}

void loop() {
    // Read Sensor
    int_value = analogRead(A0);
    // Read answer from slave 
    readSlavePort();
    
    // Send data to slave 
    if (old_int_value != int_value) {
        Serial.println("Master sent: ");
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
