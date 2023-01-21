set terminal svg size 1000,700
set xtics rotate by 45 right
set style fill solid border -1
set datafile separator ';'

set boxwidth 0.9
set style data histograms
set style histogram errorbars gap 1 lw 1

set key left top

set ylabel "MiB/s"
set yrange[0:2500]

set output "compilateurs.svg"
plot "../data/compilateur.dat" every 3::0 using 6:($7*$6/100):xtic(8) ti "ICX" ,\
"../data/compilateur.dat" every 3::1 using 6:($7*$6/100) ti "GCC" ,\
"../data/compilateur.dat" every 3::2 using 6:($7*$6/100) ti "CLANG" 

set style histogram
set output "implementations.svg"

set multiplot layout 1,2
set ylabel "speed up"
set yrange [0: 110]
plot "../data/icx.dat" using ($3/150):xtic(1) ti "ICX" ,\
"../data/gcc.dat" using ($3/179):xtic(1) ti "GCC" ,\
"../data/clang.dat" using ($3/205):xtic(1) ti "CLANG" 

set ylabel "MiB/s"
set yrange [100: 15000]
plot "../data/icx.dat" using 3:xtic(1) ti "ICX" ,\
"../data/gcc.dat" using 3:xtic(1) ti "GCC" ,\
"../data/clang.dat" using 3:xtic(1) ti "CLANG" 
unset multiplot


set output "elapsed_time.svg"
set key right top
set multiplot layout 1,3

set ylabel "elapsed time in sec"
set yrange [1:6]

set title "mm malloc"
#_mm_malloc
plot "../data/elapsed_icx.dat" using 2:xtic(1) ti "ICX" ,\
"../data/elapsed_gcc.dat" using 2:xtic(1) ti "GCC" ,\
"../data/elapsed_clang.dat" using 2:xtic(1) ti "CLANG" 

set title "aligned alloc"
#aligned_alloc
plot "../data/aligned_icx.dat" using 2:xtic(1) ti "ICX" ,\
"../data/aligned_gcc.dat" using 2:xtic(1) ti "GCC" ,\
"../data/aligned_clang.dat" using 2:xtic(1) ti "CLANG" 

set title "malloc"
#nmap
plot "../data/malloc_icx.dat" using 2:xtic(1) ti "ICX" ,\
"../data/malloc_gcc.dat" using 2:xtic(1) ti "GCC" ,\
"../data/malloc_clang.dat" using 2:xtic(1) ti "CLANG" 

unset multiplot 

set output 'kernel_time.svg'
set multiplot layout 1,3

set ylabel "elapsed time in nsec"
set yrange [*:*]

set title "mm malloc"
#_mm_malloc
plot "../data/elapsed_icx.dat" using 3:xtic(1) ti "ICX" ,\
"../data/elapsed_gcc.dat" using 3:xtic(1) ti "GCC" ,\
"../data/elapsed_clang.dat" using 3:xtic(1) ti "CLANG" 

set title "aligned alloc"
#aligned_alloc
plot "../data/aligned_icx.dat" using 3:xtic(1) ti "ICX" ,\
"../data/aligned_gcc.dat" using 3:xtic(1) ti "GCC" ,\
"../data/aligned_clang.dat" using 3:xtic(1) ti "CLANG" 

set title "malloc"
#nmap
plot "../data/malloc_icx.dat" using 3:xtic(1) ti "ICX" ,\
"../data/malloc_gcc.dat" using 3:xtic(1) ti "GCC" ,\
"../data/malloc_clang.dat" using 3:xtic(1) ti "CLANG" 

unset multiplot 
