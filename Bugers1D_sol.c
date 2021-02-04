/*
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

# include <time.h>

double u_a(double x, double t);
double u_b(double x, double t);

int main (int* argv, char**argc)
{

    FILE *fpointer;
    fpointer = fopen("brugersData.txt", "w");
    if (fpointer == NULL)
    {
        printf("Unable to write to file");
        return EXIT_FAILURE;

    }
    //initilise boundary conditions
    double a = -1.0;
    double b = +1.0;


    //initilise looping variabbles
    int i;
    int i_upperbound;
    int i_lowerbound;
    int n = 41;

     //num of steps
    int step;
    int step_num = 80;
    //double t;


     //initilise discristati
    //on steps
    double dt;
    double dx = (b - a) / (double) (step_num);


    //initlisise arrays to fill
    double *u_array;
    double *u_new;
    double *x_array;

    //initilisetimestep variables
    double t_initial = 0;
    int t_max = 1;

    //use the time boundarys to define dt
    dx = (b - a) / (double)(n - 1);
    dt = (t_initial - t_max) / (double)(step_num);


    //since we are initilising arrays to fil in runtime we need to use pointers
    //to allocate suuficent memory
    u_array = (double *)malloc(n * sizeof(double));
    u_new = (double *)malloc(n * sizeof(double));
    x_array = (double *)malloc(n * sizeof(double));


    //we need to initilise a few arrays well initlisise x array and populate it
    //with values from -1 to 1 in increments of 0,05
    if (n == 1)
    {
        x_array[0] = 0.5 * (a + b);
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            x_array[i] = ((double)(n - i - 1) * a + (double)(i) * b) / (double)(n - 1);
            //printf("%f,", x_array[i]);
        }
    }

    //this code checks for the boundary conditions as we cannot get nfirst and nlast

    for (i_lowerbound = 0; i_lowerbound < n; i_lowerbound = i_lowerbound + 5)
    {
        if ((i_lowerbound + 5) < (n - 1))
        {
            i_upperbound = i_lowerbound + 5;
        }
        else
        {
            i_upperbound = n -1;
        }

        for (int i = i_lowerbound; i <= i_upperbound; i++)
        {
            printf(" %14f", x_array[i]);

        }
        //printf("\n");

    }


    //we need to apply the boundar conditions to the first and last nodes
    //as hey cannot be calculates using the update equation, for this we need the analytical
    //solution
    step = 0;
    double t = t_initial;

    //we need an array to set the boundary condition at the first node which is zero
    double ua = -0.5;
    double ub = 0.5;

    u_new[0] = ua;
    u_new[n - 1] = ub;


    //this is the analytical solution of burgers, that we need for the first and last
    //node.
    double pi = 3.141592653589793;
    double q;
    double r;
    double s;




    q = 2 * (ua - ub) / pi;
    r = (ua + ub) / 2;


    s = 1;

    for (int i = 0; i < n; i++)
    {
        u_array[i] = -q * atan (s * (2.0 * x_array[i] - x_array[0] - x_array[n - 1]) / (x_array[n - 1] - x_array[0])) + r;
        //printf(" %14f", u_array[i]);
    }


    //implement lax wendoff
    for (step = 1; step <= step_num; step++)
    {
        t = ((double)(step_num - step) * t_initial + (double)(step) * t_max) / (double)(step_num);

        for (int i = 0; i < n - 1; i++)
        {
            u_new[i] = u_array[i];
        }
        for (int i = 1; i < n; i++)
        {
            u_new[i] = u_array[i] - (dt / dx) * (pow(u_array[i + 1], 2) - pow(u_array[i], 2)) + 0.5 * (dt * dt / dx / dx) * 0.5 *((u_array[i+1] + u_array[i]) * (pow(u_array[i+ 1], 2) - pow(u_array[i], 2)) - (u_array[i] + u_array[i - 1]) * (pow(u_array[i - 1], 2)));
            printf(" %14f", u_new[i]);
            fprintf(fpointer, "%f\n", u_new[i]);

        }

        u_new[0] = ua;
        u_new[n - 1] = ub;

     printf("\n\n");
    }

    printf("Data written to BurgersData.txt");
    printf("\n");

    free(u_new);
    free(u_array);
    free(x_array);

    return EXIT_SUCCESS;

}
*/

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>

