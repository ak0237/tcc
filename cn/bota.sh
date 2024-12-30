#!/bin/bash

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












