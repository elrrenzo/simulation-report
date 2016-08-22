#!/bin/bash
# A shell script to run ATP many times

mkdir $2
cp startup $2/
cp graphics  $2/
cp graphics.aux  $2/


for t in a b c     ### Outer for loop ###
do
	cp $1 $2/sistema_f$t.atp
    sed -i -e 's/XXXXXX/RESIS'$t'/g' $2/sistema_f$t.atp
    sed -i -e 's/YYYYYY/FAULT'$t'/g' $2/sistema_f$t.atp

    for (( d = 70 ; d < 2560; d = d+970 )) ### Inner for loop ###
    do
		ND="$(printf '%d' $(($d)))"
		L1="$(printf '%d.' $(($d)))"
		L2="$(printf '%d.' $((2600-$d)))"
		cp $2/sistema_f$t.atp $2/sistema_f${t}d${ND}.atp
		sed -i -e 's/LLLLL1/'${L1}'/g' $2/sistema_f${t}d${ND}.atp
		sed -i -e 's/LLLLL2/'${L2}'/g' $2/sistema_f${t}d${ND}.atp

		printf 'Tipo de falta: %s. Distancia: %d km\n' $t $d
		
		cd $2/
		tpbigfm sistema_f${t}d${ND}.atp > salida.lis

#		gnuplot -e "filename='foo.data'" ploter.gnu
#		ps2pdf sistema_f${t}d${ND}.ps

		cd ..

		../dataprocessing/pl4todat $2/sistema_f${t}d${ND}.pl4 $2/sistema_f${t}d${ND}.dat

		gnuplot -e "filename='$2/sistema_f${t}d${ND}.dat'" ploter.gnu > $2/sistema_f${t}d${ND}.pdf

		../dataprocessing/digwritter $2/sistema_f${t}d${ND}.dat $2/sistema_f${t}.dig $L1
    done

done

rm $2/*.tmp

ls $2/*.dig > lista.txt

../pdfgenerator/pdfgen lista.txt $2

#evince salida2.pdf
