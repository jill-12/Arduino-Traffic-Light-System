# Arduino Traffic Light System

A comprehensive Arduino-based traffic light simulation system with state management, interrupts, and emergency modes. Designed to work with **Wokwi** simulator and real Arduino hardware.

## 📋 Project Overview

This project demonstrates:
- Basic traffic light state cycling (Red → Green → Yellow)
- System interrupts for emergency mode activation
- Timer-based interrupts for precise timing control
- Serial debugging and monitoring
- Real-world traffic light behavior

## 🔧 Hardware Components (for Wokwi or Physical Setup)

### Components List:
- Arduino UNO (or Nano, Mega)
- 3 × LEDs (Red, Yellow, Green)
- 3 × Resistors (220Ω)
- 1 × Push Button (for interrupt-based versions)
- Breadboard
- Jumper wires
- USB cable (for programming)

### Pin Configuration:
```
Red LED      → Arduino Pin 13
Yellow LED   → Arduino Pin 12
Green LED    → Arduino Pin 11
Button       → Arduino Pin 2 (INT0 - External Interrupt)
GND          → Ground Rail
5V           → Power Rail
```

## 🔌 Wiring Diagram

```
┌─────────────────────────────────────┐
│         Arduino UNO                 │
│  ┌──────────────────────────────┐   │
│  │                              │   │
│  │  13 ──────[220Ω]──→ RED LED  │   │
│  │  12 ──────[220Ω]──→ YEL LED  │   │
│  │  11 ──────[220Ω]──→ GRN LED  │   │
│  │   2 ──────BUTTON──→ GND      │   │
│  │ GND ──────────────→ GND Rail │   │
│  │ 5V  ──────────────→ 5V Rail  │   │
│  └──────────────────────────────┘   │
└─────────────────────────────────────┘

All LED anodes connect to 5V through resistors.
All LED cathodes connect to GND.
```

## 📁 Project Files

1. **basic_traffic_light.ino** - Simple version without interrupts
2. **traffic_light_with_interrupts.ino** - External interrupt for emergency mode
3. **traffic_light_timer_interrupt.ino** - Timer-based interrupt version
4. **diagram.txt** - ASCII wiring diagram

## 🚀 Getting Started

### Option 1: Using Wokwi (Simulator)

1. Go to **https://wokwi.com**
2. Click **Create New Project** → Select **Arduino UNO**
3. Copy code from any `.ino` file in this repository
4. Paste into Wokwi editor
5. Add components from the component library:
   - 3 LEDs (Red, Yellow, Green)
   - 3 Resistors (220Ω)
   - 1 Push Button (for interrupt versions)
6. Wire according to the pin configuration above
7. Click **Start Simulation** ▶️

### Option 2: Real Arduino Hardware

1. Download **Arduino IDE** from https://www.arduino.cc/en/software
2. Install it and connect your Arduino via USB
3. Copy code from `.ino` file
4. Paste into Arduino IDE
5. Select **Board** → Arduino UNO
6. Select **Port** → COM port of your Arduino
7. Click **Upload** ⬆️

## 📝 Code Versions Explained

### Version 1: Basic Traffic Light (No Interrupts)
**File:** `basic_traffic_light.ino`

Simplest implementation with sequential state changes:
- Green light: 5 seconds
- Yellow light: 2 seconds
- Red light: 5 seconds
- Repeats indefinitely

**Use case:** Learning basics, simple projects

```cpp
Green → Yellow → Red → repeat
```

---

### Version 2: External Interrupt (Emergency Mode)
**File:** `traffic_light_with_interrupts.ino`

Adds emergency functionality via button press:
- Press button to activate emergency mode
- All lights blink simultaneously
- After 10 blinks, returns to normal operation
- Uses `attachInterrupt()` for real-time response

**Use case:** Emergency vehicles, real-world scenarios

**Key Features:**
- Non-blocking interrupt handling
- `volatile` keyword for variable safety
- `FALLING` edge trigger (button press)

---

### Version 3: Timer Interrupt (Precise Timing)
**File:** `traffic_light_timer_interrupt.ino`

