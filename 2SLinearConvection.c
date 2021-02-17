#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

# include <stdlib.h>
# include <stdio.h>


int main()
{


    // Define the domain
    int NX = 351;
    int NY = 351;
    int NT = 700;
    double X_LEN = 2.0;
    double Y_LEN = 2.0;
    double C = 1.0;
    double SIGMA = 0.2;

    //declare increments
    double DX = (X_LEN) / (NX - 1.0);
    double DY = (Y_LEN) / (NY - 1.0);
    double DT = SIGMA * DX;


    double* x_array;
    double* y_array;
    double** u_array;
    double** un_array;

    //generate linespace array for x going for 0 to 2 in even
    //increments of NX
    x_array = (double*)calloc(NX, sizeof(double));
    for (int i = 0; i < NX; i++)
    {
        x_array[i] = i * DX;
    }

    //generate linspace array for y going from 0 to 2 in even
    //steps of NY
    y_array = (double*)calloc(NY, sizeof(double));
    for (int j = 0; j < NY; j++)
    {
        y_array[j] = j * DY;
    }



    u_array = (double**)calloc(NY, sizeof(double*));
    un_array = (double**)calloc(NY, sizeof(double*));
    for (int i = 0; i < NY; i++)
    {
        u_array[i] = (double*)calloc(NX, sizeof(double));
        un_array[i] = (double*)calloc(NX, sizeof(double));
    }


    printf("\n\n");
    printf("The initial conditions are given below:");
    printf("\n\n");
    for (int i = 0; i < NY; i++)
    {
        for (int j = 0; j < NX; j++)
        {
            u_array[i][j] = 1.0;
            un_array[i][j] = 1.0;

            if (x_array[i] > 0.5 && x_array[i] < 1.0 && y_array[i] > 0.5 && y_array[i] < 1.0)
            {
                u_array[i][j] = 2.0;
                un_array[i][j] = 2.0;
            }
            printf(" %14f", u_array[i][j]);
        }
    }

    printf("\n\n\n\n");
    printf("Preparing solution for %d timesteps:", NX);
    printf("\n\n\n\n");

    //sleep to give user time to see ICs
    Sleep(5000);

    for (int n = 0; n < NT; n++)
    {
        printf("\n\n\n");
        printf("timestep %d", n + 1);
        printf("\n\n\n");

        for (int i = 1; i < NY; i++)
        {
            for (int j = 1; j < NX; j++)
            {
                //apply the update equation for FDBS scheme
                un_array[i][j] = u_array[i][j] - (C * (DT / DX) * (u_array[i][j] - u_array[i][j - 1])) - (C * (DT / DY) * (u_array[i][j] - u_array[i - 1][j]));
                //u_array[i][j] -= 140.0;

            }
        }

        //copy un arrays contents to u array
        for (int i = 0; i < NY; i++)
        {
            for (int j = 0; j < NX; j++)
            {
                u_array[i][j] = un_array[i][j];
            }
        }

        //redefine boundary values for x before continuing next loop
        for (int i = 0; i < NY; i++)
        {
            u_array[i][0] = 1.0;
            un_array[i][NX - 1] = 1.0;
        }

        //redefine boundary values for x before continuing next loop
        for (int j = 0; j < NX; j++)
        {
            u_array[0][j] = 1.0;
            un_array[NY - 1][0] = 1.0;

        }
        for (int i = 1; i < NY; i++)
        {
            for (int j = 1; j < NX; j++)
            {
                //printf(" %14f", u_array[i][j]);
            }
        }

    }

    printf("\n\n");
    printf("The solution after the final timestep is given below:");
    printf("\n\n");
    for (int i = 0; i < NX; i++)
    {
        for (int j = 0; j < NY; j++)
        {
            printf(" %14f", u_array[i][j]);
        }
    }

    //free memory good pointer use
    free(u_array);
    u_array = NULL;

    free(un_array);
    un_array = NULL;

    free(x_array);
    x_array = NULL;

    free(y_array);
    y_array = NULL;


    return EXIT_SUCCESS;
}
