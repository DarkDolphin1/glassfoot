#include<iostream>
#include<string.h>
#include<gmp.h>
#include<gmpxx.h>
#include<fstream>
#include<cstdlib>

#include"network/network.cpp"
#include"network/server.cpp"
#include"network/client.cpp"
#include"protocols/dh.cpp"

#pragma once

void app(bool server , bool write);

void PrintHelp();