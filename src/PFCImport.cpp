#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h>
#include "Dataset.h"



/*
 * Estrutura da celula n dimensional
 */

/*//Novas estrutudas
typedef struct {
	double xini, yini;
	double xfim, yfim;
	double card;
	double larguraMedia;
	double alturaMedia;
} celula;

typedef struct {
	int qtd_colunas;
	int qtd_linhas;
	celula *matriz;
} histogram;

const int MaxLin = 200;
const int MaxCol = 200;*/

struct Envelope { 
		struct {
			double MinX;
			double MinY;
			double MaxX;
			double MaxY;
		};
	};




typedef struct Envelope Envelope;

//const double limite = 0.8;
//
// const char *datasetName = "municipios" ;
//AQUIVAIOLIMITE
const char *datasetName = "vegeta" ;
const double limite = 0.80;





const double epsilon = 1e-7;
double qtdObjetos = 0;
#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)
void ValidaQtdObjetos(histogram *original);
void printCelula(histogram *original);
void printCelulaFile(histogram *original, FILE * fp);
double histogram_search_hist(histogram *original, Envelope query);

//envelope
const Envelope EnvelopeIntersection(const Envelope r, const Envelope s);
Envelope emptymbr = {0.0, 0.0, 0.0, 0.0};
#define ENVELOPE_AREA(mbr) ((mbr.MaxX - mbr.MinX) * (mbr.MaxY - mbr.MinY))

char ENVELOPE_INTERSECTS(const Envelope mbr1, const Envelope mbr2) {
	//IACA_START
	char result;

	result = (mbr1.MinX <= mbr2.MaxX && mbr1.MinY <= mbr2.MaxY && mbr2.MinX <= mbr1.MaxX && mbr2.MinY <= mbr1.MaxY);
	return result;
}

const Envelope EnvelopeIntersection(const Envelope r, const Envelope s) {
    if (ENVELOPE_INTERSECTS(r, s)) {
        Envelope result;
        result.MinX = r.MinX > s.MinX ? r.MinX : s.MinX;
        result.MinY = r.MinY > s.MinY ? r.MinY : s.MinY;
        result.MaxX = r.MaxX < s.MaxX ? r.MaxX : s.MaxX;
        result.MaxY = r.MaxY < s.MaxY ? r.MaxY : s.MaxY;
        return result;
    }
    else
        return emptymbr;
}

//aqui ele define os valores para o inicio x,y e fim x,y da janela
//	int xini = (query.MinX - c->xini) / limitanteLargura;
//	int xfim = (query.MaxX - c->xini) / limitanteLargura;
//	int yini = (query.MinY - c->yini) / limitanteAltura;
//	int yfim = (query.MaxY - c->yini) / limitanteAltura;

