# star_fader
## About
Connect a pwm output from a Raspberry PI to a mqtt network.
accept commands on topic /starfader/ 
   fade ON/OFF <int>
   dutycycle <uint>
   status

replies
  topic /starfader_status/
  current output %

## compiling and install
qmake
make

sudo ./starfader

Program must run as root as it uses /dev/mem to access PWM module in raspberry pi hardware.
