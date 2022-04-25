#include <stdio.h>

float f(float x) {
    return x;
}

float calc(float a, float b, int n) {
    int i;
    float x;
    float h = (b - a) / n;
    float integral = (f(a) + f(b)) / 2.0;

    x = a;
    for (i = 1; i < n; ++i) {
        x = x + h;
        integral = integral + f(x);
    }

    integral = integral * h;

    return integral; 
}

int main(int argc, char *argv[])
{
    float a, b, integral;
    int n;

    scanf("%f %f %d", &a, &b, &n);

    integral = calc(a, b, n);

    printf("The integral from %f to %f is %f\n", a, b, integral);
    return 0;
}


