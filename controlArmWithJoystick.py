"""
Use the python inputs library and the Serial library to read inputs from a joystick
and send the inputs to the robot arm.
"""
from inputs import devices
from inputs import get_gamepad
import serial
import time

ROTATION_INPUT = 'ABS_RZ'

ser = serial.Serial('/dev/ttyACM1', 9600 )

#This would potentially be wrong if we added more devices.
joystick = devices[0]

def main():
    log_file = open( "robot_log.txt", "w")
    time_delta = 0.02
    t0 = time.time()
    while( 1 ):
        t1 = time.time()
        if ( t1 - t0 > time_delta ):
            events = get_gamepad()
            for event in events:
                if event.ev_type != 'Sync':
                    if event.code == ROTATION_INPUT:
                        if event.state < 127:
                            log_file.write( '0' )
                            ser.write( '0' )
                        elif event.state > 128:
                            log_file.write( '1' )
                            ser.write( '1' )
                        else:
                            log_file.write( event.state)
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
