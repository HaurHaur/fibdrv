reset
set title 'perf'
set xlabel 'number'
set ylabel 'time(ns)'
set terminal png font " Times_New_Roman,12 "
set output "perf.png"
set xtics 1 ,10 ,100
set xtics 0 ,10 ,100
set key left 
plot "output.txt" using 1:2 with linespoints linewidth 2 title "kernel", \
"output.txt" using 1:3 with linespoints linewidth 2 title "kernel to user", \
"output.txt" using 1:4 with linespoints linewidth 2 title "user" \