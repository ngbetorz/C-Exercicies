#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void dif_hermite(int, double *, double *, double *, double*);
double aval_hermite(int, double *, double *, double);
double *crea_vec (int n);



int main(void){
    int n, i;
    double *x, *fx, *derfx, *difHer;
    double d,z;

	printf("Grau del polinomi interpolador d'Hermite':\n");
	scanf("%d", &n);
    
	x= crea_vec(n+1);    
	fx= crea_vec(n+1);      
	derfx= crea_vec(n+1);
    difHer= crea_vec(n+1);

    printf("Doneu els punts d'interpolacio\n");
	for(i=0; i<=n; i=i+2){ /*posem dues vegades les dades*/
        	scanf("%le", &x[i]);
        	x[i+1]=x[i];
    	}
    	
	printf("Doneu les imatges dels punts donats respectivament\n");
	for(i=0; i<=n; i=i+2){
        scanf("%le", &fx[i]);
        fx[i+1]=fx[i];
    }
	
	printf("Doneu el valor de les derivades respectivament\n");
	for(i=0; i<=n; i=i+2){
        scanf("%le", &derfx[i]);
        derfx[i+1]=derfx[i];
    }

	/*Ara calculem els coeficients del polinomi interpolador d'Hermite*/
	dif_hermite(n,x,fx,derfx,difHer);
	printf("El polinomi interpolador d'Hermite amb aquestes dades es:\n");
	for(i=0; i<=n; i++){
		printf("%10.9le\n", difHer[i]);	
	}
	
    printf("Introdueix un valor per avaluar el polinomi\n");
	scanf("%le", &z);
	d=aval_hermite(n, x, difHer,  z);
	printf("El polinomi avaluat en %10.9le es:%10.9le\n",z, d);	
	
	free(x);
	free(fx);
	free(derfx);
	free(difHer);
	
	return 0;
}


void dif_hermite(int n, double *x, double *fx, double *derfx, double *difHer){
	int i,j;
    
	/*Fiquem les imatges de x a difHer*/
    	for(i=0; i<=n; i++){
        	difHer[i]=fx[i]; 
    	}
    	/*Introduim les derivades*/
    	for(i=1; i<=n; i++){
        	for(j=n; j>=i; j--){ 		/*Començant pel final*/
        	/*Quan tenim derivada*/
                if((x[j]-x[j-1] == 0) && i == 1){
                    difHer[j]=derfx[j]; /*només si i==1 ja que nomes tenim la primera derivada*/
			/*Quan no la tenim, fem la diferencia dividida normal*/
                }else{
                    difHer[j]=(difHer[j]-difHer[j-1])/(x[j]-x[j-i]);
                }
        	}
    	}
	return;
	
}


double aval_hermite(int n, double *x, double *difHer, double z){
	int i,j;
	double aux=1.,res=difHer[0];
    
	for(i=1; i<=n; i++){
		aux=1.;
		for(j=0; j<i; j++){
  			aux = aux*(z-x[j]);
		}
		res+=difHer[i]*aux;
	}
	return res;
	
}

double *crea_vec (int n){
    double *v;
    v= (double *) malloc(n*sizeof(double));
    if(v==NULL){    printf("No memory\n");  exit(1);    }
    return v;
}
        
    
