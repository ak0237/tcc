#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <time.h>

#define N 1000 // numero de individuos
#define NG 1500   // numero de geracoes
#define beta 0.05 // probabilidade de se infectar 
#define gama 0.2 // probabilidade de ser removido
#define TR 1.0   // tamanho da rede
#define R 0.01


#define sigma 0.00447213595499957939
#define eta 1.0

struct INDV
{
    int estado; // 0 = S | 1 = I | 2 = R
    double x;   // posicao em x do individuo
    double y;   // posicao em y do individuo
};

void ic(const gsl_rng *w, struct INDV *in, int* s, int *i, int *r){
	int c;
    *s = *i = *r = 0;
	
	// Criando 100 individuos em posicoes aleatorias
	for(c = 0; c < N; c++){
        if(c < (N*0.9)){
            in[c].estado = 0;
            (*s)++;
        }else{
            in[c].estado = 1;
            (*i)++;
        }
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
		fprintf(file, "%e %e %d\n", in[c].x, in[c].y, in[c].estado);
	}
	fclose(file);
}


int main(int argc, char **argv){
    int t = 0, v, n, s = 0, i = 0, r = 0, txe =0;
    double dx, dy, passo, angulo pbeta;

    FILE *graf =  fopen("dat2/sir_mmcg.dat", "w");;


    struct INDV *in;

    in = (struct INDV *) calloc(N, sizeof(struct INDV));

    // Definido a seed 
	gsl_rng_default_seed= (argc == 2) ? atoi(argv[1]) : time(NULL);
    printf("%ld\n", gsl_rng_default_seed);
	
	// Criando um ponteiro para guardar um número aleatório
	gsl_rng *w= gsl_rng_alloc(gsl_rng_taus);

    // Condições iniciais
    ic(w, in, &s, &i, &r);
    op(0, in);
    fprintf(graf, "%d %d %d %d\n", t, s, i, r);

   // double rho = N / (TR * TR);            // Densidade populacional
   // double area_interacao = M_PI * R * R; // Área de interação
   // double v_movimento = sigma / 1.0;     // Velocidade média (se dt = 1)

   // double taxa_encontros = rho * area_interacao * v_movimento;

   // double beta_local = beta / taxa_encontros;



    for(t = 1; t <= NG; t++){
        for(n = 0; n < N; n++){
            if(in[n].estado == 1){
                for(v = 0; v < N; v++){
                    if(in[v].estado == 0){
                        dx = fabs(in[v].x-in[n].x);
                        if(dx > (TR * 0.5)){dx -=(TR * 0.5);}
                        dy = fabs(in[v].y-in[n].y);
                        if(dy > (TR * 0.5)){dy -=(TR * 0.5);}

                        if(sqrt(dx*dx+dy*dy) < R){
                            txe++;
                        }
                    }
                }
            }
        }

        pbeta = beta * txe;
        for(n = 0; n < N; n++){
            //printf("%d %d\n", t, n);
            switch (in[n].estado)
            {
            case 0:
                for(v = 0; v < N; v++){
                    dx = fabs(in[v].x-in[n].x);
                    if(dx > (TR * 0.5)){dx -=(TR * 0.5);}
                    dy = fabs(in[v].y-in[n].y);
                    if(dy > (TR * 0.5)){dy -=(TR * 0.5);}
                    if(in[v].estado == 1 && sqrt(dx*dx+dy*dy) < R && in[n].estado ==0){
                        if(gsl_rng_uniform(w) < pbeta){
                            in[n].estado = 1;
                            s--;
                            i++;
                        }
                    }

                }
                break;
            case 1:
                if(gsl_rng_uniform(w) < gama){
                            in[n].estado = 2;
                            i--;
                            r++;
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
        fprintf(graf, "%d %d %d %d\n", t, s, i, r);

    }

    gsl_rng_free(w);
    fclose(graf);
	free(in);
	return 0;
    
}