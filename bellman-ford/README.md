# Algoritmo de Bellman Ford

O Algoritmo de Bellman-Ford tem a função de ser um algoritmo de busca de caminho mínimo em um digrafo, por sua vez utilizando números negativos.

## Compilação e execução

* Sistema Operacional: Ubuntu;
* Para compilar é necessário está no diretório ```bellman-ford``` e digitar ```ubuntu```;
* O arquivo ```.bin``` vai para o diretório ```bin/```;
* As entradas testadas estão no diretório ```bellman-ford/input/```;
* As saídas estão no diretório ```bellman-ford/output/```.

## Entrada do algoritmo

```ubuntu
n m
v1 v2 p
. . .
. . .
. . .
vn vn pn
```

* n é o número de vertices;
* m é o número de arestas;
* O par de v's (v1 v2) são as arestas;
* p é o peso das arestas.

## Saída do algoritmo

* O formato será em ``vértice``:``valor até chegar nele`` partindo do vértice informado pelo comando -i;
* Caso não seja informado o vértice pelo comando -i, o mesmo vai utilizar o vertice 1 para o algortimo.

## Exemplo de execução

No diretorio principal do projeto digite:

```ubuntu
./bin/bellman.bin -f bellman-ford/input/entrada.mtx -i 1 
```

Saída no terminal:
```ubuntu
1:0 2:5 3:3 4:3 5:1 6:2 
```

Para salvar em um arquivo:

```ubuntu
./bin/bellman.bin -f bellman-ford/input/input-0.mtx -i 1 -o bellman-ford/output/output-0.mxt

```
