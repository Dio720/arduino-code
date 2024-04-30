#include <FS.h>
#include "SPIFFS.h"
#include <vector>

#define LED 22
#define BUTTON 21
#define DEBOUNCE_TIME 50

byte last_button_state = HIGH;
byte led_state = LOW;
unsigned long last_debounce_time = 0;

void writeFile(String state, String path) {
  File file = SPIFFS.open(path, "a");
  if (!file) {
    Serial.println("Erro ao abrir arquivo");
  } else {
    Serial.print("tamanho:");
    Serial.println(file.size());
    file.println(state);
    Serial.println("Gravou: " + state);
  }
  file.close();
}

void formatFile() {
  Serial.println("Formantando SPIFFS");
  SPIFFS.format();
  Serial.println("Formatou SPIFFS");
}

std::vector<String> readFile(String path) {
  Serial.println("Read file");
  File file = SPIFFS.open(path, "r+");
  std::vector<String> vec;
  if (!file) {
    Serial.println("Erro ao abrir arquivo ");
  } else {
    Serial.print("----------Lendo arquivo ");
    Serial.print(path);
    Serial.println("  ---------");

    while (file.position() < file.size()) {
      auto s = file.readStringUntil('\n');
      s.trim();
      vec.push_back(s);
      Serial.println(s);
    }
    file.close();
  }
  return vec;
}

void openFS() {
  if (!SPIFFS.begin()) {
    Serial.println("\nErro ao abrir o sistema de arquivos");
  } else {
    Serial.println("\nSistema de arquivos aberto com sucesso!");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Inicio");
  delay(200);

  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT); 

  //formatFile();
  Serial.println("Abrindo arquivo");
  openFS();
  auto saved_data = readFile("/logsAula.txt");
  led_state = saved_data.back().toInt();
  digitalWrite(LED, led_state); 
}

void loop() {
  int reading = digitalRead(BUTTON);
  if (reading != last_button_state) {
    last_debounce_time = millis();
  }
  if ((millis() - last_debounce_time) > DEBOUNCE_TIME) {
    if (reading == HIGH) {
      led_state = !led_state;
      digitalWrite(LED, led_state);
      writeFile(String(led_state), "/logsAula.txt");
    }
  }
  last_button_state = reading;
}
