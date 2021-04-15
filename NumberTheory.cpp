namespace number_theory
{
	vector<int> primes, lp, phis;
	vector<int> fact;
	vector<int> fib;

	int mod;
	void setmod(int x){mod = x;}

	template <typename T, typename C> 
	T add(T a, C b)
	{
		assert(a >= 0 && b >= 0);
		a %= mod, b %= mod;
		return (a + b) % mod;
	}
	template <typename T, typename C> 
	T sub(T a, C b)
	{
		assert(a >= 0 && b >= 0);
		a %= mod, b %= mod;
		return (a - b + mod) % mod;
	}
	template <typename T, typename C> 
	T mul(T a, C b)
	{
		assert(a >= 0 && b >= 0);
		a %= mod, b %= mod;
		return (a * b) % mod;
	}
	template <typename T, typename C> 
	T pw(T a, C b)
	{
		T r = 1;
		a %= mod;
		while(b){
			if(b&1)r = mul(r, a);
			a = mul(a,a);
			b >>= 1;
		}
		return r;
	}
	template <typename T> 
	T inv(T a)
	{
		return pw(a, mod - 2);
	}
	template <typename T, typename C> 
	T div(T a, C b)
	{
		return mul(a, inv(b));
	}
	template <typename T, typename F> 
	T C(T n, F k){
		if(n < k){
			return 0;
		}
		if(!k)return 1;
		T dv = mul(fact[k], fact[n - k]);
		dv = inv(dv);
		return mul(fact[n], dv);
	}
	template <typename T, typename C>
	T gcd(T a, C b)
	{
		return __gcd(a,b);
	}
	template <typename T>
	T lcm(T a, T b)
	{
		return ((a * b) / gcd(a,b));
	}
	template <typename T>
	T extended_euclidean(T a,T b,T &x,T &y)
	{
		if(b == 0){
			x = 1,y = 0;
			return a;
		}
		T x1, y1;
		T d = extended_euclidean(b, a % b, x1, y1);
		x = y1;
		y = x1 - y1 * (a / b);
		return d;
	}
	template <typename T> 
	T modular_inverse(T a, T m)
	{
		T x, y;
		T g = extended_euclidean(a, m, x , y);
		if(g != 1)return -1;

		x = (x % m + m) % m;
		return x;
	}
	bool is_prime(ll n)
	{
		if(n <= 1)return false;
		if(n <= 3)return true;
		if(n % 2 == 0 || n % 3 == 0)return false;
		for(ll i = 5;i * i <= n;i += 6){
			if(n % i == 0 || n % (i + 2) == 0)return false;
		}
		return true;
	}

	void sieve(int n)
	{
		lp.assign(n + 4, 0);

		for(int i = 2;i <= n;i++)
		{
			if(lp[i] == 0)
			{
				lp[i] = i;
				primes.pb(i);
			}

			for(int pr: primes)
			{
				if(pr > lp[i] || 1LL * i * pr > n)break;
				lp[i * pr] = pr;
			}
		}
	}
	template <typename T> 
	vector<T> prime_factorisationv(T n)
	{
		vector<T> v;
		while(n % 2 == 0)
		{
			v.pb(2);
			n /= 2;
		}
		for(T i = 3;i * i <= n;i += 2)
		{
			while(n % i == 0){
				v.pb(i);
				n /= i;
			}
		}
		if(n > 1)v.pb(n);
		return v;
	}

	template <typename T> 
	vector<T> prime_factorisationv(T n, bool c)
	{
		vector<T> v;
		while(n > 1)
		{
			T x = lp[n];
			while(n % x == 0){
				v.pb(x);
				n /= x;
			}
		}
		return v;
	}

	template <typename T> 
	map<T,int> prime_factorisationm(T n)
	{
		map<T,int> m;

		while(n % 2 == 0)
		{
			m[2]++;
			n /= 2;
		}

		for(T i = 3;i * i <= n;i += 2)
		{
			while(n % i == 0){
				m[i]++;
				n /= i;
			}
		}
		if(n > 1)m[n]++;
		return m;
	}

	template <typename T> 
	map<T,int> prime_factorisationm(T n, bool c)
	{
		map<T,int> m;
		while(n > 1)
		{
			T x = lp[n];
			while(n % x == 0)
			{
				m[x]++;
				n /= x;
			}
		}
		return m;
	}
	template <typename T> 
	vector<pair<T,int>> prime_factorisationpv(T n)
	{
		vector<pair<T,int>> v;
		for(T i = 2;i * i <= n;i++)
		{
			if(n % i == 0)
			{
				int c = 0;
				while(n % i == 0){
					++c;
					n /= c;
				}
				v.pb({i,c});
			}
		}
		return v;
	}

	template <typename T> 
	vector<pair<T,int>> prime_factorisationm(T n, bool c)
	{
		vector<pair<T,int>> v;
		while(n > 1)
		{
			T x = lp[n];
			int cnt = 0;
			while(n % x == 0)
			{
				cnt++;
				n /= x;
			}
			v.pb({x,cnt});
		}
		return v;
	}

	template <typename T> 
	vector<T> divs(T n)
	{
		vector<T> v;
		for(T i = 1;i * i <= n;i++)
		{
			if(n % i == 0)
			{
				v.pb(i);
				if(n / i != i){
					v.pb(n / i);
				}
			}
		}
		return v;
	}
	template <typename T> 
	vector<T> divs_inc(T n)
	{
		vector<T> v;
		for(T i = 1;i * i <= n;i++)
		{
			if(n % i == 0)
			{
				v.pb(i);
				if(n / i != i){
					v.pb(n / i);
				}
			}
		}
		sort(all(v));
		return v;
	}

	template <typename T>
	T PHI(T n)
	{
		T ret = n;

		for(T i = 2;i * i <= n;i++)
		{
			if(n % i == 0)
			{
				while(n % i == 0){
					n /= i;
				}
				ret -= ret / i;
			}
		}
		if(n > 1)ret -= ret / n;
		return ret;
	}

	template <typename T>
	void compute_fact(T n)
	{
		fact.resize(n + 1);
		fact[0] = fact[1] = 1;

		for(int i = 2;i <= n;i++)
			fact[i] = mul(fact[i-1],i);
	}

	template <typename T>
	void compute_phis(T n)
	{
		phis.resize(n + 2);
		phis[0] = 0, phis[1] = 1;

		for(int i = 2;i <= n;i++)
			phis[i] = i;

		for(int i = 2;i <= n;i++)
		{
			if(phis[i] == i)
			{
				for(int j = i;j <= n;j += i)
				{
					phis[j] -= phis[j] / i;
				}
			}
		}
	}
	template <typename T>
	void compute_fibs(T n)
	{
		fib.resize(n);
		fib[0] = 0, fib[1] = 1;
		for(int i = 2;i < n;i++)
			fib[i] = fib[i - 1] + fib[i - 2];
	}
	template <typename T>
	void compute_fibs(T n,T m)
	{
		fib.resize(n);
		fib[0] = 0, fib[1] = 1;
		for(int i = 2;i < n;i++){
			fib[i] = (fib[i-1] + fib[i-2]) % mod;
		}
	}

	template <typename A,typename B,typename C,typename D,typename E,typename F>
	bool solve_linear_diophantine(A a,B b,C c,D &x0, E &y0, F &g)
	{
		g = extended_euclidean(abs(a), abs(b), x0,y0);

		if(c % g)return false;

		x0 *= c / g;
		y0 *= c / g;
		if(a < 0)x0 = -x0;
		if(b < 0)y0 = -y0;
		return true;
	}	
}
//dont forget - setmod, compute facts
using namespace number_theory;
