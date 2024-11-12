#include <stdio.h>
#include <stdint.h>

/*
 * This program implements an algorithm to calculate
 * the value of 'A' raised to the power of 'B'
 *
 * Time complexity: O (A * B)
 * Space complexity: O (B)
 * ---------------------------- */

#define A 2
#define B 64

void print_mgk (unsigned long long *mgk);

int main()
{
  unsigned long long mgk[B] = { [0] = 1 };   /* our magic array */

  /*
   * 0 ^ 0 = 1;
   * 0 ^ n = 0;
   *
   * 0 as A is not handled
   */
  unsigned long long pow = 0;

  for (int i = 1; i <= B; i++)
    {
      /* 
       * value at ith index gets updated every iteration
       * which will be used to calculate the value of j+1 th index
       *
       * Keep a copy of the value at j-1 th index */
      unsigned long long prev = 1;

      for (int j = 1; j < i; j++)
        {
          /* copy the value at jth index which will be used by
           * j+1 th index in the next iteration */
          unsigned long long dup = mgk[j];

          /* update value is equal to 
           * product of sum of old value and old value at j - 1 th index
           * and the column number */
          mgk[j] = (mgk[j] + prev) * (j + 1);

          /* assign copied value to prev */
          prev = dup;
        }
    }

  for (int i = 0; i < A; i++)
    {
      /* add the magic value at index 0 (always equal to 1) */
      pow += mgk[0];

      for (int j = 0; j < B - 1; j++)
        {
          /* clone the value from next index and
           * add it self's value */
          mgk[j] += mgk[j + 1]; 
        }
    }

  printf ("pow (%d, %d) = %llu\n", A, B, pow);

  return 0;
}

void
print_mgk (unsigned long long *mgk)
{
  printf ("[ ");
  for (int i = 0; i < B; i++)
    {
      printf ("%lld ,", mgk[i]);
    }

  printf (" ]\n");
}
