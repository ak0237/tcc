#include <stdio.h>
#define BETA 0.05
#define GAMA 0.01


double S(double beta, double i, double s, double n){
    return -(beta*i*s)/n;
}

double I(double beta, double i, double s, double n, double gama){
    return ((beta*i*s)/n) - gama*i;
}

double R(double gama, double i){
    return gama*i;
}

int main(){
    double beta, i, s, r, n, gama, h=0.01, t=0.0, tf = 500.0, k1, k2, k3, k4, l1, l2, l3, l4, m1, m2, m3, m4;

    n=1000.0;
    i=100.0;
    s=900.0;
    r=0.0;


    beta = BETA;
    gama = GAMA;

    FILE *file = fopen("dat/sir_rk4.dat", "w");

    fprintf(file, "%e %e %e %e \n", t, s, i, r);

    while(t <= tf){
        k1 = S(beta, i, s, n);
        l1 = I(beta, i, s, n, gama);
        m1 = R(gama, i);

        k2 = S(beta, i+h*0.5*l1, s+h*0.5*k1, n);
        l2 = I(beta, i+h*0.5*l1, s+h*0.5*k1, n, gama);
        m2 = R(gama, i+h*0.5*l1);
        k3 = S(beta, i+h*0.5*l2, s+h*0.5*k2, n);
        l3 = I(beta, i+h*0.5*l2, s+h*0.5*k2, n, gama);
        m3 = R(gama, i+h*0.5*l2);
        k4 = S(beta, i+h*l3, s+h*k3, n);
        l4 = I(beta, i+h*l3, s+h*k3, n, gama);
        m4 = R(gama, i+h*l3);

        s += h * (1.0/6.0) * (k1 + 2.0*k2 + 2.0*k3 + k4);
        i += h * (1.0/6.0) * (l1 + 2.0*l2 + 2.0*l3 + l4);
        r += h * (1.0/6.0) * (m1 + 2.0*m2 + 2.0*m3 + m4);

        t +=h;

        fprintf(file, "%e %e %e %e \n", t, s, i, r);
    }

    fclose(file);

    return 0;

}
