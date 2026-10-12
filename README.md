# Pedestrian Crossing Traffic Light System

This project implements a pedestrian crossing control system using an Arduino UNO and an external interrupt. The vehicle traffic light remains GREEN by default. When a pedestrian presses the button, an interrupt triggers a safe pedestrian crossing sequence, after which normal traffic flow resumes.

## Project objective

Design and simulate a pedestrian crossing traffic light using Arduino UNO with the following requirements:

- Vehicle Green LED -> Pin 11
- Vehicle Yellow LED -> Pin 10
- Vehicle Red LED -> Pin 9
- Pedestrian Green LED -> Pin 8
- Push button -> Pin 2 (External Interrupt INT0)
- 220Ω resistors for LEDs

## Default state

- Vehicle Green -> ON
- Vehicle Yellow -> OFF
- Vehicle Red -> OFF
- Pedestrian Green -> OFF

## Operation sequence

When the push button is pressed:

1. Vehicle Green -> OFF
2. Vehicle Yellow -> ON for 2 seconds
3. Vehicle Yellow -> OFF
4. Vehicle Red -> ON
5. Pedestrian Green -> ON for 5 seconds
6. Pedestrian Green -> OFF
7. Vehicle Red -> OFF
8. Vehicle Green -> ON again

## Why interrupts are used

Interrupts are used because the system must react immediately when the pedestrian presses the button. Using `attachInterrupt()` means the Arduino does not need to keep checking the button constantly in the main loop. This makes the system more responsive and efficient.

## Hardware connection summary

| Component | Arduino Pin |
|---|---|
| Vehicle Green LED | 11 |
| Vehicle Yellow LED | 10 |
| Vehicle Red LED | 9 |
| Pedestrian Green LED | 8 |
| Button | 2 |

### Wiring notes

- Connect each LED to a 220Ω resistor.
- Connect the button between Pin 2 and GND.
- Use the Arduino's internal pull-up resistor (`INPUT_PULLUP`) to simplify the button connection.
- Keep all grounds connected together.

## Code explanation

### 1. Pin setup
The code assigns each LED and the button to the required Arduino pins so the hardware matches the design.

### 2. `setup()`
- Configures the LEDs as outputs
- Configures the button as `INPUT_PULLUP`
- Attaches the interrupt to Pin 2 using `attachInterrupt()`
- Calls `setNormalState()` to ensure the default green light is active when the program starts

### 3. `loop()`
The main loop checks whether the interrupt flag was set. When the pedestrian button is pressed, the loop runs the pedestrian crossing sequence and then resets the system to normal traffic flow.

### 4. `buttonISR()`
This is the Interrupt Service Routine (ISR). It fires immediately when the button is pressed. It is kept short and fast to comply with correct interrupt handling practice.

### 5. `handlePedestrianCrossing()`
This function controls the traffic sequence and safety logic:
- turns off vehicle green
- waits 2 seconds while yellow is ON
- turns yellow OFF
- turns red ON
- turns pedestrian green ON for 5 seconds
- turns pedestrian green OFF
- turns red OFF
- turns vehicle green ON again

### 6. `setNormalState()`
This ensures that when the system is idle, the normal state is:
- vehicle green ON
- vehicle yellow OFF
- vehicle red OFF
- pedestrian green OFF

## Safety logic

This design is safe because:
- vehicles are stopped before pedestrians are allowed to cross
- the yellow warning phase happens before switching to red
- the pedestrian green light appears only after the vehicle red light is ON
- the system returns to green only after the crossing is complete

## Wokwi simulation steps

1. Open Wokwi.
2. Create a new Arduino UNO simulation.
3. Add:
   - Arduino UNO
   - 4 LEDs
   - 4 × 220Ω resistors
   - 1 push button
4. Connect the components according to the pin map above.
5. Copy the code from `pedestrian_crossing_traffic_light.ino` into the Wokwi editor.
6. Run the simulation and press the button to trigger the pedestrian crossing sequence.

## Expected output

- Default state: vehicle green ON
- Button press triggers the interrupt
- Vehicle green turns OFF
- Vehicle yellow ON for 2 seconds
- Vehicle red ON
- Pedestrian green ON for 5 seconds
- Return to vehicle green

## Arduino code

```cpp
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
```

## Summary

This project demonstrates understanding of:
- external interrupts in Arduino
- synchronization between main code and ISR
- safe traffic light transitions
- real-world control logic for pedestrian crossings

It has been designed to meet the assignment requirements for a pedestrian crossing traffic light and can be simulated successfully in Wokwi.
