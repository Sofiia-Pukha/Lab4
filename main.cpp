#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <mutex> 

using namespace std;

class MyDataStructure {
    int field0 = 0;
    int field1 = 0;
    std::mutex mx; 

public:
    int get_field(int idx) 
{
        std::lock_guard<std::mutex> lock(mx);
        if (idx == 0) return field0;
        return field1;
    }

    void set_field(int idx, int val) 
{
        std::lock_guard<std::mutex> lock(mx); 
        if (idx == 0) field0 = val;
        else field1 = val;
    }

    operator string() 
{
        std::lock_guard<std::mutex> lock(mx); 
        return "Field0: " + to_string(field0) + ", Field1: " + to_string(field1);
    }
};

MyDataStructure shared_data;

void worker(string filename) 
{
    ifstream f(filename);
    if (!f.is_open()) 
    {
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
            int field_idx;
            ss >> field_idx;
            volatile int res = shared_data.get_field(field_idx);
        } else if (cmd == "write") 
        {
            int field_idx;
            ss >> field_idx >> val;
            shared_data.set_field(field_idx, val);
        } else if (cmd == "string") 
        {
            string res = string(shared_data);
            volatile size_t len = res.length();
        }
    }
    f.close();
}

int main() 
{
    cout << "Starting test with basic mutex..." << endl;
    thread t1(worker, "test_v15_1.txt");
    thread t2(worker, "test_v15_2.txt");

    t1.join();
    t2.join();

    cout << "Done with basic mutex!" << endl;
    return 0;
}
