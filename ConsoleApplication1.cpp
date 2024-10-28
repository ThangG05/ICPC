#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm> 
using namespace std;
using ll = long long;

vector<pair<int, int>> ke[100000];
vector<ll> check1;

void dijkstra(int n, int s, int t) {
    vector<int> d(n + 1, 1e9);
    d[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({ d[s], s });
    while (!q.empty()) {
        pair<int, int> top = q.top();
        int kc = top.first;
        int dinh = top.second;
        q.pop();
        if (kc > d[dinh]) {
            continue;
        }
        for (auto x : ke[dinh]) {
            int u = x.first;
            int w = x.second;
            if (d[u] > d[dinh] + w) {
                d[u] = d[dinh] + w;
                q.push({ d[u], u });
            }
        }
    }
    check1.push_back(d[t]);
}

int main() {
    int sql;
    cin >> sql;
    while (sql--) {
        int n, m;
        cin >> n >> m;


        for (int i = 0; i < 100000; i++) {
            ke[i].clear();
        }
        check1.clear();

        vector<vector<pair<int, int>>> loai(100000);


        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                loai[i].push_back({ i, j });
            }
        }

        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            pair<int, int> q = { x, y };
            auto it = find(loai[x].begin(), loai[x].end(), q);
            if (it != loai[x].end()) {
                loai[x].erase(it);
            }
        }

        for (int i = 1; i < n; i++) {
            for (auto p : loai[i]) {
                ke[p.first].push_back({ p.second, 1 });
                ke[p.second].push_back({ p.first, 1 });
            }
        }

        int s;
        cin >> s;
        for (int i = 1; i <= n; i++) {
            if (i != s) {
                dijkstra(n, s, i);
            }
        }

        if (!check1.empty()) {
            for (auto x : check1) {
                cout << x << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
