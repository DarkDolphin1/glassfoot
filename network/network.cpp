#include<gmp.h>
#include<gmpxx.h>
#include<fstream>
#include<cstdlib>
#include<iostream>

#pragma once 

void writeFile (const mpz_class &sharedKey){
    std::ofstream out("sharedKey.txt");
    if(out.is_open()){
        out<<"SharedKey:" <<sharedKey.get_str(10)<<std::endl;
        out.close();
    }else{
        std::cerr<<"[ERROR] Failed to open file for writing"<<std::endl;
    }
}
inline bool verify(){
    std::string temp;
    std::getline(std::cin,temp);
    if(temp == std::string("server-side")){
        std::cout<<"Connection established , Switching to client mode"<<std::endl;
        return true;
    }else{
        std::cout<<"Connection failed , terminating program"<<std::endl;
        std::exit(1);
    }
    return false;
}

