class AhoKorasik{
    static const int K = 2, N = 30000;

    struct node {
        int p, link, next[K], go[K];
        int link_term, status;
        bool leaf;
        char pch;
    };
public:
    node t[N + 1];
    int sz;

    AhoKorasik() { this->init(); }

    void init() {
        t[0].p = t[0].link = t[0].link_term = t[0].status = -1;
        memset(t[0].next, -1, sizeof t[0].next);
        memset(t[0].go, -1, sizeof t[0].go);
        sz = 1;
    }

    void add_string(const string& s) {
        int v = 0;
        for (size_t i = 0; i < s.length(); ++i) {
            char c = s[i] - '0';
            if (t[v].next[c] == -1) {
                memset(t[sz].next, -1, sizeof t[sz].next);
                memset(t[sz].go, -1, sizeof t[sz].go);
                t[sz].link = t[sz].link_term = t[sz].status = -1;
                t[sz].p = v;
                t[sz].pch = c;

                t[v].next[c] = sz++;
            }
            v = t[v].next[c];
        }
        t[v].leaf = true;
    }

    int get_link(int v) {
        if (t[v].link == -1)
            if (v == 0 || t[v].p == 0)
                t[v].link = 0;
            else
                t[v].link = go(get_link(t[v].p), t[v].pch);
        return t[v].link;
    }

    int go(int v, char c) {
        if (t[v].go[c] == -1)
            if (t[v].next[c] != -1)
                t[v].go[c] = t[v].next[c];
            else
                t[v].go[c] = v == 0 ? 0 : go(get_link(v), c);
        return t[v].go[c];
    }

    int find_term(int v) {
        if (t[v].link_term == -1) {
            int suf = get_link(v);
            if (t[suf].leaf || !suf)
                t[v].link_term = suf;
            else
                t[v].link_term = find_term(suf);
        }
        return t[v].link_term;
    }

    int dfs(int v=0) {  // my function
        t[v].status = 1;
        for (char x = 0; x <= 1; ++x) {
            int next = go(v, x);
            if (t[next].status == 1) {
                cout << "TAK" << endl;
                exit(0);
            } else if (t[next].status == 2 || t[next].leaf || find_term(next))
                continue;
            dfs(next);
        }
        t[v].status = 2;
        return 0;
    }
};