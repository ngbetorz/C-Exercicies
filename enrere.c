/* EXERCICI 1 LLista 2		Main - BÉ*/

/*Falta
	-comprovar l'aplicacio de la matriu canonica
	-Taula de valors
	-canviar la n del bucle per nombres grans*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void subst_enrere (int n, double **matU);
double **crea_mat(int n, int m);
void al_mat(double **a, int n);

int main(){
	int n, i, j;
	double **matU, t;
	FILE *ent;
	char nom[20];

	srand ((unsigned)time(NULL));
	
	printf("Escriu el nom del fitxer d'entrada i de sortida\n");
	scanf("%s", nom);
	ent= fopen(nom, "r");
	if(ent==NULL){	printf("Error en el fitxer d'entrada\n");	exit(1);	}

	fscanf(ent, "%d", &n);
	matU= crea_mat(n, n+1);

/*Donem valors a la matriu*/
	for(i=0; i<n; i++){
		for(j=i; j<n; j++)
			fscanf(ent, "%le", &matU[i][j]);
	}
	for(i=0; i<n; i++)
		fscanf(ent, "%le", &matU[i][n]);
		
/*Comprovem valors*/
		printf("La matriu ampliada es:\n");
		for(i=0; i<n; i++){
			for(j=0; j<=n; j++){
				printf("%e\t",matU[i][j]);
			}
		printf("\n");
		}

/*Operem i printem*/
		t= clock();
		subst_enrere(n, matU);

		printf("\nEl vector solucio es\n");
		for(i=0; i<n; i++)
			printf("%le\t", matU[i][n]);

		
		printf("\nHa tardat %e segons\n", t/(double)CLOCKS_PER_SEC);
		printf("\n\n\n");

/*Alliberem memoria*/
		al_mat(matU, n);
		fclose(ent);
	return 0;
}

void subst_enrere(int n, double **matU){
	int i, j;
	double terme;
	for(i=n-1; i>=0; i--){
		terme=0.;
		for (j=i+1; j<n; j++)
			terme += (matU[i][j] * matU[j][n]);
        	matU[i][n]= ((double)matU[i][n] - (double)terme) / (double)matU[i][i];
	}
}

double **crea_mat(int n, int m){
	int i;
	double **matU;

	matU= (double **) calloc (n,sizeof(double *));
		if(matU==NULL){	printf("No memory\n");	exit(1);	}
		for(i=0; i<n; i++){
			matU[i]= (double *) calloc (m,sizeof(double));
			if(matU[i]==NULL){	printf("No memory\n");	exit(1);	}
		}
	return matU;
}

void al_mat(double **a, int n){
	int i;

	for(i=0; i<n; i++)	free(a[i]);
	free(a);
}
