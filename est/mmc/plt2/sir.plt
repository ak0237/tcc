set terminal png size 1000, 1000
set output 'plot.png'

set xlabel "Tempo"
set ylabel "Quantidade de individuos"

set key top left 

plot "../dat2/sir_mmcg.dat" using 1:2 with lines lw 2 title "s", \
"../dat2/sir_mmcg.dat" using 1:3 with lines lw 2 title "i", \
"../dat2/sir_mmcg.dat" using 1:4 with lines lw 2 title "r"

unset output