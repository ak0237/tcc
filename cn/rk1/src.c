#include <stdio.h>
#define BETA 0.05
#define GAMA 0.01


double S(double i, double s, double n){
    return -(BETA*i*s)/n;
}

double I(double i, double s, double n){
    return ((BETA*i*s)/n) - GAMA*i;
}

double R(double i){
    return GAMA*i;
}

int main(){
    double  i, s, r, n,  h=0.1, t=0.0, tf = 500.0;

    n=1000.0;
    s=20.0;
    i=30.0;
    r=950.0;

    


    FILE *file = fopen("dat/sir_rk1.dat", "w");

    fprintf(file, "%e %e %e %e \n", t, s, i, r);
    t+=h;
    while (t < tf)
    {
        s += h*S( i, s, n);
        i += h*I( i, s, n);
        r += h*R( i);

        t +=h;

        fprintf(file, "%e %e %e %e \n", t, s, i, r);
    }
    
    fclose(file);

    return 0;
}
