#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
#include <string.h>
# include <time.h>
#include <windows.h>

//#define _CRT_SECURE_NO_WARNINGS


int main(int* argc, char** argv)
{
    //eqyation to be solved 1D linear diffusion -- du/dt + c(du/dx) = 0
    //initial conditions u(x,0) = u0(x)

    //after discretisation using forward difference time and backward differemce space
    //update equation becomes usol_array[j] = u0_array[j] + (nu * dt / (dx * dx)) * (u0_array[j + 1] + u0_array[j - 1] - 2 * u0_array[j]);

    //open files for reading
    FILE* initial_fp = NULL;
    initial_fp = fopen("linear_convection1D_initial_data.txt", "w");

    FILE* solution_fp = NULL;
    solution_fp = fopen("linear_convection1D_final_data.txt", "w");

    double domain_length = 2.0;
    int nx = 101; //num of grid points
    double dx = domain_length / (nx - 1.0); //magnitude of the spacing between grid points
    double nt = 101;//nt is the number of timesteps
    double sigma = 0.2;
    double nu = 0.3;
    double dt = (sigma / nu) * (dx * dx); //the amount of time each timestep covers

    double* x_array;
    double* u0_array;
    double* usol_array;
    int c = 1;  //assume wavespeed
    //double u0_array;

    //initilise arrays
    x_array = (double*)calloc(nx, sizeof(double));
    u0_array = (double*)calloc(nx, sizeof(double));
    usol_array = (double*)calloc(nx, sizeof(double));
    //double* initial_conditions = (double*)calloc(nx, sizeof(double));

    //populate the x array with x-coordinates
    for (int i = 0; i < nx; i++)
    {
        x_array[i] = i * dx;
    }

    //set up our initial conditions. The initial velocity u_0
    //is 2 across the interval of 0.5 <x < 1 and u_0 = 1 everywhere else.
    for (int i = 0; i < nx; i++)
    {
        if (x_array[i] > 0.5 && x_array[i] < 1.0)
        {
            u0_array[i] = 2.0;
            usol_array[i] = 2.0;
        }
        else
        {
            u0_array[i] = 1.0;
            usol_array[i] = 1.0;
        }
    }

    //print out initial conditions
    printf("\n\n");
    printf("The initial conditions are given below:");
    printf("\n\n");
    for (int i = 0; i < nx; i++)
    {
        //u0_array[i] = 2;
        printf(" %14f", u0_array[i]);
        fprintf(initial_fp, "%f\n", u0_array[i]);

    }

    printf("\n\n\n\n");
    printf("Preparing solution for %d timesteps:", nx);
    printf("\n\n\n\n");

    //sleep to give user time to see ICs
    Sleep(5000);



    //apply numerical scheme forward difference in
    //time an backward difference in space
    //u0_array = usol_array;
    for (int i = 0; i < nt; i++)
    {
        printf("\n\ntimestep %d\n\n", i + 1);

        for (int j = 1; j < nx - 1; j++)
        {

            usol_array[j] = u0_array[j] + (nu * dt / (dx * dx)) * (u0_array[j + 1] + u0_array[j - 1] - 2 * u0_array[j]);
            //printf(" %14f", usol_array[j]);
            //print array contents to validate program is working
            //printf("%f\n", u0_array[j]);
            //prinysts eac elements array
            //fprintf(fpointer, "%f\n", u0_array[j]);
        }
        for (int i = 0; i < nx; i++)
        {

            u0_array[i] = usol_array[i];
            printf(" %14f", u0_array[i]);

        }


    }

    //print out solution after final timestep
    printf("\n\n");
    printf("The solution after timestep %d is given below:", nx);
    printf("\n\n");

    for (int i = 0; i < nx; i++)
    {

        //u0_array[i] = usol_array[i];
        printf(" %14f", u0_array[i]);
        fprintf(solution_fp, "%f\n", u0_array[i]);
    }


    //dereference pointers and set to NULL
    free(u0_array);
    u0_array = NULL;
    free(usol_array);
    usol_array = NULL;
    free(x_array);
    x_array = NULL;



    return EXIT_SUCCESS;
}