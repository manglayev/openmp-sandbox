#include <omp.h>
#include <stdio.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 16
void main()
{
  int i, number_of_threads_1; double pi, sum[NUM_THREADS];
  step = 1.0 / (double) num_steps;
  omp_set_num_threads(NUM_THREADS);
  //int threads_max = omp_get_num_threads();
  //int thread_id = omp_get_thread_num();
  //double time_after = omp_get_wtime();
  #pragma omp parallel
  {
    int i, id, number_of_threads_2;
    double x;
    id = omp_get_thread_num();
    number_of_threads_2 = omp_get_num_threads();
    if(id == 0) number_of_threads_1 = number_of_threads_2;

    for(i = id, sum[id] = 0.0; i < num_steps; i = i + number_of_threads_2)
    {
      x = (i + 0.5) * step;
      sum[id] = sum[id] + 4.0/(1.0 + x*x);
    }
  }
  pi = 0.0;
  for(i = 0; i < number_of_threads_1; i++)
    pi = pi + sum[i] * step;
  printf("%.5f\n", pi);
}
