#include <iostream>
#include <fstream>

using namespace std;

class SaveFile : public fstream{
    public:
    string full_name;
    SaveFile(string);
};