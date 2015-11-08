#!/bin/bash
tamanos=(160 320 640 1280 1920 2560 3200 3840)
metodos=(0 1 2)
nombre_metodo=("Mas cercano" "Lineal" "Splines por Bloques")
echo -n "" > sal.csv
echo -n "Metodo - Tipo" >> sal.csv
for I in ${tamanos[@]}
do
	echo -n ", $I" >> sal.csv
done

for I in ${tamanos[@]}
do
	echo "-- Creando imagen: ${I} constante"
	./../crear_imagenes/main ${I}_constante.vid 10 10 $I 10 1 150
	echo "-- Creando imagen: ${I} variable"
	./../crear_imagenes/main ${I}_variable.vid 10 10 $I 10 2 5
done

for M in ${metodos[@]}
do
	echo "Tipo: CONSTANTE - ${nombre_metodo[$M]}"
	echo "" >> sal.csv
	echo -n "${nombre_metodo[$M]} - Constante" >> sal.csv
	for I in ${tamanos[@]}
	do
		echo "-- Corriendo: $I"
		tiempo_inicio=$(date +%s%N)/1000000
		./../../../main ${I}_constante.vid ${I}_constante.sal $M 2 5
		tiempo_fin=$(date +%s%N)/1000000
		echo -n ",$((tiempo_fin - tiempo_inicio))" >> sal.csv
		rm ${I}_constante.sal
	done

	echo "Tipo: VARIABLE - ${nombre_metodo[$M]}"
	echo "" >> sal.csv
	echo -n "${nombre_metodo[$M]} - Variable" >> sal.csv
	for I in ${tamanos[@]}
	do
		echo "-- Corriendo: $I"
		tiempo_inicio=$(date +%s%N)/1000000
		./../../../main ${I}_variable.vid ${I}_variable.sal $M 2 5
		tiempo_fin=$(date +%s%N)/1000000
		echo -n ",$((tiempo_fin - tiempo_inicio))" >> sal.csv
		rm ${I}_variable.sal
	done

done

for I in ${tamanos[@]}
do
	rm ${I}_constante.vid
	rm ${I}_variable.vid
done



exit 0