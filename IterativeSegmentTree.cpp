template<typename T>
struct iterative_segtree{
	int n;
    vector<T> t;
    T neutral;
    function<T(const T&,const T&)> merge;

    iterative_segtree(int _n, T _neutral, const function<T(const T&, const T&)> &_merge){
    	init(_n, _neutral, _merge);
    	build();
    }
    iterative_segtree(vector<T> a, T _neutral, const function<T(const T&, const T&)> &_merge){
     	int _n = (int)a.size();
    	init(_n, _neutral, _merge);
    	for(int i = 0;i < n;i++)
    		t[i + n] = a[i];
    	build();

    }
    void init(int _n, T _neutral, const function<T(const T&, const T&)> &_merge){
    	n = _n;
    	neutral = _neutral;
    	merge = _merge;
    	t.assign(2 * n, neutral);
    }

    void init( T _neutral, const function<T(const T&, const T&)> &_merge){
    	neutral = _neutral;
    	merge = _merge;
    	t.assign(2 * n, neutral);
    }

    void build(){
    	for(int i = n - 1;i > 0;i--){
    		t[i]  = merge(t[i << 1], t[i << 1 | 1]);
    	}
    }

    void set(int p, T val)
    {
    	p += n;
    	t[p] = val;
    	while(p > 1)
    	{
    		t[p >> 1] = merge(t[p], t[p ^ 1]);
    		p >>= 1;
    	}
    }

    void increment(int p, T val)
    {
    	p += n;
    	t[p] += val;
    	while(p > 1)
    	{
    		t[p >> 1] = merge(t[p], t[p ^ 1]);
    		p >>= 1;
    	}
    }

    T query(int l, int r){
    	++r;
    	T ans = neutral;
    	l += n, r += n;
    	while(l < r)
    	{
    		if(l & 1){
    			ans = merge(ans, t[l++]);
    		}
    		if(r & 1){
    			ans = merge(ans, t[--r]);
    		}
    		l >>= 1;
    		r >>= 1;
    	}
    	return ans;
    }
    //n, neutral, merge
};
