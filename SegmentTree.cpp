template<typename T>
struct LazySegmentTree{
    int n;
    vector<T> t, lazy, a;
    T neutral, lazy_neutral;
    function<T(const T&, const T&)> merge;
    function<T(const T&, const T&)> upd;
 
    bool range_modif = false;
    LazySegmentTree(int _n, T _neutral, T _lazy_neutral, const function<T(const T&, const T&)> &_merge, const function<T(const T&, const T&)> &_upd, bool _range_modif){
        range_modif = _range_modif;
        init(_n, _neutral, _lazy_neutral, _merge, _upd);
    }
    LazySegmentTree(vector<T> _a, T _neutral, T _lazy_neutral, const function<T(const T&, const T&)> &_merge, const function<T(const T&, const T&)> &_upd, bool _range_modif){
        range_modif = _range_modif, a = _a;
        int _n = (int)a.size();
        init(_n, _neutral, _lazy_neutral, _merge, _upd);
        build(1, 0, n - 1);
    }
 
    void init(int _n, T _neutral, T _lazy_neutral, const function<T(const T&, const T&)> &_merge, const function<T(const T&, const T&)> &_upd){
        n = _n, neutral = _neutral, lazy_neutral = _lazy_neutral, merge = _merge, upd = _upd;
        t.assign(4 * n, neutral);
        lazy.assign(4 * n, lazy_neutral);
    }
 
    void build(int i, int l, int r){
        if(l == r){
            t[i] = a[l];
            return;
        }
 
        int mid = (l + r) >> 1;
        build(2 * i, l, mid);
        build(2 * i + 1, mid + 1, r);
 
        t[i] = merge(t[2 * i], t[2 * i + 1]);
    }
 
    void push(int i, int l, int r){
        if(lazy[i] == lazy_neutral)return;
 
        t[i] = upd(t[i], lazy[i] * (range_modif ? (r - l + 1) : 1));
 
        if(l != r){
            lazy[2 * i] = upd(lazy[2 * i], lazy[i]);
            lazy[2 * i + 1] = upd(lazy[2 * i + 1], lazy[i]);
        }
        lazy[i] = lazy_neutral;
    }
 
    void modif(int i, int l, int r, int tl, int tr, T val){
        push(i, l, r);
        if(l > tr || r < tl)return;
 
        if(l >= tl && r <= tr){
            lazy[i] = upd(lazy[i], val);
            push(i, l, r);
            return;
        }
 
        int mid = (l + r) >> 1;
 
        modif(2 * i, l, mid, tl, tr, val);
        modif(2 * i + 1, mid + 1, r, tl, tr, val);
 
        t[i] = merge(t[2 * i], t[2 * i + 1]);
    }
    T query(int i, int l, int r, int tl, int tr){
        push(i, l, r);
        if(l > tr || r < tl)return neutral;
        if(l >= tl && r <= tr)return t[i];
 
        int mid = (l + r) >> 1;
 
        T left = query(2 * i, l, mid, tl, tr);
        T right = query(2 * i + 1, mid + 1, r, tl, tr);
 
        return merge(left, right);
    }
 
    void modif(int l, int r, T val){
        modif(1, 0, n - 1, l, r, val);
    }
    void modif(int poz, T val){
        modif(1, 0, n - 1, poz, poz, val);
    }
    T query(int l, int r){
        return query(1, 0, n - 1, l, r);
    }
    T query(int poz){
        return query(1, 0, n - 1, poz, poz);
    }
    //n, neutral, lazy neutral, merge, upd, bool range update
};
