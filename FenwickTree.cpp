template<typename T>
struct fenwick_tree{
	int n;
	vector<T> fen;
	int LG;
	void compute_log(int n)
	{
		LG = 1;
		while(n){
			++LG;
			n /= 2;
		}
	}
	fenwick_tree(int _n){
		n = _n + 5;
		int x = n;
		fen.assign(n + 5, 0);
		compute_log(n);
	}
	fenwick_tree(vector<ll> a){
		n = (int)a.size() + 5;
		fen.assign(n + 5, 0);
		build(a);
		compute_log(n);
	}
	fenwick_tree(vector<int> a){
		n = (int)a.size() + 5;
		fen.assign(n + 5, 0);
		build(a);
		compute_log(n);
	}

	void build(vector<int> a){
		for(int i = 0;i < (int)a.size();i++){
			upd(i + 1, a[i]);
		}
	}
	void build(vector<ll> a){
		for(int i = 0;i < (int)a.size();i++){
			upd(i + 1, a[i]);
		}
	}

	void upd(int poz, int val)
	{
		for(int i = poz;i < n;i += (i & (-i))){
			fen[i] += val;
		}
	}
	void upd(int poz, ll val)
	{
		for(int i = poz;i < n;i += (i & (-i))){
			fen[i] += val;
		}
	}

	T query(int poz){
		T ans = 0;
		for(int i = poz;i > 0;i -= (i & (-i))){
			ans += fen[i];
		}
		return ans;
	}
	T query(int l, int r){
		return query(r) - query(l - 1);
	}

	T fen_search(T v)
	{
		T sum = 0;
		int pos = 0;
		for(int i = LG;i >= 0;i--)
		{
			if(pos + (1 << i) < n && sum + fen[pos + (1 << i)] < v){
				sum += fen[pos + (1 << i)];
				pos += (1 << i);
			}
		}
		return pos + 1;
	}
};
