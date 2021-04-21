struct fenwick_tree {
    vector<ll> fen;
    int n;
    fenwick_tree(int n){
        this->n = n;
        fen.assign(n, 0);
    }

    template<typename T>
    fenwick_tree(vector<T> a){
    	this->n = sz(a);
    	fen.assign(n, 0);
        for (size_t i = 0; i < sz(a); i++)
            modif(i, a[i]);
    }
    ll query(int r){
        ll ret = 0;
        while(r >= 0){
        	ret += fen[r];
        	r = (r & (r + 1)) - 1;
        }
        return ret;
    }
    ll query(int l, int r) {
    	ll ret = query(r);
    	if(l)ret -= query(l - 1);
        return ret;
    }
    void modif(int idx, int val){
    	while(idx < n)
    	{
    		fen[idx] += val;
    		idx = idx | (idx + 1);
    	}
    }
};
