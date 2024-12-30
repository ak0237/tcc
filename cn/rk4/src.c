#include <stdio.h>
#define BETA 0.05
#define GAMA 0.01

double S( double i, double s, double n){
    return -(BETA*i*s)/n;
}

double I( double i, double s, double n){
    return ((BETA*i*s)/n) - GAMA*i;
}

double R( double i){
    return GAMA*i;
}

int main(){
    double  i, s, r, n, h=5.0, t=0.0, tf = 500.0, k1, k2, k3, k4, l1, l2, l3, l4, m1, m2, m3, m4;

    n=1000.0;
    s=550.0;
    i=50.0;
    r=400.0;



    FILE *file = fopen("dat/sir_rk4.dat", "w");

    fprintf(file, "%e %e %e %e \n", t, s, i, r);

    while(t < tf){
        k1 = S( i, s, n);
        l1 = I( i, s, n);
        m1 = R( i);

        k2 = S( i+h*0.5*l1, s+h*0.5*k1, n);
        l2 = I( i+h*0.5*l1, s+h*0.5*k1, n);
        m2 = R( i+h*0.5*l1);
        k3 = S( i+h*0.5*l2, s+h*0.5*k2, n);
        l3 = I( i+h*0.5*l2, s+h*0.5*k2, n);
        m3 = R( i+h*0.5*l2);
        k4 = S( i+h*l3, s+h*k3, n);
        l4 = I( i+h*l3, s+h*k3, n);
        m4 = R( i+h*l3);

        s += h * (1.0/6.0) * (k1 + 2.0*k2 + 2.0*k3 + k4);
        i += h * (1.0/6.0) * (l1 + 2.0*l2 + 2.0*l3 + l4);
        r += h * (1.0/6.0) * (m1 + 2.0*m2 + 2.0*m3 + m4);

        t +=h;

        fprintf(file, "%e %e %e %e \n", t, s, i, r);
    }

    fclose(file);

    return 0;

}
