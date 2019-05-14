#!/usr/bin/gnuplot -persist

set xrange [-2: 2]
set yrange [-2: 2]

set xlabel 'x'
set ylabel 'y'

plot "output.dat" u 1:2

