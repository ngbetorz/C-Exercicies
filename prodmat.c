/*Exercici 3, llista 2		Bé*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **prodMat (double **a, int filA, int colA, double **b, int colB);
double **crea_mat(int n, int m);
void al_mat(double **a, int n);

int main(){
	int i, j, n, m, p;
	double **a, **b, **prod;

/*dimensions, memoria*/
	printf("Escriu les dimensions de les matrius\n");
	scanf("%d%d%d", &n, &m, &p);

	a= crea_mat(n,m);
	b= crea_mat(m,p);

/*Llegim*/
	printf("Components de la primera matriu\n");
	for(i=0; i<n; i++){
		for(j=0; j<m; j++)
			scanf("%le", &a[i][j]);
	}
	printf("Components de la segona matriu\n");
	for(i=0; i<m; i++){
		for(j=0; j<p; j++)
			scanf("%le", &b[i][j]);
	}
/*Comprovem*/
	printf("La primera matriu\n");
	for(i=0; i<n; i++){
		for(j=0; j<m; j++)
			printf("%e\t", a[i][j]);
		printf("\n");
	}
	printf("\nLa segona matriu\n");
	for(i=0; i<m; i++){
		for(j=0; j<p; j++)
			printf("%e\t", b[i][j]);
		printf("\n");
	}


/*Operem*/
	prod= prodMat(a, n, m, b, p);
	printf("El producte de les matrius es\n");
	for(i=0; i<n; i++){
		for(j=0; j<p; j++)
			printf("%e\t", prod[i][j]);
		printf("\n");
	}

/*Alliberem*/
	al_mat(a, n);
	al_mat(b, m);
	al_mat(prod, n);

	return 0;
}

double **prodMat(double **a, int filA, int colA, double **b, int colB){
	int i, j, k;
	double **prod;

	prod= crea_mat(filA,colB);

	for(i=0; i<filA; i++){
		for(j=0; j<colB; j++){
			prod[i][j]= 0;
			for(k=0; k<colA; k++)
				prod[i][j] += a[i][k]*b[k][j];
		}
	}

	return prod;
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
