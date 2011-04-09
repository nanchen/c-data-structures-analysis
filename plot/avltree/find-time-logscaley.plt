set logscale y
set yrange [1:1000]
set ylabel "Time complexity (number of execution steps) logscale"
plot "find.dat" using 1:2 title "find T(N) => 7.99 * logN", \
7.99 * log(x)/log(2) notitle        
