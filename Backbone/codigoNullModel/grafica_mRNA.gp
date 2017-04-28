#!/usr/local/bin/gnuplot --persist

# gnuplot -c grafica3.gp "Bueno.dat" 2.0322 4.18
# gnuplot -c grafica3.gp "ARG1" ARG2 ARG3     # ARG1 = Resultados.dat, ARG2 = YNull, ARG3 = log(N) 

name=ARG1
eqx=ARG3 + 0
set xrange [eqx-0.05:eqx+0.05]
CTE=ARG2 + 0
f(x)=CTE
# plot f(x) title 'Null Model' , name w p pt 7 lc 7 title 'Distribucion'
plot f(x) title 'Null Model' , name using 2:3 w p pt 7 lc 7 title 'Genes', ARG4 using 2:3 w p pt 7 lc "blue" title 'mRNAs'

set title "miRNA-gen Network ENFERMOS"
set xlabel "log(k)"
set ylabel "kY(k)"

# set term png
# set out 'fugura.png'

# set term postscript eps enhanced color solid  
# # set out name.'.eps'
# set out "Enfermos_mir-gen.eps"
# replot

pause -1
