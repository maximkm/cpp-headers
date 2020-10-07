template<typename T>
struct SparseTable {
    vector<T> LOG;
    vector<vector<T>> ST;

    explicit SparseTable(const vector<T>& data) {
        int n = 2 * data.size();
        LOG.resize(n);
        LOG[1] = 0;
        for (int i = 2; i < n; ++i)
            LOG[i] = LOG[i / 2] + 1;
        ST = vector<vector<T>>(n, vector<T>(n));
        ST[0] = data;
        int k = 1;
        while ((1 << k) <= n) {
            for (int i = 0; i + (1 << k) <= n; ++i)
                ST[k][i] = min(ST[k - 1][i], ST[k - 1][i + (1 << (k - 1))]);
            ++k;
        }
    }

    T MIN(int l, int r) const {
        int k = LOG[r - l + 1];
        return min(ST[k][l], ST[k][r - (1 << k) + 1]);
    }
};