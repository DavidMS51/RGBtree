# gently modulating xmas tree lights
# Author: David Saul  2016
# based on the work of Tony DiCola (tony@tonydicola.com)
#
# you will need to install rpi_ws281x for this application to run
# you can find the instructions for this in a number of places including the Adafruit site

import time
from time import sleep
from neopixel import *
import random

# Here we import the Python's colorsys module which will help us convert HSV values into RGB.

import colorsys


# LED strip configuration:
LED_COUNT      = 6      # Number of LED pixels.
LED_PIN        = 18      # GPIO pin connected to the pixels (must support PWM!).
LED_FREQ_HZ    = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA        = 5       # DMA channel to use for generating signal (try 5)
LED_BRIGHTNESS = 100     # Set to 0 for darkest and 255 for brightest
LED_INVERT     = False   # True to invert the signal (when using NPN transistor level shift)

def all_leds_off():
    # set all 6 LEDs to black (i.e. off).
    for i in range(6):
        led.setPixelColorRGB(i,0,0,0)
    led.show()


# Main program logic follows:
if __name__ == '__main__':
	# Create NeoPixel object with appropriate configuration.
	led = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS)
	# Intialize the library (must be called once before other functions).
	led.begin()

	
	print ('Press Ctrl-C to quit.')
	all_leds_off()

 #       led.setPixelColor(1,16711935)
#	led.show()
#	sleep(10)

	ledb = [0,0,0,0,0,0]
	rand = random.randint(0,5)
	randt = rand
	randst = random.randint(1,999)
	randstt = randst

	# setup initial start points for each led and display them
	for i in range(0,6):
		ledb[i] = random.randint(1,999)		#setup random colours as starting point
		print "led",i,ledb[i]

		# display starting colours
		color = colorsys.hsv_to_rgb(ledb[i]/1000.0, 1.0, 1.0)

                r = int(color[0]*255)
                g = int(color[1]*255)
                b = int(color[2]*255)
                sleep(.05)
                led.setPixelColorRGB(i,r,g,b)
                led.show()


	while True:
		while rand == randt:			#select a led randomly
			rand = random.randint(0,5)	# avoiding repreats	
			
		randt = rand

		while randst == randstt:		#select a colour finish point randomly
			randst = random.randint(1,999)	# avoiding repreats
		randstt = randst
		
		i = ledb[rand]				#setup correct start point

		print "led = ",rand,"start = ", i , "finish =",randst
		
		ledb[rand] = randst			#make next start point current finish point

		while i != randst:			#smoothly run through colours, for selected LED

        		color = colorsys.hsv_to_rgb(i/1000.0, 1.0, 1.0)
        
			r = int(color[0]*255)
			g = int(color[1]*255)
			b = int(color[2]*255)
			sleep(.05)
			led.setPixelColorRGB(rand,r,g,b)
			led.show()
			i = i + 1
			if i == 1000:
				i=1
