#include<gmp.h>
#include<gmpxx.h>
#include<string>

#pragma once

// structure to hold keys 
struct Keys{
    mpz_class a_PrivateKey = -1;
    mpz_class b_PrivateKey = -1;
    mpz_class A_PublicKey = -1;
    mpz_class B_PublicKey = -1;
    mpz_class SharedKey = -1;
};

mpz_class generateKeyRandom(unsigned int);
unsigned long long strong_seed();