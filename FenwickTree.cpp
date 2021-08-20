template<typename T, bool zero_indexing>
struct fenwick_tree{
    int N;
    vector<T> fen;
    fenwick_tree(int n){
        N = n, fen.assign(n + 1, 0);
    }
    void modif(int p, T val){
        for(int i = p + zero_indexing;i <= N;i += i & -i)fen[i] += val;
    }
    T query(int l, int r){
        T ret = 0;
        for(int i = r + zero_indexing;i;i -= i & -i)ret += fen[i];
        for(int i = l-1+zero_indexing;i;i-=i&-i)ret -= fen[i];
        return ret;
    }
};
