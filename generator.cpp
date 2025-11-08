#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;


int PROB_V15[] = {10, 5, 50, 10, 25};
int PROB_EQUAL[] = {20, 20, 20, 20, 20};
int PROB_BAD[] = {5, 40, 5, 45, 5};

enum OpType { READ0, WRITE0, READ1, WRITE1, OP_STRING };

void generate_file(const string& filename, int lines_count, const int probs[5]) 
{
    ofstream f(filename);
    if (!f.is_open()) 
    {
        cerr << "Error opening " << filename << endl;
        return;
    }

    mt19937 gen(time(nullptr) + hash<string>{}(filename)); 
    uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < lines_count; ++i) {
        int r = dist(gen);
        int current_prob = 0;

        if ((current_prob += probs[0]) >= r)
        {
            f << "read 0\n";
        } else if ((current_prob += probs[1]) >= r) 
        {
            f << "write 0 " << (rand() % 100) << "\n";
        } else if ((current_prob += probs[2]) >= r) 
        {
            f << "read 1\n";
        } else if ((current_prob += probs[3]) >= r) 
        {
            f << "write 1 " << (rand() % 100) << "\n";
        } else 
        {
            f << "string\n";
        }
    }
    f.close();
    cout << "Generated: " << filename << endl;
}

int main() {
    srand(time(nullptr));
    int N = 200000; 

    generate_file("test_v15_1.txt", N, PROB_V15);
    generate_file("test_v15_2.txt", N, PROB_V15);
    generate_file("test_v15_3.txt", N, PROB_V15);

    generate_file("test_eq_1.txt", N, PROB_EQUAL);
    generate_file("test_eq_2.txt", N, PROB_EQUAL);
    generate_file("test_eq_3.txt", N, PROB_EQUAL);

    generate_file("test_bad_1.txt", N, PROB_BAD);
    generate_file("test_bad_2.txt", N, PROB_BAD);
    generate_file("test_bad_3.txt", N, PROB_BAD);

    return 0;
}
