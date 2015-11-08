#!/bin/bash

#Tests Tenis 

test() {

echo 'Testeando ' $1

echo 'generando inputs'

python videoToTextfile.py tests/$1/$1_input.avi tests/$1/$1Real.in

./main tests/$1/$1Real.in tests/$1/$1_FramesInt2.in 3 2
./main tests/$1/$1Real.in tests/$1/$1_FramesInt4.in 3 4
./main tests/$1/$1Real.in tests/$1/$1_FramesInt6.in 3 6

echo 'Testeando vecino mas cercano'

./main tests/$1/$1_FramesInt2.in tests/$1/$1_Vecino_FramesInt2.out 0 2
./main tests/$1/$1_FramesInt4.in tests/$1/$1_Vecino_FramesInt4.out 0 4
./main tests/$1/$1_FramesInt6.in tests/$1/$1_Vecino_FramesInt4.out 0 6

python textfileToVideo.py tests/$1/$1_Vecino_FramesInt2.out tests/$1/$1_Vecino_FramesInt2.avi
python textfileToVideo.py tests/$1/$1_Vecino_FramesInt2.out tests/$1/$1_Vecino_FramesInt4.avi
python textfileToVideo.py tests/$1/$1_Vecino_FramesInt2.out tests/$1/$1_Vecino_FramesInt6.avi

echo 'Testeando interpolacion lineal'

./main tests/$1/$1_FramesInt2.in tests/$1/$1_Lineal_FramesInt2.out 1 2
./main tests/$1/$1_FramesInt4.in tests/$1/$1_Lineal_FramesInt4.out 1 4
./main tests/$1/$1_FramesInt6.in tests/$1/$1_Lineal_FramesInt6.out 1 6

python textfileToVideo.py tests/$1/$1_Lineal_FramesInt2.out tests/$1/$1_Lineal_FramesInt2.avi
python textfileToVideo.py tests/$1/$1_Lineal_FramesInt4.out tests/$1/$1_Lineal_FramesInt4.avi
python textfileToVideo.py tests/$1/$1_Lineal_FramesInt6.out tests/$1/$1_Lineal_FramesInt6.avi

echo 'Testeando splines con bloques de 4'

./main tests/$1/$1_FramesInt2.in tests/$1/$1_Splines_FramesInt2_TamBloque4.out 2 2 4
./main tests/$1/$1_FramesInt4.in tests/$1/$1_Splines_FramesInt4_TamBloque4.out 2 4 4
./main tests/$1/$1_FramesInt6.in tests/$1/$1_Splines_FramesInt6_TamBloque4.out 2 6 4

python textfileToVideo.py tests/$1/$1_Splines_FramesInt2_TamBloque4.out tests/$1/$1_Splines_FramesInt2_TamBloque4.avi
python textfileToVideo.py tests/$1/$1_Splines_FramesInt4_TamBloque4.out tests/$1/$1_Splines_FramesInt4_TamBloque4.avi
python textfileToVideo.py tests/$1/$1_Splines_FramesInt6_TamBloque4.out tests/$1/$1_Splines_FramesInt6_TamBloque4.avi

echo 'Testeando splines con bloques de 8'

./main tests/$1/$1_FramesInt2.in tests/$1/$1_Splines_FramesInt2_TamBloque8.out 2 2 8
./main tests/$1/$1_FramesInt4.in tests/$1/$1_Splines_FramesInt4_TamBloque8.out 2 4 8
./main tests/$1/$1_FramesInt6.in tests/$1/$1_Splines_FramesInt6_TamBloque8.out 2 6 8

python textfileToVideo.py tests/$1/$1_Splines_FramesInt2_TamBloque8.out tests/$1/$1_Splines_FramesInt2_TamBloque8.avi
python textfileToVideo.py tests/$1/$1_Splines_FramesInt4_TamBloque8.out tests/$1/$1_Splines_FramesInt4_TamBloque8.avi
python textfileToVideo.py tests/$1/$1_Splines_FramesInt6_TamBloque8.out tests/$1/$1_Splines_FramesInt6_TamBloque8.avi

echo 'Testeando splines con bloques de 16'

./main tests/$1/$1_FramesInt2.in tests/$1/$1_Splines_FramesInt2_TamBloque16.out 2 2 16
./main tests/$1/$1_FramesInt4.in tests/$1/$1_Splines_FramesInt4_TamBloque16.out 2 4 16
./main tests/$1/$1_FramesInt6.in tests/$1/$1_Splines_FramesInt6_TamBloque16.out 2 6 16

python textfileToVideo.py tests/$1/$1_Splines_FramesInt2_TamBloque16.out tests/$1/$1_Splines_FramesInt2_TamBloque16.avi
python textfileToVideo.py tests/$1/$1_Splines_FramesInt4_TamBloque16.out tests/$1/$1_Splines_FramesInt4_TamBloque16.avi
python textfileToVideo.py tests/$1/$1_Splines_FramesInt6_TamBloque16.out tests/$1/$1_Splines_FramesInt6_TamBloque16.avi

}


if [ "$1" = "tenis" ] | ["$1" = "morocho"] | [ "$1" = "perro" ] 
	then 
	test $1
else 
	 echo 'parámetros incorrectos'
fi
exit