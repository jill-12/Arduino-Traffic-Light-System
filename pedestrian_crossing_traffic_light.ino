// Pedestrian Crossing Traffic Light System
// Arduino UNO
// Vehicle Green -> Pin 11
// Vehicle Yellow -> Pin 10
// Vehicle Red -> Pin 9
// Pedestrian Green -> Pin 8
// Push button -> Pin 2 (External Interrupt INT0)

const int VEHICLE_GREEN = 11;
const int VEHICLE_YELLOW = 10;
const int VEHICLE_RED = 9;
const int PEDESTRIAN_GREEN = 8;
const int BUTTON_PIN = 2;

volatile bool pedestrianRequest = false;
bool crossingInProgress = false;

void setup() {
  // Set LED pins as outputs
  pinMode(VEHICLE_GREEN, OUTPUT);
  pinMode(VEHICLE_YELLOW, OUTPUT);
  pinMode(VEHICLE_RED, OUTPUT);
  pinMode(PEDESTRIAN_GREEN, OUTPUT);

  // Button pin uses internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Attach the external interrupt to Pin 2
  // FALLING means the button goes from HIGH to LOW when pressed
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);

  // Start in the normal default state
  setNormalState();
}

void loop() {
  // If the button interrupt set the request flag, start the pedestrian crossing
  if (pedestrianRequest && !crossingInProgress) {
    pedestrianRequest = false;
    handlePedestrianCrossing();
  }

  // Keep the system in normal operation when no request is active
  setNormalState();
}

// Interrupt Service Routine (ISR)
// This function must be short and fast because it is called immediately by hardware.
void buttonISR() {
  pedestrianRequest = true;
}

void handlePedestrianCrossing() {
  crossingInProgress = true;

  // Step 1: Vehicle Green -> OFF
  digitalWrite(VEHICLE_GREEN, LOW);

  // Step 2: Vehicle Yellow -> ON for 2 seconds
  digitalWrite(VEHICLE_YELLOW, HIGH);
  delay(2000);

  // Step 3: Vehicle Yellow -> OFF
  digitalWrite(VEHICLE_YELLOW, LOW);

  // Step 4: Vehicle Red -> ON
  digitalWrite(VEHICLE_RED, HIGH);

  // Step 5: Pedestrian Green -> ON for 5 seconds
  digitalWrite(PEDESTRIAN_GREEN, HIGH);
  delay(5000);

  // Step 6: Pedestrian Green -> OFF
  digitalWrite(PEDESTRIAN_GREEN, LOW);

  // Step 7: Vehicle Red -> OFF
  digitalWrite(VEHICLE_RED, LOW);

  // Step 8: Return to normal traffic flow
  setNormalState();

  crossingInProgress = false;
}

void setNormalState() {
  // Default state required by the assignment:
  // Vehicle Green = ON
  // Vehicle Yellow = OFF
  // Vehicle Red = OFF
  // Pedestrian Green = OFF
  digitalWrite(VEHICLE_GREEN, HIGH);
  digitalWrite(VEHICLE_YELLOW, LOW);
  digitalWrite(VEHICLE_RED, LOW);
  digitalWrite(PEDESTRIAN_GREEN, LOW);
}
