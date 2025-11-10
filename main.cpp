#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <shared_mutex> 
#include <sstream>
#include <chrono>

using namespace std;

class MyDataStructure 
{
private:
    int field0 = 0;
    int field1 = 0;
    mutable std::shared_mutex mx;
public:
    int get_field(int field_idx) const 
{
        std::shared_lock<std::shared_mutex> lock(mx);
        if (field_idx == 0) return field0;
        else return field1;
    }

    void set_field(int field_idx, int val) 
{
        std::unique_lock<std::shared_mutex> lock(mx);
        if (field_idx == 0) field0 = val;
        else field1 = val;
    }

    operator string() const 
{
        std::shared_lock<std::shared_mutex> lock(mx);
        stringstream ss;
        ss << "Field0: " << field0 << ", Field1: " << field1;
        return ss.str();
    }
};

MyDataStructure shared_data;

void worker(string filename) 
{
    ifstream f(filename);
    if (!f.is_open()) return;

    string line, cmd;
    int field_idx, val;

    while (getline(f, line)) 
    {
        stringstream ss(line);
        ss >> cmd;
        if (cmd == "read") 
        {
            ss >> field_idx;
            volatile int res = shared_data.get_field(field_idx);
        }
        else if (cmd == "write") 
        {
            ss >> field_idx >> val;
            shared_data.set_field(field_idx, val);
        }
        else if (cmd == "string") 
        {
            string res = string(shared_data);
            volatile size_t len = res.length();
        }
    }
    f.close();
}

void run_test(int num_threads, const vector<string>& files) 
{
    auto start = chrono::high_resolution_clock::now();

    vector<thread> threads;
    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(worker, files[i]);
    }

    for (auto& t : threads) 
    {
        t.join();
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diff = end - start;

    cout << "Threads: " << num_threads << " | Time: " << diff.count() << " ms" << endl;
}

int main() {
    cout << "=== Starting ===" << endl;

    vector<string> files_v15 = {"test_v15_1.txt", "test_v15_2.txt", "test_v15_3.txt"};
    vector<string> files_eq = {"test_eq_1.txt", "test_eq_2.txt", "test_eq_3.txt"};
    vector<string> files_bad = {"test_bad_1.txt", "test_bad_2.txt", "test_bad_3.txt"};

    cout << "\n--- Scenario A (Variant 15 conditions: 85% reads) ---" << endl;
    run_test(1, files_v15);
    run_test(2, files_v15);
    run_test(3, files_v15);

    cout << "\n--- Scenario B (Equal conditions: all 20%) ---" << endl;
    run_test(1, files_eq);
    run_test(2, files_eq);
    run_test(3, files_eq);

    cout << "\n--- Scenario C (Bad conditions: many writes) ---" << endl;
    run_test(1, files_bad);
    run_test(2, files_bad);
    run_test(3, files_bad);

    cout << "\n=== Done ===" << endl;
    return 0;
}