//funcao para fazer a consulta
double histogram_search_hist(histogram *original, Envelope query){
	double result = 0.0;
	const double epsilon = 1e-100;

	//pegando a boarda incial para comecar

	celula *c = GET_CELL(original, 0, 0);

//	printf("query.MinX:%lf query.MaxX:%lf\n "
//		    "query.MinY:%lf query.MaxY:%lf\n"
//			, query.MinX,query.MaxX,
//			query.MinY,query.MaxY);



	//encontrando o query.minX ou o maior menor

	int xxini = 0;

//(query.MaxX - c->xfim) < epsilon
	for (int x = 0; x < original->qtd_colunas; x++) {
		c = GET_CELL(original, x, 0);
			//o numero tem que ser menor ou igual que MinX e ser o maior deles
//		&& (c->xini - xini) > epsilon
//		printf("c->xini:%lf\nquery.MinX:%lf\n",
//				c->xini,
//				query.MinX);

			if((c->xini - query.MinX) < epsilon   ){
				xxini++;

//				printf("entrou:\n");

			}

	}
	xxini--;
//	printf("xxini:%d\n", xxini);


	//encontrando o query.MaxX ou o menor maior


	int xxfim = 0;
	for (int x = 0; x < original->qtd_colunas; x++) {
		c = GET_CELL(original, x, 0);
//		printf("c->xfim:%lf\nquery.MaxX:%lf\n",
//					c->xfim,
//					query.MaxX);

			if(!((query.MaxX - c->xfim) < epsilon)  ){
//				printf("entrou:\n");
				xxfim++;
			}

	}
//	printf("xxfim:%d\n", xxfim);


	//encontrando o query.minY ou o maior menor

	int  yyini = 0;
	for (int y = 0; y < original->qtd_linhas; y++) {
		c = GET_CELL(original, 0, y);
//		printf("c->yini:%lf\nquery.MinY:%lf\n",
//					c->yini,
//					query.MinY);
			//o numero tem que ser menor ou igual que MinX e ser o maior deles
			if(c->yini - query.MinY  < epsilon  ){
//				printf("entrou:\n");
				yyini++;
			}

	}
	yyini--;
//	printf("yyini:%d\n", yyini);

	//encontrando o query.MaxY ou o menor maior
	int yyfim = 0;
	for (int y = 0; y < original->qtd_linhas; y++) {
		c = GET_CELL(original, 0, y);
//		printf("c->yfim:%lf\nquery.MaxY:%lf\n",
//							c->yfim,
//							query.MaxY);

			if(!(query.MaxY - c->yfim  < epsilon)  ){

				yyfim++;
			}

	}
	// printf("yyfim:%d\n", yyfim);


	for(int x = xxini; x <= xxfim; x++) {
		Envelope rs;

		c = GET_CELL(original, x, 0);
//		printf("%lf\n", c->xini);
		rs.MinX = c->xini;


	//	c = GET_CELL(original, x+1, 0);
//		printf("%lf\n", c->xfim);
		rs.MaxX = c->xfim;

		for(int y = yyini; y <= yyfim; y++) {

			c = GET_CELL(original, 0, y);
			rs.MinY = c->yini ;
//			printf("yy%lf\n", c->yini);

//			c = GET_CELL(original, 0, y+1);
			rs.MaxY = c->yfim;
//			printf("yy%lf\n", c->yfim);

			//printf("x:%d y:%d\n", x,y);

			c = GET_CELL(original, x, y);
			if (ENVELOPE_INTERSECTS(query, rs)) {
				Envelope inters = EnvelopeIntersection(query, rs);
				double int_area = ENVELOPE_AREA(inters);
//				printf("int_area:%lf\n", int_area);
				double bucket_area = ENVELOPE_AREA(rs);
//				printf("bucket_area:%lf\n", bucket_area);
				double fraction = int_area / bucket_area;
//				printf("fraction:%lf\n", fraction);
				result += fraction * c->card;
//				printf("card:%lf\n", c->card);
//				printf("result:%lf\n", result);
			}
		}
	}
	result += 0.00001;
	return result;
}



histogram* metodoSimples(histogram *original, int modo, int xinicial,
		int yinicial);

//#define GET_CELL(h, i,j) (&((h)->matriz[ (i) * (h)->qtd_linhas + (j)]))

//ainda nao esta implementada
//quando chegar a h1 e o query,


void print_hist(histogram *h1, char nome) {
	char filename[100];

	sprintf(filename, "hist-%s.shp-%dx%d-%.2f-RG.geojson", datasetName, h1->qtd_colunas, h1->qtd_linhas, limite);
	FILE *f = fopen(filename, "wb");
	if (f == NULL) {
		perror("Error printing histogram");
		return;
	}

	fprintf(f, "{'type': 'FeatureCollection', 'features': [\n");



	for (int x = 0; x < h1->qtd_colunas; x++) {
		for (int y = 0; y < h1->qtd_linhas ; y++) {

			celula *c = GET_CELL(h1, x, y);

			fprintf(f,
					"{\"type\": \"Feature\", \"geometry\": {\"type\": \"Polygon\", \"coordinates\": [[");
			fprintf(f, "[%f, %f],", c->xini, c->yini);
			fprintf(f, "[%f, %f],", c->xfim, c->yini);
			fprintf(f, "[%f, %f],", c->xfim, c->yfim);
			fprintf(f, "[%f, %f],", c->xini, c->yfim);
			fprintf(f, "[%f, %f]", c->xini, c->yini);
			fprintf(f, "]]}, 'properties': {");
			fprintf(f, "\"name\": \"%d.%d\",", x, y);

			fprintf(f, "\"card\": %f,", c->card);
			fprintf(f, "\"points\": 0.000000,");
			fprintf(f, "\"place\": 0,");
			fprintf(f, "\"avgwidth\": %f,", c->larguraMedia);
			fprintf(f, "\"avgheight\": %f,", c->alturaMedia);

			fprintf(f, "}},\n");

		}
	}

	fprintf(f, "]}\n");
	fclose(f);
}

