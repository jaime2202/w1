Washer Machine Remote Monitoring 2016/17

This project has been developed for being able to use an Adafruit Huzzah Microcontroller along with an 3-axis accelerometer 

I developed this after being frustrated with living in the fourth floor of my university dorm room and going downstairs to realize that my laundry had not finished only

The way it functions is by taking readings from the LIS3DH Accelerometer Module during a set interval of measure

After the entire wash cycle has completed the board will compare the data to previous measurments and determine if it is done

Once the Microcontroller has determined that the wash is done it will transmit to the io.adafruit website where there is a feed that monitors the output of the board

The method I decided to go with notifying the user that the laundry is done is by integrating an IFTTT applet that monitor that feed and from there an array of things can be triggered to notify the user such as sms message, google/apple calendar integration




