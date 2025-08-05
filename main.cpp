#include<iostream>
#include<string.h>
#include<gmp.h>
#include<gmpxx.h>
#include<fstream>
#include<cstdlib>

struct Keys{
    mpz_class a_PrivateKey = 123456789;
    mpz_class b_PrivateKey = 987654321;
    mpz_class A_PublicKey;
    mpz_class B_PublicKey;
    mpz_class SharedKey;
};

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
};

void writeFile (const mpz_class &sharedKey){
    std::ofstream out("sharedKey.txt");
    if(out.is_open()){
        out<<"SharedKey:" <<sharedKey.get_str(10)<<std::endl;
        out.close();
    }else{
        std::cerr<<"[ERROR] Failed to open file for writing"<<std::endl;
    }
}

inline void notify(){
    std::cout<<"server-side"<<std::endl;
}

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

int main (int argc , char** argv){
    bool is_server = false;
    if(argc > 1 && std::string(argv[1]) == "server-side"){
        is_server = true;
    }

    std::string p_hex = "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD1"
                        "29024E088A67CC74020BBEA63B139B22514A08798E3404DD"
                        "EF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245"
                        "E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7ED"
                        "EE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3D"
                        "C2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F"
                        "83655D23DCA3AD961C62F356208552BB9ED529077096966D"
                        "670C354E4ABC9804F1746C08CA18217C32905E462E36CE3B"
                        "E39E772C180E86039B2783A2EC07A28FB5C55DF06F4C52C9"
                        "DE2BCBF6955817183995497CEA956AE515D2261898FA0510"
                        "15728E5A8AACAA68FFFFFFFFFFFFFFFF";
    DH dh(p_hex);
    Keys key;

    if(is_server){
        server(dh,key);
    }else{
        client(dh,key);
    }
    return 0;
}
