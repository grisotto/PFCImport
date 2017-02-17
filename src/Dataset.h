
#ifndef DATASET_H_
#define DATASET_H_
#define GET_CELL(h, i,j) (&((h)->matriz[ (i) * (h)->qtd_linhas + (j)]))
//AQUILIMITESELIMITANTE

//const int MaxLin = 200;
//const int MaxCol = 200;
//const double limitanteLargura = 0.225792;
//const double limitanteAltura = 0.195139  ;



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
