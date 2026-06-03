# Day 2 – Digital I/O, Serial Debug & Relay Safety

## Objective

Build a debounced push-button input system, LED output control, Serial Monitor debugging workflow, and safe relay-based solenoid valve control using Arduino Uno.

---

## Tasks Completed

### 1. Button LED Toggle

* Push button connected to Arduino digital input.
* Software debounce implemented to eliminate false triggers.
* LED state toggles on each valid button press.

### 2. Serial Debugging

* Serial Monitor used for:

  * Button state monitoring
  * LED status messages
  * Relay activation logs
  * Troubleshooting input/output behavior

### 3. Relay Controlled Solenoid Valve

* Solenoid valve powered through a relay module.
* Arduino GPIO controls relay input only.
* External power source used for valve operation.
* No direct GPIO-to-solenoid connection.

### 4. Safety Documentation

* Relay wiring inspected before power-up.
* Solenoid current requirements verified.
* Supervisor sign-off recorded in `docs/SAFETY.md`.

---

## Repository Structure

```text
arduino-internship/
│
├── sketches/
│   ├── button_led/
│   │   ├── button_led.ino
│   │   └── README.md
│   │
│   └── relay_valve/
│       ├── relay_valve.ino
│       └── README.md
│
├── docs/
│   ├── DEBUGGING.md
│   ├── SAFETY.md
│   └── HARDWARE.md
│
├── wiring-images/
│   ├── button_led.jpg
│   └── relay_valve.jpg
│
└── .gitignore
```

---

## Hardware Used

* Arduino Uno
* Breadboard
* Push Button
* LED
* 220 Ω Resistor
* 2-Channel Relay Module
* Solenoid Valve
* Jumper Wires
* External Power Supply

---

## Wiring Overview

### Button + LED

| Component | Arduino Pin |
| --------- | ----------- |
| Button    | D2          |
| LED       | D13         |

### Relay + Solenoid

| Component | Arduino Pin |
| --------- | ----------- |
| Relay IN1 | D8          |
| Relay VCC | 5V          |
| Relay GND | GND         |

The solenoid valve is connected through the relay contacts and powered using an external supply.

---

## Files Submitted

* `button_led/button_led.ino`
* `relay_valve/relay_valve.ino`
* `docs/DEBUGGING.md`
* `docs/SAFETY.md`
* Wiring photographs in `wiring-images/`

---

## Learning Outcomes

* Implemented software debounce for reliable button input.
* Used Serial Monitor for debugging embedded applications.
* Practiced safe relay interfacing techniques.
* Learned proper Git repository organization for Arduino projects.
* Documented hardware, wiring, and safety procedures.

---

## Git Commit Example

```bash
git add .
git commit -m "Day 2: Added button LED toggle and relay valve control"
```

---

## Status

✅ Task Completed

**Tutorial Reference:** Days 3–4 · Task 2
