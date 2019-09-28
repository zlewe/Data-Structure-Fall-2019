//
// PrimeChecker.cpp
// ds_hw1_warm_up
//
/************************************************************************************
Miller-Rabin Test
Deterministic Variant - Always holds for 64-bit integers

Pseudocode from Wikipedia: 
	Input: n > 1, an odd integer to be tested for primality
	Output: “composite” if n is composite, “prime” otherwise

	write n as 2^r·d + 1 with d odd (by factoring out powers of 2 from n − 1)
	WitnessLoop: for all a in the range [2, min(n−2, ⌊2(ln n)^2⌋)]:
	   x ← a^d mod n
	   if x = 1 or x = n − 1 then
		  continue WitnessLoop
	   repeat r − 1 times:
		  x ← x^2 mod n
		  if x = n − 1 then
			 continue WitnessLoop
	   return “composite”
	return “prime”


I modified above pseudocode for efficient M-R Test using best known SPRP bases sets as listed in https://miller-rabin.appspot.com/:

Jaeschke Set: 2,7,61  (Holds for n < 4759123141 (>32-bit))
Sinclair Set: 2,325,9375,28178,450775,9780504,1795265022   (Holds for at least n < 2^64)
----------------------------------
Implementation by Ewe Zu Lin 
Copyright @2019
Distributed under GNU GPL v3.0
*************************************************************************************/
#include "PrimeChecker.h"
#include <stdint.h>
#define UINT32_MAX (0xffffffff)	//use for checking if n is larger than 32bit

unsigned long PRIMECHECKER::PrimeChecker(unsigned long a, unsigned long b){
	unsigned long count = 0;

	for (unsigned long i = a; i <= b; i++)
		if(is_Prime(i))
			count++;

	return count;
}

/***********************************************************************************
Outer Function: If n pass SPRP Test with the SPRP bases, n is a prime.
Pseudocode:
	Input: n, an integer up to 64-bit unsigned int
	Output: “composite” if n is composite, “prime” otherwise
	
	if n = even then
		if n = 2 then
			return "prime"
		else 
			return "composite"
		
	if n < 32-bit then use Jaeschke Set as SPRP bases set
	else use Sinclair Set as SPRP bases set
	
	for all a (witness) in the SPRP bases set
		if inner function(n) does not return "probable prime"
			return "composite"
	return "prime"
*************************************************************************************/
bool PRIMECHECKER::is_Prime (unsigned long n)
{
    //sprp32_base = 2, 7, 61 (Jaeschke)
	//sprp64_base = 2, 325, 9375, 28178, 450775, 9780504, 1795265022 (Sinclair)

	//base cases
	if (n == 2)
		return (1);
	if ((n & 0x1) == 0)	//even
		return (0);

	switch (n <= UINT32_MAX){
		case true:	//32bit
			if (!CheckSPRP(n, 2)) return (0);
			if (!CheckSPRP(n, 7)) return (0);
			if (!CheckSPRP(n, 61)) return (0);
			break;
		
		case false:	//64bit
			if (!CheckSPRP(n, 2)) return (0);
			if (!CheckSPRP(n, 325)) return (0);
			if (!CheckSPRP(n, 9375)) return (0);
			if (!CheckSPRP(n, 28178)) return (0);
			if (!CheckSPRP(n, 450775)) return (0);
			if (!CheckSPRP(n, 9780504)) return (0);
			if (!CheckSPRP(n, 1795265022)) return (0);
			break;
	
	}

    return (1); //prime
}

/***********************************************************************************
Modular Exponentiation by Repeated Squaring (Pseudocode from Wikipedia):
	function modular_pow(base, exponent, modulus)
		if modulus = 1 then return 0
		Assert :: (modulus - 1) * (modulus - 1) does not overflow base
		result := 1
		base := base mod modulus
		while exponent > 0
			if (exponent mod 2 == 1):
			   result := (result * base) mod modulus
			exponent := exponent >> 1
			base := (base * base) mod modulus
		return result
*************************************************************************************/
__uint128_t PRIMECHECKER::modular_pow(unsigned long b, unsigned long e, unsigned long m)
{
	if (m == 1)
		return 0;
	
	__uint128_t res = 1;
	__uint128_t w = b; //prevent base overflow
	w = w % m;
	while (e != 0){
		if ((e & 0x1) == 1)
			res = (res*w) % m;
		e >>= 1;
		w = (w*w) % m;
	}
	return res;
}

/***********************************************************************************
Inner Function: Check for SPRP (Strong Probable Prime Test)
Pseudocode:
	Input: n > 2, an odd integer up to 64-bit unsigned int, and a (witness) from the SPRP bases set 
	Output: "composite" if n is composite, "probable prime" otherwise
	
	write n as 2^r·d + 1 with d odd (by factoring out powers of 2 from n - 1)

	a ← a mod n 
	if a = 0 then
		return "probable prime"
	
	x ← a^d mod n		***(since we are dealing with big 64-bit integer, we use modular exponentiation by repeated squaring to calculate a^d mod n)***
    if x = 1 or x = n − 1 then
		return "probable prime"
	repeat r − 1 times:
		x ← x^2 mod n
		if x = n − 1 then
			return "probable prime"
	return “composite”
*************************************************************************************/
bool PRIMECHECKER::CheckSPRP (unsigned long n, unsigned long a){
	unsigned long m = n-1, d, y;
	unsigned long one = 2;
	unsigned int r = 1;
	
	//represent n as (2^r)*d + 1
	while ((m & one) == 0){
    	r++;
	one <<=  1;
    } 
    d = m >> r;
	
    a %= n;
    if (a == 0)
		return 1;		//probable prime


    __uint128_t u;
	
    u = modular_pow(a,d,n);
    
    if ((y = (unsigned long) u) == 1)
		return (1);		//probable prime
    if (y == m)
		return (1);  	//probable prime
	
    for (unsigned int j = 1; j < r; j++)
    {
		__uint128_t u = y;
		u = u*u % n;

		if ((y = (unsigned long) u) == m)
			return (1);	//probable prime
    }

    return (0);
}