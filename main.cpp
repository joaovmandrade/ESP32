bool monitoring = false;

void setup() {
  Serial.begin(115200);

  Serial.println("BioSpine MVP iniciado");
  Serial.println("Comandos:");
  Serial.println("START");
  Serial.println("STOP");
  Serial.println("STATUS");
  Serial.println("CALIBRATE");
}

void loop() {

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

      Serial.println(
        "{\"success\":true,\"message\":\"Monitoring stopped\"}"
      );
    }

    else if (command == "CALIBRATE") {

      Serial.println(
        "{\"success\":true,\"message\":\"Calibration completed\"}"
      );
    }

    else if (command == "STATUS") {

      int angle = random(0, 45);

      String status;

      if (angle <= 10) {
        status = "GOOD";
      }
      else if (angle <= 20) {
        status = "WARNING";
      }
      else {
        status = "BAD";
      }

      Serial.print("{\"angle\":");
      Serial.print(angle);
      Serial.print(",\"status\":\"");
      Serial.print(status);
      Serial.println("\"}");
    }

    else {

      Serial.println(
        "{\"error\":\"Unknown command\"}"
      );
    }
  }
}