void printCelula(histogram *h1) {

	for (int x = 0; x < h1->qtd_colunas; x++) {
		for (int y = 0; y < h1->qtd_linhas ; y++) {
			celula *c = GET_CELL(h1, x, y);
			printf("{(%f, %f);", c->xini, c->yini);
			printf(" (%f, %f)} ", c->xfim, c->yfim);
			printf("c: %f l: %f a: %f\t", c->card, c->larguraMedia,
					c->alturaMedia);

		}
		printf("\n\n");
	}
	printf("Terminou de imprimir o histograma\n");

}

void printCelulaFile(histogram *h1, FILE * fp) {
	for (int x = 0; x < h1->qtd_colunas; x++) {
			for (int y = 0; y < h1->qtd_linhas ; y++) {
			celula *c = GET_CELL(h1, x, y);
			fprintf(fp, "{(%f, %f);", c->xini, c->yini);
			fprintf(fp, " (%f, %f)} ", c->xfim, c->yfim);
			fprintf(fp, "c: %f l: %f a: %f\t", c->card, c->larguraMedia,
					c->alturaMedia);

		}
		fprintf(fp, "\n\n");
	}
	fprintf(fp, "Terminou de imprimir o histograma\n");

}
bool doubleEqual(double a, double b) {
	return fabs(a - b) < epsilon;
}

void ValidaQtdObjetos(histogram *original) {

	if (qtdObjetos == 0) {
		for (int x = 0; x < original->qtd_colunas; x++) {
					for (int y = 0; y < original->qtd_linhas; y++) {
				celula *c = GET_CELL(original, x, y);

				qtdObjetos += c->card;

			}

		}

	} else {
		double qtdObjAftMethodo = 0;
		for (int x = 0; x < original->qtd_colunas; x++) {
					for (int y = 0; y < original->qtd_linhas; y++) {
				celula *c = GET_CELL(original, x, y);

				qtdObjAftMethodo += c->card;

			}

		}

		if (doubleEqual(qtdObjetos, qtdObjAftMethodo)) {
			printf("Quantidade de objetos eh a MESMA, %f\n", qtdObjetos);
		} else {
			printf("Quantidade de objetos eh a DIFERENTE, %.15f != %.15f \n",
					qtdObjetos, qtdObjAftMethodo);
		}

	}

}

/**
 * Funcao para printar na tela
 * modo == 0 - linha
 * modo == 1 - coluna
 *
 */
