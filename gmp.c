/**
 * $ gcc gmp.c -o gmp -lgmp
 *
 **/

#include <stdio.h>
#include <gmp.h>

/*
 * This program implements an algorithm to calculate
 * the value of 'A' raised to the power of 'B'
 *
 * Time complexity: O (A * B)
 * Space complexity: O (B)
 * ---------------------------- */

#define A 2
#define B 10000

#define LOG(str) \
    do { \
      printf ("%s\n", str); \
      fflush(stdout); \
    } while (0);

int main()
{
  mpz_t mgk[B] = { 0 };   /* our magic array */
  mpz_set_ui (mgk[0], 1);

  mpz_t pow;
  mpz_init (pow);

  for (int i = 1; i <= B; i++)
    {
      /* 
       * value at ith index gets updated every iteration
       * which will be used to calculate the value of j+1 th index
       *
       * Keep a copy of the value at j-1 th index */
      mpz_t prev;
      mpz_init (prev);
      mpz_set_ui (prev, 1);

      for (int j = 1; j < i; j++)
        {
          /* copy the value at jth index which will be used by
           * j+1 th index in the next iteration */
          mpz_t dup;
          mpz_init (dup);
          mpz_set (dup, mgk[j]);

          /* update value is equal to 
           * product of sum of old value and old value at j - 1 th index
           * and the column number */
          mpz_t temp1, temp2, temp3;
          mpz_inits (temp1, temp2, temp3, NULL);

          mpz_set_ui (temp1, j);
          mpz_add_ui (temp1, temp1, 1); 

          mpz_set (temp2, mgk[j]);
          mpz_add (temp2, temp2, prev);
          mpz_mul (temp3, temp1, temp2);

          mpz_set (mgk[j], temp3);

          /* assign copied value to prev */
          mpz_set (prev, dup);

          mpz_clear (dup);
          mpz_clear (temp1);
          mpz_clear (temp2);
          mpz_clear (temp3);
        }

      mpz_clear (prev);
      if (i % 100 == 0)
        LOG ("quack");
    }

  for (int i = 0; i < A; i++)
    {
      /* add the magic value at index 0 (always equal to 1) */
      mpz_add (pow, pow, mgk[0]);

      for (int j = 0; j < B - 1; j++)
        {
          /* clone the value from next index and
           * add it self's value */
          mpz_add (mgk[j], mgk[j], mgk[j + 1]);
        }
    }

  gmp_printf ("pow (%d, %d) = %Zd\n", A, B, pow);

  for (int i = 0; i < B; i++)
    {
      mpz_clear (mgk[i]);
    }

  mpz_clear (pow);

  return 0;
}
