#!/bin/bash

test() {

	echo 'Calculando' $2 $1 

	if [ "$2" = "ecm" ]; then 
		modo=4 
	else 
		modo=5 
	fi

	echo 'Calculando Vecino mas cercano'

	echo 'Frames internos = 2'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Vecino_FramesInt2.out $modo 0 tests/$1/$1_Vecino_FramesInt2.out basura.out 0 0
	
	echo 'Frames internos = 4'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Vecino_FramesInt4.out $modo 0 tests/$1/$1_Vecino_FramesInt4.out basura.out 0 0
	
	echo 'Frames internos = 6'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Vecino_FramesInt6.out $modo 0 tests/$1/$1_Vecino_FramesInt6.out basura.out 0 0

	echo 'Calculando interpolación lineal'

	echo 'Frames internos = 2'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Lineal_FramesInt2.out $modo 0 tests/$1/$1_Lineal_FramesInt2.out basura.out 0 0
	
	echo 'Frames internos = 4'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Lineal_FramesInt4.out $modo 0 tests/$1/$1_Lineal_FramesInt4.out basura.out 0 0

	echo 'Frames internos = 6'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Lineal_FramesInt6.out $modo 0 tests/$1/$1_Lineal_FramesInt6.out basura.out 0 0

	echo 'Calculando splines de bloque 4'

	echo 'Frames internos = 2'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Splines_FramesInt2_TamBloque4.out $modo 0 tests/$1/$1_Splines_FramesInt2_TamBloque4.out basura.out 0 0
	
	echo 'Frames internos = 4'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Splines_FramesInt4_TamBloque4.out $modo 0 tests/$1/$1_Splines_FramesInt4_TamBloque4.out basura.out 0 0
	
	echo 'Frames internos = 6'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Splines_FramesInt6_TamBloque4.out $modo 0 tests/$1/$1_Splines_FramesInt6_TamBloque4.out basura.out 0 0

	echo 'Calculando splines de bloque 8'

	echo 'Frames internos = 2'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Splines_FramesInt2_TamBloque8.out $modo 0 tests/$1/$1_Splines_FramesInt2_TamBloque8.out basura.out 0 0
	
	echo 'Frames internos = 4'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Splines_FramesInt4_TamBloque8.out $modo 0 tests/$1/$1_Splines_FramesInt4_TamBloque8.out basura.out 0 0
	
	echo 'Frames internos = 6'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Splines_FramesInt6_TamBloque8.out $modo 0 tests/$1/$1_Splines_FramesInt6_TamBloque8.out basura.out 0 0

	echo 'Calculando splines de bloque 16'

	echo 'Frames internos = 2'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Splines_FramesInt2_TamBloque16.out $modo 0 tests/$1/$1_Splines_FramesInt2_TamBloque16.out basura.out 0 0
	
	echo 'Frames internos = 4'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Splines_FramesInt4_TamBloque16.out $modo 0 tests/$1/$1_Splines_FramesInt4_TamBloque16.out basura.out 0 0
	
	echo 'Frames internos = 6'
	./main tests/$1/$1Real.in tests/$1/$2/$2_Splines_FramesInt6_TamBloque16.out $modo 0 tests/$1/$1_Splines_FramesInt6_TamBloque16.out basura.out 0 0

}



if [[ ( "$1" = "tenis" || "$1" = "morocho" || "$1" = "perro" || "$1" = "cupcake" || "$1" = "bebes" || "$1" = "fideos" ) && ("$2" = "ecm" || "$2" = "psnr") ]];
	then 
	test $1 $2
else 
	 echo 'parámetros incorrectos'
fi
exit