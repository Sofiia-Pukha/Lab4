#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>

using namespace std;

void generate_file(string filename, int lines) 
{
    ofstream f(filename);
    srand(time(NULL));
   for(int i=0; i<lines; ++i) 
   {
        int r = rand() % 3;
        if(r == 0) f << "read 0\n";
        else if(r == 1) f << "write 0 " << rand()%100 << "\n";
        else f << "string\n";
    f.close();
}

int main() {
    generate_file("test.txt");
    return 0;
}
