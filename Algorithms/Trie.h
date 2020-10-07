class Trie {
    struct node {
        map<char, node> next;
        bool leaf=false;
    };
public:
    node root;

    void add_string(const string& s) {
        node* now = &root;
        for (const char& c: s) {
            now = &now->next[c];
        }
        now->leaf = true;
    }

    void print(node* now, string text) {
        if (now->leaf)
            cout << text << endl;
        for (auto it = now->next.begin(); it != now->next.end(); ++it) {
            char x = it->ff;
            print(&it->ss, text + x);
        }
    }

    void print() {
        print(&root, "");
    }
};
