#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class MyDataStructure 
{
    int field0 = 0;
    int field1 = 0;
public:
    int get_field(int idx) 
{
        if (idx == 0) return field0;
        return field1;
    }
    void set_field(int idx, int val) 
{
        if (idx == 0) field0 = val;
        else field1 = val;
    }
    operator string() 
{
        return "Field0: " + to_string(field0) + ", Field1: " + to_string(field1);
    }
};

MyDataStructure shared_data;

void worker(string filename) 
{
    ifstream f(filename);
    if (!f.is_open()) {
        cout << "Error opening " << filename << endl;
        return;
    }

    string line, cmd;
    int val;

    while (getline(f, line)) 
    {
        stringstream ss(line);
        ss >> cmd;
        if (cmd == "read") 
        {
            int field;
            ss >> field;
            // cout << "read " << field << endl;
        } else if (cmd == "write") 
        {
            int field;
            ss >> field >> val;
            // cout << "write " << field << " " << val << endl;
        } else if (cmd == "string") 
        {
            // cout << "string op" << endl;
        }
    }
    f.close();
}

int main() {
    worker("test_v15_1.txt"); 
    return 0;
}
