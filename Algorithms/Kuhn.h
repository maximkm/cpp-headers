class Kuhn {
public:
    vector<vector<int>> g;
    vector<int> edge;
    vector<bool> used;

    Kuhn(int left, int right) {
        g.resize(left);
        used.resize(left);
        edge.resize(right, -1);
    }

    void add_edge(int left, int right) {
        g[left].push_back(right);  // only edge from left
    }

    bool kuhn(int v) {
        if (used[v])
            return false;
        used[v] = true;
        for (int i = 0; i < sz(g[v]); ++i) {
            int to = g[v][i];
            if (edge[to] == -1 || kuhn(edge[to])) {
                edge[to] = v;
                return true;
            }
        }
        return false;
    }

    void find() {
        for (int v = 0; v < sz(g); ++v) {
            fill(all(used), false);  // can assign
            kuhn(v);
        }
    }
};