#set term X11 size 600, 1200
set terminal pdf size 7, 14
#set terminal X11

#set terminal wxt size 350,600 enhanced persist

set style line 1  lc rgb '#0000ee' lt 1 lw 3.0 # --- blue
set style line 2  lc rgb '#ff0000' lt 1 lw 3.0 # --- red
set style line 3  lc rgb '#000000' lt 1 lw 3.0 # --- black
set style line 4  lc rgb '#008080' lt 1 lw 3.0 # --- teal
set style line 5  lc rgb '#ff00ff' lt 1 lw 3.0 # --- magenta
set style line 6  lc rgb '#ff4500' lt 1 lw 3.0 # --- orange
#filename="sistema_fad70.dat"
#set output "prueba.pdf"

#set title font ",12"
set lmargin at screen 0.10
set rmargin at screen 0.95
set grid xtics


set multiplot layout 7,1 title filename font ",14" offset 2,0
#set offset 0,0,graph 0.05, graph 0.05

set autoscale fix

# set key autotitle columnhead
set tics font ",10"
set key font ",11"

#1 PLOT Tensones envio
set size 1,0.10
set origin 0,0.89

set title "Sending terminal" offset 0,-1
set ylabel "kV" font ",11" offset 0,0

set xtics format ''
plot filename using (column("Time")*1000):(column("vSHWLA")/1000) title "vSHWLA" with lines ls 1, \
	'' using (column("Time")*1000):(column("vSHWLB")/1000) title "vSHWLB" with lines ls 2, \
	'' using (column("Time")*1000):(column("vSHWLC")/1000) title "vSHWLC" with lines ls 3, \
	'' using (column("Time")*1000):(column("VA")/1000) title "VA" with lines ls 1, \
	'' using (column("Time")*1000):(column("VB")/1000) title "VB" with lines ls 2, \
	'' using (column("Time")*1000):(column("VC")/1000) title "VC" with lines ls 3 
#2 PLOT Correntes envio
set title " "
set ylabel "kA" offset -2.0,0
set size 1,0.10
set origin 0,0.818
plot filename using (column("Time")*1000):(column("iCBXIASHWLA")/1000) title "iCBXIA" with lines ls 4, \
	'' using (column("Time")*1000):(column("iCBXIBSHWLB")/1000) title "iCBXIB" with lines ls 5, \
	'' using (column("Time")*1000):(column("iCBXICSHWLC")/1000) title "iCBXIC" with lines ls 6, \
	'' using (column("Time")*1000):(column("IA")/1000) title "IA" with lines ls 4, \
	'' using (column("Time")*1000):(column("IB")/1000) title "IB" with lines ls 5, \
	'' using (column("Time")*1000):(column("IC")/1000) title "IC" with lines ls 6 

#3 PLOT Tensoes no ponto de falta
set title "Fault point"
set ylabel "kV" offset 0,0
set size 1,0.10
set origin 0,0.73
plot filename using (column("Time")*1000):(column("vFAULTA")/1000) title "vFAULTA" with lines ls 1, \
	'' using (column("Time")*1000):(column("vFAULTB")/1000) title "vFAULTB" with lines ls 2, \
	'' using (column("Time")*1000):(column("vFAULTC")/1000) title "vFAULTC" with lines ls 3 

#4 PLOT Correntes no ponto de falta
set title " "
set ylabel "kA" offset -3.0,0
#set tmargin at screen TOP
#set bmargin at screen TOP-DY
set size 1,0.10
set origin 0,0.657
plot filename using (column("Time")*1000):(column("iCBNIARHWLA")/1000) title "iCBNIA" with lines ls 4, \
	'' using (column("Time")*1000):(column("iCBNIBRHWLB")/1000) title "iCBNIB" with lines ls 5, \
	'' using (column("Time")*1000):(column("iCBNICRHWLC")/1000) title "iCBNIC" with lines ls 6
#5 PLOT Tensoes recepcao
set title "Recieving terminal"
set ylabel "kV" offset 0,0
set size 1,0.10
set origin 0,0.57
plot filename using (column("Time")*1000):(column("vRHWLA")/1000) title "vRHWLA" with lines ls 1, \
	'' using (column("Time")*1000):(column("vRHWLB")/1000) title "vRHWLB" with lines ls 2, \
	'' using (column("Time")*1000):(column("vRHWLC")/1000) title "vRHWLC" with lines ls 3 

#6 PLOT Correntes recepcao
set title " "
set ylabel "kA" offset -3.0,0
#set tmargin at screen TOP
#set bmargin at screen TOP-DY
set size 1,0.10
set origin 0,0.497
plot filename using (column("Time")*1000):(column("iCBNIARHWLA")/1000) title "iCBNIA" with lines ls 4, \
	'' using (column("Time")*1000):(column("iCBNIBRHWLB")/1000) title "iCBNIB" with lines ls 5, \
	'' using (column("Time")*1000):(column("iCBNICRHWLC")/1000) title "iCBNIC" with lines ls 6

#7 PLOT Saidas Digitais
set title " "
set ylabel " "
set ytics ("FSA" 1,"FSB" 2.5,"FSC" 4,"FSAB" 5.5,"FSBC" 7,"FSCA" 8.5)
unset key
set size 1,0.10
set origin 0,0.4
set yrange [0.5:10]
plot filename using (column("Time")*1000):(column("dFSA")+1) title "FSA" with lines ls 1, \
	'' using (column("Time")*1000):(column("dFSB")+2.5) title "FSB" with lines ls 2, \
	'' using (column("Time")*1000):(column("dFSC")+4) title "FSC" with lines ls 3, \
	'' using (column("Time")*1000):(column("dFSAB")+5.5) title "FSAB" with lines ls 4, \
	'' using (column("Time")*1000):(column("dFSBC")+7) title "FSBC" with lines ls 5, \
	'' using (column("Time")*1000):(column("dFSCA")+8.5) title "FSCA" with lines ls 6



set xlabel 'Time [ms]' offset 0,1.0
set xtics format "%4.1f"


unset multiplot


