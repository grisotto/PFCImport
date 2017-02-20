# PFC2 - Rafael Grisotto

Divisão de histograma

[![Divisão do histograma](/image/histograma.png)](https://computacao.jatai.ufg.br/)
## Atualizações
* __2.5__ (13/01/17): Método validado por três datasets - municipios, alertas e rodovia.
    * Resultado e figuras estao na pasta [Resultados/][results]


    **Tabela Comparativa**


|   | Granularidade(n x n)                          | Granularidade Após | Validação quantidade objetos | Validação de celulas pelo QGIS | prefixo arquivo |
|---|:------------:|:------------:|:------------:|:------------:|:------------:|
| Municipios |   `10x10`, `50x50`, `100x100`   |  `6x6`, `17x6`, `100x100`            |   <a href="url"><img src="http://image.flaticon.com/icons/png/128/9/9260.png" height="16" width="16" > <img src="http://image.flaticon.com/icons/png/128/9/9260.png" height="16" width="16" > <img src="http://image.flaticon.com/icons/png/128/9/9260.png" height="16" width="16" ></a>           |    Validação simples          |  mun-{dgeo, antes, deps}-nxn             |             
| Alertas |    `50x50`, `100x100`  |  `50x50`, `100x100`    |     <a href="url"><img src="http://image.flaticon.com/icons/png/128/9/9260.png" height="16" width="16" > <img src="http://image.flaticon.com/icons/png/128/9/9260.png" height="16" width="16" > <img src="http://image.flaticon.com/icons/png/128/9/9260.png" height="16" width="16" ></a>          |    Validação simples                       | ale-{dgeo, antes, deps}-nxn              |              
| Rodovia |     `50x50`, `200x200`          |  `45x36`, `98x23`            |   <a href="url"><img src="http://image.flaticon.com/icons/png/128/9/9260.png" height="16" width="16" > <img src="http://image.flaticon.com/icons/png/128/9/9260.png" height="16" width="16" > <img src="http://image.flaticon.com/icons/png/128/9/9260.png" height="16" width="16" ></a>  |    Validação simples               | rod-{dgeo, antes, deps}-nxn             | 

* __2.3__ (12/01/17): Método validado por um dataset real
    * Testando com o dataset municipios e o mesmo gerou o geojson correto e esta na figura abaixo.

* __2.0__ (03/01/17): Gerando arquivo geojson e erros visuais do método
    * **Já temos a primeira figura do método!! e o método esta funcionando, falta apenas fechar o canto haha**
    [![Municipios antes](/image/municipios-antesMetodo.png)]
    [![Municipios depois](/image/municipios-depoisMetodo.png)]


* __1.6__ (22/12/16): Teste com histograma real e correção de falhas encontradas.
    * **Células com card = 0 serão ignoradas da soma e da divisão.**
    * Verificação de divisão por 0.
    * Definidos constantes do tamanho de altura e largura.
    * Corrigidos erros de leak de memory.


* __1.5__ (20/12/16): Utilizando idea do Thiago
    * Usando #define para buscar "matrix" dentro do vetor.
    * O metodo ficou mais simples, resolve uma linha/coluna por vez.
    * Funcinando por completo para os dois casos básicos, não faz nenhum merge ou todos os merges.



* __1.2__ (01/12/16): Separação das duas formas de resolver o problema
    * Planos para mudança da forma para fazer com vetor, assim atualizando o tamanho do histograma a cada merge de col/lin.


* __1.1__ (30/11/16): Separação das duas formas de resolver o problema
    * Foi implementado o metodo da forma independente e parcialmente a forma de merge entre o histogramLargura e o histogramaAltura. A lógica pronta esta no caderno.

    * *Forma 1* - Modo independente de dimensão. Mesmo removendo uma linha/coluna, eu mantenho os dados das celulas na outra dimensão.
    * *Forma 2* - Modo dependente de dimensão. Removendo uma linha/coluna, eu atualizo a quantidade deta e também da granulidade.
    

   
* __1.0__ (23/11/16): Aleatórios e primeiros testes
    * Números aleatorios com min e maximo
    * Funcao de impressao pronta

Comentários:
```
O método esta muito simples ainda, precisa de mais aprimoramento.
```


    
[results]: <https://github.com/grisotto/PFC2/tree/master/Resultados>