#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct IndexAndSum
{
    int left;
    int right;
    int sum;
}IndexAndSum;

IndexAndSum FindMaxCrossSubarray(int *a, int left, int middle, int right) {
    assert(a != NULL);
    IndexAndSum result;
    memset(&result, 0, sizeof(result));

    int left_sum = a[middle];
    int left_max_sum = left_sum;
    int i = middle - 1;
    while (i >= left) {
        left_sum += a[i];
        if (left_sum > left_max_sum) {
            left_max_sum = left_sum;
            result.left = i;
        }
        --i;
    }

    int right_sum = a[middle+1];
    int right_max_sum = right_sum;
    i = middle + 2;
    while (i <= right) {
        right_sum += a[i];
        if (right_sum > right_max_sum) {
            right_max_sum = right_sum;
            result.right = i;
        }
        ++i;
    }

    result.sum = left_sum + right_sum;
    return result;
}

//分治法找出数组最大子数组和
IndexAndSum FindMaxSubarray(int *a, int left, int right) {
    IndexAndSum result;
    memset(&result, 0, sizeof(result));
    if (left == right) {
        result.left = left;
        result.right = right;
        result.sum = a[left];
    } else {
        int middle = (left + right)/2;
        IndexAndSum left_result = FindMaxSubarray(a, left, middle);
        IndexAndSum right_result = FindMaxSubarray(a, middle+1, right);
        IndexAndSum cross_result = FindMaxCrossSubarray(a, left, middle, right);

        if (left_result.sum > right_result.sum && left_result.sum > cross_result.sum) {
            result = left_result;
        } else if (right_result.sum > left_result.sum && right_result.sum > cross_result.sum) {
            result = right_result;
        } else {
            result = cross_result;
        }
    }
    return result;
}

//线性时间内找出数组最大子数组和
IndexAndSum FindMaxSubarrayLine(int *a, int left, int right) {
    IndexAndSum r;
    memset(&r, 0, sizeof(r));
    if (a == NULL)
      return r;

    int sum = a[left];
    r.sum = sum;
    r.left = left;
    r.right = left;
    int tmp_index = left;

    int i;
    for (i = left + 1; i <= right; ++i) {
        sum += a[i];
        if (r.sum < sum) {
            r.sum = sum;
            r.left = tmp_index;
            r.right = i;
        }
        else if (sum < 0) {
            sum = 0;
            tmp_index = i+1;
        }
    }
    return r;
}

//求第i个最大或最小元素  ---begin---
//分治法期望为O(n) 最坏O(n*n)

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//已数组末元素为key划分数组
int RandomPartition(int *a, int left, int right) {
    int key = a[right];
    int i = left -1 ;
    int j;
    for (j = left; j < right; ++j) {
        if (a[j] >= key) {
            ++i;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i+1], &a[right]);
    int k;
    for (k = 0; k < 10; ++k) {
        printf("%d,", a[k]);
    }
    printf("---key:%d\n", key);
    return i+1;
}

int RandomSelect(int *a, int left, int right, int i) {
    if (left == right) {
        return left;
    }

    int q = RandomPartition(a, left, right);
    int k = q - left + 1;
    if (k == i) {
        return q;
    } else if (k < i) {
        return  RandomSelect(a, q+1, right, i-k);
    } else {
        return RandomSelect(a, left, q-1, i);
    }
}
//                       ---end---

int main(int argc, char *argv[]) {
    int a[] = {-1, 10, -13, 4, -5, 6, -7, -8, -9, 0};
    //IndexAndSum result = FindMaxSubarray(a, 0, sizeof(a)/sizeof(a[0])-1);
    //IndexAndSum result = FindMaxSubarrayLine(a, 0, sizeof(a)/sizeof(a[0])-1);
    //printf("left:%d, right:%d, sum:%d\n", result.left, result.right, result.sum);
    int i;
    for (i = 0; i < sizeof(a)/sizeof(a[0]); ++i) {
        printf("%d, ", a[i]);
    }
    printf("--\n");
    int ret = RandomSelect(a, 0, sizeof(a)/sizeof(a[0])-10, 5);
    for (i = 0; i < sizeof(a)/sizeof(a[0]); ++i) {
        printf("%d, ", a[i]);
    }
    printf("--\n");
    printf("index:%d, value:%d\n", ret, a[ret]);

    return 0;
}
