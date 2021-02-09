# include <math.h>
# include <stdlib.h>
# include <stdio.h>
#include <string.h>
# include <time.h>


int main ( )
{
    //eqyation to be solved 1D linear advection -- du/dt + c(du/dx) = 0
    //initial conditions u(x,0) = u0(x)

    //after discretisation using forward difference time and backward differemce space
    //update equation becomes u[i] = u0[i] - c * dt/dx * (u0[i] - u[i - 1]);

    int nx = 41; //num of grid points
    double dx = 2.0 / (nx - 1.0); //magnitude of the spacing between grid points
    double nt = 25;//nt is the number of timesteps
    double dt = 0.25; //the amount of time each timestep covers
    int c = 1;  //assume wavespeed
    //double u0_array;

    //initilise arrays
    double* u0_array = (double*)calloc(nx, sizeof(double));
    double* usol_array = (double*)calloc(nx, sizeof(double));

    //set up our initial conditions. The initial velocity u_0
    //is 2 across the interval of 0.5 <x < 1 and u_0 = 1 everywhere else.
    //we will define an array of ones
    for (int i = 0; i < nx-1; i++)
    {
        if (i * dx >= 0.5 && i * dx <= 1)
        {
            u0_array[i] = 2;
        }else
        {
             u0_array[i] = 1;
        }
    }

    //test to see array has been initilised properly
    for (int i = 0; i < nx; i++)
    {
        //u0_array[i] = 2;
        printf("%f, ", u0_array[i]);

    }
    //apply numerical scheme forward difference in
    //time an backward difference in space
    //u0_array = usol_array;
    for (int i = 0; i < nt - 1; i++)
    {

        usol_array = u0_array;


        for (int j = 1; j < nx-1; j++)
        {
            u0_array[j] = usol_array[j] - c * (dt/dx) * (usol_array[j] - usol_array[j - 1]);
            //print array contents to validate program is working
            printf("%f", u0_array[j]);

        }

    }

    return EXIT_SUCCESS;
}



