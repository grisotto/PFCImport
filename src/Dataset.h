
#ifndef DATASET_H_
#define DATASET_H_
#define GET_CELL(h, i,j) (&((h)->matriz[ (i) * (h)->qtd_linhas + (j)]))
const int MaxLin = 100;
const int MaxCol = 100;
const double limitanteLargura = 0.451583;
const double limitanteAltura = 0.390278 ;
//AQUILIMITESELIMITANTE






//Novas estrutudas
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




histogram* importarHistograma ();



#endif /* DATASET_H_ */
