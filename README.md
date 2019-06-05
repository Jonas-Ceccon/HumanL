# HumanL
The GitHub of the HL project,
The functional basic program is now done

I'm  currently working on a way to make a tool that will let people easily edit a LED strip or a matrix that is compatible with the adafruit neomatrix library

This is how it works :

1 - The users designs his strip/matrix with a tkinter interface (may change that later)

2 - The informations are written in a .txt file (making it easy to edit wiht my tiny bare hands)

3 - The informations are sent to the arduino via serial port (you'll need an USB cable)

4 - The arduino writes the information on a .txt file

5 - The arduino reads the datas that it wrote and lights the corresponding LEDs in the correspondings colors

