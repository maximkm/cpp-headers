template<typename T>
void count_sort(vector<T>& p, vector<T>& c) {
    uint32_t n = p.size();
    vector<uint32_t> cnt(n);
    for (const uint32_t& x : c)
        ++cnt[x];
    vector<T> p_new(n);
    vector<uint32_t> pos(n);
    pos[0] = 0;
    for (uint32_t i = 1; i < n; ++i)
        pos[i] = pos[i - 1] + cnt[i - 1];
    for (const T& x : p) {
        uint32_t i = c[x];
        p_new[pos[i]] = x;
        ++pos[i];
    }
    p = move(p_new);
}

template<typename T>
void suffix_array(string& s, vector<T>& p, vector<T>& c) {
    s += '#';
    int n = s.size();
    p.resize(n);
    c.resize(n);
    vector<pair<uint32_t, uint32_t>> a(n);
    for (uint32_t i = 0; i < n; ++i)
        a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (uint32_t i = 0; i < n; ++i)
        p[i] = a[i].second;
    c[p[0]] = 0;
    for (uint32_t i = 1; i < n; ++i) {
        if (a[i].first == a[i - 1].first)
            c[p[i]] = c[p[i - 1]];
        else
            c[p[i]] = c[p[i - 1]] + 1;
    }
    uint32_t k = 1;
    while (k < n) {
        for (uint32_t i = 0; i < n; ++i)
            p[i] = (p[i] - k + n) % n;
        count_sort(p, c);
        vector<T> c_new(n);
        c_new[p[0]] = 0;
        bool flag = true;
        for (uint32_t i = 1; i < n; ++i) {
            if (c[p[i - 1]] == c[p[i]] && c[(p[i - 1] + k) % n] == c[(p[i] + k) % n]) {
                c_new[p[i]] = c_new[p[i - 1]];
                flag = false;
            } else
                c_new[p[i]] = c_new[p[i - 1]] + 1;
        }
        c = move(c_new);
        k <<= 1;
        if (flag)
            break;
    }
    s.pop_back();
}

template <typename T>
void LCP(string& s, vector<T>& lcp, vector<T>& p, vector<T>& c) {
    int n = c.size();
    lcp.resize(n - 1);
    int k = 0;
    for (int i = 0; i < n - 1; ++i) {
        int j = p[c[i] - 1];
        while (s[i + k] == s[j + k]) ++k;
        lcp[c[i] - 1] = k;
        k = max(k - 1, 0);
    }
}
