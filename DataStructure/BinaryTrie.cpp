const int lgmax = 30;
 
struct trie
{
    trie *next[2];
    trie()
    {
        next[0] = next[1] = nullptr;
    };
    void insert(int val, int bit = lgmax)
    {
        if (bit == -1)
        {
            return;
        }
        int este = (val & (1 << bit)) > 0;
        if (next[este] == nullptr)
        {
            next[este] = new trie();
        }
        next[este]->insert(val, bit - 1);
    }
    int query(int val, int bit = lgmax)
    {
        if (bit == -1)
        {
            return 0;
        }
        int este = (val & (1 << bit)) > 0;
        if (next[1 - este])
        {
            return (1 << bit) + next[1 - este]->query(val, bit - 1);
        }
        else
        {
            return next[este]->query(val, bit - 1);
        }
    }
};