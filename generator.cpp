#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void generate_file(string filename) 
{
    ofstream f(filename);
    if (f.is_open()) {
        f << "read 0\n";
        f << "write 1 55\n";
        f << "string\n";
        f.close();
        cout << "Created " << filename << endl;
    }
}

int main() {
    generate_file("test.txt");
    return 0;
}
