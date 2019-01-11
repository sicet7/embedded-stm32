# Application Documentation
## Functioning
<sup>subject to change</sup>  
  
 This Application is a sensor display.  
 The Applicaton has 4 touch buttons in the top of the display that will be the main way that the user interacts with the device.  
 Each button will change the page to a given sensor's output.

 The touch button in the top left of the devices screen, will change to the Temperature Sensors output.

 The 2nd touch button from the left, will change to the Light Sensor's output.

 The 3rd touch button from the left, will change to the Sound Sensor's output.

 The 4th touch button from the left, will change to a screen displaying static text.

## TODO's
1) Make the touch detection and sensor reading happen on seperate threads.
2) Make Better text output.
3) Split Display class functionallities into smaller more manageable classes.
4) Make the application remember what sensor output was on when the power to the device was cut (write to memory card). 
5) Make use of the Temperature & Humidity sensor instead of the Temperature sensor.
6) Make the Convert class method's take an optional "size" argument to make it possible to avoid pointer overflow's
## Problems
1) Currently the touch is not very responsive because it has to wait for the Sensor ouput to be read and processed before running the next loop iteration.
2) Currently the output from the sound sensor when converted to decibel is not correct.
3) Currently the output from the Light sensor is not formated to any kind of valid unit.
### Predicted
1) The Application class will have to take into account multible thread access(thread safe) when the code if mad multi-threaded.
2) The Application will need to take into account the problem with having multible thread and then still process interupts correctly (this was mentioned by mbed developers as not being handled by the mbed library).