int main ( )
{

    FILE *fpointer;
    fpointer = fopen("B.txt", "w");

    double a = -1;
    double b = 1;
    double dt;
    int step;
    int step_num = 80;
    double dx = (b - a) / (double)(step_num);
    int i_lowerbound;
    int i_upperbound;
    int n = 41;
    double t_initial;
    double t_max;
    double *u_new;
    double *u_original;
    double *boundary_array;


    n = 41;
    a = -1.0;
    b = +1.0;
    dx = ( b - a ) / ( double ) ( n - 1 );
    step_num = 80;
    t_initial = 0.0;
    t_max = 1.0;
    dt = ( t_max - t_initial ) / ( double ) ( step_num );

    u_new = ( double * ) malloc ( n * sizeof ( double ) );
    u_original = ( double * ) malloc ( n * sizeof ( double ) );
    boundary_array = ( double * ) malloc ( n * sizeof ( double ) );

    if (n == 1)
    {
        boundary_array[0] = 0.5 * (a + b);
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            boundary_array[i] = ((double)(n - i - 1) * a + (double)(i) * b) / (double)(n - 1);
        }


    }




    for ( i_lowerbound = 0; i_lowerbound < n; i_lowerbound = i_lowerbound + 5 )
    {

    if ((i_lowerbound + 5) < (n - 1))
    {
        i_upperbound = (i_lowerbound + 5);
    }
    else
    {
        i_upperbound = (n - 1);
    }
    for ( int i = i_lowerbound; i <= i_upperbound; i++ )
    {
        printf ( "  %14f", boundary_array[i] );
    }
    printf ( "\n" );
    }


    /*
      Set the initial condition,
      and apply boundary conditions to first and last entries.
    */
    step = 0;
    double pi = 3.141592653589793;
    double q;
    double r;
    double s;
    double ua;
    double ub;


      //u_init ( n, boundary_array, t, u_new );

    ua = -0.5;
    ub = 0.5;
    boundary_array[0] = -0.5;
    boundary_array[n - 1] = 0.5;

    q = 2 * (ua - ub) / pi;
    r = (ua + ub) / 2;
    s = 1.0;

    for (int i = 0; i < n; i++)
    {
        u_new[i] = -q * atan(s * (2 * boundary_array[i] - boundary_array[n - 1]) / (boundary_array[n - 1] - boundary_array[0])) + r;
    }
    u_new[0] = -0.5;
    u_new[n-1] = 0.5;


    /*
      Use the Lax-Wendroff method.
    */
    for ( step = 1; step <= step_num; step++ )
    {
    t_initial = ( ( double ) ( step_num - step ) * t_initial
        + ( double ) (            step ) * t_max )
        / ( double ) ( step_num        );

    for ( int i = 0; i < n; i++ )
    {
        u_original[i] = u_new[i];
    }

    for ( int i = 1; i < n - 1; i++ )
    {
        u_new[i] = u_original[i]
        - ( dt / dx ) * ( pow ( u_original[i+1], 2 ) - pow ( u_original[i-1], 2 ) )
        + 0.5 * ( dt * dt / dx / dx ) * 0.5 *
        (   ( u_original[i+1] + u_original[i] ) * ( pow ( u_original[i+1], 2 ) - pow ( u_original[i], 2 ) )
            - ( u_original[i] + u_original[i-1] ) * ( pow ( u_original[i], 2 ) - pow ( u_original[i-1], 2 ) ) );
            printf(" %14f", u_new[i]);
            fprintf(fpointer, "%f\n", u_new[i]);
    }
    printf("\n\n");
    u_new[0] = -0.5;
    u_new[n-1] = 0.5;


    }

    free ( u_new );
    free ( u_original );
    free ( boundary_array );
    /*
      Terminate.
    */
    printf ( "\n" );
    printf ( "FD1D_BURGERS_LAX:\n" );
    printf ( "  Normal end of execution.\n" );

    printf ( "\n" );

    return 0;
}

