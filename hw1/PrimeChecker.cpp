//
// PrimeChecker.cpp
// ds_hw1_warm_up
//
#include "PrimeChecker.h"
#include <stdlib.h>
#include <cstdint>
#define ll long long

bool Miller(ll, int);
static int is_prime(uint64_t);

unsigned long PRIMECHECKER::PrimeChecker(unsigned long a, unsigned long b){
	int iter = 10;
	unsigned long count = 0;

	for (unsigned long i = a; i <= b; i++)
		if(is_prime(i))
			count++;

	return count;
}

bool PRIMECHECKER::isPrime(unsigned long n){

	bool flag = true;
	for(unsigned long i = 2; i*i <= n; i++){
		if(n % i == 0){
          		flag = false;
			break;
		}
	}

	return flag;
}

ll mulmod(ll a, ll b, ll m){
   ll x = 0,y = a % m;
   while (b > 0) {
      if (b % 2 == 1) {
         x = (x + y) % m;
      }
      y = (y * 2) % m;
      b /= 2;
   }
   return x % m;
}

ll modulo(ll base, ll e, ll m) {
   ll x = 1;
   ll y = base;
   while (e > 0) {
      if (e % 2 == 1)
         x = (x * y) % m;
         y = (y * y) % m;
         e = e / 2;
   }
   return x % m;
}

bool Miller(ll p, int iteration) {
   if (p < 2) {
      return false;
   }
   if (p != 2 && p % 2==0) {
      return false;
   }
   ll s = p - 1;
   while (s % 2 == 0) {
      s /= 2;
   }
   for (int i = 0; i < iteration; i++) {
      ll a = rand() % (p - 1) + 1, temp = s;
      ll mod = modulo(a, temp, p);
      while (temp != p - 1 && mod != 1 && mod != p - 1) {
         mod = mulmod(mod, mod, p);
         temp *= 2;
      }
      if (mod != p - 1 && temp % 2 == 0) {
         return false;
      }
   }
   return true;
}

/******************************************************************************/

static int sprp (uint64_t n, uint64_t a)
{
    unsigned __int128 m = n - 1, r, y;
    unsigned int s = 1, j;

    /* assert(n > 2 && (n & 0x1) != 0); */

    while ((m & (UINT64_C(1) << s)) == 0) s++;
    r = m >> s; /* r, s s.t. 2^s * r = n - 1, r in odd. */

    if ((a %= n) == 0) /* else (0 < a < n) */
        return (1);

    {
        uint64_t u = 1, w = a;

        while (r != 0)
        {
            if ((r & 0x1) != 0)
                u = (u * w) % n; /* (mul-rdx) */

            if ((r >>= 1) != 0)
                w = (w * w) % n; /* (sqr-rdx) */
        }

        if ((y = (uint64_t) u) == 1)
            return (1);
    }

    for (j = 1; j < s && y != m; j++)
    {
        unsigned __int128 u = y;
        u = (u * u) % n; /* (sqr-rdx) */

        if ((y = (uint64_t) u) <= 1) /* (n) is composite: */
            return (0);
    }

    return (y == m);
}

/******************************************************************************/

static int is_prime (uint64_t n)
{
    const uint32_t sprp32_base[] = /* (Jaeschke) */ {
        2, 7, 61, 0};

    const uint32_t sprp64_base[] = /* (Sinclair) */ {
        2, 325, 9375, 28178, 450775, 9780504, 1795265022, 0};

    const uint32_t *sprp_base;

    /* assert(n > 1); */

    if ((n & 0x1) == 0) /* even: */
        return (n == 2);

    sprp_base = (n <= UINT32_MAX) ? sprp32_base : sprp64_base;

    for (; *sprp_base != 0; sprp_base++)
        if (!sprp(n, *sprp_base)) return (0);

    return (1); /* prime. */
}
