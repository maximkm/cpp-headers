vector<int> Zfunc(const string& s) {
    int n = sz(s);
    vector<int> z(n, 0);
    for (int i=1, l=0, r=0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

vector<int> Pref_func(const string& s) {
    int n = sz(s);
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int k = pi[i - 1];
        while (k && s[i] != s[k])
            k = pi[k - 1];
        pi[i] = k;
        if (s[i] == s[k])
            ++pi[i];
    }
    return pi;
}