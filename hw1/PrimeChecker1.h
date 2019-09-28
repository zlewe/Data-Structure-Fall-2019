// 
// PrimeChecker.h
// DS hw1 warm up
//
/************************************************************************************
Naive Primality Test

1. Simple Primality Test
2. Slightly Optimised Simple Primality Test
----------------------------------
Implementation by Ewe Zu Lin 
Copyright @2019
Distributed under GNU GPL v3.0
*************************************************************************************/
#ifndef _PrimeChecker_
#define _PrimeChecker_

class PRIMECHECKER {
	private:
	bool isPrime(unsigned long n);
	bool isPrime2(unsigned long n);

	public:
	unsigned long PrimeChecker(unsigned long, unsigned long);
};
#endif

