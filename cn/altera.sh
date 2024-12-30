#!/bin/bash

# Nome do arquivo C
FILE="src.c"

# Nova mensagem do pragma
NEW_BETA=0.5
NEW_GAMA=0.1

# Substituir o valor da variável no arquivo
sed -i "s/#define BETA [0-9]*/#define MY_VARIABLE $NEW_BETA/" "$FILE"

# Compilar o programa
gcc -o program "$FILE"

# Executar o programa
./program

# RK1
echo "RK 1 ..."
cd rk1
./bota.sh
cd plt
mv plot.png rk1.png
cp rk1.png ../../figs
cd ../../

# RK2

echo "RK 2 ..."
cd rk2
./bota.sh
cd plt
mv plot.png rk2.png
cp rk2.png ../../figs
cd ../../

# RK4 

echo "RK 4 ..."
cd rk4
./bota.sh
cd plt
mv plot.png rk4.png
cp rk4.png ../../figs
cd ../../

# RK45

echo "RK 45 ..."
cd rk45
./bota.sh
cd plt
mv plot.png rk45.png
cp rk45.png ../../figs
cd ../../