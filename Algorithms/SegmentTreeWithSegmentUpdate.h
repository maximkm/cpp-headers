class SegmentTreeUpdate {
    struct node {
        ll x{}, d{};

        ll val() { return x + d; }
    };

public:
    vector<node> T;
    int n, k;

    SegmentTreeUpdate(int len) : n(len) {
        k = 1;
        while (k < n)
            k <<= 1;
        T.resize(2 * k);
    }

    void build() {
        for (int i = 0; i < n; ++i)
            cin >> T[k - 1 + i].x;
        for (int i = k - 2; i >= 0; --i)
            T[i].x = T[2 * i + 1].x + T[2 * i + 2].x;
    }

    void push(int v) {
        if (v >= k - 1)
            return;
        T[2 * v + 1].d += T[v].d / 2;
        T[2 * v + 2].d += T[v].d / 2;
        T[v].d = 0;
        T[v].x = T[2 * v + 1].val() + T[2 * v + 2].val();
    }

    void update(int ql, int qr, ll val, int v, int l, int r) {
        if (r <= ql or qr <= l)
            return;
        if (ql <= l and r <= qr) {
            T[v].d += val * (r - l);
            return;
        }
        push(v);
        int m = (l + r) >> 1;
        update(ql, qr, val, 2 * v + 1, l, m);
        update(ql, qr, val, 2 * v + 2, m, r);
        T[v].x = T[2 * v + 1].val() + T[2 * v + 2].val();
    }

    void update(int ql, int qr, ll val) {
        update(ql, qr, val, 0, 0, k);
    }

    ll cut_sum(int ql, int qr, int v, int l, int r) {
        if (ql >= r or qr <= l)
            return 0;
        if (ql <= l and r <= qr)
            return T[v].val();
        push(v);
        int m = (l + r) >> 1;
        return cut_sum(ql, qr, 2 * v + 1, l, m) + cut_sum(ql, qr, 2 * v + 2, m, r);
    }

    ll cut_sum(int ql, int qr) {
        return cut_sum(ql, qr, 0, 0, k);
    }
};