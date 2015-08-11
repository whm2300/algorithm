#include <stdio.h>

void merge(int a[], int first, int mid, int end, int tmp[]) {
    int i = first;
    int j = mid + 1;
    int k = first;

    while (i < mid + 1 && j < end + 1) {
        if (a[i] > a[j]) {
            tmp[k++] = a[j++];
        } else {
            tmp[k++] = a[i++];
        }
    }

    while (i < mid + 1) {
        tmp[k++] = a[i++];
    }
    while (j < end + 1) {
        tmp[k++] = a[j++];
    }
    for (i = first; i < end + 1; ++i) {
        a[i] = tmp[i];
    }
}

//归并排序
void merge_sort(int a[], int first, int end, int tmp[]) {
    if (first < end) {
        int mid = (first + end)/2;
        merge_sort(a, first, mid, tmp);
        merge_sort(a, mid+1, end, tmp);
        merge(a, first, mid, end, tmp);
    }
}

int main(int argc, char *argv[]) {
    int a[] = {9, 1, 8, 2, 7, 9, 9, 3, 6, 4, 5, 5, 5, 5, 1};
    int b[100];
    merge_sort(a, 0, sizeof(a)/sizeof(a[0]) -1, b);
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); ++i) {
        printf("%d\n", a[i]);
    }
}
