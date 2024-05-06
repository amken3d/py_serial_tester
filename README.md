# Py Serial Tester
This software project allows the connection check between a Raspberry Pi and a RP2040. It uses the defined pins for TX and RX and communicates via UART protocol.

### Installing on Raspberry Pi and RP2040
- If you are using GPIO0/1 on the rp2040, then just upload the uf2 file in the build folder in bootsel mode (drag and drop)
- Run the python3 py_serial_tester.py 

## System Requirements
- Raspberry Pi device
- RP2040 device
- Pico SDK
- C development environment

## Project Structure
- The main code resides in `main.c` file
- The file includes UART, stdlib, stdio, irq, and hardware for RP2040.

## Setup & Installation
1. Install the Pico SDK on your development system by following the instructions here: https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf
2. Clone or download this repository to your local system.
3. Navigate inside the project's directory using your terminal.



## Building the Project
- To build the project, use the `cmake` build system provided by the Pico SDK.
- A typical procedure might include creating a build subdirectory, navigating into it, and running `cmake ..` followed by `make`
- Refer to offical Pico SDK documentation.

## Running the Program
- Once built, the binary program needs to be transfered to the RP2040. Typically, this requires a reboot of the RP2040 into the bootloader, after which the binary file can be copied onto the RP2040.
- On successful login, the program will run and exchange data between the Raspberry Pi and RP2040

## Py Serial Tester: Python Companion Usage

This project also has a Python companion program that communicates with the RP2040 device. The Python script is used to send data in bytes, including a checksum byte. It also receives data from the connected serial devices.

Here are instructions for running the Python companion:

### Prerequisites
- Python 3.x installed on your Raspberry Pi. You can download it from https://www.python.org/downloads/ or via package manager.
- PySerial module installed. PySerial simplifies the process of reading from and writing to serial interfaces on your Raspberry Pi. Install it using pip:

## Running the Program
In the folder where the py_serial_tester.py is run the command

python3 py_serial_tester.py

## Support
If you have any problems or questions, feel free to create a new issue on the repository and be sure to include as much detail as possible

Happy coding!
