#!/bin/bash
declare -a tamano_bloque
tamano_bloque[0]=5
for I in {1..8}
do
	tamano_bloque[$I]=$((${tamano_bloque[$(($I-1))]}*2))
done
for I in {9..38}
do
	tamano_bloque[$I]=$((${tamano_bloque[$(($I-1))]}+640))
done
cantidad_frames=${tamano_bloque[-1]}

echo "Creando imagen: $cantidad_frames frames"
./../crear_imagenes/main img.vid 10 10 $cantidad_frames 10 2 5

cantidad_repeticiones=10
declare -a repeticiones

echo -n "" > sal.csv
echo -n "Tipo" >> sal.csv
for I in ${tamano_bloque[@]}
do
	echo -n ", $I" >> sal.csv
done


echo "" >> sal.csv
for I in ${tamano_bloque[@]}
do
	echo "---- Corriendo: $I"
	for (( R = 1; R <= $cantidad_repeticiones; R++ ))
	do
		echo "$R/$cantidad_repeticiones"
		tiempo_inicio=$(date +%s%N)/1000000
		./../../../main img.vid img.sal 2 2 $tamano_bloque
		tiempo_fin=$(date +%s%N)/1000000
		repeticiones[$R]=$((tiempo_fin - tiempo_inicio))
		rm img.sal
	done
	mediana=$(./../calcular_mediana/main ${repeticiones[@]})
	echo -n ", $((tiempo_fin - tiempo_inicio))" >> sal.csv
done

rm img.vid


exit 0