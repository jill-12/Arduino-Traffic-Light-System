// Traffic Light System with Timer Interrupt
// Uses Timer1 for precise, non-blocking timing
// More reliable than delay() for production systems
//
// IMPORTANT: Requires TimerOne library
// Install via Arduino IDE: Sketch → Include Library → Manage Libraries
// Search for "TimerOne" and install by Jesse Tane

#include <TimerOne.h>

const int RED = 13;         // Red LED pin
const int YELLOW = 12;      // Yellow LED pin
const int GREEN = 11;       // Green LED pin

// volatile: these variables are modified in interrupt routine
volatile int state = 0;          // 0 = Green, 1 = Yellow, 2 = Red
volatile unsigned long timerCount = 0;  // Count timer interrupts

void setup() {
  // Set all LED pins as output
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
  // Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("Timer Interrupt Traffic Light System Started");
  
  // Initialize Timer1
  // 1000000 microseconds = 1 second
  Timer1.initialize(1000000);
  
  // Attach interrupt function that runs every 1 second
  Timer1.attachInterrupt(timerInterrupt);
}

void loop() {
  // Main loop does very little
  // All work is done in the interrupt routine
  delay(100);  // Just a small delay to prevent watchdog issues
  
  // Optional: You can add other non-blocking tasks here
}

// TIMER INTERRUPT FUNCTION
// Called every 1 second (1000000 microseconds)
// This is where all the timing logic happens
void timerInterrupt() {
  timerCount++;  // Increment counter each second
  
  // State machine logic
  // Transition states based on elapsed time
  
  if (state == 0 && timerCount >= 5) {
    // Green light duration: 5 seconds
    // Time to switch to yellow
    state = 1;
    timerCount = 0;
    Serial.println("Transitioning to YELLOW");
  } 
  else if (state == 1 && timerCount >= 2) {
    // Yellow light duration: 2 seconds
    // Time to switch to red
    state = 2;
    timerCount = 0;
    Serial.println("Transitioning to RED");
  } 
  else if (state == 2 && timerCount >= 5) {
    // Red light duration: 5 seconds
    // Time to switch back to green
    state = 0;
    timerCount = 0;
    Serial.println("Transitioning to GREEN");
  }
  
  // Update LED outputs based on current state
  updateLights();
}

// Update LEDs based on current state
void updateLights() {
  // Turn all lights off first
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  
  // Turn on appropriate light based on state
  if (state == 0) {
    digitalWrite(GREEN, HIGH);
    if (timerCount == 1) Serial.println("GREEN - Go!");  // Print once per state
  } 
  else if (state == 1) {
    digitalWrite(YELLOW, HIGH);
    if (timerCount == 1) Serial.println("YELLOW - Caution!");
  } 
  else if (state == 2) {
    digitalWrite(RED, HIGH);
    if (timerCount == 1) Serial.println("RED - Stop!");
  }
}

// ADVANTAGES OF TIMER INTERRUPT OVER delay():
// ✓ Precise timing (hardware-based, not software)
// ✓ Non-blocking: main loop can do other tasks
// ✓ More reliable for production systems
// ✓ Easier to synchronize multiple devices
// ✓ Better for real-time applications
//
// DISADVANTAGES:
// ✗ More complex code
// ✗ Requires additional library
// ✗ Uses hardware timer (some features unavailable)
