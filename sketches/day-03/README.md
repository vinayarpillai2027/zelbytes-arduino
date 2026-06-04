
# Day 3 - Digital I/O: LEDs, Buttons and Debouncing

## Objective

Learn how to interface digital input and output devices using an Arduino Uno by controlling an LED with a push button and implementing software debouncing to ensure reliable button presses.

---

## Concepts Learned

* Digital Input and Output
* LED polarity and current limiting
* Current-limiting resistor
* Push button operation
* Internal pull-up resistors
* Active-low logic
* Contact bounce
* Software debouncing
* Non-blocking timing using `millis()`
* Serial monitoring for debugging

---

## Components Used

* Arduino Uno R3
* Breadboard
* LED
* 220 Ω Resistor
* Push Button (Tactile Switch)
* Jumper Wires
* USB Cable

---

## Circuit Connections

### LED Connection

| Component       | Connection                            |
| --------------- | ------------------------------------- |
| LED Anode (+)   | Arduino Pin 13 through 220 Ω resistor |
| LED Cathode (-) | GND                                   |

### Button Connection

| Component    | Connection    |
| ------------ | ------------- |
| Button Pin 1 | Arduino Pin 2 |
| Button Pin 2 | GND           |

The button uses Arduino's internal pull-up resistor (`INPUT_PULLUP`), so no external resistor is required.

---

## Program Description

The sketch continuously monitors the push button state.

When a valid button press is detected:

* The button state is debounced using a timer based on `millis()`.
* The LED toggles between ON and OFF.
* A message is printed to the Serial Monitor.
* Multiple false triggers caused by mechanical switch bounce are ignored.

---

## Debouncing Method

Mechanical push buttons do not switch cleanly and can generate multiple rapid ON/OFF transitions during a single press.

To solve this problem:

1. The button state is monitored continuously.
2. A debounce timer is started whenever a change is detected.
3. The new state is accepted only if it remains stable for 50 milliseconds.

This ensures one physical button press results in only one action.

---

## Expected Output

### LED Behavior

* First button press → LED ON
* Second button press → LED OFF
* Third button press → LED ON
* Continues toggling with each valid press

### Serial Monitor Output

```text
Toggle
Toggle
Toggle
```

One message should appear for each deliberate button press.

---

## Files

```text
day-03-debounce.ino
README.md
wiring-images/day-03.jpg
```

---

## Configuration

Pin assignments are documented in:

```text
shared/config.h
```

Example:

```cpp
#define LED_STATUS 13
#define BTN_MANUAL 2
```

---

## Learning Outcomes

By completing this task, I learned:

* How to wire an external LED safely using a resistor.
* How to read digital inputs from a push button.
* How internal pull-up resistors work.
* Why active-low logic is commonly used in embedded systems.
* How contact bounce affects button readings.
* How to implement non-blocking software debouncing using `millis()`.
* How to debug digital circuits using the Serial Monitor.

---

## Verification Checklist

* [x] LED wired correctly with current-limiting resistor
* [x] Button connected using `INPUT_PULLUP` configuration
* [x] Debouncing implemented using `millis()`
* [x] LED toggles correctly on button press
* [x] Serial Monitor displays one message per press
* [x] Pin assignments documented in `config.h`
* [x] Wiring photo saved in `wiring-images/day-03.jpg`
* [x] Sketch committed to branch `day-03-debounce`

---

## Status

✅ Completed
