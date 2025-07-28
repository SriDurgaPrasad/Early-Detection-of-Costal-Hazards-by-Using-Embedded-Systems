# Early-Detection-of-Costal-Hazards-by-Using-Embedded-Systems
This project aims to develop a low-cost, IoT-enabled coastal hazard detection system designed to protect vulnerable communities from natural disasters such as tsunamis, storm surges, and extreme weather events. Built using the NodeMCU microcontroller, the system integrates multiple environmental sensors and communication modules to enable real-time monitoring and early warning alerts.

On the transmitter side:
ADXL335 for motion/vibration detection (e.g., early tsunami or land movement signals),
DHT22 for temperature and humidity monitoring,
BMP180 for atmospheric pressure tracking.

The receiver side includes:
A GSM module for sending SMS alerts to authorities and community members,
A buzzer for immediate local alerts.

Sensor data is transmitted via WiFi to the ThingSpeak cloud platform for real-time visualization and trend analysis. The system supports a dual-alert mechanism—local (buzzer) and remote (SMS)—to ensure prompt awareness in case of anomalies. By analyzing environmental patterns, the setup can detect early warning signs of coastal hazards and initiate preventive actions.
