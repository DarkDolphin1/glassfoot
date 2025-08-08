#include"app.hpp"
#include"app.cpp"

int main (int argc , char** argv){
    
    bool is_server = false;
    bool write = true;
    bool help = false;
    
    for(int i = 0; i < argc; i++){
        if(argv[i] == std::string("--server")) is_server = true;
        if(argv[i] == std::string("--nowrite")) write = false;
        if(argv[i] == std::string("--help")) help = true;
    }
    
    if(help){
        PrintHelp();
        return 0;
    }
    app(is_server,write);

    return 0;
}