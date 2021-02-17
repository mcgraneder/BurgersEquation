#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#define PI (3.141592653589793)



//TODO---------( 2 ) ADD STABILITY ANALYSIS
//             ( 1 ) CLEAN UP CODE



//function prototypes
char program_brief(char user_input, double NT, double NX, double XMAX, double TMAX);
void program_update(bool buffer_condition);
double stability(double** u_analytical, int ipos, double NX, double DT, double DX, int ineg);

int main()
{

    int NX = 101;
    int NT = 101;
    double DX = (double)2.0 * PI / (double)(NX - 1);
    double NU = 0.07;
    double DT = NU * DX;
    double phi;
    double dphi;

    FILE* initial_fp = NULL;
    initial_fp = fopen("Burgers_equation_1D_initial_data.txt", "w");

    FILE* final_fp = NULL;
    final_fp = fopen("Burgers_equation_1D_final_data.txt", "w");



    double* u = (double*)calloc(NX, sizeof(double));
    double* un = (double*)calloc(NX, sizeof(double));
    double* x = (double*)calloc(NX, sizeof(double));
    double* t = (double*)calloc(NX, sizeof(double));

    //set up x cordintates. populates x as a linspace
    //array in range from 0 to 2 pi in even sreps of
    // nx increments
    for (int i = 0; i < NX; i++)
    {
        x[i] = i * DX;


        //printf("%f, ", x[i]);
    }

    //print out initial conditions
    printf("\n\n");
    printf("The initial conditions are given below:");
    printf("\n\n");
    for (int i = 0; i < NX; i++)
    {
        //get rid of ts
        phi = exp(-pow((x[i] - 4 * t[i]), 2) / (4 * NU * (t[i] + 1)))
            + exp(-pow((x[i] - 4 * t[i] - 2 * PI), 2) / (4 * NU * (t[i] + 1)));

        dphi = (-0.5 * (x[i] - 4 * t[i]) / (NU * (t[i] + 1)) * exp(-pow((x[i] - 4 * t[i]), 2) / (4 * NU * (t[i] + 1)))
            - 0.5 * (x[i] - 4 * t[i] - 2 * PI) / (NU * (t[i] + 1)) * exp(-pow((x[i] - 4 * t[i] - 2 * PI), 2) / (4 * NU * (t[i] + 1))));

        u[i] = -2.0 * NU * (dphi / phi) + 4.0;
        un[i] = u[i];

        printf(" %14f", u[i]);
        fprintf(initial_fp, "%f\n", u[i]);

    }

    printf("\n\n\n\n");
    printf("Preparing solution for %d timesteps:", NX);
    printf("\n\n\n\n");

    //sleep to give user time to see ICs
    //Sleep(5000);


    //implement numerical methid to compute solution backward difference
    for (int i = 1; i < NT; i++)
    {
        memcpy(un, u, sizeof(double));
        printf("\n\n\n");
        printf("timestep %d", i + 1);
        printf("\n\n\n");

        for (int j = 1; j < NX - 1; j++)
        {
            un[j] = u[j] - u[j] * (DT / DX) * (u[j] - u[j - 1]) + NU * (DT / DX * DX) * (u[j + 1] - 2 * u[j] + u[i - 1]);
            //printf(" %14f", un[j]);


        }
        for (int i = 0; i < NX; i++)
        {
            u[i] = un[i];
        }

        //copy over array contents after each spatial update for next iteration


        //set boundary conditions to ICs at end of each timestep
        un[0] = u[0] - u[0] * (DT / DX) * (u[0] - u[NX - 2]) + NU * (DT / DX * DX) * (u[1] - 2 * u[0] + u[NX - 2]);
        un[NX - 1] = un[0];
        //printf(" %14f", un[i]);

    }

    //print out solution after final timestep
    printf("\n\n");
    printf("The solution after timestep %d is given below:", NX);
    printf("\n\n");
    for (int i = 0; i < NX; i++)
    {
        printf(" %14f\n", un[i]);
        fprintf(final_fp, "%f\n", un[i]);
    }

    //good pointer use free memory
    free(u);
    u = NULL;

    free(un);
    un = NULL;

    free(x);
    x = NULL;

    return EXIT_SUCCESS;
}




