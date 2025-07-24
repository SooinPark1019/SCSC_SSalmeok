struct Trie {
    bool finish; // 끝나는 지점을 표시해줌
    Trie* next[26]; // 26가지 알파벳에 대한 트라이
    Trie() : finish(false) {
        memset(next, 0, sizeof(next));
    }
    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (next[i])
                delete next[i];
    }
    void insert(string& key, int pos) {
        if (pos==key.length())
            finish = true;
        else {
            int curr = key[pos] - 'A';
            if (next[curr] == NULL)
                next[curr] = new Trie();
            next[curr]->insert(key, pos+1);
        }
    }
    bool find(string& key, int pos) {
        if (pos==key.length()) return this.finish;
        int curr = key[pos] - 'A';
        if (next[curr] == NULL) return false;
        return next[curr]->find(key, pos+1);
    }
};