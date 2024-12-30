#include <stdio.h>
#define BETA 0.05
#define GAMA 0.01

double S( double i, double s, double n){
    return -(BETA*i*s)/n;
}

double I( double i, double s, double n){
    return ((BETA*i*s)/n) - GAMA*i;
}

double R(double i){
    return GAMA*i;
}

int main(){
    double i, s, r, n, h=5.0, t=0.0, tf = 500.0, k1, k2, l1, l2, m1, m2;

    n=1000.0;
    s=550.0;
    i=50.0;
    r=400.0;




    FILE *file = fopen("dat/sir_rk2.dat", "w");

    fprintf(file, "%e %e %e %e \n", t, s, i, r);

    while(t < tf){
        k1 = S( i, s, n);
        l1 = I( i, s, n );
        m1 = R( i);

        k2 = S( i+h*l1, s+h*k1, n);
        l2 = I( i+h*l1, s+h*k1, n );
        m2 = R( i+h*l1);

        s += h * 0.5 * (k1 + k2);
        i += h * 0.5 * (l1 + l2);
        r += h * 0.5 * (m1 + m2);

        t +=h;

        fprintf(file, "%e %e %e %e \n", t, s, i, r);
    }

    fclose(file);

    return 0;

}
