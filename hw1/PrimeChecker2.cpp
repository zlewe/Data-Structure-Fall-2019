//
// PrimeChecker.cpp
// ds_hw1_warm_up
//
#include "PrimeChecker.h"
#include <stdlib.h>
#define ll long long

bool Miller(ll, int);

unsigned long PRIMECHECKER::PrimeChecker(unsigned long a, unsigned long b){
	int iter = 10;
	unsigned long count = 0;

	for (unsigned long i = a; i <= b; i++)
		if(Miller(i,iter))
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
      ll a = std::rand() % (p - 1) + 1, temp = s;
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
