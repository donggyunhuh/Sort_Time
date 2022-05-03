#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 256

//�������� ���� ����
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t)) // SWAP�Լ� ����
int original[MAX_SIZE];                                 //�����Լ��� ���� �����͸� ������ ���� �迭
int list[MAX_SIZE];                                     //�� ���� �˰����򿡼� ����� ������ �迭
int n;                                                  //�������� ������ �޴� �������� ����
int arrry[MAX_SIZE];
clock_t start, finish, used_time = 0;
//���� �ð� ������ ���� ����
void Heap_Sort(int[], int);
void Build_Max_Heap(int[], int);
void Max_Heapify(int[], int, int);

void Heap_Sort(int arrry[], int n)
{

    int *temp;
    int i;
    printf("�� ���� ��... ");
    Build_Max_Heap(arrry, n); // ���� ���� �����.
    for (i = n - 1; i >= 0; i--)
    {
        SWAP(arrry[0], arrry[i], temp); // �θ���� ������ ���� SWAP
        n--;                            // �θ��带 ����.
        Max_Heapify(arrry, 0, n);       // �� ���� �ǽ�.
    }
}

// Build_Max_Heap �Լ�
void Build_Max_Heap(int arrry[], int length)
{

    int parent_position;

    // ���� ��带 ������ �� ������ ������ ����.
    // �迭�� 0���� �����ϹǷ� length/2�� -1�� �������.
    for (parent_position = length / 2 - 1; parent_position >= 0; parent_position--)
    {
        Max_Heapify(arrry, parent_position, length); // �� ���� �ǽ�.
    }
}

// Max_heapify �Լ�
void Max_Heapify(int arrry[], int parent_position, int heap_size)
{

    int *temp;
    int left, right, largest;

    left = 2 * parent_position + 1;
    right = 2 * parent_position + 2;

    if ((left < heap_size) && (arrry[left] > arrry[parent_position])) // ���� �ڽ� ���� �θ��� ��.
        largest = left;
    else
        largest = parent_position;

    if ((right < heap_size) && (arrry[right] > arrry[largest])) // ������ �ڽĳ��� ������ ���� ���� ū ��� ���� ��.
        largest = right;

    if (largest != parent_position)
    {
        SWAP(arrry[parent_position], arrry[largest], temp); // ���� ū ��带 �θ���� SWAP.
        Max_Heapify(arrry, largest, heap_size);             // �ٽ� �θ��带 ������� Heapify�� �ǽ�.
    }
}

//������
int partition(int arrry[], int left, int right)
{
    int pivot = arrry[left], tmp, low = left, high = right + 1;

    do
    {
        do
            low++;
        while (low <= right && arrry[low] < pivot);

        do
            high--;
        while (high >= left && arrry[high] > pivot);
        if (low < high)
            SWAP(arrry[low], arrry[high], tmp);
    } while (low < high);

    SWAP(arrry[left], arrry[high], tmp);
    return high;
}
void quick_sort(int arrry[], int left, int right)
{
    if (left < right)
    {
        int q = partition(arrry, left, right);
        quick_sort(arrry, left, q - 1);
        quick_sort(arrry, q + 1, right);
    }
}

//���� ����
void bubble_sort(int arrry[], int n)
{
    int i, j, tmp;
    printf("���� ���� ��... ");
    for (i = n - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
            if (arrry[j] > arrry[j + 1])
                SWAP(arrry[j], arrry[j + 1], tmp);
    }
}

//���� ����
void selection_sort(int arrry[], int n)
{
    int i, j, least, tmp;

    printf("���� ���� ��... ");
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
            if (arrry[j] < arrry[least])
                least = j;
        SWAP(arrry[i], arrry[least], tmp);
    }
}

//���� ����
void insertion_sort(int arrry[], int n)
{
    int i, j, key;
    printf("���� ���� ��... ");
    for (i = 1; i < n; i++)
    {
        key = arrry[i];
        for (j = i - 1; j >= 0 && arrry[j] > key; j--)
            arrry[j + 1] = arrry[j];
        arrry[j + 1] = key;
    }
}
void inc_insertion_sort(int arrry[], int first, int last, int gap)
{
    int i, j, key;
    for (i = first + gap; i <= last; i = i + gap)
    {
        key = arrry[i];
        for (j = i - gap; j >= first && key < arrry[j]; j = j - gap)
            arrry[j + gap] = arrry[j];
        arrry[j + gap] = key;
    }
}

//�� ����
void shell_sort(int arrry[], int n)
{
    int i, gap;
    printf("�� ���� ��... ");
    for (gap = n / 2; gap > 0; gap = gap / 2)
    {
        if ((gap % 2) == 0)
            gap++;
        for (i = 0; i < gap; i++)
            inc_insertion_sort(arrry, i, n - 1, gap);
    }
}

//���� ���ذ�
int partition1(int list[], int left, int right)
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
void quick_sort1(int list[], int left, int right)
{
    if (left < right)
    {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}

//�� ���� �����͸� ����� �Լ�
void reverseArray(int *arrry, int n)
{
    int temp;

    for (int i = 0; i < n / 2; i++)
    {
        temp = arrry[i];
        arrry[i] = arrry[(n - 1) - i];
        arrry[(n - 1) - i] = temp;
    }
}

//���� �迭�� �����ϴ� �Լ�
void CopyArr(void)
{
    int i;
    for (i = 0; i < n; i++)
        list[i] = original[i];
}
// ���ĵ� �����͸� ����� �Լ�
void sortedarry(void)
{
    int i;
    for (i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            arrry[i] = list[j];
        }
    }
    arrry[i] = list[i];
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
    printf(" ���� ��...... ");
    printf(" �Ϸ�! \n");
    printf("\n");
    quick_sort1(list, 0, n);

    printf("------- �� ���ĵ� ��� -------\n");
    printf("\n");

    sortedarry();
    reverseArray(arrry, n);
    start = clock();
    selection_sort(arrry, n);
    finish = clock();
    CalcTime();

    sortedarry();
    reverseArray(arrry, n);
    start = clock();
    insertion_sort(arrry, n);
    finish = clock();
    CalcTime();

    sortedarry();
    reverseArray(arrry, n);
    start = clock();
    bubble_sort(arrry, n);
    finish = clock();
    CalcTime();

    sortedarry();
    reverseArray(arrry, n);
    start = clock();
    shell_sort(arrry, n);
    finish = clock();
    CalcTime();

    sortedarry();
    reverseArray(arrry, n);
    start = clock();
    Heap_Sort(arrry, n);
    finish = clock();
    CalcTime();

    sortedarry();
    reverseArray(arrry, n);
    start = clock();
    printf("�� ���� ��... ");
    quick_sort(arrry, 0, n);
    finish = clock();
    CalcTime();
}