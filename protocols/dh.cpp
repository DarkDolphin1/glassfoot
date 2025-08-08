#include"dh.hpp"
#include<gmp.h>
#include<gmpxx.h>

#pragma once

class DH {
    public:
    mpz_class p , g;
    DH(const std::string& p_hex , const mpz_class gen = 2){
        p.set_str(p_hex,16);
        g = gen;
    }

    mpz_class generatePublicKey (const mpz_class& a)const{
        mpz_class PublicKey;
        mpz_powm( PublicKey.get_mpz_t() ,g.get_mpz_t() ,a.get_mpz_t() ,p.get_mpz_t() );
        return PublicKey;
    }

    mpz_class computeSharedKey(const mpz_class& B , const mpz_class& a)const{
        mpz_class SharedKey;
        mpz_powm(SharedKey.get_mpz_t(), B.get_mpz_t(), a.get_mpz_t() , p.get_mpz_t());
        return SharedKey;
    }

    inline bool checkKeys(const Keys &key){
    if(key.a_PrivateKey == - 1 || key.A_PublicKey == -1 || key.b_PrivateKey == -1 || key.B_PublicKey == -1) return false;
    if(key.SharedKey == -1) return false;
    return true;
    }
};