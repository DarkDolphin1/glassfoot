#include<gmp.h>
#include<gmpxx.h>
#include<fstream>
#include<cstdlib>
#include<iostream>
#include"../protocols/dh.hpp"
#include"../protocols/dh.cpp"


enum class OPR{
    SEND,
    RECV
};
enum class BASE{
    BIN = 2,
    OCT = 8,
    DEC = 10,
    HEX = 16
};

void writeFile (const mpz_class &sharedKey){
    std::ofstream out("sharedKey.txt");
    if(out.is_open()){
        out<<"SharedKey:"<<sharedKey.get_str(16)<<std::endl;
        out.close();
    }else{
        std::cerr<<"[ERROR] Failed to open file for writing"<<std::endl;
    }
}

inline bool verify(){
    std::string temp;
    std::getline(std::cin,temp);
    if(temp == std::string("server-side")){
        return true;
    }else{
        std::cout<<"Connection failed , terminating program"<<std::endl;
        std::exit(1);
    }
    return false;
}

inline void log(std::string str){
    std::cout<<str<<std::endl;
}

std::string constructMessage(Keys &key , BASE base ,OPR op){
    std::string message;
    if(op == OPR::SEND){    // this means we are constructing a message to send
        message += "SEND.";
        if(base == BASE::HEX){
            int base = 16;
            message += "HEX:";
            message += key.A_PublicKey.get_str(base);
        }else{
            int base = 10;
            message += "DEC:";
            message += key.A_PublicKey.get_str(base);
        }
    return message;
    }else{
        std::cerr<<"[ERROR] : can not read keys this way \n";
    }
    return "";
}

bool wait(std::string target,std::string *inputPtr){
    return (inputPtr->substr(4)==target);
}

void askKey(BASE base){
    std::string messageReq;
    messageReq += "RECV.";
    if(base == BASE::HEX){
        messageReq += "HEX:";
    }else if(base == BASE::DEC){
        messageReq += "DEC:";
    }else std::cerr<<"[ERROR] type not supported (yet) \n";
    messageReq += "0000011111";
    log(messageReq);
}

void readKey (mpz_class &KEY , std::string *strPtr){
    const int skip = 9;

    //dissect the input
    std::string incomingKey = strPtr->substr(skip);    //get key
    std::string op = strPtr->substr(0,4);              //get op , kinda useless 
    auto base = strPtr->substr(5,3);                   //get base , very important

    if(base == std::string("HEX")){
        KEY.set_str(incomingKey,16);
    }else if(base == std::string("DEC")){
        KEY.set_str(incomingKey,10);
    }
}

inline void notify(bool status){
    if(status){
        std::cout<<"1"<<std::endl;
    }else std::cout<<"0"<<std::endl;
}
