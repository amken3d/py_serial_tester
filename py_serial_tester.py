import serial
import time
import random

def open_serial_connection(port, baud_rate, timeout):
    try:
        return serial.Serial(port, baud_rate, timeout=timeout)
    except serial.SerialException as e:
        print(f"Failed to open serial port {port}: {str(e)}")
        return None

def calculate_checksum(data_bytes):
    return sum(data_bytes) & 0xFF

def send_random_data_with_checksum(serial_port):
    # Generate random data
    data = [random.randint(0, 255) for _ in range(10)]  # For example, 10 random bytes
    data_bytes = bytes(data)
    # Calculate checksum
    checksum = calculate_checksum(data_bytes)
    # Send data with checksum
    try:
        serial_port.write(data_bytes + bytes([checksum]))
        print("Sent:", data_bytes.hex(), "Checksum:", format(checksum, '02x'))
    except serial.SerialException as e:
        print("Error sending data:", str(e))

def receive_data(serial_port):
    try:
        while serial_port.in_waiting > 0:
            received_data = serial_port.read(serial_port.in_waiting).decode()
            print("Received:", received_data)
    except serial.SerialException as e:
        print("Error receiving data:", str(e))

def main():
    serial_port = open_serial_connection('/dev/ttyAMA0', 115200, timeout=1)
    if not serial_port:
        return  # Exit if serial port couldn't be opened

    try:
        while True:
            send_random_data_with_checksum(serial_port)
            time.sleep(1)  # Allow time for data to be sent and for a response
            receive_data(serial_port)
            time.sleep(2)  # Delay before next send
    finally:
        serial_port.close()

if __name__ == "__main__":
    main()
