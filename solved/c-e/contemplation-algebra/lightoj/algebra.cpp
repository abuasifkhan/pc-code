#include <cstdio>
#include <cstring>


#define Zero(v) memset((v), 0, sizeof(v))

const int MAX_ROWS = 2;
const int MAX_COLS = 2;


typedef unsigned long long u64;


template <typename T>
struct Matrix {
    int r, c;
    T m[MAX_ROWS][MAX_COLS];
    T x[MAX_ROWS][MAX_COLS];
    Matrix(int R, int C) : r(R), c(C) {}
    void init(T *v) {
        for (int i = 0, p = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                m[i][j] = v[p++];
    }
    void iden() {
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                m[i][j] = i == j ? 1 : 0;
    }

    Matrix &operator*=(const Matrix &y) {
        Zero(x);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j) {
                T v = 0;
                for (int k = 0; k < c; ++k)
                    v += m[i][k] * y.m[k][j];
                x[i][j] = v;
            }
        memcpy(m, x, sizeof(m)); return *this;
    }
};

template<typename TB, typename TE>
void sq_pow(TB b, TE e, TB &r) {
    for (; e; e >>= 1, b *= b) if (e & 1) r *= b;
}


int p, q, n;

Matrix<u64> A(2, 2);
Matrix<u64> R(2, 2);


u64 solve()
{
    if (n == 0) return 2;
    if (n == 1) return p;

    u64 a[] = { p, -q , 1, 0 };
    A.init(a);

    R.iden();
    sq_pow(A, n - 1, R);

    u64 ans = R.m[0][0] * p + R.m[0][1] * 2;
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d", &p, &q, &n);
        printf("Case %d: %llu\n", ++ncase, solve());
    }

    return 0;
}
