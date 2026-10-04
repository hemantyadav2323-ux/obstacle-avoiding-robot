# Obstacle Avoiding Robot (Arduino Simulation)

A simulated obstacle avoiding robot built in Tinkercad Circuits using an Arduino Uno, an ultrasonic distance sensor and an L293D motor driver. The robot drives forward while the path is clear. When an obstacle comes closer than 25 cm, it stops, reverses, turns on the spot and then checks the distance again.

Built as the Tier 2 project of the Devotics Industrial Experience Program.

## Components

- Arduino Uno R3
- Ultrasonic distance sensor (3-pin, GND / 5V / SIG)
- L293D motor driver IC
- 2 x DC motors (left and right wheel)
- Breadboard and jumper wires

## Circuit Diagram

![Circuit diagram](images/circuit.png)

![Schematic view](images/schematic.png)

## Pin Connections

| Arduino Pin | Connected To | Purpose |
|---|---|---|
| 2 | Ultrasonic sensor SIG | Trigger and echo on one pin |
| 4 | L293D pin 15 | Left motor forward |
| 5 | L293D pin 10 | Left motor backward |
| 6 | L293D pin 2 | Right motor forward |
| 7 | L293D pin 7 | Right motor backward |

The sensor's 5V and GND pins go to the 5V and GND rails. L293D power: pins 1, 8, 9 and 16 go to 5V, and pins 4, 5, 12 and 13 go to GND.

## How It Works

The 3-pin sensor uses a single SIG pin. The code sends a short pulse on that pin, then switches the pin to input and measures how long the echo takes to return. The time is converted to centimetres by dividing by 58.

| Distance | State | Motor action |
|---|---|---|
| More than 25 cm | FORWARD | Both motors drive forward |
| 25 cm or less | STOP | Both motors stop for 1 s |
| | REVERSE | Both motors run backward for 1.5 s |
| | TURN | Motors run in opposite directions for 1.5 s (spin in place) |

After the turn, the loop starts again and re-reads the distance. If the way is clear, the robot goes forward. If not, it repeats the sequence.

The current state and the distance are printed to the Serial Monitor at 9600 baud.

## How to Run

1. Open the Tinkercad project (link below) and click Start Simulation.
2. Open the Serial Monitor. It prints the distance and the state.
3. Click the ultrasonic sensor to show the round obstacle, then drag it toward the sensor.
4. Below 25 cm the robot goes through STOP, REVERSE and TURN. Move the obstacle away and it drives forward again.

Tinkercad project: (link to be added)

Code: [obstacle_avoider/obstacle_avoider.ino](obstacle_avoider/obstacle_avoider.ino)

## Possible Improvements

- Mount the sensor on a servo to scan left and right and turn toward the clearer side
- Use PWM on the L293D enable pins to slow down as the obstacle gets closer
- Add a second sensor on each side for wall detection
- Build the hardware version on a real chassis

## Author

Hemant Yadav, 4th year BTech Robotics and Automation, Medicaps University
