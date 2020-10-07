class Dinic {
    struct edge {
        int a, b, cap, flow;
    };
public:
    static const int MAXN = 2e2, INF = 1e9;

    int s, t, d[MAXN], ptr[MAXN], q[MAXN];
    vector<edge> e;
    vector<int> g[MAXN];

    Dinic(int source, int drain) : s(source), t(drain) {};

    void add_edge(int a, int b, int cap) {
        edge e1 = {a, b, cap, 0};
        edge e2 = {b, a, 0, 0};
        g[a].push_back(sz(e));
        e.push_back(e1);
        g[b].push_back(sz(e));
        e.push_back(e2);
    }

    bool bfs() {
        int qh{}, qt{};
        q[qt++] = s;
        memset(d, -1, MAXN * sizeof d[0]);
        d[s] = 0;
        while (qh < qt && d[t] == -1) {
            int v = q[qh++];
            for (size_t i = 0; i < g[v].size(); ++i) {
                int id = g[v][i], to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    int dfs(int v, int flow) {
        if (!flow)
            return 0;
        if (v == t)
            return flow;
        for (; ptr[v] < sz(g[v]); ++ptr[v]) {
            int id = g[v][ptr[v]], to = e[id].b;
            if (d[to] != d[v] + 1)
                continue;
            int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    int findMaxFlow() {
        int flow = 0;
        while (bfs()) {
            memset(ptr, 0, MAXN * sizeof ptr[0]);
            while (int pushed = dfs(s, INF))
                flow += pushed;
        }
        return flow;
    }
};
