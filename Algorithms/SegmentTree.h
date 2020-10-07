class SegmentTree {
public:
    vector<ll> T;
    int n, k;
    SegmentTree(int len) : n(len) {
        k = 1;
        while (k < n)
            k <<= 1;
        T.resize(2 * k);
    }

    void build(const vector<int>& data) {
        for (int i = 0; i < n; ++i)
            T[k - 1 + i] = data[i];
        for (int i = k - 2; i >= 0; --i)
            T[i] = T[2 * i + 1] + T[2 * i + 2];
    }

    ll cut_sum(int ql, int qr, int v, int l, int r) {
        if (r <= ql or qr <= l)
            return 0;
        if (ql <= l and r <= qr)
            return T[v];
        int m = (r + l) / 2;
        return cut_sum(ql, qr, 2*v+1, l, m) + cut_sum(ql, qr, 2*v+2, m, r);
    }

    ll cut_sum(int ql, int qr) {
        return cut_sum(ql, qr, 0, 0, k);
    }

    void update(int x, ll elem) {
        int v = x + k - 1;
        T[v] = elem;
        while (v) {
            --v, v /= 2;
            T[v] = T[2*v + 1] + T[2*v + 2];
        }
    }
};