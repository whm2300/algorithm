#include <stdio.h>

int max(int a, int b) {
    return a > b ? a: b;
}

//自顶向下递归实现
int CutRod(int *p, int n) {
    if (n == 0) {
        return 0;
    }

    int q = -10000;
    int i;
    for (i = 1; i <= n; ++i) {
        q = max(q, p[i]+CutRod(p, n-i));
    }
    return q;
}

//带备忘录的自顶向下法
int MemoizedCutRodAux(int *p, int n, int *r) {
    if (r[n] >= 0) {
        return r[n];
    }

    int q;
    if (n == 0) {
        q = 0;
    } else {
        q = -1;
        int i;
        for (i = 1; i <= n; ++i) {
            q = max(q, p[i]+MemoizedCutRodAux(p, n-i, r));
        }
    }
    r[n] = q;
    return q;
}
int MemoizedCutRod(int *p, int n) {
    int r[n];
    int i;
    for (i = 0; i <= n; ++i) {
        r[i] = -1000;
    }
    return MemoizedCutRodAux(p, n, r);
}

//自底向上
int BottomUpCutRod(int *p, int n) {
    int r[n];
    int i;
    int j;
    r[0] = 0;
    for (j = 1; j <= n; ++j) {
        int q = -1;
        for (i = 1; i <= j; ++i) {
            q = max(q, p[i]+r[j-i]);
        }
        r[j] = q;
    }
    return r[n];
}

int main(int argc, char *argv[]) {
    int i;
    //int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int p[64];
    for (i = 0; i < 64; ++i) {
        p[i] = 2*i+1;
    }
    for (i = 1; i < 64; ++i) {
        //int ret = CutRod(p, i);
        //int ret = MemoizedCutRod(p, i);
        int ret = BottomUpCutRod(p, i);
        printf("i:%d, r:%d\n", i, ret);
    }
    return 0;
}
