#include <bits/stdc++.h>
using namespace std;

int char_to_int(char& c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    return c - 'a' + 26;
}

vector<string> split(string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream token_stream(s);
    
    while (getline(token_stream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

class UnionFind {
    public:
        vector<int> parent;
        vector<int> rank;

        UnionFind(int& n) {
            (this -> parent).resize(n);
            (this -> rank).resize(n, 0);

            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        int find(int& x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }

            return parent[x];
        }

        void unite(int& x, int& y) {
            int parent_x = find(x);
            int parent_y = find(y);

            if (parent_x == parent_y) return;

            if (rank[parent_x] < rank[parent_y]) {
                parent[parent_x] = parent_y;
            }

            else if (rank[parent_x] > rank[parent_y]) {
                parent[parent_y] = parent_x;
            }

            else {
                parent[parent_y] = parent_x;
                rank[parent_x]++;
            }
        }

        bool connected(int x, int y) {
            return find(x) == find(y);
        }
};

int main() {
    string country_str, build_str, destroy_str;
    cin >> country_str >> build_str >> destroy_str;

    vector<string> country_rows = split(country_str, ',');
    vector<string> build_rows = split(build_str, ',');
    vector<string> destroy_rows = split(destroy_str, ',');

    int N = country_rows.size();
    int base_cost = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (country_rows[i][j] == '1') {
                base_cost += char_to_int(destroy_rows[i][j]);
            }
        }
    }

    vector<tuple<int, int, int>> edges;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int weight;

            if (country_rows[i][j] == '1') {
                weight = -char_to_int(destroy_rows[i][j]);
            } 
            
            else {
                weight = char_to_int(build_rows[i][j]);
            }

            edges.push_back(make_tuple(weight, i, j));
        }
    }

    sort(edges.begin(), edges.end());

    UnionFind uf(N);
    long long mst_weight = 0;
    int count = 0;

    for (auto& edge : edges) {
        if (count == N - 1) break;

        int weight = get<0>(edge);
        int u = get<1>(edge);
        int v = get<2>(edge);

        if (!uf.connected(u, v)) {
            uf.unite(u, v);
            mst_weight += weight;
            count++;
        }
    }

    long long total_cost = base_cost + mst_weight;
    cout << total_cost << endl;
}