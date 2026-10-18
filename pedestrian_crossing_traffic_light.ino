// Pedestrian Crossing Traffic Light System
// Arduino UNO

const int VEHICLE_GREEN = 11;
const int VEHICLE_YELLOW = 10;
const int VEHICLE_RED = 9;
const int PEDESTRIAN_GREEN = 8;
const int BUTTON_PIN = 2;

volatile bool pedestrianRequest = false;
volatile unsigned long lastInterruptTime = 0;

bool crossingInProgress = false;
 
void setup() {
  pinMode(VEHICLE_GREEN, OUTPUT);
  pinMode(VEHICLE_YELLOW, OUTPUT);
  pinMode(VEHICLE_RED, OUTPUT);
  pinMode(PEDESTRIAN_GREEN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);

  setNormalState();
}

void loop() {
  if (pedestrianRequest && !crossingInProgress) {
    pedestrianRequest = false;
    handlePedestrianCrossing();
  }
  // No setNormalState() here — it runs once in setup() and after each crossing
}

void buttonISR() {
  unsigned long now = millis();
  // Debounce: ignore triggers within 300ms of the last one
  if (now - lastInterruptTime > 300) {
    pedestrianRequest = true;
    lastInterruptTime = now;
  }
}

void handlePedestrianCrossing() {
  crossingInProgress = true;

  // Step 1: Vehicle Green OFF
  digitalWrite(VEHICLE_GREEN, LOW);

  // Step 2: Vehicle Yellow ON for 2 seconds
  digitalWrite(VEHICLE_YELLOW, HIGH);
  delay(2000);
  digitalWrite(VEHICLE_YELLOW, LOW);

  // Step 3: Vehicle Red ON
  digitalWrite(VEHICLE_RED, HIGH);

  // Step 4: Pedestrian Green ON for 5 seconds
  digitalWrite(PEDESTRIAN_GREEN, HIGH);
  delay(5000);
  digitalWrite(PEDESTRIAN_GREEN, LOW);

  // Step 5: Vehicle Red OFF
  digitalWrite(VEHICLE_RED, LOW);

  // Step 6: Return to normal
  setNormalState();

  // Clear any pending requests that came in during the sequence
  pedestrianRequest = false;
  crossingInProgress = false;
}

void setNormalState() {
  digitalWrite(VEHICLE_GREEN, HIGH);
  digitalWrite(VEHICLE_YELLOW, LOW);
  digitalWrite(VEHICLE_RED, LOW);
  digitalWrite(PEDESTRIAN_GREEN, LOW);
}
