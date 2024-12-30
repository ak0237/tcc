#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <time.h>

#define N 500000 // numero de individuos
#define NG 500   // numero de geracoes
#define beta 0.5 // probabilidade de se infectar 
#define gama 0.1 // probabilidade de ser removido
#define TR 1.0   // tamanho da rede


#define sigma 0.00447213595499957939
#define eta 1.0

struct INDV
{
    int estado; // 0 = S | 1 = I | 2 = R
    double x;   // posicao em x do individuo
    double y;   // posicao em y do individuo
};

void ic(const gsl_rng *w, struct INDV *in){
	int c;
	
	// Criando 100 individuos em posicoes aleatorias
	for(c = 0; c < N; c++){
		in[c].estado = int(gsl_rng_uniform(w) * 3);
		in[c].x= gsl_rng_uniform(w)*TR;
		in[c].y= gsl_rng_uniform(w)*TR;
	}
}

void op(int t, struct INDV *in){
	int c;
	char name[100];
	FILE *file;
	
	sprintf(name, "dat/p-%d.dat", t);
	file = fopen(name, "w");
	for(c = 0; c < N; c++){
		fprintf(file, "%e %e %d\n", in[c].x, in[c].y, in[n].estado);
	}
	fclose(file);
}


int main(){
    int t = 0, v, n;
    double 

    struct INDV *in;

    in = (struct INDV *) calloc(N, sizeof(struct INDV));

    // Definido a seed 
	gsl_rng_default_seed= (argc == 2) ? atoi(argv[1]) : time(NULL);
	
	// Criando um ponteiro para guardar um número aleatório
	gsl_rng *w= gsl_rng_alloc(gsl_rng_taus);

    // Condições iniciais
    ic(w, in);
    op(0, in);

    for(t = 1; t <= NG; t++){
        for(n = 0; n < N; n++){
            switch (in[n].estado)
            {
            case 0:
                for(v = 0; v <= N; v++){
                    dx = fabs(in[v].x-in[n].x);
                    dy = fabs(in[v].y-in[n].y);
                    if(in[v].estado == 1 && sqrt(dx*dx+dy*dy) < R && in[n].estado ==0){
                        if(gls_rng_uniform(w) < beta){
                            in[n].estado = 1;
                        }
                    }

                }
                break;
            case 1:
                if(gls_rng_uniform(w) < gama){
                            in[n].estado = 2;
                        }
                break;
            case 2:

                break;
            default:
                break;
            }
            // Movimentando o individuo
			angulo = M_PI*(gsl_rng_uniform(w)-0.5)*eta; // Angulo
			passo = fabs(gsl_ran_gaussian(w, sigma)); // Tamanho do passo
			in[n].x += passo*cos(angulo); // Passo em x
			if(in[n].x > TR){in[n].x -= TR;} // Condicao periodica de contorno
			if(in[n].x < 0.0){in[n].x += TR;} // Condicao periodica de contorno
			in[n].y += passo*sin(angulo); // Passo em y
			if(in[n].y > TR){in[n].y -= TR;} // Condicao periodica de contorno
			if(in[n].y < 0.0){in[n].y += TR;} // Condicao periodica de contorno


        }
        op(t, in);

    }

    gsl_rng_free(w);
	free(in);
	return 0;
    
}