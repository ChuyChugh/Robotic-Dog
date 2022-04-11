#pragma once
#ifndef ODrive_h
#define ODrive_h

#include <math.h>
#include <ODriveArduino.h>

#ifndef l1
#define l1 205.5
#endif

#ifndef l2
#define l2 10
#endif

#ifndef encoder_cpr
#define encoder_cpr 8192
#endif

#ifndef theta1_offset
#define theta1_offset 10
#endif

#ifndef theta2_offset
#define theta2_offset 10
#endif

#ifndef x_offset
#define x_offset 10
#endif

#ifndef y_offset
#define y_offset 10
#endif

#ifndef ratio
#define ratio 9
#endif

template<class T> inline Print& operator <<(Print& obj, T arg);
template<> inline Print& operator <<(Print& obj, float arg);

namespace axis{
    double set_axis0(double x, double y);
    double set_axis1(double x, double y);
}
enum class Speed{
    SLOW,
    MEDIUM,
    FAST
};
enum class Direction{
    FORWARD,
    BACKWARD,
    CW,
    CCW
};
class Dog{
    private:
        double x, y;
        ODriveArduino fL, fR, bL, bR;
        Speed speed;
        Direction direction;
    public:
        Dog(ODriveArduino frontLeft, ODriveArduino frontRight, ODriveArduino backLeft, ODriveArduino backRight);
        void set_direction(Direction d){direction = d;}
        void set_speed(Speed s){speed = s;}
        void walk_indefinitely(double increment);
        void walk_distance(double distance);
        void turn_angle(double angle);
};
#endif