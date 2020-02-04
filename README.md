# teensy_comms_for_mihir
Teensy comms using EasyTransfer

## How this works...

This works using the EasyTransfer library. Easy transfer objects are created for each channel of communications (individual objects for in and out). The paired receive and send structs **must be identical**.

## How to personalize this...

At the top of each ino file, define statements are used to disambiguate serial ports. To change what serial ports are used, change the define statements. 

To change the data structs, change the struct definition in each ino file. **MAKE CERTAIN THAT THE PAIRED STRUCTS BETWEEN BOARDS ARE IDENTICAL**.

## Debugging Stuff

I included a blinking LED to indicate data being sent and received. I also included a serial print to a laptop connected by USB.
