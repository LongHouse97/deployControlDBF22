# deployControlDBF22
Code for the deployment controller of the joanneum Aeronautics AIAA DBF 22 aircraft.

## Flashing Code:
```
avrdude -c usbasp -p atmega8u2 -U flash:w:deploycontrol.hex
```