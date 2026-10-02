// Traffic Light System - Basic Version (No Interrupts)
// Simple sequential state cycling: Green → Yellow → Red → repeat
// Perfect for learning Arduino basics

const int RED = 13;        // Red LED pin
const int YELLOW = 12;     // Yellow LED pin
const int GREEN = 11;      // Green LED pin

void setup() {
  // Set all LED pins as output
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
  // Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("Traffic Light System Started");
}

void loop() {
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
  
  // Loop repeats automatically
}

// Helper function to turn on one light and turn off others
void setLight(int light) {
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(light, HIGH);
}
