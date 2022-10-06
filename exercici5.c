#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcions.h"

double g (double x) {
	return x*x;
}

double K (double x, double t) {
	double resultat = x*x + t*t;
	return resultat;
}

int main(void) {
	int n, i, j;
	double **A, lambda, tol;
	/*A serà matriu ampliada per a poder utilitzar les funcions dels altres exercicis*/

	printf("n\n");
	scanf("%d", &n);
    
    printf("Lambda\n");
    scanf("%le", &lambda);

	printf("tolerància\n");
	scanf("%le", &tol);

    A = crea_mat(n+1, n+2);
	
	/*Valoro el cas lambda == 0*/
	if (lambda == 0) {
		printf("La solució és:\n");
		for (i = 0; i <= n; ++i) 
            printf("%le ", g((double)i/(double)n));
		printf("\n");
		return 0;
	} 


	/*Inicialitzo tota la matriu A tenint en compte discretitzacions i fórmula dels trapezis*/
	for (i=0; i<n+1; i++) {
		for(j=0; j<n+1; j++) {

			if(i==j) {   /*A[i][j]= (-lambda / n) * (k(i/n, i/n) - n/lamda)*/
				A[i][j] = (-lambda/(double)n) * (K((double)i/(double)n, (double)i/(double)n) - (double)n/lambda);
			}

			else if(i!=j && j==n) {   /*Xn=i/n --> Xn=1*/  /*-lambda/n * (k(i/n, 1) /2)*/
				A[i][j] = -lambda/(double)n * (K((double)i/(double)n, 1.)/2.);
			}

			else if(i!=j && j==0) {   /* (-lambda/n) * (k(i/n, n) / 2)*/
				A[i][j] = -lambda/(double)n * (K((double)i/(double)n, 0.)/2.);
			}

			else if(i!=j && j!=n && j!=0) {    /*(-lambda/n) * (k(i/n, j/n))*/
				A[i][j] = -lambda/(double)n * (K((double)i/(double)n, (double)j/(double)n));
			}
		}
	}


	/*Tracto apart el cas A[0][0] i A[n][n] perquè la matriu no segueix el mateix patró que en la resta de i == j*/
	A[0][0] = -lambda/(double)n * (K(0.,0.)/2. - (double)n/lambda);
	A[n][n] = -lambda/(double)n * (K(1.,1.)/2. - (double)n/lambda);


	/*Guardo el terme independent, que és la funció g*/
	for(i = 0; i < n+1; ++i) 
        A[i][n+1] = g((double)i/(double)n);

	/*Vull veure com em queda la matriu ampliada A, que serà el sistema a resoldre*/
	printf("\nLa matriu A queda com:\n");
	for(i = 0; i < n+1; ++i) {
		for(j = 0; j <= n+1; ++j) {
			printf("%le  ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

    

	/*Soluciono el sistema*/
	gauss(n+1, A, 1, tol);
    printf("Hola\n");
	
    subst_enrere(n+1, A);
    printf("Hola2\n");
    
    al_mat(A, n+1);
    

	return 0;
}
