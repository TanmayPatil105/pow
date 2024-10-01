#include <stdio.h>
#include <stdint.h>

/* Simple power logic */
uint64_t pow_ (uint64_t a,
              uint64_t b)
{
  uint64_t __pow = 1;

  for (int i = 0; i < b; i++)
    {
      __pow *= a;
    }

  return __pow;
}

#define A 5
#define B 12

int main()
{
  uint64_t __pow;

  __pow = pow_ (A, B);

  printf ("pow (%d, %d) = %ld\n", A, B, __pow);

  return 0;
}
