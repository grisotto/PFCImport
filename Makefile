SHELL := /bin/bash
CC= g++
SHAPES= municipios
# SHAPES= alertas charminar Crops elevcontour hidrografia hydroinland municipios Railroads railways Rivers roads rodovia vegeta 
NXN=50

LIMITE= 0.75 0.76 0.77 0.78 0.79 0.80 0.81 0.82 0.83 0.84 0.85 0.86 0.87 0.88 0.89 0.90 0.91
# LIMITE= 0.75


DATASET = ab
#primeira parte: roda o dgeo e copia o arquivo exportado para a pasta parte1
#pega esta arquivo manualmente e roda o vim com o regex
#este arquivo eh gerado com nome padrao que o meu codigo ja reconhece como um header
#rodo o meu codigo com este "header" atualizado
#o vim roda o regex, mas no maximo 10 comandos 
#vim -c %s/class=".\{-}"//g -c :wq dash.html
#removendo nan 
#vim -c %s/-nan/0/g -c wq 
#sed -i.bak '/AQUI/ r fazer.geojson' rafael.txt
#$(SHAPES)
#fazer a leitura do arquivo csv
#	$(MAKE) -C dgeohistogram geojson


all: $(SHAPES)

	

$(SHAPES): 
	@echo Primeira parte para o: $@
	@cd dgeohistogram && echo "To no dgeohistogram" && \
	./main areaf fix $(NXN) $(NXN) ../shapes/$@.shp 0.05
	cp dgeohistogram/histogram/{hist-$@.shp.geojson,hist-$@.shp-$(NXN)x$(NXN)-parametros.txt,hist-$@.shp-$(NXN)x$(NXN)-resultados.txt,consulta.txt} parte1/
	@echo 'Vamos tirar os nan, primeira linha e ultima linha'
	@cd parte1 && vim -c %s/-nan/0/g -c wq  hist-$@.shp.geojson && \
	vim -c 1d -c wq  hist-$@.shp.geojson && \
	cp hist-$@.shp.geojson hist-$@.shp.geojson.tmp && \
	head -n -1 hist-$@.shp.geojson.tmp > hist-$@.shp.geojson && \
	./transformC.sh hist-$@.shp.geojson
	@echo copiando para o dataset
	cp parte1/{hist-$@.shp.geojson,hist-$@.shp-$(NXN)x$(NXN)-parametros.txt,hist-$@.shp-$(NXN)x$(NXN)-resultados.txt,consulta.txt} ./ 
	sed -i.bak '/AQUICOMECA/ r hist-$@.shp.geojson' Dataset.cpp
	sed -i.bak '/AQUILIMITESELIMITANTE/ r hist-$@.shp-$(NXN)x$(NXN)-parametros.txt' Dataset.h
	$(MAKE) $(LIMITE)
	cp Dataset.cpp Dataset_$@_$(NXN).cpp
	cp Dataset.cpp.bak Dataset.cpp && rm Dataset.cpp.bak
	cp Dataset.h Dataset_$@_$(NXN).h
	cp Dataset.h.bak Dataset.h && rm Dataset.h.bak

$(LIMITE):	
	sed -i.bak '/AQUIVAIOLIMITE/a const double limite = $@;\n char const *datasetName = "$(SHAPES)";' PFCImport.cpp
	g++ -std=c++11 PFCImport.cpp Dataset.cpp -o pfc_$(SHAPES)_$(NXN)_$@
	cp PFCImport.cpp PFCImport_$(SHAPES)_$(NXN)_$@.cpp
	cp PFCImport.cpp.bak PFCImport.cpp && rm PFCImport.cpp.bak
	./pfc_$(SHAPES)_$(NXN)_$@


clear:
	rm -f *.txt *.geojson



		
		