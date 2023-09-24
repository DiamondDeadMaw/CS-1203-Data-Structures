#include <stdio.h>
#include <stdbool.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int arr[], int start, int end) {
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

void generatePermutations(int n) {
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    int count = 0;
    while (true) {
        printf("%d", ++count);
        printf(":");
        for (int i = 0; i < n; i++) {
            printf("%d", arr[i]);
            if (i < n - 1) {
                printf(",");
            }
        }
        printf("\n");

        int k = -1;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] < arr[i + 1]) {
                k = i;
            }
        }

        if (k == -1) {
            break;
        }

        int l = -1;
        for (int i = k + 1; i < n; i++) {
            if (arr[k] < arr[i]) {
                l = i;
            }
        }

        swap(&arr[k], &arr[l]);

        reverse(arr, k + 1, n - 1);
    }
}

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    generatePermutations(n);

    return 0;
}
