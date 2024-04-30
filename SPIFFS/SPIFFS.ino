#include <FS.h>
#include "SPIFFS.h"

#define LED 22
#define BUTTON 21
#define DEBOUNCE_TIME 50

int num=0;
String str;
String s;

auto last_button_state = HIGH;
auto led_state = LOW;
unsigned long last_debounce_time = 0;

void writeFile(String state, String path) { //escreve conteúdo em um arquivo
  File rFile = SPIFFS.open(path, "w");
  if (!rFile) {
    Serial.println("Erro ao abrir arquivo!");
  }
  else {
    Serial.print("tamanho");
    Serial.println(rFile.size());
    rFile.println(state);
    Serial.print("Gravou: ");
    Serial.println(state);
  }
  rFile.close();
}

String readFile(String path) {
  Serial.println("Read file");
  File rFile = SPIFFS.open(path, "r");//r+ leitura e escrita
  if (!rFile) {
    Serial.println("Erro ao abrir arquivo!");
  }
  else {
    Serial.print("----------Lendo arquivo ");
    Serial.print(path);
    Serial.println("  ---------");
    String state = rFile.readStringUntil('\n');
    Serial.println(s);
    rFile.close();
    return state;
  }
}

void formatFile() {
  Serial.println("Formantando SPIFFS");
  SPIFFS.format();
  Serial.println("Formatou SPIFFS");
}

void openFS(void) {
  if (!SPIFFS.begin()) {
    Serial.println("\nErro ao abrir o sistema de arquivos");
  }
  else {
    Serial.println("\nSistema de arquivos aberto com sucesso!");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("inicio");
  delay(200);
  //formatFile();
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  Serial.println("abrir arquivo");
  openFS(); 
  Serial.println("ler arquivo");
  String test = readFile("/logsAula.txt");
  led_state = test.toInt();
  digitalWrite(LED, led_state);
  Serial.println("LED inicializado com sucesso: " + String(led_state));
}

void loop() {
  auto reading = digitalRead(BUTTON);
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
