#!/bin/bash

# Binários
prim=./prim.bin
kruskal=./kruskal.bin
dijkstra=./dijkstra.bin

echo -e "\n";

echo "Testando algoritmo de Kruskal"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	val=$($kruskal -f $i);
	correto=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2);
	if [ $val -eq $correto ]; then 
		echo -e "Custo \e[32mOK\e[0m"; 
	else	
		echo  -e "\e[31mCusto incorreto\e[0m";
	fi

	$kruskal -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mNão é um subgrafo\e[0m";
	fi

done

echo -e "\n";

echo "Testando algoritmo de Prim"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	val=$($prim -f $i);
	correto=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2);
	
	if [ $val -eq $correto ]; then 
		echo -e "Custo \e[32mOK\e[0m";
		else 
		echo  -e "\e[31mCusto incorreto\e[0m";
	fi

	$prim -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m";
	else
		echo -e "\e[31mNão é um subgrafo\e[0m";
	fi

done

echo -e "\n";

echo "Testando algoritmo de Dijkstra"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	j=$(basename $i);
	$dijkstra -f $i > temp;
	diff -w temp ./sp/$j > /dev/null ;

	rm temp;
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mErro\e[0m";
	fi

done