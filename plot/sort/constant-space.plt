set ylabel "Space complexity (bytes)"
plot "insertion-sort-(average-case).dat" using 1:3 title "insertion-sort-(average-case)\n shell-sort-(average-case)\n S(N) => 8.00", \
8.00 notitle, \
"heap-sort-(average-case).dat" using 1:3 title "\n\n\nheap-sort-(average-case) S(N) => 20.00", \
20.00 notitle        
