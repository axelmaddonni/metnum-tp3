#!/bin/bash
declare -a tamanos
tamanos[0]=5
for I in {1..12}
do
	tamanos[$I]=$((${tamanos[$(($I-1))]}*2))
done

metodos=(0 1 2)
nombre_metodo=("Mas cercano" "Lineal" "Splines por Bloques")
cantidad_repeticiones=10
declare -a repeticiones

for I in ${tamanos[@]}
do
	echo "-- Creando imagen: ${I}"
	./../crear_imagenes/main ${I}.vid 10 10 $I 10 2 5
done


echo -n "" > sal.csv
echo -n "Tipo" >> sal.csv
for I in ${tamanos[@]}
do
	echo -n ", $I" >> sal.csv
done

for M in ${metodos[@]}
do
	echo "--------------------------------"
	echo "" >> sal.csv
	echo "${nombre_metodo[$M]}"
	for I in ${tamanos[@]}
	do
		echo "---- Corriendo ${nombre_metodo[$M]}: $I"
		for (( R = 1; R <= $cantidad_repeticiones; R++ ))
		do
			echo "$R/$cantidad_repeticiones"
			tiempo_inicio=$(date +%s%N)/1000000
			./../../../main ${I}.vid ${I}.sal $M 2 5
			tiempo_fin=$(date +%s%N)/1000000
			repeticiones[$R]=$((tiempo_fin - tiempo_inicio))
			rm ${I}.sal
		done
		mediana=$(./../calcular_mediana/main ${repeticiones[@]})
		echo -n ", $((tiempo_fin - tiempo_inicio))" >> sal.csv
	done
done

rm ${I}.vid


exit 0