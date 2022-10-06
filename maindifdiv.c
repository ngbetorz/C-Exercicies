#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void dif_div(int n, double *x, double *y, double *difer);
double aval(int n, double *x, double *difer, double z);
double testLagrange (int m, double a, double b, int num);
double *crea_vec(int n);
double fun(double x);

int main (){
	int n, i, m, num;
	double *x, *y, *difer, z, punt, a, b, emax;

	n=4;
	x=crea_vec (n+1);
	y=crea_vec (n+1);
    difer=crea_vec (n+1);
	
    x[0]= 1.;
    x[1]= 3.;
    x[2]= 4.;
    x[3]= 8.;
    
    y[0]= 2.;
    y[1]= 3.;
    y[2]= 2.;
    y[3]= 10.;
 
/*Diferencies dividides*/
    dif_div(n, x, y, difer);
    printf("diferencies dividides \t x= ");
    for(i=0; i<=n; i++)
        printf("%le\t", difer[i]);
    
/*Aval*/
    z=0.5;
    punt= aval(n, x, difer, z);
    printf("\nEl polinomi evaluat en el punt %le és:\t %le\n", z, punt);
    
/*Lagrange*/
    m=5;
    a=-0.9;
    b=0.5;
    num=200;
    emax= testLagrange(m, a, b, num);
    printf("L'error màxim en aquest interval es: %le\n", emax);
    
    
    
    printf("\n\n");
    
    free(x);
    free(y);
    free(difer);
    
    return 0;
}

double testLagrange (int m, double a, double b, int num){
    int i;
    double h=a, *v1, *v2, *difer, punt, error, E=0.;
    
    v1=crea_vec (m);
    v2=crea_vec (m);
    difer= crea_vec(m);

    h= (b-a)/(double)m;
    
    v1[0]= a;
    v2[0]= fun(v1[0]);
    for(i=1; i<m; i++){
        v1[i]= v1[i-1]+h;
        v2[i]= fun(v1[i]);
    }
    
    
    h= (b-a)/(double)num;
    dif_div(m-1, v1, v2, difer);
    do{
        i=0;
        punt= aval (m-1, v1, difer, h);
        error= fun(h) - punt;
        if(fabs(error) > E)     E=error;
        h += h;
    } while (h<b);
    
    
    return E;
}
    
double aval(int n, double *x, double *difer, double z){
    double res=0;
    int i;

    for(i=n; i>0 ; i--)
        res=(res+difer[i])*(z-x[i-1]);        

    res+=difer[0];
    return res;
}

void dif_div(int n, double *x, double *y, double *difer){
    int i,j;

    for(i=0; i<=n; i++)
        difer[i]=y[i];
    for(i=1; i<=n; i++) {    
        for(j=n; j>=i ; j--) {      
        /*comencem per sota*/
            difer[j]=(difer[j]-difer[j-1])/(x[j]-x[j-i]);      
        } /*a cada pas es canvia el valor de j fins a arribar al primer*/
    }
}

double fun(double x){
    double y;
    y= sqrt(1+x);
    return y;
}

double *crea_vec(int n){
    double *v;
    
    v=(double *) malloc((n)*sizeof(double));
    if(v==NULL){	printf("No memory\n");	exit(1);	}
    
    return v;
}
