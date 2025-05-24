#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Slot {
    string key;
    string status;

    Slot() {
        this -> key = "";
        this -> status = "never used";
    }
};

class HashTable {
    private:
        vector<Slot> table;

    public:
        HashTable(): table(26) {}

        int hash(const string& key) {
            return key.back() - 'a';
        }

        int search(const string& key) {
            int idx = hash(key);

            for (int i = 0; i < 26; i++) {
                int curr = (idx + i) % 26;

                if (table[curr].status == "never used") {
                    return -1;
                }

                if (table[curr].status == "occupied" && table[curr].key == key) {
                    return curr;  
                } 
            }

            return -1;
        }

        void insert(const string& key) {
            if (search(key) != -1) return;

            int idx = hash(key);

            for (int i = 0; i < 26; i++) {
                int curr = (idx + i) % 26;

                if (table[curr].status != "occupied") {
                    table[curr].key = key;
                    table[curr].status = "occupied";
                    return;
                }
            }
        }

        void remove(const string& key) {
            int pos = search(key);

            if (pos == -1) return;

            table[pos].status = "tombstone";
        }

        void print() {
            for (int i = 0; i < 26; i++) {
                if (table[i].status == "occupied") {
                    cout << table[i].key << " ";
                }
            }

            cout << endl;
        }
};

int main() {
    HashTable table;
    string input;
    getline(cin, input);
    istringstream iss(input);
    string move;

    while (iss >> move) {
        if (move[0] == 'A') {
            table.insert(move.substr(1));
        }

        else {
            table.remove(move.substr(1));
        }
    }

    table.print();
}