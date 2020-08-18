#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <exception>
#include <fstream>

using namespace std; //?

namespace ble{

    int Ble(){
        printf("%s\n", "ble");
        return 0;
    }

    int func(int x, int y){
        if (x > y){
            return x/y;
        }
        else return 0;
    }
}
namespace waah{
    int Waah(){
        printf("%s\n", "waah");
        return 0;
    }
}

int main(int argc, char** argv){
    using namespace waah;
    Waah();
    ble::Ble();

        int x;
        cout << "give numbah\n";
    try{
        cin >> x;
    }
    catch(const exception& e){
        throw runtime_error("Input invalido\n");
        cout << e.what();
        return -1;
    }
    catch(...){
        cout << "excepcion desconocida";
        throw;
    }

    cout << "numbah given: " << x << "\n";

    //ARCHIVOS

    cout << "comando: " + access("archTXT.txt", F_OK);

/*
    FILE* fp = fopen("archTXT.txt","r");
    if(fp == nullptr) throw runtime_error("no se pudo abrir el archivo. ");
    fclose(fp);
*/
    //se puede usar std::string&
    //FILE* fs;
    //std::ifstream fs("archTXT");

    return 0;
}
