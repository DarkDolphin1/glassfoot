#include"client.hpp"
#include"network.cpp"

#pragma once

void client(const DH &dh , Keys &key){
    std::cout<<"Inside Client function"<<std::endl;
    if(verify()){
        // generate public keys and send it to server
        key.B_PublicKey = dh.generatePublicKey(key.b_PrivateKey);
        std::cout<<key.B_PublicKey.get_str(10)<<std::endl;

        // get server's public keys and compute Shared key
        std::string aPublicKeyString;
        std::getline(std::cin,aPublicKeyString);
        key.A_PublicKey.set_str(aPublicKeyString,10);

        key.SharedKey = dh.computeSharedKey(key.A_PublicKey,key.b_PrivateKey);

        writeFile(key.SharedKey);
    }else{
        std::cout<<"Verification failed";
    }
}