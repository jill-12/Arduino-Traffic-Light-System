// Traffic Light System with External Interrupts
// Adds emergency mode activation via button press on Pin 2
// Button triggers all lights to blink simultaneously

const int RED = 13;                    // Red LED pin
const int YELLOW = 12;                 // Yellow LED pin
const int GREEN = 11;                  // Green LED pin
const int INTERRUPT_BUTTON = 2;        // External interrupt pin (INT0)

// volatile: ensures variable is updated immediately (used with interrupts)
volatile bool emergencyMode = false;   // Emergency mode flag

void setup() {
  // Set all LED pins as output
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(INTERRUPT_BUTTON, INPUT_PULLUP);  // Button with internal pullup
  
  // Attach interrupt to Pin 2, trigger on FALLING edge (button press)
  // digitalPinToInterrupt(2) converts pin number to interrupt number
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_BUTTON), emergencyInterrupt, FALLING);
  
  // Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("Traffic Light System with Interrupts Started");
  Serial.println("Press button on Pin 2 to activate emergency mode");
}

void loop() {
  // Check if emergency mode is activated
  if (!emergencyMode) {
    normalTraffic();  // Normal operation
  } else {
    emergencyTraffic();  // Emergency blinking
  }
}

// Normal traffic light cycle
void normalTraffic() {
  // GREEN LIGHT - Go!
  setLight(GREEN);
  Serial.println("GREEN - Go!");
  delay(5000);  // 5 seconds

  // YELLOW LIGHT - Caution!
  setLight(YELLOW);
  Serial.println("YELLOW - Caution!");
  delay(2000);  // 2 seconds

  // RED LIGHT - Stop!
  setLight(RED);
  Serial.println("RED - Stop!");
  delay(5000);  // 5 seconds
}

// Emergency mode: all lights blink together
void emergencyTraffic() {
  Serial.println("EMERGENCY MODE - All lights blinking!");
  
  // Blink 10 times (5 full cycles)
  for (int i = 0; i < 10; i++) {
    // Turn all lights ON
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, HIGH);
    delay(200);  // On for 200ms
    
    // Turn all lights OFF
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
    delay(200);  // Off for 200ms
  }
  
  // Exit emergency mode
  emergencyMode = false;
  Serial.println("Emergency mode ended, returning to normal operation");
}

// Helper function to set only one light ON
void setLight(int light) {
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(light, HIGH);
}

// INTERRUPT SERVICE ROUTINE (ISR)
// This function is called immediately when button is pressed
// Keep it short and avoid blocking operations!
void emergencyInterrupt() {
  emergencyMode = true;
  Serial.println("\n*** EMERGENCY BUTTON PRESSED! ***\n");
}
