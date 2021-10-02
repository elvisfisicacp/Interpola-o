# Interpola-o
Interpolação usado forma de Newton com três coeficientes
#include <stdio.h>
#include <stdlib.h>

/// ------------------- Valores constantes -----------------------------
#define n 10 ///número de pontos entre cada dois pontos dos dados que serão inseridos
char nome[] = "interpolacao.dat"; ///nome do arquivo dos dados a serem interpolados

/// ------------------- Protótipos de Funções --------------------------
double quantidades_de_linhas(int i);
void entrada_de_dados(double *x, double *y, double *q, int t);
double delta_x(double x1,double x2);
double f(double x1,double x2,double y1,double y2);
void entrada_de_dados(double *x, double *y, int t);


/// ------------------- Função principal -------------------------------
int main() 
{
	//DECLAÇÃO DE VARIÁVEIS 
	int N = 0; 
	N = quantidades_de_linhas(N); ///quantidades de linhas no arquivo
	printf("%d\n\n\n\n\n", N);
	double *y, *x, *h;
	double a[N][N], fk[N][N], Pn[n][N], xi[n][N];
	y = new double[N]; ///vetor para os dados do eixo y
	x = new double[N]; ///vetor para os dados do eixo x
	h = new double[N];
	entrada_de_dados(x,y,N);
	///a0
	for(int k = 0; k < N; k++)
	{
		fk[0][k] = y[k];
		a[0][k] = fk[0][k];
	}
	
	///a1
	for(int k = 0; k < (N-1); k++)
	{
		fk[1][k] = f(x[k],x[k+1],y[k],y[k+1]);
		a[1][k] = fk[1][k]; 
		
	}
	for(int k = 0; k < (N-2); k++)
	{
		fk[2][k] = f(x[k],x[k+2],fk[1][k],fk[1][k+1]);
		a[2][k] = fk[2][k];
	}
	
	for(int k = 0; k < (N-3); k++)
	{
		a[3][k] = f(x[k],x[k+3],fk[2][k],fk[2][k+1]);
	}
	
	
	for(int k = 0; k < (N-1); k++)
	{
		h[k] = delta_x(x[k], x[k+1]);
	}
	
	
	
	for(int k = 0; k < (N-1); k++)
	{
		for(int i = 0; i < n; i++)
		{
			xi[i][k] = x[k] + h[k]*(i+1);
		}
	}
	FILE *output;
	
	output = fopen("dados.txt", "w");
	for(int k = 0; k<N-1; k++)
	{
		for(int i=0,contador=1 ; i<n-1 ; i++,contador++)
		{
			Pn[i][k]=a[0][k]+a[1][k]*(xi[i][k]-x[k])+a[2][k]*(xi[i][k]-x[k])*(xi[i][k]-x[k+1])+a[3][k]*(xi[i][k]-x[k])*(xi[i][k]-x[k+1])*(xi[i][k]-x[k+2]);	
			fprintf(output,"%lf %lf \n",xi[i][k],Pn[i][k]);
			printf("%lf %lf \n",xi[i][k],Pn[i][k]);
		}
	}

	// LIBERANDO MEMÓRIA
	delete y;
	delete x;
	y = NULL;
	x = NULL;
	return 0;
}


/// ------------------- Funções ----------------------------------------
// DIVIDIR O INTERVALO EM "n" SUBINTERVALOS 
double delta_x(double x1,double x2)
{
	return (x2-x1)/n;
} /// end delta_x

// COEFICIENTES: ai e f[x1,...,xn]
double f(double x1,double x2,double y1,double y2)
{
	return (y2-y1)/(x2-x1);
} /// end coeficiente

// ENTRADA DE DADOS
void entrada_de_dados(double *x, double *y, int t)
{
	FILE *arquivo;
	arquivo = fopen(nome,"rt");
    for(int l = 0; l<t; l++)
    {
		fscanf(arquivo, "%lf %lf\n", &x[l], &y[l]);
	}
	
    fclose(arquivo);
} /// end entrada_de_dados

// CONTA A QUANTIDADE DE LINHAS NO ARQUIVO
double quantidades_de_linhas(int i)
{
	FILE *arq;
    char c, letra = '\n';
    arq = fopen(nome,"rt");
    if(arq==NULL)
    {
		printf("ERRO. Sem o arquivo de dados com este nome no diretório do programa. \n");
	}
		
    while(fread (&c, sizeof(char), 1, arq)){
		if(c == letra){
			i++;
		}
	}
	return i;
    fclose(arq);
} /// end quantidades_de_linhas
