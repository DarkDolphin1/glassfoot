#include"server.hpp"
#include"../protocols/dh.cpp"
#include"network.cpp"
#include<iostream>

#pragma once

void server(const DH &dh , Keys &key){
    notify();
    std::cout<<std::flush;

    // warning : server keys are not generated yet

    //get client's (Bob's) Public keys
    std::string bPublicKeyString;
    std::getline(std::cin,bPublicKeyString);
    key.B_PublicKey.set_str(bPublicKeyString,10); // might want to look into this later to see if base should be 10 or 16 

    //generate and send server's (Alice's) public keys
    key.A_PublicKey = dh.generatePublicKey(key.a_PrivateKey);
    std::cout<<std::flush<<key.A_PublicKey<<std::endl;

    //compute shared key
    key.SharedKey = dh.computeSharedKey(key.B_PublicKey,key.a_PrivateKey);

    writeFile(key.SharedKey);
}

inline void notify(){
    std::cout<<"server-side"<<std::endl;
}