# ESPStop

ESPStop is a low-cost software Emergency Stop button based on the ESP32. It is designed to be used in combination with any hardware connected to a wireless network. Requiring only a simple UDP server in the target software, the ESPStop can be easily integrated into many existing frameworks. Connect to your ROS creations and have a wireless kill switch to use while prototyping!

## Configuration

Configured over BLE using the BleepingProtocol, the device will connect to a given WiFi network and begin sending UDP packets to the destination device.

## States

Once connected to a WiFi network, the device will operate in the following states:

- Active
  - Sending [OK] packets
- Armed
  - Device is Stopped
  - Button is not pressed
- Stopped
  - Device is Stopped
  - Button is pressed

## Notice

ESPStop is provided as-is an offers no guarentees.

This software should never be used where human safety may be at risk.

It is ultimately up to the designer and operator to maintain a safe working environment.

