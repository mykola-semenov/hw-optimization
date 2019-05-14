#!/usr/bin/gnuplot -persist

set logscale z 10

set xlabel 'x'
set ylabel 'y'
set zlabel 'n'

set title 'Метод Монте-Карло'
splot 'output.dat' u 2:3:1 w p lc rgb 'red'