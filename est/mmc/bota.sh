#!/bin/bash

echo "compilando..."
gcc main.c -lgsl -lgslcblas -lm -o a

echo "apagando..."

make


echo "executando..."
./a
cd plt2
echo "gerando o gráfico 2"
gnuplot sir.plt
cd ../plt
echo "gerando o gráfico 1"
gnuplot p.plt
echo "fazendo o video..."
ffmpeg -framerate 30 -i p-%d.png -c:v libx264 -pix_fmt yuv420p output.mp4














