#include <stdio.h>
#include <omp.h>

static unsigned long long MULTIPLIER  = 764261123;
static unsigned long long PMOD        = 2147483647;
static unsigned long long mult_n;
double random_low, random_hi;

#define MAX_THREADS 128

#define DIMENSION 3
unsigned long long rseed[DIMENSION];
static int first[MAX_THREADS][DIMENSION][4];

static  unsigned long long tmpseed[MAX_THREADS][DIMENSION];

double xyz[DIMENSION];

#pragma omp threadprivate(rseed,xyz)


void random(int num, double * ret)
{
   unsigned long long random_next;
   int i,j;

   int id=omp_get_thread_num();

   for(j=0; j< DIMENSION; j++){
     //re-use the first random numbers generated for different threads.
     if(id > 0 && first[id][j][0] == 1){
       first[id][j][0]=0;
     }
     else
     {
       rseed[j] = (unsigned long long)((mult_n  * rseed[j])% PMOD);
     }

     ret[j]=((double)rseed[j]/(double)PMOD);
   }
}

void seed(unsigned long long *iseed)
{
   int i, j, id, nthreads;
   id = omp_get_thread_num();

   #pragma omp single
   {
      // Init the flags for all threads.
      for(j=0; j< DIMENSION; j++){
        for(i=0; i< MAX_THREADS; i++){
          first[i][j][0]=1;
        }
        //
        nthreads = omp_get_num_threads();
        tmpseed[0][j] = iseed[j];
        mult_n = MULTIPLIER;
        for (i = 1; i < nthreads; ++i)
        {
          tmpseed[i][j] = (unsigned long long)((mult_n*tmpseed[0][j]) % PMOD);
          mult_n = (mult_n * MULTIPLIER) % PMOD;
        }
      }
  }
  for(j=0; j< DIMENSION; j++){
    rseed[j] = (unsigned long long) tmpseed[id][j];
  }
}


static long num_trials = 10000;
int main ()
{
 unsigned long long myseed[3], setseed;
 long i; long Ncirc = 0; double pi, x, y;
// int nthreads=0;

 myseed[0]=123456789;
 myseed[1]=123456;
 myseed[2]=56789;
#pragma omp parallel private (x, y) reduction (+:Ncirc)
  {
     seed(myseed);
     #pragma omp for
     for(i=0;i<num_trials; i++)
     {
       random(2,xyz);
       x=xyz[0];
       y=xyz[1];
       if (( x*x + y*y) <= 1.0) Ncirc++;
     }
  }
  pi = 4.0 * ((double)Ncirc/(double)num_trials);
  printf("\n %d trials, pi = %f \n",num_trials, pi);
}
