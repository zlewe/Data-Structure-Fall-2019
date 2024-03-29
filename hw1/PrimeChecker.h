// 
// PrimeChecker.h
// DS hw1 warm up
//
/************************************************************************************
Miller-Rabin Test
Deterministic Variant - Always holds for 64-bit integers

Efficient M-R Test using best known SPRP bases (Jaeschke, Sinclair)
----------------------------------
Implementation by Ewe Zu Lin 
Copyright @2019
Distributed under GNU GPL v3.0
*************************************************************************************/
#ifndef _PrimeChecker_
#define _PrimeChecker_

class PRIMECHECKER {
	private:
	bool is_Prime(unsigned long);
	bool CheckSPRP(unsigned long, unsigned long);
	__uint128_t modular_pow(unsigned long, unsigned long, unsigned long);

	public:
	unsigned long PrimeChecker(unsigned long, unsigned long);
};
#endif

