# Automatic Water Dispenser with Arduino

[![Assembly](https://img.shields.io/badge/language-C++-purple.svg)](https://es.wikipedia.org/wiki/C++)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![University: UPT](https://img.shields.io/badge/University-Politehnica%20Timisoara-red.svg)](https://www.upt.ro/)
[![Status: Academic](https://img.shields.io/badge/Status-Academic%20Project-success.svg)](https://github.com/mijay6/Automatic-Water-Dispenser-with-Arduino)
[![Version](https://img.shields.io/badge/Version-1.0.0-brightgreen.svg) ](https://github.com/mijay6/Automatic-Water-Dispenser-with-Arduino/releases) 

## Description
This project presents the design and implementation of an automatic water dispenser using Arduino. The system offers an efficient, hygienic, and precise solution for controlled water dispensing into containers, eliminating the need to manually pour water and reducing waste by preventing overflow.

![Prototype of the Water Dispenser](docs/media/images/IMG_20230527_203134.jpg)

# System Components
- Arduino board (central control system)
- Ultrasonic sensors (3×):
    - Water level detection in reservoir
    - Container presence detection
    - Container fill level detection
- Water pump with relay control
- LCD display for user interface
- LED indicators (red and green)
- Buzzer for audio feedback
- Power supply for pump and electronics

# Software Architecture
The water dispenser software was developed in Arduino language, providing an interface between components and precise control of functionality. Main functions include:

- Measuring water level in the reservoir using ultrasonic sensor data
- Detecting container presence and determining its capacity
- Controlling the water pump for controlled container filling
- Displaying fill status via LED indicators and LCD display

# Code
The main control code is available in [src](src/) directory

## Online Simulation
Try the system online via Wokwi Simulator:  
[Open Simulation on Wokwi](https://wokwi.com/projects/363978666759620609)

## Documentation
- [Original Documentation (Romanian)](docs/Project_Documentation_RO.pdf)
- [Components and BOM](docs/Project_Components_and_BOM.pdf)

# Future Improvements
- Advanced user interface with touch screen
- Mobile app for remote control
- Automatic container size recognition
- Water quality monitoring

## Authors
- @danyel513
- @Mihai Dobra
  
Politehnica University of Timișoara  
Faculty of Automation and Computer Science  
Electronic devices and measurements   
Academic Year 2022-2023

## Contributing
Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct and the process for submitting pull requests.
