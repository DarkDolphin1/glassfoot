#include"server.hpp"
#include"../protocols/dh.cpp"
#include"network.cpp"
#include<iostream>

#pragma once

void server(const DH &dh , Keys &key , bool write){
    notify();
    std::cout<<std::flush;

    // warning : server keys are not generated yet
    key.a_PrivateKey = generateKeyRandom();

    //get client's (Bob's) Public keys
    std::string bPublicKeyString;
    std::getline(std::cin,bPublicKeyString);

    if(key.B_PublicKey.set_str(bPublicKeyString,10) != 0){
        std::cerr<<"error parsing the string from client"<<std::flush;
        exit(1);
    }

    key.B_PublicKey.set_str(bPublicKeyString,10); // might want to look into this later to see if base should be 10 or 16 

    //generate and send server's (Alice's) public keys
    if(key.a_PrivateKey == -1){
        exit(1);
    }

    key.A_PublicKey = dh.generatePublicKey(key.a_PrivateKey);
    std::cout<<std::flush<<key.A_PublicKey<<std::endl;

    //compute shared key
    key.SharedKey = dh.computeSharedKey(key.B_PublicKey,key.a_PrivateKey);

    if(write) writeFile(key.SharedKey);
}

inline void notify(){
    std::cout<<"server-side"<<std::endl;
}