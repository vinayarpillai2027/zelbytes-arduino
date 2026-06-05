# Day 8: DHT22/AM2301 Temperature & Humidity

## Objective
Interface DHT22 sensor for environmental monitoring in polyhouse mushroom cultivation. Read temperature and humidity values with proper error handling and non-blocking code structure.

## Circuit Configuration

### Wiring: DHT22 with 10kΩ Pull-up Resistor

        5V ────────────────────────┬──────────── VCC
                                   │
    Arduino D2 ────────────────────┼──────────── DATA
                                   │
                                 10kΩ
                                   │
    GND ──────────────────────────┴──────────── GND (sensor)

### Pin Connections
| Arduino | DHT22 | Notes |
|---------|-------|-------|
| 5V | VCC (Pin 1) | 3.3-5V compatible |
| D2 | DATA (Pin 2) | Digital pin with pull-up |
| GND | GND (Pin 4) | Common ground |

### Components
| Component | Value | Notes |
|-----------|-------|-------|
| Arduino | Uno | 5V logic |
| Sensor | DHT22/AM2301 | Temperature & Humidity |
| Resistor | 10kΩ | Pull-up on DATA line |
| Breadboard | - | Half-size |
| Jumper Wires | - | Male-Male |

## Sensor Specifications
| Parameter | Range | Accuracy | Resolution |
|-----------|-------|----------|------------|
| Temperature | -40 to 80°C | ±0.5°C | 0.1°C |
| Humidity | 0-100% RH | ±2% RH | 0.1% RH |
| Sampling Rate | 0.5 Hz | - | 2s minimum interval |

## Installation

### Library Setup
1. Open Arduino IDE
2. Tools → Manage Libraries (Ctrl+Shift+I)
3. Search "DHT sensor library" by Adafruit
4. Install latest version (1.4.4+)
5. Also install "Adafruit Unified Sensor" dependency

### Dependencies
- Adafruit DHT Sensor Library (v1.4.4+)
- Adafruit Unified Sensor Library (v1.1.14+)

## Calibration Results
| Test | Condition | Temperature | Humidity | Notes |
|------|-----------|-------------|----------|-------|
| 1 | Room ambient | 25.3°C | 45.2% | Stable reading |
| 2 | Near heat source | 32.1°C | 38.5% | Temp rise, humidity drop |
| 3 | After misting | 24.8°C | 72.4% | Humidity spike observed |

## Sample Output (CSV Format)
| timestamp_ms | temp_c | humidity_pct | heat_index | status |
|--------------|--------|--------------|------------|--------|
| 2000 | 25.3 | 45.2 | 25.1 | OK |
| 4000 | 25.4 | 45.0 | 25.2 | OK |
| 6000 | 25.5 | 44.8 | 25.3 | OK |
| 8000 | 25.3 | 45.1 | 25.1 | OK |
| 10000 | 25.6 | 44.5 | 25.4 | OK |
| 12000 | 32.1 | 38.5 | 33.2 | OK |
| 14000 | 24.8 | 72.4 | 24.9 | SPIKE_DETECTED |

## Error Handling

### Common Errors
| Error | Cause | Solution |
|-------|-------|----------|
| isnan(temp) = true | Bad connection | Check DATA pin wiring |
| Reading timeout | < 2s between reads | Increase delay to 2000ms |
| All values -999 | Pull-up missing | Add 10kΩ between DATA and 5V |
| Stuck at same value | Sensor frozen | Power cycle sensor |

### Error Codes in Code
| Return Value | Meaning |
|--------------|---------|
| -999.0 | Sensor read failed (isnan) |
| -998.0 | Reading too fast (< 2s) |
| -997.0 | Value out of valid range |

## Sensor Placement Guidelines

### ✅ DO
- Place away from direct misting/solenoid spray
- Ensure adequate airflow around sensor
- Mount at crop canopy height (15-20cm above substrate)
- Keep at least 10cm from heat sources
- Use radiation shield if exposed to direct sunlight

### ❌ DON'T
- Place directly in irrigation mist path
- Mount near exhaust fans or vents
- Enclose in sealed container (needs airflow)
- Touch sensor element with bare fingers
- Exceed 2s minimum read interval

## Humidity Spike Documentation
During irrigation events, humidity can spike 20-30% within 30 seconds. These spikes are normal and should be noted for Day 19 capstone integration where solenoid control will factor in post-irrigation humidity recovery time.

## Project Structure
Day8_DHT22/
├── Day8_DHT22.ino              # Main sketch
├── calibration.h               # Sensor calibration constants
├── sample_log.csv              # 30-line sample data log
└── README.md                   # This file

## Usage
1. Install DHT sensor library via Library Manager
2. Wire DHT22 with 10kΩ pull-up resistor on DATA line
3. Upload Day8_DHT22.ino to Arduino Uno
4. Open Serial Monitor at 9600 baud
5. Observe CSV output with temperature and humidity
6. Test by breathing on sensor to see humidity rise

## Sample Code Structure
```cpp
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void loop() {
  static unsigned long lastRead = 0;
  if (millis() - lastRead >= 2000) {
    lastRead = millis();
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    if (!isnan(temp) && !isnan(hum)) {
      Serial.println(String(millis()) + "," + temp + "," + hum);
    }
  }
}
