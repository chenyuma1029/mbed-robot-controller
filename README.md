# Embedded Control Subsystem for Autonomous Vehicle (Mbed OS)

![Language](https://img.shields.io/badge/Language-C++-blue)
![Platform](https://img.shields.io/badge/Platform-Mbed_OS_6-green)
![Hardware](https://img.shields.io/badge/MCU-NXP_LPC1768-orange)

## 📌 Project Overview
This repository contains the **refactored embedded control subsystem** of a distributed autonomous vehicle (dual-core architecture utilizing an NXP LPC1768 and a Raspberry Pi). 

While the broader team project included high-level edge AI and WeChat mini-program interfaces, **the primary objective of this specific repository is to showcase a completely redesigned, object-oriented firmware architecture.** By decoupling the RTOS communication logic from the low-level motor kinematics, the system achieves enterprise-grade maintainability, highly reliable UART synchronization, and low-latency ultrasonic collision avoidance.

## 🎯 Hardware Design & My Contributions
Beyond the firmware architecture, my core contributions to this project also encompassed the custom hardware layer:
- **Custom PCB Design:** Engineered and routed the main logic board integrating an **LM2596** DC-DC step-down voltage regulator and an **L298N** motor driver.
- **Firmware Refactoring:** Stripped the original monolithic codebase and reconstructed it into a modular, object-oriented paradigm.
- **RTOS Concurrency:** Implemented Mbed OS multithreading and hardware interrupts to handle simultaneous ultrasonic ranging and UART data parsing without blocking the main control loop.

## 📁 Refactored System Architecture
The codebase is strictly separated into business logic, communication protocols, and hardware abstraction:

```text
.
├── core/                       # 🧠 Core System Logic
│   └── config.h                # Global hardware instantiation and state variables
├── comm/                       # 📡 Communication & Parsing Layer
│   ├── CommandProcessor.* # OOP-based parser for discrete & multi-parameter commands
│   └── SerialComm.* # Encapsulates RTOS Mailboxes, thread logic, and UART interrupts
├── hardware_libs/              # ⚙️ Hardware Abstraction Layer (External Dependency)
│   ├── MotionControl.* # Kinematics for Mecanum wheel omnidirectional movement
│   ├── StdMotor.* # Standard PWM motor driver
│   └── Ultrasonic.hpp          # Ultrasonic sensor ranging
├── common_libs/                # 🧮 Math Utilities (External Dependency)
│   └── Vector.hpp              # 2D Vector mathematics for trajectory calculation
└── main.cpp                    # 🚀 Minimalist application entry point
```

## ⚙️ Code Authorship & Acknowledgements
To ensure this repository is fully compilable and functional, it includes the Hardware Abstraction Layer (`hardware_libs/` and `common_libs/`). 

- **My Original Work:** The architectural refactoring, custom PCB design, RTOS communication scheduling (`comm/`), the object-oriented command parser (`core/`), and the main entry point (`main.cpp`).
- **External Dependencies:** The low-level PWM motor drivers, Mecanum wheel kinematics, and ultrasonic sensor reading libraries (`hardware_libs/`) were originally developed by my teammate. Full credit for the foundational hardware driving logic goes to the team.

## 🚀 Quick Start
### Prerequisites
- [Mbed Studio](https://os.mbed.com/studio/)
- Target MCU: NXP LPC1768

### Build & Flash
1. Clone this repository to your local machine.
2. Open the directory in Mbed Studio. The `mbed_app.json` and `mbed-os.lib` files will automatically resolve the required Mbed OS 6 dependencies.
3. Connect the LPC1768 via USB.
4. Click **Build and Run** to compile the C++ source and flash the binary to the board.
5. The system will boot and wait for UART instructions (Baud rate: 9600 for Bluetooth, 115200 for RPi).
