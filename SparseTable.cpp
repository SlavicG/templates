template<bool mx, bool idx>
struct sparse_table{
	int n, k;
	vector<vector<int>> st;
	vector<int> a;
	sparse_table(vector<int> v){
		a = v;
		n = sz(a);
		k = lg(n);
		st.assign(n + 1, vector<int>(k + 1));
		build();
	}

	int merge(int x, int y){
		if(mx)return a[x] < a[y] ? y : x;
		return a[x] < a[y] ? x : y;
	}
	void build(){
		for(int i = 0;i < n;i++){
			st[i][0] = i;
		}
		for(int j = 1;j <= k;j++){
			for(int i = 0;i + (1 << j) - 1 < n;i++){
				st[i][j] = merge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
			}
		}
	}

	int query(int l, int r){
		int j = lg(r - l + 1);
		int i = merge(st[l][j], st[r - (1 << j) + 1][j]);
		return (idx ? i : a[i]);
	}

	int lg(int n){
		return (31 - __builtin_clz(n));
	}
	//1 - mx, 0 mn, 1 - return index, 0 - return value.
};
