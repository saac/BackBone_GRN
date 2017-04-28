#!/usr/local/bin/gnuplot --persist

# gnuplot -c grafica3.gp "Bueno.dat" 2.0322 4.18
# gnuplot -c grafica3.gp "ARG1" ARG2 ARG3     # ARG1 = Resultados.dat, ARG2 = YNull, ARG3 = log(N) 



eqx=ARG3 + 0
set xrange [eqx-0.05:eqx+0.05]
CTE=ARG2 + 0
f(x)=CTE
set xlabel "log(k)"
set ylabel "kY(k)"
plot f(x) title 'Null Model' , ARG1 w p pt 7 lc 7 title 'Distibucion'
#pause -1

set term postscript eps enhanced color solid  
set out 'RedPrueba2.eps'

replot
