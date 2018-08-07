#include "math.h"
#include "stdio.h"
#include "stdlib.h"

#define DRAG_COEFF 1e-2

#define STEP_SIZE 1e-3

typedef struct state 
{
    double x; // position
    double y; // position
    double vx; // velocity
    double vy; // velocity
} state;

//The only x acceleration is drag
double ax(state s)
{
    return -DRAG_COEFF*s.vx*s.vx*s.vx/fabs(s.vx);
}

//The y acceleration is gravity and drag
double ay(state s)
{
    return -9.81-DRAG_COEFF*s.vy*s.vy*s.vy/fabs(s.vy);
}

state verlet(state s)
{
    state s_new;
    // Update velocities (half step)
    s_new.vx = s.vx + 0.5*STEP_SIZE*ax(s);
    s_new.vy = s.vy + 0.5*STEP_SIZE*ay(s);
    // Update positions
    s_new.x = s.x + STEP_SIZE*s_new.vx;
    s_new.y = s.y + STEP_SIZE*s_new.vy;
    // Update velocities (half step)
    s_new.vx = s_new.vx + 0.5*STEP_SIZE*ax(s);
    s_new.vy = s_new.vy + 0.5*STEP_SIZE*ay(s);
    return s_new;
    
}

int main(int argc, char *argv[])
{
    //The program takes one argument, the initial velocity
    if(argc != 2) {
        printf("Please input velocity in km/h!\n");
        return -1;
    }
    double v_i = atof(argv[1])/3.6; // convert km/h to m/s
    state s;
    s.x = 0;
    s.y = 2; // start at person's height
    s.vx = v_i/sqrt(2); // throw the ball at a 45 degree angle
    s.vy = v_i/sqrt(2);
    while (s.y > 0) {
        s = verlet(s);
    }
    printf("You throw the ball a distance of %5.4e metres\n", s.x);
    return 0;
}
