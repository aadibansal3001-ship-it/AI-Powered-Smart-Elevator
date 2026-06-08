// AI Powered Smart Elevator
// Basic ESP32 Elevator Controller

#define FLOOR1_BTN 13
#define FLOOR2_BTN 12
#define FLOOR3_BTN 14

#define MOTOR_UP 26
#define MOTOR_DOWN 27

#define FLOOR1_SENSOR 32
#define FLOOR2_SENSOR 33
#define FLOOR3_SENSOR 25

#define EMERGENCY_STOP 4

int currentFloor = 1;
int targetFloor = 1;

void setup() {
  Serial.begin(115200);

  pinMode(FLOOR1_BTN, INPUT_PULLUP);
  pinMode(FLOOR2_BTN, INPUT_PULLUP);
  pinMode(FLOOR3_BTN, INPUT_PULLUP);

  pinMode(FLOOR1_SENSOR, INPUT_PULLUP);
  pinMode(FLOOR2_SENSOR, INPUT_PULLUP);
  pinMode(FLOOR3_SENSOR, INPUT_PULLUP);

  pinMode(EMERGENCY_STOP, INPUT_PULLUP);

  pinMode(MOTOR_UP, OUTPUT);
  pinMode(MOTOR_DOWN, OUTPUT);

  stopMotor();

  Serial.println("AI Smart Elevator Started");
}

void loop() {

  if (digitalRead(EMERGENCY_STOP) == LOW) {
    stopMotor();
    Serial.println("EMERGENCY STOP ACTIVATED");
    return;
  }

  if (digitalRead(FLOOR1_BTN) == LOW) {
    targetFloor = 1;
  }

  if (digitalRead(FLOOR2_BTN) == LOW) {
    targetFloor = 2;
  }

  if (digitalRead(FLOOR3_BTN) == LOW) {
    targetFloor = 3;
  }

  updateCurrentFloor();

  if (targetFloor > currentFloor) {
    moveUp();
  }
  else if (targetFloor < currentFloor) {
    moveDown();
  }
  else {
    stopMotor();
  }
}

void updateCurrentFloor() {

  if (digitalRead(FLOOR1_SENSOR) == LOW) {
    currentFloor = 1;
  }

  if (digitalRead(FLOOR2_SENSOR) == LOW) {
    currentFloor = 2;
  }

  if (digitalRead(FLOOR3_SENSOR) == LOW) {
    currentFloor = 3;
  }
}

void moveUp() {
  digitalWrite(MOTOR_UP, HIGH);
  digitalWrite(MOTOR_DOWN, LOW);

  Serial.print("Moving Up to Floor ");
  Serial.println(targetFloor);
}

void moveDown() {
  digitalWrite(MOTOR_UP, LOW);
  digitalWrite(MOTOR_DOWN, HIGH);

  Serial.print("Moving Down to Floor ");
  Serial.println(targetFloor);
}

void stopMotor() {
  digitalWrite(MOTOR_UP, LOW);
  digitalWrite(MOTOR_DOWN, LOW);
}
