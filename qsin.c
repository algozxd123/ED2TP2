#include "qsin.h"

void swap(Aluno *a, Aluno *b)
{
    Aluno t = *a;
    *a = *b;
    *b = t;
}

int partition(Aluno arr[], int low, int high)
{
    Aluno pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].nota < pivot.nota)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortInterno(Aluno arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSortInterno(arr, low, pi - 1);
        quickSortInterno(arr, pi + 1, high);
    }
}