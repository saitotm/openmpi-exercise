#include <stdio.h>
#include "mpi.h"

float f(float x) {
    return x;
}

float calc_kernel(float local_a, float local_b, int local_n, float h) {
    int i;
    float x;
    float integral = (f(local_a) + f(local_b)) / 2.0;

    x = local_a;
    for (i = 1; i < local_n; ++i) {
        x = x + h;
        integral = integral + f(x);
    }

    integral = integral * h;

    return integral; 
}

int main(int argc, char *argv[])
{
    float a, b, integral, total;
    int n;
    int rank, p_size;
    int dest = 0;
    int tag = 0;
    float h;
    MPI_Status status;

    a = 0.0;
    b = 1.41421;
    n = 1024;
    h = (b - a) / n;
    // scanf("%f %f %d", &a, &b, &n);


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p_size);

    int local_n = n / p_size;
    float local_a = a + rank * local_n * h;
    float local_b = local_a + local_n * h;
    integral = calc_kernel(local_a, local_b, local_n, h);
    
    if (rank == 0) {
        total = integral;
        for (int source = 1; source < p_size; source++) {
            MPI_Recv(&integral, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status);
            total = total + integral;
        }
    } else {
        MPI_Send(&integral, 1, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        printf("The integral from %f to %f is %f\n", a, b, total);
    }

    MPI_Finalize();

    return 0;
}


