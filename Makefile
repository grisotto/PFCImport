CC= g++
SHAPES= alertas charminar Crops elevcontour hidrografia hydroinland municipios Railroads railways Rivers roads rodovia vegeta 
NXN=20

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


all: alertas
#	$(MAKE) -C dgeohistogram geojson
	

alertas: 
	@echo Primeira parte para o: $@
	@cd dgeohistogram && echo "To no dgeohistogram" && \
	./main areaf fix $(NXN) $(NXN) ../shapes/$@.shp 0.05
	cp dgeohistogram/histogram/hist-$@.shp.geojson parte1/
	@echo 'Vamos tirar os nan, primeira linha e ultima linha'
	@cd parte1 && vim -c %s/-nan/0/g -c wq  hist-$@.shp.geojson && \
	vim -c 1d -c wq  hist-$@.shp.geojson && \
	cp hist-$@.shp.geojson hist-$@.shp.geojson.tmp && \
	head -n -1 hist-$@.shp.geojson.tmp > hist-$@.shp.geojson && \
	./transformC.sh hist-$@.shp.geojson
	@echo copiando para o dataset
	cp parte1/hist-$@.shp.geojson ./ 
	sed -i.bak '/AQUICOMECA/ r hist-$@.shp.geojson' Dataset.cpp
	g++ -std=c++11 PFCImport.cpp Dataset.cpp -o pfc_$@_$(NXN)
	cp Dataset.cpp Dataset_$@_$(NXN).cpp
	cp Dataset.cpp.bak Dataset.cpp



		
		