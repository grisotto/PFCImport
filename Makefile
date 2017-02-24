SHELL := /bin/bash
CC= g++
SHAPES= vegeta
# SHAPES= alertas charminar Crops elevcontour hidrografia hydroinland municipios Railroads railways Rivers roads rodovia vegeta 
NXN=200

# LIMITE= 0.50 0.53 0.56 0.60 0.63 0.66 0.70 0.73 0.76 0.80 0.83 0.86 0.90
LIMITE= 0.50 0.52 0.54 0.56 0.58 0.60 0.62 0.64 0.66 0.68 0.70 0.72 0.74 0.76 0.78 0.80 0.82 0.84 0.86 0.88 0.90 0.92 0.94 1.0
# LIMITE = 1.0


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
	# @cd parte1 && vim -c %s/-nan/0/g -c wq  hist-$@.shp.geojson && \
#vim -c %s/-nan/0/g -c wq  hist-$@.shp.geojson
	# $(eval TMP := $@)
	# @echo hi $(TMP)

# informacoes:
# 	municipios sempre quando a consulta retorna 24 no origianl e 25 no meu!!
	# railways deu um erro retorn 4 e no meu 5
	# rodovia deu um erro retorno 8 e no meu 7
	# vegeta deu um erro retorno 24 e no meu 25

all: $(SHAPES)

	

$(SHAPES): 
	@echo Primeira parte para o: $@
	@cd dgeohistogram && echo "To no dgeohistogram" && \
	./main areaf fix $(NXN) $(NXN) ../shapes/$@.shp 0.05
	cp dgeohistogram/histogram/{hist-$@.shp.geojson,hist-$@.shp-$(NXN)x$(NXN)-parametros.txt,hist-$@.shp-$(NXN)x$(NXN)-resultados.txt,consulta.txt} parte1/
	@echo 'Vamos tirar a primeira linha e ultima linha'
	@cd parte1 && vim -c 1d -c wq  hist-$@.shp.geojson && \
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
	paplay /usr/share/sounds/freedesktop/stereo/complete.oga

$(LIMITE):	
	sed -i.bak '/AQUIVAIOLIMITE/a const double limite = $@;\n char const *datasetName = "$(SHAPES)";' PFCImport.cpp
	g++ -std=c++11 PFCImport.cpp Dataset.cpp -o pfc_$(SHAPES)_$(NXN)_$@
	cp PFCImport.cpp.bak PFCImport.cpp && rm PFCImport.cpp.bak
	./pfc_$(SHAPES)_$(NXN)_$@
	rm pfc_$(SHAPES)_$(NXN)_$@


clear:
	rm -f *.txt *.geojson



		
		