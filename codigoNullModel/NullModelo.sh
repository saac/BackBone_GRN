#!/bin/sh

N=$(wc -l $1 | cut -d " " -f1)

./NullMod $1 $N $2

data=$(cat parametros | cut -d " " -f1)
Ynull=$(cat parametros | cut -d " " -f2)
logK=$(cat parametros | cut -d " " -f3)

gnuplot -c grafica.gp $data $Ynull $logK