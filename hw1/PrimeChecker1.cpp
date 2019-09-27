//
// PrimeChecker.cpp
// ds_hw1_warm_up
//
#include "PrimeChecker.h"

unsigned long PRIMECHECKER::PrimeChecker(unsigned long a, unsigned long b){
	unsigned long count = 0;

	for (unsigned long i = a; i <= b; i++)
		if(isPrime2(i))
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

bool PRIMECHECKER::isPrime2(unsigned long n){
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    // This is checked so that we can skip
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0) return false;

    for (unsigned long i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;

    return true;
}
