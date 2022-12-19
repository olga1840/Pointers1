#include<iostream>
using namespace std;
#define tab "\t"

void FillRand(int arr[], const int n);
void Print(int* rr, const int n);

int* push_back(int* arr, int& n, int value);
int* push_front(int* arr, int& n, int value);


void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "¬ведите количество элементов: "; cin >> n;
	int* arr = new int[n];
	
	FillRand(arr, n);
	Print(arr, n);

	int value;
	cout << "¬ведите добавл€емое значение: "; cin >> value;
	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "¬ведите добавл€емое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);


	delete[] arr;
	//Memory leak
}

void FillRand(int arr[], const int n)
{
	cout << typeid(arr).name() << endl;
	for (int i = 0; i < n; i++)
	{
		//через арифметику указателей и оператор разыменовани€
		*(arr + i) = rand() % 100;
	}
}

void Print(int arr[], const int n)
{
	cout << typeid(arr).name() << endl;
	for (int i = 0; i < n; i++)
	{
		//через оператор индексировани€
		//[] - оператор индексировани€ (subscript operator)
		cout << arr[i] << tab;
	}
	cout << endl;
}

int* push_back(int* arr, int& n, int value)
{
	//1) создаем новый массив нужного размера:
	int* buffer = new int[n + 1];
	//2) копируем все содержимое исходного массива в буферный:
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//3) удал€ем исходный массив:
	delete[] arr;
	//4) подмен€ем адрес в указателе 'arr' адресом нового массива:
	arr = buffer;
	//5) только после всего этого в конец массива 'arr' можно добавить значение value
	arr[n] = value;
	//6) после добавлени€ в массив 'arr' элемента, количество его элементов увеличиваетс€
	n++;
	//7) mission complete - элемент добавлен!
	return arr;
}

int* push_front(int* arr, int& n, int value)
{
	int* buffer = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;
	arr = buffer;
	arr[0] = value;
	n++;
	return arr;
}
