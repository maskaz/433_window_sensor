# 433mhz/Attiny85 window sensor with tilt sensing


Simple project from unused parts, builded for need to know in what status (open / close / tilt) windows are.


Needed parts:

1. Attiny85
2. 433mhz transmitter  (im using fs1000a)
3. two reed switches
4. two magnets
5. enclosure
6. batteries


Two reed switchs are located on not moving part of the window.
Upper reed switch is connected to Attiny85 interrupt pin. When it state will change,  Attiny85 will be awakened  from deep sleep,  will check
state on interrupt pin and pin connected to lower reed switch.

Depending on state those two reed switches,Attiny will send send signal that can be interpreted by Home assistant.

Libraries and additional software:

For RPI:

Because HA support for GPIO 433hz receivers is deprecated (on Raspberry Pi) important part of this project is this code:
https://github.com/Josar/RandomStuff/tree/master/Openhab-related?fbclid=IwAR34MRh7sx63tUwFGPHkGMdJ2-DRiPM5PgSixv8ITbYxMqI8azxpJqheVak

Receives codes from 433mhz receiver and sends to mqtt.

For Attiny85:

https://github.com/sui77/rc-switch



Ad.1. SPST Reed switches needs to be pulled up by 4.7k resistors, so it will reduce a bit batteries life.
      If you will find small SPDT type,use it.


