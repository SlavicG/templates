template<typename T, bool zero_indexing>
struct fen_2d{
    vector<vector<T>> fen;
    int n, m;
    fen_2d(int N, int M){
        n = N, m = M;
        fen.assign(n + 1, vector<int>(m + 1 , 0));
    }
 
    void modif(int x, int y, int val){
        if(zero_indexing)++x, ++y;
        for(int i = x;i <= n; i += i & -i){
            for(int j = y;j <= m; j += j & -j){
                fen[i][j] += val;
            }
        }
    }
 
    T query(int x, int y)
    {
        if(zero_indexing)++x, ++y;
        T ret = 0;
        for(int i = x; i >= 1;i -= i & -i){
            for(int j = y;j >= 1;j -= j & -j){
                ret += fen[i][j];
            }
        }
        return ret;
    }
 
    T query(int x1, int y1, int x2, int y2)
    {
        T ans = query(x2,y2)-query(x2,y1-1)-query(x1-1,y2)+query(x1-1,y1-1);
        return ans;
    }
};
