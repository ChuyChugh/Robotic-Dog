#include <math.h>
#include <ODriveArduino.h>
#include "ODrive.h"

template<class T> inline Print& operator <<(Print& obj, T arg){ 
    obj.print(arg);   
    return obj; 
}

template<> inline Print& operator <<(Print& obj, float arg){ 
    obj.print(arg, 4); 
    return obj; 
}
Dog::Dog(ODriveArduino frontLeft, ODriveArduino frontRight, ODriveArduino backLeft, ODriveArduino backRight):
    fL(frontLeft),
    fR(frontRight),
    bL(backLeft),
    bR(backRight),
    speed(Speed::MEDIUM),
    direction(Direction::FORWARD){}

double axis::set_axis0(double x, double y){
    double numerator = square(l1)+square(x) +square(y)-square(l2), denominator = 2 * l1 * hypot(x,y), result = 0;
    double* n_pointer = &numerator, *d_pointer = &denominator;
    result = (acos(x/hypot(x,y)) - acos(numerator/denominator))/2/PI * encoder_cpr * ratio;
    delete n_pointer;
    delete d_pointer;
    return result;
}
double axis::set_axis1(double x, double y){
    double numerator = square(l1)-square(x) -square(y)+square(l2), denominator = 2 * l1 * l2, result = 0;
    double* n_pointer = &numerator, *d_pointer = &denominator;
    result = PI/2 - acos((*n_pointer)/(*d_pointer)) /2/PI * encoder_cpr * ratio;
    delete n_pointer;
    delete d_pointer;
    return result;
}
void Dog::walk_indefinitely(double increment){

    fR.SetPosition(0,axis::set_axis0(x_offset+increment/2.0,y_offset-6.35), 15);
    fR.SetPosition(1,axis::set_axis1(x_offset+increment/2.0,y_offset-6.35), 15);
    bL.SetPosition(0,axis::set_axis0(x_offset-increment/2.0,y_offset-6.35), 15);
    bL.SetPosition(1,axis::set_axis1(x_offset-increment/2.0,y_offset-6.35), 15);
    delay(150);

    fR.SetPosition(0,axis::set_axis0(x_offset+increment/2.0,y_offset), 15);
    fR.SetPosition(1,axis::set_axis1(x_offset+increment/2.0,y_offset), 15);
    bL.SetPosition(0,axis::set_axis0(x_offset-increment/2.0,y_offset), 15);
    bL.SetPosition(1,axis::set_axis1(x_offset-increment/2.0,y_offset), 15);
    delay(150);

    while(true){
        bR.SetPosition(0,axis::set_axis0(x_offset+increment,y_offset-6.35), 15);
        bR.SetPosition(1,axis::set_axis1(x_offset+increment,y_offset-6.35), 15);
        fL.SetPosition(0,axis::set_axis0(x_offset-increment,y_offset-6.35), 15);
        fL.SetPosition(1,axis::set_axis1(x_offset-increment/2.0,y_offset-6.35), 15);
        delay(150);

        bR.SetPosition(0,axis::set_axis0(x_offset+increment,y_offset), 15);
        bR.SetPosition(1,axis::set_axis1(x_offset+increment,y_offset), 15);
        fL.SetPosition(0,axis::set_axis0(x_offset-increment,y_offset), 15);
        fL.SetPosition(1,axis::set_axis1(x_offset-increment,y_offset), 15);
        delay(150);

        fR.SetPosition(0,axis::set_axis0(x_offset+increment,y_offset-6.35), 15);
        fR.SetPosition(1,axis::set_axis1(x_offset+increment,y_offset-6.35), 15);
        bL.SetPosition(0,axis::set_axis0(x_offset-increment,y_offset-6.35), 15);
        bL.SetPosition(1,axis::set_axis1(x_offset-increment,y_offset-6.35), 15);
        delay(150);

        fR.SetPosition(0,axis::set_axis0(x_offset+increment,y_offset), 15);
        fR.SetPosition(1,axis::set_axis1(x_offset+increment,y_offset), 15);
        bL.SetPosition(0,axis::set_axis0(x_offset-increment,y_offset), 15);
        bL.SetPosition(1,axis::set_axis1(x_offset-increment,y_offset), 15);
        delay(150);
    }
}
void Dog::walk_distance(double distance){
    switch(speed){

        case Speed::SLOW:
            fR.SetPosition(0,axis::set_axis0(x_offset+distance/2.0,y_offset-6.35), 10);
            fR.SetPosition(1,axis::set_axis1(x_offset+distance/2.0,y_offset-6.35), 10);
            bL.SetPosition(0,axis::set_axis0(x_offset-distance/2.0,y_offset-6.35), 10);
            bL.SetPosition(1,axis::set_axis1(x_offset-distance/2.0,y_offset-6.35), 10);
            delay(150);

            fR.SetPosition(0,axis::set_axis0(x_offset+distance/2.0,y_offset), 10);
            fR.SetPosition(1,axis::set_axis1(x_offset+distance/2.0,y_offset), 10);
            bL.SetPosition(0,axis::set_axis0(x_offset-distance/2.0,y_offset), 10);
            bL.SetPosition(1,axis::set_axis1(x_offset-distance/2.0,y_offset), 10);
            delay(150);

            bR.SetPosition(0,axis::set_axis0(x_offset+distance,y_offset-6.35), 10);
            bR.SetPosition(1,axis::set_axis1(x_offset+distance,y_offset-6.35), 10);
            fL.SetPosition(0,axis::set_axis0(x_offset-distance,y_offset-6.35), 10);
            fL.SetPosition(1,axis::set_axis1(x_offset-distance,y_offset-6.35), 10);
            delay(150);

            bR.SetPosition(0,axis::set_axis0(x_offset+distance,y_offset), 10);
            bR.SetPosition(1,axis::set_axis1(x_offset+distance,y_offset), 10);
            fL.SetPosition(0,axis::set_axis0(x_offset-distance,y_offset), 10);
            fL.SetPosition(1,axis::set_axis1(x_offset-distance,y_offset), 10);
            delay(150);
            
        case Speed::MEDIUM:

            fR.SetPosition(0,axis::set_axis0(x_offset+distance/2.0,y_offset-6.35), 15);
            fR.SetPosition(1,axis::set_axis1(x_offset+distance/2.0,y_offset-6.35), 15);
            bL.SetPosition(0,axis::set_axis0(x_offset-distance/2.0,y_offset-6.35), 15);
            bL.SetPosition(1,axis::set_axis1(x_offset-distance/2.0,y_offset-6.35), 15);
            delay(150);

            fR.SetPosition(0,axis::set_axis0(x_offset+distance/2.0,y_offset), 15);
            fR.SetPosition(1,axis::set_axis1(x_offset+distance/2.0,y_offset), 15);
            bL.SetPosition(0,axis::set_axis0(x_offset-distance/2.0,y_offset), 15);
            bL.SetPosition(1,axis::set_axis1(x_offset-distance/2.0,y_offset), 15);
            delay(150);

            bR.SetPosition(0,axis::set_axis0(x_offset+distance,y_offset-6.35), 15);
            bR.SetPosition(1,axis::set_axis1(x_offset+distance,y_offset-6.35), 15);
            fL.SetPosition(0,axis::set_axis0(x_offset-distance,y_offset-6.35), 15);
            fL.SetPosition(1,axis::set_axis1(x_offset-distance,y_offset-6.35), 15);
            delay(150);

            bR.SetPosition(0,axis::set_axis0(x_offset+distance,y_offset), 15);
            bR.SetPosition(1,axis::set_axis1(x_offset+distance,y_offset), 15);
            fL.SetPosition(0,axis::set_axis0(x_offset-distance,y_offset), 15);
            fL.SetPosition(1,axis::set_axis1(x_offset-distance,y_offset), 15);
            delay(150);

        case Speed::FAST:

            fR.SetPosition(0,axis::set_axis0(x_offset+distance/2.0,y_offset-6.35), 20);
            fR.SetPosition(1,axis::set_axis1(x_offset+distance/2.0,y_offset-6.35), 20);
            bL.SetPosition(0,axis::set_axis0(x_offset-distance/2.0,y_offset-6.35), 20);
            bL.SetPosition(1,axis::set_axis1(x_offset-distance/2.0,y_offset-6.35), 20);
            delay(150);

            fR.SetPosition(0,axis::set_axis0(x_offset+distance/2.0,y_offset), 20);
            fR.SetPosition(1,axis::set_axis1(x_offset+distance/2.0,y_offset), 20);
            bL.SetPosition(0,axis::set_axis0(x_offset-distance/2.0,y_offset), 20);
            bL.SetPosition(1,axis::set_axis1(x_offset-distance/2.0,y_offset), 20);
            delay(150);

            bR.SetPosition(0,axis::set_axis0(x_offset+distance,y_offset-6.35), 20);
            bR.SetPosition(1,axis::set_axis1(x_offset+distance,y_offset-6.35), 20);
            fL.SetPosition(0,axis::set_axis0(x_offset-distance,y_offset-6.35), 20);
            fL.SetPosition(1,axis::set_axis1(x_offset-distance,y_offset-6.35), 20);
            delay(150);

            bR.SetPosition(0,axis::set_axis0(x_offset+distance,y_offset), 20);
            bR.SetPosition(1,axis::set_axis1(x_offset+distance,y_offset), 20);
            fL.SetPosition(0,axis::set_axis0(x_offset-distance,y_offset), 20);
            fL.SetPosition(1,axis::set_axis1(x_offset-distance,y_offset), 20);
            delay(150);

    }
}