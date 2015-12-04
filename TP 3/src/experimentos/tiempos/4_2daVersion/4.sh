#!/bin/bash
videos=('morocho' 'tenis' 'bebes' 'fideos' 'perro' 'cupcake')
#16 26 42 66
cantidad_intermedios=(2 4 6 9)

metodos=(0 1 2)
nombre_metodo=("Mas cercano" "Lineal" "Splines por Bloques")


echo -n "" > sal.csv
echo "--------------------------------"
echo -n "Metodo, Video" >> sal.csv
for I in ${cantidad_intermedios[@]}
do
	echo -n ", $I" >> sal.csv
done
for M in ${metodos[@]}
do
	for vid in ${videos[@]}
	do
		echo "--Metodo: ${nombre_metodo[$M]} -> Video: ${vid}"
		echo "" >> sal.csv
		echo -n "${nombre_metodo[$M]}, ${vid}" >> sal.csv
		for I in ${cantidad_intermedios[@]}
		do
			echo "---- Corriendo: $I"
			tiempo_inicio=$(date +%s%N)/1000000
			./../../../main ../../../tests/${vid}/${vid}_input.in ../../../tests/${vid}/${vid}.sal $M $I 5
			tiempo_fin=$(date +%s%N)/1000000
			rm ../../../tests/${vid}/${vid}.sal
			echo -n ", $((tiempo_fin - tiempo_inicio))" >> sal.csv
		done
	done
done


exit 0