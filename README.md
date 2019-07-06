# SensorApp

The application was created for the sensor Bosch XDK 110, using XDK Workbench and Eclipse Mita.

In order to run the application, the following should be done:
1) it should be imported into XDK Workbench, in order to
- generate all the needed files
- be able to flash it to a connected sensor

2) in the file application.mita, in the function "wireless" the values below should be replaced:
- "ssid" should be set to the value of the wireless network to which the sensor can connect
- "psk" (used for creating "authentication") should be the value of the password for the network that will be used
