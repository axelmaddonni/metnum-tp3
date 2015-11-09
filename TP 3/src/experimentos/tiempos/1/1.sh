#!/bin/bash
tamanos=(160 320 640 1280 1920 2560 3200 3840 4120 4760)
metodos=(0 1 2)
nombre_metodo=("Mas cercano" "Lineal" "Splines por Bloques")
cantidad_repeticiones=10
declare -a repeticiones

for I in ${tamanos[@]}
do
	echo "-- Creando imagen: ${I} constante"
	./../crear_imagenes/main ${I}_constante.vid 10 10 $I 10 1 150
	echo "-- Creando imagen: ${I} variable"
	./../crear_imagenes/main ${I}_variable.vid 10 10 $I 10 2 5
done

for M in ${metodos[@]}
do
	echo "--------------------------------"

	echo -n "" > sal_${M}.csv
	echo -n "Tipo" >> sal_${M}.csv
	for I in ${tamanos[@]}
	do
		echo -n ", $I" >> sal_${M}.csv
	done


	echo "--${nombre_metodo[$M]} Constante"
	echo "" >> sal_${M}.csv
	echo -n "Constante" >> sal_${M}.csv
	for I in ${tamanos[@]}
	do
		echo "---- Corriendo: $I"
		for (( R = 1; R <= $cantidad_repeticiones; R++ ))
		do
			echo "$R/$cantidad_repeticiones"
			tiempo_inicio=$(date +%s%N)/1000000
			./../../../main ${I}_constante.vid ${I}_constante.sal $M 2 5
			tiempo_fin=$(date +%s%N)/1000000
			repeticiones[$R]=$((tiempo_fin - tiempo_inicio))
			rm ${I}_constante.sal
		done
		mediana=$(./../calcular_mediana/main ${repeticiones[@]})
		echo -n ", $((tiempo_fin - tiempo_inicio))" >> sal_${M}.csv
	done

	echo "--${nombre_metodo[$M]} Variable"
	echo "" >> sal_${M}.csv
	echo -n "Variable" >> sal_${M}.csv
	for I in ${tamanos[@]}
	do
		echo "-- Corriendo: $I"
		for (( R = 1; R <= $cantidad_repeticiones; R++ ))
		do
			echo "$R/$cantidad_repeticiones"
			tiempo_inicio=$(date +%s%N)/1000000
			./../../../main ${I}_variable.vid ${I}_variable.sal $M 2 5
			tiempo_fin=$(date +%s%N)/1000000
			repeticiones[$R]=$((tiempo_fin - tiempo_inicio))
			rm ${I}_variable.sal
		done
		mediana=$(./../calcular_mediana/main ${repeticiones[@]})
		echo -n ", $mediana" >> sal_${M}.csv
	done

done

for I in ${tamanos[@]}
do
	rm ${I}_constante.vid
	rm ${I}_variable.vid
done


exit 0