Uses hardware timer for more reliable timing:
- Timer interrupt every 1 second
- State machine approach
- No blocking delays
- More precise timing control

**Use case:** Production systems, multiple lights, synchronized networks

**Requires:** `TimerOne` library (install via Arduino IDE → Sketch → Include Library → Manage Libraries)

## 🎯 Light Duration Table

| Light | Duration | Real-world Usage |
|-------|----------|------------------|
| **Green** | 5 seconds | Allow traffic to proceed |
| **Yellow** | 2 seconds | Warning to drivers |
| **Red** | 5 seconds | Stop all traffic |
| **Emergency Blink** | 2 seconds (all) | Alert mode |

## 📊 State Diagram

```
        ┌─────────┐
        │  GREEN  │
        │ 5 sec   │
        └────┬────┘
             │
             ▼
        ┌─────────┐
        │ YELLOW  │
        │ 2 sec   │
        └────┬────┘
             │
             ▼
        ┌─────────┐
        │  RED    │
        │ 5 sec   │
        └────┬────┘
             │
             └─────→ (repeat)
```

## 🔴 Serial Monitor Output

When running, the Serial Monitor displays:

```
Traffic Light System Started
GREEN - Go!
YELLOW - Caution!
RED - Stop!
GREEN - Go!
...
```

**To view in Arduino IDE:**
1. Tools → Serial Monitor (or Ctrl+Shift+M)
2. Set baud rate to **9600**
3. Watch real-time output

## 🛠️ Installation & Setup

### Arduino IDE Setup:

```bash
# 1. Install Arduino IDE
# Download from: https://www.arduino.cc/en/software

# 2. For Timer Interrupt version only:
# In Arduino IDE:
# Sketch → Include Library → Manage Libraries
# Search: "TimerOne"
# Install by Jesse Tane

# 3. Connect Arduino via USB
# Select board and port
# Upload the sketch
```

## 🚨 Interrupt Concepts

### External Interrupt (Pin 2/3)
```cpp
attachInterrupt(digitalPinToInterrupt(2), functionName, FALLING);
```
- Triggers when button pressed (FALLING = HIGH to LOW)
- Immediately calls `functionName()`
- Use `volatile` for shared variables
- Keep ISR functions short and fast

### Timer Interrupt
```cpp
Timer1.initialize(1000000);  // 1 second
Timer1.attachInterrupt(functionName);
```
- Calls function at fixed intervals
- Better for timing-critical tasks
- More reliable than `delay()`
- Requires TimerOne library

## 💡 Tips & Best Practices

✅ **Do:**
- Use `volatile` for variables changed in ISR
- Keep interrupt functions short
- Use timer interrupts for precise timing
- Test with Serial output for debugging

❌ **Don't:**
- Use `delay()` inside interrupt functions
- Call Serial.print() in timer interrupts (can cause issues)
- Forget to declare `volatile` for shared variables

## 📚 Learning Resources

- [Arduino Interrupts Tutorial](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)
- [Wokwi Simulator](https://wokwi.com)
- [Arduino Pin Mapping](https://www.arduino.cc/en/Reference/AttachInterrupt)
- [Timer Interrupt Library](https://github.com/PaulStoffregen/TimerOne)

## 🔍 Troubleshooting

| Problem | Solution |
|---------|----------|
| LEDs not lighting | Check resistor connections, verify pin numbers |
| Button not working | Confirm pin 2, check pullup resistor |
| Serial not showing | Set baud rate to 9600 in Serial Monitor |
| Upload fails | Verify COM port and board selection |
| Timing inaccurate | Use timer interrupt version instead of delays |

## 📞 Support

For issues or questions:
1. Check the troubleshooting section
2. Review the comments in the `.ino` files
3. Test on Wokwi first before real hardware

## 📄 License

Open source - Feel free to modify and use for educational purposes.

## 🎓 Educational Value

This project teaches:
- Arduino programming basics
- Digital I/O (input/output)
- Interrupts and ISR (Interrupt Service Routines)
- Timer-based programming
- State machines
- Serial communication
- Circuit design and breadboarding

---

**Happy coding! 🚦**
