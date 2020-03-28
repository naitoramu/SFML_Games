#include "saveFile.hpp"

using namespace std;

SaveFile::SaveFile(string name){
    full_name = "maps/" + name + ".txt";
    open(full_name, ios::out | ios::app);
    if(!good()){
        cout << "Nie mozna utworzyc pliku" << full_name << endl;
    }
}