histogram* metodoSimples(histogram *original, int modo, int xinicial,
		int yinicial) {
	//declaracao das estruturas auxiliares

	double somaMedias = 0;

	//Modo linha
	if (modo == 0) {
		int contCelzero = 0;
		for (int x = 0; x < original->qtd_colunas; ++x) {
			celula *origi = GET_CELL(original, x, xinicial);

			somaMedias = somaMedias + (origi->alturaMedia * origi->card);
// 			if (origi->alturaMedia < epsilon){
// //				printf("col: %d lin: %d tem alturaZero: %f\n", x,xinicial, origi->alturaMedia);
// 				contCelzero++;
// 			}

		}
		 printf("Antes somaMedias: %f\n", somaMedias);
		// somaMedias = somaMedias / ((original->qtd_colunas - contCelzero) == 0 ? 1 : (original->qtd_colunas - contCelzero));

		somaMedias = somaMedias / original->qtd_colunas;
		celula *origi = GET_CELL(original, 0, xinicial);
		printf("yfim:%f - yini:%f = %f. Qts vezes o limitanteAltura:%f\n", origi->yfim, origi->yini, origi->yfim - origi->yini, (origi->yfim - origi->yini) / limitanteAltura );
		printf("Dps somaMedias: %f\nlimitanteAltura:%f\n", somaMedias, limitanteAltura);


		//Verifico se a soma das medias ficou => 80% da comprimento da dimensão da celula
//		if (somaMedias >= (limitanteAltura * limite) || somaMedias < epsilon) {
		if (somaMedias >= (((origi->yfim) - (origi->yini))) || somaMedias < epsilon) {
			printf("Entrou\n");

			for (int k = 0; k < original->qtd_colunas; ++k) {

				celula *origi = GET_CELL(original, k, xinicial);
				celula *origiProx = GET_CELL(original, k, xinicial + 1);
//				printf("{(%f, %f);", origi->xini, origi->yini);
//				printf(" (%f, %f)} c: %f \n", origi->xfim, origi->yfim,
//						origi->card);
//
//				printf("{(%f, %f);", origiProx->xini, origiProx->yini);
//				printf(" (%f, %f)} c: %f \n", origiProx->xfim, origiProx->yfim,
//						origiProx->card);
//
//				printf("Antes: %f\n", origi->alturaMedia);

				//como faco uma divisao, se nao tiver card em nenhum das col/lin, da uma divisao por 0.
				if ((origi->card) == 0 || (origiProx->card) == 0) {
					if ((origi->card) == 0) {

//						printf("Original == 0\n");
						origi->alturaMedia = origiProx->alturaMedia;

						origi->larguraMedia = origiProx->larguraMedia;

					} else {
					//	printf("OriginalProx == 0\n");
						//a partir daqui se der merda

					}
				} else {
				//	printf("Nada de zeros\n");

					origi->alturaMedia = ((origi->card * origi->alturaMedia)
							+ (origiProx->card * origiProx->alturaMedia))
							/ (origiProx->card + origi->card);

					origi->larguraMedia = ((origi->card * origi->larguraMedia)
							+ (origiProx->card * origiProx->larguraMedia))
							/ (origiProx->card + origi->card);

				}

				origi->card = origi->card + origiProx->card;
			//	printf("Depos: %f\n", origi->alturaMedia);

				origi->yfim = origiProx->yfim;

			}

			histogram* mod = (histogram*) malloc(sizeof(histogram));
			mod->qtd_colunas = original->qtd_colunas;
			mod->qtd_linhas = original->qtd_linhas - 1;
			mod->matriz = (celula*) malloc(
					sizeof(celula) * MaxLin * MaxCol);

			int cont = 0;

			for (int x = 0; x < original->qtd_colunas; x++) {
				//ignorando a linha que foi mergada com a anterior

				for (int y = 0; y < original->qtd_linhas; y++) {

					if ((xinicial + 1) != y) {
						celula *origi = GET_CELL(original, x, y);

						celula *novo = GET_CELL(mod, x, cont);

						novo->xini = origi->xini;
						novo->yini = origi->yini;
						novo->xfim = origi->xfim;
						novo->yfim = origi->yfim;
						novo->card = origi->card;
						novo->larguraMedia = origi->larguraMedia;
						novo->alturaMedia = origi->alturaMedia;
						cont++;
					}

				}
				cont = 0;

			}

			free(original);

			return (mod);
		}

	}
	//------------------------------------------------------------------
//	Modo coluna
//	-----------------------------------
	else {
		int contCelzero = 0;
		for (int y = 0; y < original->qtd_linhas; ++y) {
			celula *origi = GET_CELL(original, yinicial, y);

			somaMedias = somaMedias +  (origi->larguraMedia * origi->card);
			// if (origi->alturaMedia == 0) contCelzero++;
		}
//		printf("Antes somaMedias: %f\n", somaMedias);
		// somaMedias = somaMedias
		// 		/ ((original->qtd_linhas - contCelzero) == 0 ?
		// 				1 : (original->qtd_linhas - contCelzero));

		somaMedias = somaMedias / original->qtd_linhas;

		//preciso calcular assim
		//medo o tamanho fixo inicial, faço uma diferença entre xfim - xini e divido este valor pelo limitanteLargura


		celula *origi = GET_CELL(original, yinicial, 0);
//		printf("Dps somaMedias: %f\nlimitanteLargura * limite: %f\n", somaMedias, limitanteLargura * limite);
//		printf("xfim: %f xini: %f\n", origi->xfim, origi->xini);
//		printf("Limitante: %f\n", (fabs(fabs(origi->xfim) - fabs(origi->xini))) );

		//Verifico se a soma das medias ficou >> 80% da comprimento da dimensão da celula
//		if (somaMedias >= (limitanteLargura * limite) || somaMedias < epsilon) {
		if ((somaMedias >= (origi->xfim - origi->xini)) || somaMedias < epsilon) {

			for (int k = 0; k < original->qtd_linhas; ++k) {

				celula *origi = GET_CELL(original, yinicial, k);
				celula *origiProx = GET_CELL(original, yinicial + 1, k);
//				printf("{(%f, %f);", origi->xini, origi->yini);
//				printf(" (%f, %f)} c: %f \n", origi->xfim, origi->yfim,
//						origi->card);
//
//				printf("{(%f, %f);", origiProx->xini, origiProx->yini);
//				printf(" (%f, %f)} c: %f \n", origiProx->xfim, origiProx->yfim,
//						origiProx->card);
//
//				printf("Antes: %f\n", origi->larguraMedia);

				//como faco uma divisao, se nao tiver card em nenhum das col/lin, da uma divisao por 0.
				if ((origi->card) == 0 || (origiProx->card) == 0) {
					if ((origi->card) == 0) {

//						printf("Original == 0\n");
						origi->alturaMedia = origiProx->alturaMedia;

						origi->larguraMedia = origiProx->larguraMedia;

					} else {
						// printf("OriginalProx == 0\n");

					}
				} else {
		//			printf("Nada de zeros\n");

					origi->alturaMedia = ((origi->card * origi->alturaMedia)
							+ (origiProx->card * origiProx->alturaMedia))
							/ (origiProx->card + origi->card);

					origi->larguraMedia = ((origi->card * origi->larguraMedia)
							+ (origiProx->card * origiProx->larguraMedia))
							/ (origiProx->card + origi->card);

				}

				origi->card = origi->card + origiProx->card;
		//		printf("Depos: %f\n", origi->larguraMedia);

				origi->xfim = origiProx->xfim;

			}

			histogram* mod = (histogram*) malloc(sizeof(histogram));
			mod->qtd_colunas = original->qtd_colunas - 1;
			mod->qtd_linhas = original->qtd_linhas;
			mod->matriz = (celula*) malloc(
					sizeof(celula) * MaxLin * MaxCol);

			int cont = 0;

			for (int x = 0; x < original->qtd_colunas; x++) {
				//ignorando a coluna que foi mergada com a anterior

				if ((yinicial + 1) == x) {
					x++;
				}
				for (int y = 0; y < original->qtd_linhas; y++) {

					celula *origi = GET_CELL(original, x, y);

					celula *novo = GET_CELL(mod, cont, y);

					novo->xini = origi->xini;
					novo->yini = origi->yini;
					novo->xfim = origi->xfim;
					novo->yfim = origi->yfim;
					novo->card = origi->card;
					novo->larguraMedia = origi->larguraMedia;
					novo->alturaMedia = origi->alturaMedia;

				}
				cont++;


			}

			free(original);

			return (mod);
		}

	}

	return (original);

}

