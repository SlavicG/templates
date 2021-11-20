template<typename T>
struct SegmentTree2D{
    vector<vector<T>> t, b;
    T neutral;
    int n, m;
    function<T(const T&, const T&)> merge;

    SegmentTree2D(int N, int M, T _neutral, vector<vector<T>> a, const function<T(const T&, const T&)> &_merge){
        n = N, m = M, b = a, merge = _merge, neutral = _neutral;
        t.assign(4 * n, vector<T>(4 * m, neutral));
        build_x(1, 0, n - 1);
    }
    void build_y(int i, int l, int r, int x, int lx, int rx){
        if(l == r){
            if(lx == rx)t[x][i] = b[lx][l];
            else t[x][i] = merge(t[2 * x][i], t[2 * x + 1][i]);
            return;
        }
        int mid = (l + r) / 2;

        build_y(2 * i, l, mid, x, lx, rx);
        build_y(2 * i + 1, mid + 1, r, x, lx, rx);

        t[x][i] = merge(t[x][2 * i], t[x][2 * i + 1]);
    }

    void build_x(int i, int l, int r){
        if(l != r){
            int mid = (l + r) / 2;
            build_x(2 * i, l, mid);
            build_x(2 * i + 1, mid + 1, r);
        }

        build_y(1, 0, m - 1, i, l, r);
    }

    T query_y(int i, int l, int r, int tl, int tr, int x){
        if(l > tr || r < tl)return neutral;
        if(l >= tl && r <= tr)return t[x][i];

        int mid = (l + r) / 2;

        T left = query_y(2 * i, l, mid, tl, tr, x);
        T right = query_y(2 * i + 1, mid + 1, r, tl, tr, x);

        return merge(left, right);
    }

    T query_x(int i, int l, int r, int tl, int tr, int ly, int ry){
        if(l > tr || r < tl)return neutral;
        if(l >= tl && r <= tr)return query_y(1, 0, m - 1, ly, ry, i);

        int mid = (l + r) / 2;
        T left = query_x(2 * i, l, mid, tl, tr, ly, ry);
        T right = query_x(2 * i + 1, mid + 1, r, tl, tr, ly, ry);

        return merge(left, right);
    }

    void modif_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, T val){
        if(lx > x || rx < x || ly > y || ry < y)return;
        if(ly == ry){
            if(lx == rx)t[vx][vy] = val;
            else t[vx][vy] = merge(t[vx * 2][vy], t[vx * 2 + 1][vy]);
            return;
        }

        int mid = (ly + ry) / 2;
        modif_y(vx, lx, rx, 2 * vy, ly, mid, x, y, val);
        modif_y(vx, lx, rx, 2 * vy + 1, mid + 1, ry, x, y, val);

        t[vx][vy] = merge(t[vx][vy * 2], t[vx][vy * 2 + 1]);
    }

    void modif_x(int vx, int lx, int rx, int x, int y, T val){
        if(lx > x || rx < x)return;
        if(lx != rx){
            int mid = (lx + rx) / 2;
            modif_x(vx * 2, lx, mid, x, y, val);
            modif_x(vx * 2 + 1, mid + 1, rx, x, y, val);
        }

        modif_y(vx, lx, rx, 1, 0, m - 1, x, y, val);
    }

    T query(int x1, int y1, int x2, int y2){
        return query_x(1, 0, n - 1, x1, x2, y1, y2);
    }

    void modif(int x, int y, T val){
        modif_x(1, 0, n - 1, x, y, val);
    }

    //n, m, neutral, vector, merge
};
