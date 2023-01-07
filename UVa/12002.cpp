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

        // Get the first i plates
        deque< ii > l(1);
        for (int ctr = 0; ctr < 1; ++ctr)
            l[ctr] = v[ctr];
        
        // Get the last N - i - 1 plates
        deque< ii > r((N-1));
        for (int ctr = 0; ctr < (N-1); ++ctr)
            r[ctr] = v[N - 1 - ctr];

        int ans = -1;
        for (int i = 0; i < N; ++i) {

            int lds_l = LDS(l), lds_r = LDS(r);
            ans = max(ans, lds_l + lds_r);

            if (r.empty())
                break;
            auto p = r.back(); r.pop_back();
            auto it = lower_bound(l.begin(), l.end(), p, comp1);
            l.insert(it, p);
        }
        
        printf("%d\n", ans);
    }

    return 0;
}
