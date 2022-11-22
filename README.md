<p align="center">
  <img src="Arduino.png" >
</p>

# Temperature-monitoring-with-arduino
In this project the aim was to develop a low cost temperature monitoring system with calibration by an arduino system. Such system have a 4x4 keypad, three push buttons, a temperature sensor (TMP36), and an arduino uno.

The keypad was added to insert the number of points for calibration and entering the values of temperature from a standard reference. Thus another reference must be used to calibrate the system.

The buttons are used in this equipment to trigger the calibration, monitor the highest value written, and clean such highest value written. If you push the calibration button once, you will activate the calibration mode. When you finish the calibration, push the calibration button again to get out from calibration mode. Then the measurements will start. Pushing once the highest value button, the showed values will be related only with highest temperature. Another push will turn to current measurment. In case to erase the highest measurment, you only have to push the reset button. Such reset button only works when the highest value mode is on.
