# ���� �˰��� ���� �м� with C

201901730 �㵿��

## ����

- ����
- �˰��� �ڵ�
- �˰��� ����ð� ���
- �˰��� ���� �м�(�׷���)
- ���
- log��(����ð�) �׷��� �м� �� ���

## ����

�����ð��� ��� ���ľ˰��� ���� ���� �м��� �����Ͽ���.

��������, ��������, ��������, ������, ������, �������� ������� �����Ͽ���.

�Է� ������ ���� ���ϰ� �̿� ���� ���� �˰��� ���� �ð��� �����ߴ�.

�׷����� ��Ÿ���� �˰��� ���� �м��� �ǽ��ߴ�.

�׷����� ����ð��� ���� ����� ����� ���̴�.

c���� ����������, _c���� ���� Ǯ� �ڷᱸ��_ ���縦 �����ߴ�.

## �˰��� �ڵ�

- �⺻ �������, SWAP, �迭 ����, �ð� ���� ���� ���� ����, �� ���� ������� ����

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 256

//�������� ���� ����
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t)) // SWAP�Լ� ����
int original[MAX_SIZE];                                 //�����Լ��� ���� �����͸� ������ ���� �迭
int list[MAX_SIZE];                                     //�� ���� �˰��򿡼� ����� ������ �迭
int n;                                                  //�������� ������ �޴� �������� ����
int arrry[MAX_SIZE];

