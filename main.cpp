#include <Wire.h>

#define LED_PIN 2

#define FLEX_LEFT_PIN 34
#define FLEX_RIGHT_PIN 35
#define FSR_PIN 32

bool monitoring = false;

unsigned long lastReading = 0;
const unsigned long interval = 1000;

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  randomSeed(micros());

  Wire.begin(21, 22);

  Serial.println("BioSpine V3");
  Serial.println("START");
  Serial.println("STOP");
  Serial.println("STATUS");
  Serial.println("CALIBRATE");
}

float readMPUAngle() {

  // FUTURO:
  // retornar leitura real do MPU6050

  return random(0, 450) / 10.0;
}

int readFlexLeft() {

  // FUTURO:
  // return analogRead(FLEX_LEFT_PIN);

  return random(300, 800);
}

int readFlexRight() {

  return random(300, 800);
}

int readFSR() {

  return random(0, 100);
}

void sendData() {

  float angle = readMPUAngle();

  int flexLeft = readFlexLeft();

  int flexRight = readFlexRight();

  int pressure = readFSR();

  String posture;

  bool alert = false;

  if (angle <= 10) {

    posture = "GOOD";
  }
  else if (angle <= 20) {

    posture = "WARNING";
  }
  else {

    posture = "BAD";

    alert = true;
  }

  digitalWrite(
    LED_PIN,
    alert ? HIGH : LOW
  );

  Serial.print("{");

  Serial.print("\"angle\":");
  Serial.print(angle);

  Serial.print(",");

  Serial.print("\"flex_left\":");
  Serial.print(flexLeft);

  Serial.print(",");

  Serial.print("\"flex_right\":");
  Serial.print(flexRight);

  Serial.print(",");

  Serial.print("\"pressure\":");
  Serial.print(pressure);

  Serial.print(",");

  Serial.print("\"status\":\"");
  Serial.print(posture);
  Serial.print("\"");

  Serial.print(",");

  Serial.print("\"alert\":");
  Serial.print(alert ? "true" : "false");

  Serial.println("}");
}

void loop() {

  if (monitoring) {

    if (millis() - lastReading >= interval) {

      lastReading = millis();

      sendData();
    }
  }

  if (Serial.available()) {

    String command = Serial.readStringUntil('\n');

    command.trim();

    if (command == "START") {

      monitoring = true;

      Serial.println(
        "{\"success\":true,\"message\":\"Monitoring started\"}"
      );
    }

    else if (command == "STOP") {

      monitoring = false;

      digitalWrite(LED_PIN, LOW);

      Serial.println(
        "{\"success\":true,\"message\":\"Monitoring stopped\"}"
      );
    }

    else if (command == "STATUS") {

      sendData();
    }

    else if (command == "CALIBRATE") {

      Serial.println(
        "{\"success\":true,\"message\":\"Calibration completed\"}"
      );
    }

    else {

      Serial.println(
        "{\"error\":\"Unknown command\"}"
      );
    }
  }
}