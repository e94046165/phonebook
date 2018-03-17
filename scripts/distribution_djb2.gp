set title "hash table distribution"
set xlabel "index"
set ylabel "numbers"
set terminal png font " Times_New_Roman,12 "
set output "distribution_djb2.png"

plot \
"hash1.txt" using 1:2 with linespoints linewidth 2 title "djb2"

   

