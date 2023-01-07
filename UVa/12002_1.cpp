#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

bool comp1(const pair<int, int> &a, const pair<int, int> &b) {
    if (a.first != b.first)
        return a.first < b.first;
    else
        return a.second > b.second;
}

bool aux_cmp(const int &a, const int &b) {
    return a >= b;
}

int LDS(const deque< ii > &a) {
    vector< int > aux;
    for (int i = 0; i < a.size(); ++i) {
        auto p = a[i];
        int n = p.second;
        if (aux.empty()) {
            aux.push_back(n);
        } else {
            if (aux.back() > n) {
                aux.push_back(n);
            } else {
                int idx = lower_bound(aux.begin(), aux.end(), n, aux_cmp) - aux.begin();
                aux[idx] = n;
            }
        }
    }
    return int(aux.size());
}

int main() {

    int N;

    vector< ii > v;
    int lds[500];
    while (true) {
        scanf("%d", &N);
        if (N == 0)
            break;

        v.clear(); v.resize(N);

        for (int i = 0; i < N; ++i) {
            scanf("%d", &v[i].first);
            v[i].second = i;
        }

        sort(v.begin(), v.end());
        
        // Get the last N - i - 1 plates
        deque< ii > l, r(N);
        for (int ctr = 0; ctr < N; ++ctr)
            r[ctr] = v[N - 1 - ctr];

        // Precompute LDS(r)
        int ans = -1;
        vector<int> aux;
        for (int i = 0; i < N; ++i) {
            int n = r[i].second;
            if (aux.empty()) {
                aux.push_back(n);
                lds[i] = 1;
            } else {
                if (aux.back() > n) {
                    aux.push_back(n);
                    lds[i] = aux.size();
                } else {
                    int idx = lower_bound(aux.begin(), aux.end(), n, aux_cmp) - aux.begin();
                    aux[idx] = n;
                    lds[i] = idx + 1;
                }
            }
        }

        int lds_l = 0, lds_r = lds[N - 1];
        for (int i = 0; i < N; ++i) {

            lds_l = LDS(l);
            lds_r = lds[N - 1 - i];
            ans = max(ans, lds_l + lds_r);

            auto p = r[N - 1 - i];
            auto it = lower_bound(l.begin(), l.end(), p, comp1);
            l.insert(it, p);
        }
        
        printf("%d\n", ans);
    }

    return 0;
}
