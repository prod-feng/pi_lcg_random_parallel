# pi_lcg_random_parallel
LCG LeapFrog random number generator, OpenMP multiple thread safe

This is a lcg random number generator, uses leapfrog method. It is OpenMP multiple thread safe.

>gcc -fopenmp pi_random_parallel.c -lgomp -o pi_random_parallel.exe

Running the program with different number of threads give the identical result:

[feng@]$  export OMP_NUM_THREADS=2
[feng@]$  time ./pi_random_parallel.exe 

 10000000 trials, pi = 3.141159 

real	0m0.519s
user	0m0.518s
sys	0m0.001s
[feng@]$  export OMP_NUM_THREADS=2
[feng@]$  time ./pi_random_parallel.exe 

 10000000 trials, pi = 3.141159 

real	0m0.404s
user	0m0.803s
sys	0m0.002s
[feng@]$  export OMP_NUM_THREADS=3
[feng@]$  time ./pi_random_parallel.exe 

 10000000 trials, pi = 3.141159 

real	0m0.332s
user	0m0.989s
sys	0m0.001s
[feng@]$  export OMP_NUM_THREADS=4
[feng@]$  time ./pi_random_parallel.exe 

 10000000 trials, pi = 3.141159 

real	0m0.342s
user	0m1.354s
sys	0m0.001s

Developed on CentOS 6.2, Kernel 2.6.32-220.2.1.el6.x86_64, gcc (GCC) 4.4.6 20110731

