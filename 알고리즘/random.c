#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 600

//�������� ���� ����
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t)) // SWAP�Լ� ����
int original[MAX_SIZE];                                 //�����Լ��� ���� �����͸� ������ ���� �迭
int list[MAX_SIZE];                                     //�� ���� �˰��򿡼� ����� ������ �迭
int n;                                                  //�������� ������ �޴� �������� ����
clock_t start, finish, used_time = 0;
//���� �ð� ������ ���� ����
void Heap_Sort(int[], int);
void Build_Max_Heap(int[], int);
void Max_Heapify(int[], int, int);

void Heap_Sort(int list[], int n)
{

    int *temp;
    int i;
    printf("�� ���� ��... ");
    Build_Max_Heap(list, n); // ���� ���� �����.
    for (i = n - 1; i >= 0; i--)
    {
        SWAP(list[0], list[i], temp); // �θ���� ������ ���� SWAP
        n--;                          // �θ��带 ����.
        Max_Heapify(list, 0, n);      // �� ���� �ǽ�.
    }
}

// Build_Max_Heap �Լ�
void Build_Max_Heap(int list[], int length)
{

    int parent_position;

    // ���� ��带 ������ �� ������ ������ ����.
    // �迭�� 0���� �����ϹǷ� length/2�� -1�� �������.
    for (parent_position = length / 2 - 1; parent_position >= 0; parent_position--)
    {
        Max_Heapify(list, parent_position, length); // �� ���� �ǽ�.
    }
}

// Max_heapify �Լ�
void Max_Heapify(int list[], int parent_position, int heap_size)
{

    int *temp;
    int left, right, largest;

    left = 2 * parent_position + 1;
    right = 2 * parent_position + 2;

    if ((left < heap_size) && (list[left] > list[parent_position])) // ���� �ڽ� ���� �θ��� ��.
        largest = left;
    else
        largest = parent_position;

    if ((right < heap_size) && (list[right] > list[largest])) // ������ �ڽĳ��� ������ ���� ���� ū ��� ���� ��.
        largest = right;

    if (largest != parent_position)
    {
        SWAP(list[parent_position], list[largest], temp); // ���� ū ��带 �θ���� SWAP.
        Max_Heapify(list, largest, heap_size);            // �ٽ� �θ��带 ������� Heapify�� �ǽ�.
    }
}

//������
int partition(int list[], int left, int right)
{
    int pivot = list[left], tmp, low = left, high = right + 1;

    do
    {
        do
            low++;
        while (low <= right && list[low] < pivot);

        do
            high--;
        while (high >= left && list[high] > pivot);
        if (low < high)
            SWAP(list[low], list[high], tmp);
    } while (low < high);

    SWAP(list[left], list[high], tmp);
    return high;
}
void quick_sort(int list[], int left, int right)
{
    if (left < right)
    {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}

//���� ����
void bubble_sort(int list[], int n)
{
    int i, j, tmp;
    printf("���� ���� ��... ");
    for (i = n - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
            if (list[j] > list[j + 1])
                SWAP(list[j], list[j + 1], tmp);
    }
}

//���� ����
void selection_sort(int list[], int n)
{
    int i, j, least, tmp;

    printf("���� ���� ��... ");
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[least])
                least = j;
        SWAP(list[i], list[least], tmp);
    }
}

//���� ����
void insertion_sort(int list[], int n)
{
    int i, j, key;
    printf("���� ���� ��... ");
    for (i = 1; i < n; i++)
    {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; j--)
            list[j + 1] = list[j];
        list[j + 1] = key;
    }
}
void inc_insertion_sort(int list[], int first, int last, int gap)
{
    int i, j, key;
    for (i = first + gap; i <= last; i = i + gap)
    {
        key = list[i];
        for (j = i - gap; j >= first && key < list[j]; j = j - gap)
            list[j + gap] = list[j];
        list[j + gap] = key;
    }
}
void shell_sort(int list[], int n)
{
    int i, gap;
    printf("�� ���� ��... ");
    for (gap = n / 2; gap > 0; gap = gap / 2)
    {
        if ((gap % 2) == 0)
            gap++;
        for (i = 0; i < gap; i++)
            inc_insertion_sort(list, i, n - 1, gap);
    }
}

//���� �迭�� �����ϴ� �Լ�
void CopyArr(void)
{
    int i;
    for (i = 0; i < n; i++)
        list[i] = original[i];
}

//���� �ð��� ���� �� ����ϴ� �Լ�
void CalcTime(void)
{
    used_time = finish - start;
    printf("�Ϸ�!\n�ҿ� �ð� : %f sec\n\n", (float)used_time / CLOCKS_PER_SEC);
}

void main()
{
    int i;

    n = MAX_SIZE;
    for (i = 0; i < n; i++)
        original[i] = rand();

    printf("�������� ���� : %d\n\n", n);

    CopyArr();
    start = clock();
    selection_sort(list, n);
    finish = clock();
    CalcTime();

    CopyArr();
    start = clock();
    insertion_sort(list, n);
    finish = clock();
    CalcTime();

    CopyArr();
    start = clock();
    bubble_sort(list, n);
    finish = clock();
    CalcTime();

    CopyArr();
    start = clock();
    shell_sort(list, n);
    finish = clock();
    CalcTime();

    CopyArr();
    start = clock();
    printf("�� ���� ��... ");
    quick_sort(list, 0, n);
    finish = clock();
    CalcTime();


    CopyArr();
    start = clock();
    Heap_Sort(list, n);
    finish = clock();
    CalcTime();

}