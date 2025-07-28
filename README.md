# Early-Detection-of-Costal-Hazards-by-Using-Embedded-Systems
This project aims to develop a low-cost, IoT-enabled coastal hazard detection system designed to protect vulnerable communities from natural disasters such as tsunamis, storm surges, and extreme weather events. Built using the NodeMCU microcontroller, the system integrates multiple environmental sensors and communication modules to enable real-time monitoring and early warning alerts.

On the transmitter side:
                        ADXL335 for motion/vibration detection (e.g., early tsunami or land movement signals),
                        DHT22 for temperature and humidity monitoring,
                        BMP180 for atmospheric pressure and altitude tracking.

On the receiver side:
                    A GSM module for sending SMS alerts to authorities and community members,
                    A buzzer for immediate local audio alerts.
                                  
Sensor data is transmitted via WiFi to the ThingSpeak cloud platform for real-time visualization and trend analysis. The system continuously monitors temperature, humidity, pressure, and altitude levels. If any of these parameters exceed safe thresholds, the system automatically triggers a buzzer alert and sends SMS warnings to ensure rapid awareness and response.

This dual-alert mechanism—local (buzzer) and remote (SMS)—ensures immediate communication of potential hazards. By analyzing these environmental conditions, the setup can detect early warning signs of coastal threats and help initiate timely preventive actions.


OUTPUT:
[WATCH THIS CONNECTIONS](./Videooutput.mp4)
![op1](https://github.com/user-attachments/assets/10ca62cd-6b77-4465-b62f-d3ce1080e44c)
![op2](https://github.com/user-attachments/assets/2b0f27d3-4512-479a-a40d-955eb82ab29d)
![smsop](https://github.com/user-attachments/assets/3c61bef9-d6e2-4a73-a348-54048bb0a354)

