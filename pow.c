#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define A 5
#define B 12

int main()
{
  uint64_t __pow;

  /* glibc pow() */
  __pow = pow (A, B);

  printf ("pow (%d, %d) = %ld\n", A, B, __pow);

  return 0;
}
