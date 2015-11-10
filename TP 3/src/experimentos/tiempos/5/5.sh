#!/bin/bash

metodos=(2 6)
nombre_metodo=("Splines por Bloques" "Splines Doble Lectura")
cantidad_repeticiones=1
declare -a repeticiones

cantidad_frames=5

echo "Creando imagen: $cantidad_frames frames"
./../crear_imagenes/main img.vid 10 $cantidad_frames 10 10 2 5

echo -n "" > sal.csv
echo "--------------------------------"
echo -n "Metodo" >> sal.csv
for M in ${metodos[@]}
do

	echo "--${nombre_metodo[$M]}"
	echo "" >> sal.csv
	echo -n "${nombre_metodo[$M]}" >> sal.csv
	for (( R = 1; R <= $cantidad_repeticiones; R++ ))
	do
		echo "$R/$cantidad_repeticiones"
		tiempo_inicio=$(date +%s%N)/1000000
		./../../../main img.vid img.sal $M 2 5
		tiempo_fin=$(date +%s%N)/1000000
		repeticiones[$R]=$((tiempo_fin - tiempo_inicio))
		#rm img.sal
	done
	mediana=$(./../calcular_mediana/main ${repeticiones[@]})
	echo -n ", $((tiempo_fin - tiempo_inicio))" >> sal.csv

done

#rm img.vid


exit 0