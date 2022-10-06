/*Exercici 2, llista 2		BÉ*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

double **crea_mat(int n, int m);
void al_mat(double **a, int n);
void subst_endavant(int n, double **matL);

int main(){
	int i, j, n;
	double **matL, t;
	FILE *ent, *sort;
	char nom1[20], nom2[20];

/*Fitxers, dimensio n, guardem memoria*/
	printf("Escriu el nom del fitxer d'entrada i de sortida\n");
	scanf("%s%s", nom1, nom2);

	ent= fopen(nom1, "r");
	if(ent==NULL){	printf("Error en el fitxer d'entrada\n");	exit(1);	}
	sort= fopen(nom2, "w");

	fscanf(ent, "%d", &n);
	srand((unsigned)time(NULL));

	matL= crea_mat(n, n+1);

	
/*escanegem i comprovem valors*/
	for(i=0; i<n; i++){
		for(j=0; j<=i; j++)
			fscanf(ent, "%le", &matL[i][j]);
	}
	for(i=0; i<n; i++)
		fscanf(ent, "%le", &matL[i][n]);

	fprintf(sort, "La matriu es\n");
	for(i=0; i<n; i++){
		for(j=0; j<=n; j++)
			fprintf(sort, "%e\t", matL[i][j]);
		fprintf(sort, "\n");
	}

/*Operem i imprimim*/
/*inicialitzem el tempo*/
	t= clock();
	subst_endavant(n, matL);
	fprintf(sort,"\n\nEl vector solucio es\n");
	for(i=0; i<n; i++)
		fprintf(sort, "%e\t", matL[i][n]);
	fprintf(sort, "\n");

	printf("\nHa tarat %e segons\n", t/(double)CLOCKS_PER_SEC);
	printf("\n\n");

/*alliberem i tanquem*/
	al_mat(matL, n);
	fclose(ent);
	fclose(sort);

return 0;
}

void subst_endavant(int n, double **matL){
	int i, j;
	double terme;

	matL[0][n] = matL[0][n] / matL[0][0];

	for(i=1; i<n; i++){
		terme=0;
		for(j=0; j<i; j++)
			terme += matL[i][j] * matL[j][n];
		matL[i][n]= ((double)matL[i][n] - (double)terme) / (double)matL[i][i];
	}
}

double **crea_mat(int n, int m){
	int i;
	double **matL;

	matL= (double **) calloc(n,sizeof(double*));
	if(matL==NULL){	printf("No memory\n");	exit(1);	}
	for(i=0; i<n; i++){
		matL[i]= (double *) calloc(m,sizeof(double));
		if(matL[i]==NULL){	printf("No memory\n");	exit(1);	}
	}
	return matL;
}

void al_mat(double **a, int n){
	int i;

	for(i=0; i<n; i++)	free(a[i]);
	free(a);
}
