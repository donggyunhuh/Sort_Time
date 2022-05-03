#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 256

//데이터의 개수 지정
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t)) // SWAP함수 설정
int original[MAX_SIZE];                                 //랜덤함수로 만든 데이터를 저장할 원본 배열
int list[MAX_SIZE];                                     //각 정렬 알고리즘에서 사용할 데이터 배열
int n;                                                  //데이터의 개수를 받는 전역변수 설정
int arrry[MAX_SIZE];

clock_t start, finish, used_time = 0;
//실행 시간 측정을 위한 변수
void Heap_Sort(int[], int);
void Build_Max_Heap(int[], int);
void Max_Heapify(int[], int, int);

void Heap_Sort(int arrry[], int n)
{

    int *temp;
    int i;
    printf("힙 정렬 중... ");
    Build_Max_Heap(arrry, n); // 먼저 힙을 만든다.
    for (i = n - 1; i >= 0; i--)
    {
        SWAP(arrry[0], arrry[i], temp); // 부모노드와 마지막 노드와 SWAP
        n--;                            // 부모노드를 삭제.
        Max_Heapify(arrry, 0, n);       // 힙 유지 실시.
    }
}

// Build_Max_Heap 함수
void Build_Max_Heap(int arrry[], int length)
{

    int parent_position;

    // 리프 노드를 제외한 맨 마지막 노드부터 시작.
    // 배열은 0부터 시작하므로 length/2에 -1을 해줘야함.
    for (parent_position = length / 2 - 1; parent_position >= 0; parent_position--)
    {
        Max_Heapify(arrry, parent_position, length); // 힙 유지 실시.
    }
}

// Max_heapify 함수
void Max_Heapify(int arrry[], int parent_position, int heap_size)
{

    int *temp;
    int left, right, largest;

    left = 2 * parent_position + 1;
    right = 2 * parent_position + 2;

    if ((left < heap_size) && (arrry[left] > arrry[parent_position])) // 왼쪽 자식 노드와 부모노드 비교.
        largest = left;
    else
        largest = parent_position;

    if ((right < heap_size) && (arrry[right] > arrry[largest])) // 오른쪽 자식노드와 이전에 얻은 제일 큰 노드 값과 비교.
        largest = right;

    if (largest != parent_position)
    {
        SWAP(arrry[parent_position], arrry[largest], temp); // 값이 큰 노드를 부모노드로 SWAP.
        Max_Heapify(arrry, largest, heap_size);             // 다시 부모노드를 대상으로 Heapify를 실시.
    }
}

//퀵정렬
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

//버블 정렬
void bubble_sort(int arrry[], int n)
{
    int i, j, tmp;
    printf("버블 정렬 중... ");
    for (i = n - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
            if (arrry[j] > arrry[j + 1])
                SWAP(arrry[j], arrry[j + 1], tmp);
    }
}

//선택 정렬
void selection_sort(int arrry[], int n)
{
    int i, j, least, tmp;

    printf("선택 정렬 중... ");
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
            if (arrry[j] < arrry[least])
                least = j;
        SWAP(arrry[i], arrry[least], tmp);
    }
}

//삽입 정렬
void insertion_sort(int arrry[], int n)
{
    int i, j, key;
    printf("삽입 정렬 중... ");
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

//쉘 정렬
void shell_sort(int arrry[], int n)
{
    int i, gap;
    printf("쉘 정렬 중... ");
    for (gap = n / 2; gap > 0; gap = gap / 2)
    {
        if ((gap % 2) == 0)
            gap++;
        for (i = 0; i < gap; i++)
            inc_insertion_sort(arrry, i, n - 1, gap);
    }
}

//정렬 기준값
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

//원본 배열을 복사하는 함수
void CopyArr(void)
{
    int i;
    for (i = 0; i < n; i++)
        list[i] = original[i];
}
// 정렬된 데이터를 만드는 함수
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

//실행 시간을 측정 및 출력하는 함수
void CalcTime(void)
{
    used_time = finish - start;
    printf("완료!\n소요 시간 : %f sec\n\n", (float)used_time / CLOCKS_PER_SEC);
}

void main()
{
    int i;

    n = MAX_SIZE;
    for (i = 0; i < n; i++)
        original[i] = rand();

    printf("데이터의 개수 : %d\n\n", n);

    CopyArr();
    printf(" 정렬 중...... ");
    printf(" 완료! \n");
    printf("\n");
    quick_sort1(list, 0, n);

    printf("------- 정렬된 경우 -------\n");
    printf("\n");

    sortedarry();
    start = clock();
    selection_sort(arrry, n);
    finish = clock();
    CalcTime();

    sortedarry();
    start = clock();
    insertion_sort(arrry, n);
    finish = clock();
    CalcTime();

    CopyArr();
    start = clock();
    bubble_sort(arrry, n);
    finish = clock();
    CalcTime();

    CopyArr();
    start = clock();
    shell_sort(arrry, n);
    finish = clock();
    CalcTime();

    CopyArr();
    start = clock();
    Heap_Sort(arrry, n);
    finish = clock();
    CalcTime();

    CopyArr();
    start = clock();
    printf("퀵 정렬 중... ");
    quick_sort(arrry, 0, n);
    finish = clock();
    CalcTime();
}