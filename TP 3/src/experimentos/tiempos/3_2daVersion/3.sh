#!/bin/bash 
#
videos=('morocho' 'tenis' 'bebes' 'fideos' 'perro' 'cupcake')
tamano_bloque=(5 10 20 40 80)

echo -n "" > sal.csv
echo -n "" > sal_mem.csv
echo -n "Video" >> sal.csv
echo -n "Video" >> sal_mem.csv
for I in ${tamano_bloque[@]}
do
	echo -n ", $I" >> sal.csv
	echo -n ", $I" >> sal_mem.csv
done

for vid in ${videos[@]}
do
	echo "--Video: ${vid}"
	echo "" >> sal.csv
	echo "" >> sal_mem.csv
	echo -n "${vid}" >> sal.csv
	echo -n "${vid}" >> sal_mem.csv
	for I in ${tamano_bloque[@]}
	do
		echo "---- Corriendo: $I"
		tiempo_inicio=$(date +%s%N)/1000000
		mem=$(./../../../main ../../../tests/${vid}/${vid}_input.in ../../../tests/${vid}/${vid}.sal 2 2 $I)
		tiempo_fin=$(date +%s%N)/1000000
		rm ../../../tests/${vid}/${vid}.sal
		echo -n ", $((tiempo_fin - tiempo_inicio))" >> sal.csv
		echo -n ", $mem" >> sal_mem.csv
	done
done

exit 0
