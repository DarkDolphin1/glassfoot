#include"server.hpp"
#include"../protocols/dh.cpp"
#include"network.cpp"
#include<iostream>

#pragma once

void server(const DH &dh , Keys &key , bool write){
    notify();
    std::cout<<std::flush;
    key.a_PrivateKey = generateKeyRandom();
    std::string bPublicKeyString;
    const auto Base = BASE::HEX;

    // send request to get client's (Bob's) Public keys
    askKey(Base);

    std::string str;
    auto strPtr = &str;
    std::getline(std::cin,str);
    if(wait(std::string("SEND"),strPtr)){
        readKey(key.B_PublicKey,strPtr);
    }

    // notify(true);    // skipping this for now as i haven't finished with error checking approach
    str = "";
    //generate and send server's (Alice's) public keys
    if(key.a_PrivateKey == -1){
        exit(1);
    }

    // time to send our public keys
    key.A_PublicKey = dh.generatePublicKey(key.a_PrivateKey);
    std::getline(std::cin,str);
    if(wait(std::string("RECV"),strPtr)){
        log(constructMessage(key,BASE::HEX,OPR::SEND));
    }

    //compute shared key
    key.SharedKey = dh.computeSharedKey(key.B_PublicKey,key.a_PrivateKey);

    if(write) writeFile(key.SharedKey);
}

inline void notify(){
    std::cout<<"server-side"<<std::endl;
}