# Day 7: LDR Calibration

## Objective
Understanding LDR value generation using voltage divider circuit and calibrating light thresholds for the polyhouse monitoring system.

## Circuit Configuration

### Wiring: LDR to 5V, 10kΩ to GND (Pull-Down)

        5V
        │
    ┌───┴───┐
    │  LDR  │  
    └───┬───┘
        │
        ├────── A0
        │
    ┌───┴───┐
    │ 10kΩ  │  
    └───┬───┘
        │
       GND

### Components
| Component | Value | Notes |
|-----------|-------|-------|
| Arduino | Uno | 10-bit ADC |
| LDR | GL5528 | Photoresistor |
| Resistor | 10kΩ | Brown-Black-Orange |
| Breadboard | - | Half-size |
| Jumper Wires | - | Male-Male |

## Calibration Results
| Test | Condition | Method | Raw ADC |
|------|-----------|--------|---------|
| 1 | Pitch Dark | Covered with black tape + cup | **0** |
| 2 | Ambient | Normal room fluorescent light | **818** |
| 3 | Bright | Phone flashlight at 5cm | **986** |

## Light Threshold Bands
| Condition | ADC Range | Description |
|-----------|-----------|-------------|
| Pitch Dark | 0 - 100 | Completely covered, no light |
| Dark | 101 - 400 | Very dim, hand shadow |
| Dim | 401 - 700 | Indirect light, under table |
| Ambient | 701 - 900 | Normal room lighting |
| Bright | 901 - 1023 | Direct flashlight/sunlight |

## How It Works

### Why 0 when covered?
LDR in dark → High resistance (~1MΩ)
Voltage divider: Most voltage drops across LDR
A0 reads: ~0V → ADC value: 0

### Why 818 in room light?
LDR in ambient light → Medium resistance (~2.5kΩ)
Voltage divider: Voltage splits between LDR and 10kΩ
A0 reads: ~4V → ADC value: 818

### Why 986 with flashlight?
LDR in bright light → Low resistance (~400Ω)
Voltage divider: Most voltage drops across 10kΩ
A0 reads: ~4.8V → ADC value: 986

## Key Takeaways
- **Inverted behavior:** Low ADC = Dark, High ADC = Bright
- **LDR resistance decreases** as light intensity increases
- **Voltage divider formula:** Vout = Vin * Rfixed / (Rldr + Rfixed)
- **ADC conversion:** ADC = (Vout / Vref) * 1023

## Project Structure
Day7_LDR_Calibration/
├── Day7_LDR_Calibration.ino    # Main sketch
├── calibration.h               # Calibration constants
└── README.md                   # This file

## Usage
1. Upload Day7_LDR_Calibration.ino to Arduino Uno
2. Open Serial Monitor at 9600 baud
3. Cover/uncover LDR to observe value changes
4. Compare readings against calibration table

## Date
2026-06-05


