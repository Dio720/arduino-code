#include <FS.h>
#include "SPIFFS.h"

#define LED 21
#define TOUCH_BUTTON 4
#define TOUCH_MAGIC_VALUE 15

int num=0;
String str;
String s;

auto last_button_state = HIGH;
auto led_state = LOW;

void writeFile(String state, String path) { //escreve conteúdo em um arquivo
  File rFile = SPIFFS.open(path, "a");//a para anexar
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
    while (rFile.position() < rFile.size())
    {
      s = rFile.readStringUntil('\n');
      s.trim();
      Serial.println(s);
    }
    rFile.close();
    return s;
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

  pinMode(LED, OUTPUT);
  //formatFile();
  Serial.println("abrir arquivo");
  openFS(); 
  Serial.println("ler arquivo");
  String last_led_state = readFile("/logsAula.txt"); 
  led_state = last_button_state.toInt();
  digitalWrite(LED, led_state);
  Serial.println("LED Atualizado com sucesso: " + String(led_state));
}

void loop() {
  Serial.print("Touch: ");
  auto touch_reading = touchRead(TOUCH_BUTTON);
  if (touch_reading < TOUCH_MAGIC_VALUE) {
    led_state = !led_state;
    digitalWrite(LED, led_state);
    writeFile(String(led_state), "/logsAula.txt");
  }
  delay(1000);

}


