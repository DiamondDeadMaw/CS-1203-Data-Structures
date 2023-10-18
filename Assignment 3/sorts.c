#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// TIME COMPLEXITY ANALYSIS AND COMPARISONS UPLOADED ON CLASSROOM


void printArray(int arr[], int size) {
    for (int i = 0; i< size; i++) {
        printf("%d", arr[i]);
        if (i < size-1) {
            printf(", ");
        }
    }
    printf("\n");
}

//insertion sort
void insertionSort(int arr[] , int size) {
    int j = 0;
    int key = 0;

    for (int i = 0; i < size; i++ ) {
        key = arr[i];
        j = i-1;

        while (j >=0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j + 1] = key; 
    }
}

// merge sort 

// takes lower index, middle index, upper index
void merge(int arr[], int l, int m, int u) {
    int n1 = m-l + 1;
    int n2 = u - m;

    int L[n1], R[n2];

    for (int i = 0; i<n1; i++) {
        L[i] = arr[l + i];
    }

    for (int i = 0; i < n2; i++) {
        R[i] = arr[m + i + 1];
    }

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while ( i< n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }


}

void mergeSort(int arr[], int l , int u) {
    if (l < u) {
        int m = l + (u-l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, u);

        merge(arr, l, m, u);
    }
}


// quick sort

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];

    int i = low-1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        quickSort(arr, low, pivotIndex-1);
        quickSort(arr, pivotIndex+1, high); 
    }
}
void bubbleSort(int arr[], int size) {
    for (int i = 0; i< size-1; i++) {
        for (int j = 0; j < size - i - 1; j++ ) {
                if (arr[j] > arr[j+1]) {
                    swap(&arr[j], &arr[j+1]);
                }
        }
    }
}

void runTests(int size) {

    printf("Generating a random array of size ");
    printf("%d \n", size);

    srand(time(NULL));

    int *arr = (int*)malloc(size * sizeof(int));
    int *arr1 = (int*)malloc(size * sizeof(int));
    int *arr2 = (int*)malloc(size * sizeof(int));
    int *arr3 = (int*)malloc(size * sizeof(int));
    int *arr4 = (int*) malloc(size * sizeof(int));

    for (int i = 0; i<size;i++) {
        arr[i] = rand();
        arr1[i] = arr[i];
        arr2[i] = arr[i];
        arr3[i] = arr[i];
        arr4[i] = arr[i];
    }

    printf("Array generated \n");

        printf("Time taken by insertion sort: ");
    clock_t start = clock();
    insertionSort(arr1, size);
    clock_t end = clock();

    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f \n", elapsed_time);

    printf("Time taken by bubble sort: ");
    start = clock();
    bubbleSort(arr4, size-1);
    end = clock();

    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f \n", elapsed_time);

    printf("Time taken by merge sort: ");
    start = clock();
    mergeSort(arr2, 0, size-1);
    end = clock();

    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f \n", elapsed_time);


    printf("Time taken by quick sort: ");
    start = clock();
    quickSort(arr3, 0, size-1);
    end = clock();

    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f \n", elapsed_time);

    


    free(arr);
    free(arr1);
    free(arr2);
    free(arr3);
}



int main() {


    runTests(10000);
    runTests(100000);
    


    return 0;
}