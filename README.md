# star_fader
## Why
The winter is long and dark in scandinavia, an automatic slow fading of lights is sometimes needed
This code is used to fade on and fade off an IKEA LEDberg (modified with a transistor  drive step)

## About
Connect a pwm output from a Raspberry PI to a mqtt network.
```
accept commands on topic /starfader/ 
   fade ON/OFF <int>
   dutycycle   <uint>
   status

replies
    topic /starfader_status/
    current output %
```
## compiling and install
qmake
make

sudo ./starfader

Program must run as root as it uses /dev/mem to access PWM module in raspberry pi hardware.
