struct start_pin {
  const int touch = 4;
  const int led = 13;
};
struct player_pin {
  const int touch;
  const int led;
};
start_pin start;
player_pin player1{2, 12};
player_pin player2{15, 14};

void setup() {
  // put your setup code here, to run once:
  pinMode(start.touch, INPUT);
  pinMode(start.led, OUTPUT);
  
  pinMode(player1.touch, INPUT);
  pinMode(player1.led, OUTPUT);
  
  pinMode(player2.touch, INPUT);
  pinMode(player2.led, OUTPUT);

  Serial.begin(115200);
  Serial.println("Hi, mom");
}

void loop() {
  // put your main code here, to run repeatedly:
  auto start_game = digitalRead(start.touch);
  Serial.println(start_game);

  if (start_game == HIGH) {
    for (size_t i = 0; i < 3; ++i) {
      digitalWrite(start.led, HIGH);
      delay(500);
      digitalWrite(start.led,LOW);
      delay(500);
    }
  
    
    const auto start_time = millis();

    while (true) {
      if (digitalRead(player1.touch) == HIGH) {
        digitalWrite(player1.led, HIGH);
        Serial.print("Player 1 wins! Reaction time:");
        Serial.print(millis() - start_time);
        break;
      }
      if (digitalRead(player2.touch) == HIGH) {
        digitalWrite(player2.led, HIGH);
        Serial.print("Player 2 wins! Reaction time:");
        Serial.print(millis() - start_time);
        break;
      }
    }
  }
  delay(10); // this speeds up the simulation
}


