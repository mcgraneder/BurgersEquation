
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
            fprintf(fpointer, "%f\n", u_new[i]);S
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

