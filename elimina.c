#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*int pivot (double **mat, int fil, int k);
int gauss(int n, double **a, int pivotem, double tol);
void subst_enrere(int n, double **matU);
double **crea_mat(int n, int m);
void al_mat(double *a, int n);
double *crea_vec(int n);*/



int pivot (double **mat, int fil, int k){
    int i, r;
        
    for (i=k+1; i<fil; i++){
        if (fabs(mat[i][k]) > fabs(mat[r][r]))
            r= i;
    }
    return r;
}

int gauss(int n, double **a, int pivotem, double tol){
/*n és la dimensio de la matriu sense terme independent*/
	int i, j, k, max;
	double multi;
	double *aux;

	if(pivotem==1)
		aux= crea_vec(n+1);
	for(i=0; i<n; i++){
		if(pivotem==1){
			/*fem pivotatge*/
			max= pivot(a, n, i);
			aux= a[max];
			a[max]=a[i];
			a[i]=aux;
		}
		for(j=i+1; j<n; j++){
			if(fabs(a[i][i]) > tol){
				multi = a[j][i]/a[i][i];
			}else{	return 0;	}
			for(k=i; k<=n; k++)
				a[j][k] -= (multi*a[i][k]);
		}
	}
	free (aux);
	return 1;
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
	double **a;
	a=(double **) malloc(n*sizeof(double));
	if(a==NULL){	printf("No memory\n");	exit(1);	}
	for(i=0; i<n; i++){
		a[i]= (double *) malloc(m*sizeof(double));
		if(a[i]==NULL){	printf("No memory\n");	exit(1);	}
	return a;
}

void al_mat(double *a, int n){
	int i;
	for(i=0; i<n; i++)	
		free(a[i]);
	free(a);
}
	
double *crea_vec(int n){
	double *v;
	v= (double *) calloc(n,sizeof(double));
	if(v==NULL){	printf("No memory\n");	exit(1);	}

	return v;
}
    
