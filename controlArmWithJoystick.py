"""
Use the python inputs library and the Serial library to read inputs from a joystick
and send the inputs to the robot arm.
"""
from inputs import devices
from inputs import get_gamepad
import serial

def bound_rotation( degree ):
    if degree < 0:
        return 0
    elif degree > 180:
        return 180
    else:
        return degree

ROTATION_INPUT = 'ABS_RZ'

ser = serial.Serial('/dev/ttyACM0', 9600 )

#This would potentially be wrong if we added more devices.
joystick = devices[0]
print(dir(joystick))

def main():
    while(1):
        events = get_gamepad()
        for event in events:
            if event.ev_type != 'Sync':
                if event.code == ROTATION_INPUT:
                    print(event.ev_type, event.code, event.state)
                    rotation_degree = bound_rotation( event.state )
                    ser.write( chr(rotation_degree ) )
                else:
                    print("Bad evt type")
    


def main2():
    import time
    angleIdx = 0
    while(1):
        if angleIdx == 0:
            ser.write( " " )
            angleIdx = 1
        else:
            ser.write( "}" )
            angleIdx = 0
        time.sleep(2)


"""
ABS_RZ is rotating the joystick
ABS_X is moving the joystick in the X
ABS_Y is moving the joystick in the Y

ABS_THROTTLE is the trigger. Seems that pressing gives 180, 
releasing gives 181.
"""

if __name__ == "__main__":
    main2()
