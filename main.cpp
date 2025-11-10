#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void worker(string filename) {
    ifstream f(filename);
    if (!f.is_open()) {
        cout << "Error opening " << filename << endl;
        return;
    }

    string line, cmd;
    int val;

    while (getline(f, line)) {
        stringstream ss(line);
        ss >> cmd;
        if (cmd == "read") {
            int field;
            ss >> field;
            // cout << "read " << field << endl;
        } else if (cmd == "write") {
            int field;
            ss >> field >> val;
            // cout << "write " << field << " " << val << endl;
        } else if (cmd == "string") {
            // cout << "string op" << endl;
        }
    }
    f.close();
}

int main() {
    worker("test_v15_1.txt"); 
    return 0;
}
