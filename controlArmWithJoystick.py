"""
Use the python inputs library and the Serial library to read inputs from a joystick
and send the inputs to the robot arm.
"""
from inputs import devices
from inputs import get_gamepad
import serial
import time

ROTATION_INPUT = 'ABS_RZ'
FRONT_BACK_INPUT = 'ABS_Y'
UP_INPUT = 'BTN_THUMB'
DOWN_INPUT = 'BTN_THUMB2'

HAND_INPUT = 'ABS_THROTTLE' 
HAND_INPUT_MAX = 35
HAND_INPUT_MIN = 185

ser = serial.Serial('/dev/ttyACM0', 9600 )

#This would potentially be wrong if we added more devices.
joystick = devices[0]

def main():
    time_delta = 0.002
    t0 = time.time()
    while( 1 ):
        t1 = time.time()
        if ( t1 - t0 > time_delta ):
            events = get_gamepad()
            for event in events:
                if event.ev_type != 'Sync':
                    if event.code == HAND_INPUT:
                        if event.state < 60:
                            ser.write( '7' )
                        elif event.state > 160:
                            ser.write( '6' )
                        else:
                            pass
                    if event.code == ROTATION_INPUT:
                        if event.state < 100:
                            ser.write( '0' )
                        elif event.state > 135:
                            ser.write( '1' )
                        else:
                            pass
                    if event.code == FRONT_BACK_INPUT:
                        if event.state < 300:
                            ser.write( '5' )
                        elif event.state > 650:
                            ser.write( '4' )
                        else:
                            pass
                    if event.code == UP_INPUT:
                        ser.write( '3' )
                    if event.code == DOWN_INPUT:
                        ser.write( '2' )
            t0 = time.time()

"""
ABS_RZ is rotating the joystick
ABS_X is moving the joystick in the X
ABS_Y is moving the joystick in the Y

ABS_THROTTLE is the trigger. Seems that pressing gives 180, 
releasing gives 181.
"""

if __name__ == "__main__":
    main()
