#include <omp.h>
#include <stdio.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 16
void main()
{
  double pi = 0.0;
  step = 1.0 / (double) num_steps;
  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel
  {
    int i, id, number_of_threads_1, number_of_threads_2;
    double x, sum;
    id = omp_get_thread_num();
    number_of_threads_1 = omp_get_num_threads();
    if(id == 0) number_of_threads_2 = number_of_threads_1;
    id = omp_get_thread_num();
    number_of_threads_1 = omp_get_num_threads();
    for(i = id, sum = 0.0; i < num_steps; i = i + number_of_threads_1)
    {
      x = (i + 0.5) * step;
      sum += 4.0/(1.0 + x*x);
    }
    #pragma omp critical
    pi += sum * step;
  }
  printf("%.5f\n", pi);
}