clock_t start, finish, used_time = 0;
//���� �ð� ������ ���� ����
void Heap_Sort(int[], int);
void Build_Max_Heap(int[], int);
void Max_Heapify(int[], int, int);
```

<br/>

- ��������

```c
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
```

<br/>

- ��������

```c
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
```

<br/>

- ��������

```c
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
```

<br/>

- ������

```c
void shell_sort(int arry[], int n)
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
```

<br/>

- ������

```c
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
```

<br/>

- ������

```c
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
```

<br/> 
 
- ����ð��� ���� �� ����
```c
void CalcTime(void)
{
    used_time = finish - start;
    printf("�Ϸ�!\n�ҿ� �ð� : %f sec\n\n", (float)used_time / CLOCKS_PER_SEC);
}
```

<br/>

- ���� �迭�� �����ϴ� �Լ�

```c
void CopyArr(void)
{
    int i;
    for (i = 0; i < n; i++)
        list[i] = original[i];
}
```

<br/>

- ���ĵ� �����͸� ����� �Լ�

```c
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
```

<br/>

- �� ���� �����͸� ����� �Լ�

```c
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
```

<br/>

- ���� �������� ��� main �Լ�

```c
void main()
{
    int i;

    n = MAX_SIZE;
    for (i = 0; i < n; i++)
        original[i] = rand(); // ���� �� �迭

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
```

<br/>

- ���� �������ΰ�� main �Լ�(�Ϻ� ����)

```c
void main()
{
    int i;

    n = MAX_SIZE;
    for (i = 0; i < n; i++)
        original[i] = rand();

    printf("�������� ���� : %d\n\n", n);

    CopyArr(); // ���ĵ� �����͸� ����� ���� �������� ���
    printf(" ���� ��...... ");
    printf(" �Ϸ�! \n");
    printf("\n");
    quick_sort1(list, 0, n);

    printf("------- ���ĵ� ��� -------\n");
    printf("\n");

    sortedarry(); // ���ĵ� ������ arrry�迭
    start = clock();
    selection_sort(arrry, n);
    finish = clock();
    CalcTime();
    ...
}
```

<br/>

- �� ���� �������� ��� main �Լ�(�Ϻ� ����)

```c
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
    reverseArray(arrry, n); // ���ĵ� �����͸� �� ����
    start = clock();
    selection_sort(arrry, n);
    finish = clock();
    CalcTime();
    ...
}
```

## �˰��� ����ð� ���

- �Է� ������ �� [2, 4, 8, 16, 32, ..., 1048576] (������ 32���Ϳ�����, Ȯ���� 2���� ������)

- �ð��� ��հ����� ����Ϸ� ����ߴ�. (�뷫 10���� ����)

- ���� �������� ���
<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/exel_arrangement/random.png?raw=true" height="651px" width="777px"></p>

<br/>

- ���� �������� ���
<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/exel_arrangement/sorted.png?raw=true" height="651px" width="777px"></p>
<br/>

- �� ���� �������� ���
<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/exel_arrangement/reverse.png?raw=true" height="651px" width="777px"></p>
<br/>

## �˰��� �м�

### �׷���

### ���� �������� ���

<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/graph/ramdom_case.png?raw=true" height="450px" width="800px"></p>
<br/>

- BEST ���� : ������
<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/graph/random_best_quick.png?raw=true" height="450px" width="800px"></p>
<br/>

- WORST ���� : ��������
<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/graph/random_worst_bubble.png?raw=true" height="450px" width="800px"></p>
<br/>

### ���� �������� ���

<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/graph/sorted_case.png?raw=true" height="450px" width="800px"></p>
<br/>

- BEST ���� : ��������
<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/graph/sorted_best_insert.png?raw=true" height="450px" width="800px"></p>
<br/>

- WORST ���� : ��������
<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/graph/sorted_worst_bubble.png?raw=true" height="450px" width="800px"></p>
<br/>

### �� ���� �������� ���

<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/graph/reverse_case.png?raw=true" height="500px" width="895px"></p>
<br/>

- BEST ���� : ��������
<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/graph/reverse_best_insert.png?raw=true" height="492px" width="895px"></p>
<br/>

- WORST ���� : ��������
<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/graph/reverse_worst_bubble.png?raw=true" height="492px" width="895px"></p>
<br/>

## ���

- **���� �������� ��쿡�� ������ �˰����� ����ð��� ���� ª�Ұ�, ���� ������ ���� ����ð��� ���� �����.**

- **���� �������� ��쿡�� �������� �˰����� ����ð��� ���� ª�Ұ�, ���� ������ ���� ����ð��� ���� �����.**

  �������� �˰��� Ư���� ���ĵ� �����Ϳ����� ����ð��� ª�Ұ�, ���������� ���Ŀ��ο� ������� ������ �� ���Ҹ� ���ϹǷ� ����ð��� ���� �����.

- **�� ���� �������� ��쿡�� �������� �˰����� ����ð��� ���� ª�Ұ� ���� ������ ���� ����ð��� ���� �����.**

  ���������� ���ĵǾ� �����Ƿ� �������� �˰����� ���� ����ð��� ª������, ���������� ���Ŀ��ο� ������� ������ �� ���Ҹ� ���ϹǷ� ����ð��� ���� �����.

## �� ���� �˰����� �ð����⵵

<br/>

> 1.  �������� : O(n��)

> 2.  �������� : O(n��)

> 3.  �������� : O(n��)

> 4.  �� ���� : O(n^1.5)

> 5.  �� ���� : O(nlog��n)

> 6.  ������ : O(nlog��n)

<br/>

## ��������, ��������, ��������

- �ð����⵵�� O(n��)�̹Ƿ� ����ð��� log���� ���� ����� ����ϰ�, �׷����� ����� ���Ҵ�.

> ���� ���������� ��Ÿ����?

<br/>

- ���� �������� ���
<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/log2/random_log2.png?raw=true" height="416px" width="954px"></p>

> ���������� ��Ÿ����!
> <br/>

- ���ĵ� �������� ���
<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/log2/sorted_log2.png?raw=true" height="416px" width="954px"></p>

> ��������, ���������� ���������� ��Ÿ����!

> ���������� �����;��� ���� ��쿡�� �������̴ٰ� ���� ������ ����� ���.
> <br/>

- �� ���ĵ� �������� ���
<p align="center"><img src="https://github.com/donggyunhuh/Sort_Time/blob/master/log2/reverse_log2.png?raw=true" height="416px" width="954px"></p>

> ��������, ���������� ���������� ��Ÿ����!

> ���������� �����;��� ���� ��쿡�� �������̴ٰ� ���� ������ ����� ���.
> <br/>

### ���

- **����ð��� log���� ���� ����� ��Ÿ����, �׷����� ����� ��������, �ð����⵵�� O(n��)�̹Ƿ� �׷����� ������ ����� ���!**
