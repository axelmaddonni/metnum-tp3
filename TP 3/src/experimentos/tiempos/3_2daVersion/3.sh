#!/bin/bash
videos=('morocho' 'tenis' 'bebes' 'fideos' 'perro' 'cupcake')
tamano_bloque=(5 10 20 30 40 60 80)

echo -n "" > sal.csv
echo -n "" > sal_mem.csv
echo -n "Video" >> sal.csv
echo -n "Video" >> sal_mem.csv
for I in ${tamano_bloque[@]}
do
	echo -n ", $I" >> sal.csv
	echo -n ", $I" >> sal_mem.csv
done

cantidad_repeticiones=4
declare -a repeticiones
declare -a repeticiones_memoria

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
		for (( R = 1; R <= $cantidad_repeticiones; R++ ))
		do
			echo "$R/$cantidad_repeticiones"
			tiempo_inicio=$(date +%s%N)/1000000
			repeticiones_memoria[$R]=$(./../../../main ../../../tests/${vid}/${vid}_input.in ../../../tests/${vid}/${vid}.sal 2 2 $I)
			tiempo_fin=$(date +%s%N)/1000000
			repeticiones[$R]=$((tiempo_fin - tiempo_inicio))
			rm ../../../tests/${vid}/${vid}.sal
		done
		mediana=$(./../calcular_mediana/main ${repeticiones[@]})
		mediana_memoria=$(./../calcular_mediana/main ${repeticiones_memoria[@]})
		echo -n ", ${mediana}" >> sal.csv
		echo -n ", ${mediana_memoria}" >> sal_mem.csv
	done
done

exit 0
