#!/bin/bash
declare -a cantidad_intermedios
cantidad_intermedios[0]=5
for I in {1..8}
do
	cantidad_intermedios[$I]=$((${cantidad_intermedios[$(($I-1))]}*2))
done
for I in {9..38}
do
	cantidad_intermedios[$I]=$((${cantidad_intermedios[$(($I-1))]}+640))
done

metodos=(0 1 2)
nombre_metodo=("Mas cercano" "Lineal" "Splines por Bloques")
cantidad_repeticiones=10
declare -a repeticiones

cantidad_frames=200

echo "Creando imagen: $cantidad_frames frames"
./../crear_imagenes/main img.vid 10 $cantidad_frames 10 10 2 5

echo -n "" > sal.csv
echo "--------------------------------"
echo -n "Metodo" >> sal.csv
for I in ${cantidad_intermedios[@]}
do
	echo -n ", $I" >> sal.csv
done
for M in ${metodos[@]}
do

	echo "--${nombre_metodo[$M]}"
	echo "" >> sal.csv
	echo -n "${nombre_metodo[$M]}" >> sal.csv
	for I in ${cantidad_intermedios[@]}
	do
		echo "---- Corriendo: $I"
		for (( R = 1; R <= $cantidad_repeticiones; R++ ))
		do
			echo "$R/$cantidad_repeticiones"
			tiempo_inicio=$(date +%s%N)/1000000
			./../../../main img.vid img.sal $M 2 5
			tiempo_fin=$(date +%s%N)/1000000
			repeticiones[$R]=$((tiempo_fin - tiempo_inicio))
			rm img.sal
		done
		mediana=$(./../calcular_mediana/main ${repeticiones[@]})
		echo -n ", $((tiempo_fin - tiempo_inicio))" >> sal.csv
	done

done

rm img.vid


exit 0