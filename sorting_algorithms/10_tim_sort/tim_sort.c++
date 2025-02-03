#include <bits/stdc++.h>
using namespace std;

const int RUN = 32;

// Função para ordenar um subarray de tamanho no máximo RUN usando Insertion Sort
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Função para mesclar dois subarrays ordenados
void merge(int arr[], int left, int mid, int right) {
    int len1 = mid - left + 1, len2 = right - mid;
    int leftArr[len1], rightArr[len2];

    // Copia os elementos para os subarrays temporários
    for (int i = 0; i < len1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < len2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    // Mescla os subarrays ordenados de volta no array principal
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes do subarray esquerdo, se houver
    while (i < len1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copia os elementos restantes do subarray direito, se houver
    while (j < len2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Função iterativa do TimSort para ordenar o array
void timSort(int arr[], int n) {
    // Ordena os subarrays individuais de tamanho RUN
    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, min((i + RUN - 1), (n - 1)));

    // Mescla os subarrays de tamanho RUN em tamanhos maiores (64, 128, 256, etc.)
    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            // Mescla os subarrays apenas se houver elementos suficientes
            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}

// Função auxiliar para imprimir um array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Programa principal
int main() {
    int arr[] = {-2, 7, 15, -14, 0, 15, 0, 7, -7, -4, -13, 5, 8, -14, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    printArray(arr, n);

    // Chamada da função de ordenação
    timSort(arr, n);

    printf("Array ordenado:\n");
    printArray(arr, n);

    return 0;
}
