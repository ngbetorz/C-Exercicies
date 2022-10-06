#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include"funcions.h"

int pivot (double **mat, int fil, int k);
int gauss(int n, double **a, int pivotem, double tol);
void subst_enrere(int n, double **matU);
double **crea_mat(int n, int m);
void al_mat(double **a, int n);
double *crea_vec(int n);

int main(){
	int i, j, pivotem, el_gauss;
	double **a, tol;
	FILE *ent, *sort;
	char nom1[20], nom2[20];

/*Fitxers, dimensio n, guardem memoria*/
	printf("Escriu el nom del fitxer d'entrada i de sortida\n");
	scanf("%s%s", nom1, nom2);
	ent= fopen(nom1, "r");
	if(ent==NULL){	printf("Error en el fitxer d'entrada\n");	exit(1);	}
	sort= fopen(nom2, "w");

	fscanf(ent, "%d", &n);
	a=crea_mat(n, n+1);

/*Matriu*/
	for(i=0; i<n; i++){
		for(j=0; j<=n; j++)
			fscanf(ent, "%le", &a[i][j]);
/*Pivotatge i tolerancia*/
	do{
		printf("Pivotatge=1, sense=0\n");
		scanf("%d", &pivotem);
	}while(pivotem!=1 || pivotem!=0);
	printf("Tolerancia\n");
	scanf("%le", &tol);

	el_gauss= gauss(n, a, pivotem, tol);
	if(el_gauss==0){
		printf("No s'ha pogut fer eliminacio gaussiana\n");
		exit(1);
	}

/*Ara ja tenim una matriu triangular superior i podem resoldre el sistema per substitució enrere*/
	subst_enrere(n, a);
/*Escrivim el vector solucio (terme independent, i.e, n+1-èssima columna*/
	for(i=0; i<n; i++)
		fprintf(sort, "%e\t", a[i][n]);
	fprintf(sort, "\n");

	al_mat(a, n);
	fclose(ent);
	fclose(sort);

	return 0;
}





	





