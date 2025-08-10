#include "server.hpp"
#include "../protocols/dh.hpp"
#include "network.cpp"
#include <iostream>
#include <string>

/**
 * @brief Server-side implementation of Diffie-Hellman key exchange
 * @param dh The Diffie-Hellman cryptographic object
 * @param key Reference to the Keys structure to store generated keys
 * @param write Flag indicating whether to write the shared key to file
 */
void server(const DH& dh, Keys& key, bool write) {
    notify();
    std::cout << std::flush;
    
    // Generate server's private key
    key.a_PrivateKey = generateKeyRandom();
    if (key.a_PrivateKey == -1) {
        std::cerr << "Error: Failed to generate private key" << std::endl;
        exit(1);
    }
    
    const auto base = BASE::HEX;
    
    // Phase 1: Request and receive client's public key
    askKey(base);
    
    std::string inputBuffer;
    std::string* inputPtr = &inputBuffer;
    
    std::getline(std::cin, inputBuffer);
    if (wait(std::string("SEND"), inputPtr)) {
        readKey(key.B_PublicKey, inputPtr);
    }
    
    // Phase 2: Generate and send server's public key
    key.A_PublicKey = dh.generatePublicKey(key.a_PrivateKey);
    
    inputBuffer.clear(); // Reset buffer for next input
    std::getline(std::cin, inputBuffer);
    
    if (wait(std::string("RECV"), inputPtr)) {
        log(constructMessage(key, BASE::HEX, OPR::SEND));
    }
    
    // Phase 3: Compute shared secret key
    key.SharedKey = dh.computeSharedKey(key.B_PublicKey, key.a_PrivateKey);
    
    // Optionally write shared key to file
    if (write) {
        writeFile(key.SharedKey);
    }
}

inline void notify() {
    std::cout << "server-side" << std::endl;
}