double Random(double min, double max) {
	double random = ((double) rand()) / (double) RAND_MAX;
	double diff = max - min;
	double mult = random * diff;
	return (min + mult);
}

int main() {

	//TODO 1: Toda linha/coluna que tiver a media = 0 deve ter merged com aproxima  - DONE
	//TODO 2: Fazer funcao para validar histogram.card.inicial == histogram.card.final - TEM QUE SEREM IGUAIS - DONE
	//TODO 3: Incluir aqui a funcao que gera o geojason, e printar o histograma depois e comparar no QGIS
	//TODO 3: Fazer a validacao das medias das colunas/linhas antes e depois do método completo
	srand(time(NULL));
//    struct cel celulaXY[MaxLin][MaxCol];

//Adicionado o código do Thiago

/*	histogram* h1 = (histogram*) malloc(sizeof(histogram));
	h1->qtd_colunas = MaxCol;
	h1->qtd_linhas = MaxLin;
	h1->matriz = (celula*) malloc(
			sizeof(celula) * h1->qtd_colunas * h1->qtd_linhas);

	//Inicio Teste real

	celula *c;*/

	histogram* h1 = importarHistograma();

//	printCelula(h1);



	//Fim Teste real

	ValidaQtdObjetos(h1);

	// print_hist(h1, 'A');

//	FILE * fp;
//	fp = fopen("file.txt", "w+");
//	printCelulaFile(h1, fp);
	// printCelula(h1);

	printf("\ninicio\n");


//	//Linha
	int merge = MaxCol;
	int xinicial = 0;
	int qtd_lin = h1->qtd_linhas - 1;

	for (int cont = 0; cont < qtd_lin; cont++) {
		h1 = metodoSimples(h1, 0, xinicial, 0);

//		 printf("qtd: %d \n", h1->qtd_linhas);

		if (h1->qtd_linhas != merge) {

			xinicial--;
			merge--;
		}

		xinicial++;
//		printCelula(h1);
//		printf("Mandando a linha: %d para ser comparada com a proxima \n" , xinicial + 1);
//		printCelulaFile(h1, fp);

	}

	//Coluna
	merge = MaxLin;
	int yinicial = 0;
	// -1 para nao comparar a ultima com ??
	int qtd_col = h1->qtd_colunas - 1;

	for (int cont = 0; cont < qtd_col; cont++) {
		h1 = metodoSimples(h1, 1, 0, yinicial);

		// printf("qtd: %d \n", h1->qtd_colunas);

		if (h1->qtd_colunas != merge) {

			yinicial--;
			merge--;
		}

		yinicial++;
//		printCelula(h1);
//		printf("Mandando a coluna: %d para ser comparada com a proxima \n" , yinicial + 1);
//		printCelulaFile(h1, fp);

	}


	ValidaQtdObjetos(h1);

	printf("%dx%d\n",h1->qtd_colunas,h1->qtd_linhas);

	 print_hist(h1, 'D');


	/*
	 * TODO:Inicio da parte da consulta - não preciso
	 */

	int qtd = 500;
	//tenho que ler o arquivo
	char filename1[100];

	// sprintf(filename, "hist-%s.shp-%dx%d-%.2f-RG.geojson", datasetName, MaxX, MaxY, limite);

	sprintf(filename1, "hist-%s.shp-%.2f-%dx%d-RG-Results.txt", datasetName, limite, h1->qtd_colunas, h1->qtd_linhas);

	FILE *consulta;
	FILE *resultadoconsultaNrafael;

	consulta=fopen("consulta.txt", "r");
	resultadoconsultaNrafael=fopen(filename1, "wb");

	if (consulta == NULL || resultadoconsultaNrafael == NULL)
		{
    		printf("Error opening file!\n");
    		exit(1);
		}


//	double query_size = 0.5;
//	double width = limitanteLargura;
//	double height = limitanteAltura;

	int n = 0;
	fprintf(resultadoconsultaNrafael,"estimativaRG-%.2f-%dx%d\n", limite, h1->qtd_colunas, h1->qtd_linhas);
	while(n < qtd){
		n++;
		Envelope query;

		fscanf(consulta,"%lf",&query.MinX);
		fscanf(consulta,"%lf",&query.MinY);
		fscanf(consulta,"%lf",&query.MaxX);
		fscanf(consulta,"%lf",&query.MaxY);
//
//		printf( "%e %e %e %e\n",
//		        	query.MinX, query.MinY,
//		        	query.MaxX, query.MaxY
//		        	);



// 		char wkt[512];
//    	sprintf(wkt, "POLYGON((%e %e, %e %e, %e %e, %e %e, %e %e))",
//        	query.MinX, query.MinY,
//        	query.MaxX, query.MinY,
//        	query.MaxX, query.MaxY,
//        	query.MinX, query.MaxY,
//        	query.MinX, query.MinY);


		int rhq = histogram_search_hist(h1, query);
		
		fprintf(resultadoconsultaNrafael,"%d\n",rhq);

		// fprintf(resultadoconsultaNrafael,"Query %d: e: %d\n", n, rhq);




	}


    fclose(resultadoconsultaNrafael);
	fclose(consulta);


		/*
		 * TODO: Fim da parte da consulta - não preciso
		 */
	free(h1);

	return 0;
}


