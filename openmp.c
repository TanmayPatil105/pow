/**
 * $ gcc openmp.c -o openmp -lgmp -fopenmp
 *
 **/

#include <stdio.h>
#include <gmp.h>
#include "omp.h"


#define A 2
#define B 10000

#define LOG(str) \
    do { \
      printf ("%s\n", str); \
      fflush(stdout); \
    } while (0);

int main()
{
  mpz_t mgk_x[B] = { 0 };   /* our magic array */
  mpz_t mgk_y[B] = { 0 };
  mpz_t *x = mgk_x;
  mpz_t *y = mgk_y;

  mpz_set_ui (mgk_x[0], 1);
  mpz_set_ui (mgk_y[0], 1);

  mpz_t pow;
  mpz_init (pow);

  for (int i = 1; i <= B; i++)
    {
      #pragma omp parallel for
      for (int j = 1; j < i; j++)
        {
          mpz_t temp1, temp2;
          mpz_inits (temp1, temp2, NULL);

          mpz_set_ui (temp1, j + 1);

          mpz_set (temp2, y[j]);
          mpz_add (temp2, temp2, y[j-1]);

          mpz_mul (temp1, temp1, temp2);

          mpz_set (x[j], temp1);

          mpz_clear (temp1);
          mpz_clear (temp2);
        }

      /* should be atomic */
      mpz_t *tmp = x;
      x = y;
      y = tmp;

      if (i % 1000 == 0)
        LOG ("quack");
    }

  x = B & 1 ? mgk_x : mgk_y;

  for (int i = 0; i < A; i++)
    {
      mpz_add (pow, pow, x[0]);
      for (int j = 0; j < B - 1; j++)
        {
          mpz_add (x[j], x[j], x[j + 1]);
        }
    }

  gmp_printf ("pow (%d, %d) = %Zd\n", A, B, pow);

  for (int i = 0; i < B; i++)
    {
      mpz_clear (mgk_x[i]);
      mpz_clear (mgk_y[i]);
    }

  mpz_clear (pow);

  return 0;
}
