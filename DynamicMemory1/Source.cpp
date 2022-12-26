#include<iostream>
using namespace std;

#define tab "\t"

#define delimeter "\n------------------------------------\n"

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void Print(int* arr, const int n);

int* insert(int* arr, int& n, int value, int index);
int* pop_back(int* arr, int& n);
int* pop_front(int* arr, int& n);
int* erase(int* arr, int& n, int index);

void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите количество элементов: "; cin >> n;
	int* arr = new int[n];

	FillRand(arr, n);
	Print(arr, n);

	int value;
	cout << "Введите добавляемое значение: "; cin >> value;
	int index;
	cout << "Введите индекс добавляемого значения: "; cin >> index;
	arr = insert(arr, n, value, index);
	Print(arr, n);

	cout << delimeter << endl;
	arr = pop_back(arr, n);
	Print(arr, n);

	cout << delimeter << endl;
	arr = pop_front(arr, n);
	Print(arr, n);

	cout << delimeter << endl;
	cout << "Введите индекс исключаемого значения: "; cin >> index;
	arr = erase(arr, n, index);
	Print(arr, n);

	delete[] arr;
}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	cout << typeid(arr).name() << endl;
	for (int i = 0; i < n; i++)
	{
		//через арифметику указателей и оператор разыменования
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
	}
}

void Print(int arr[], const int n)
{
	cout << typeid(arr).name() << endl;
	for (int i = 0; i < n; i++)
	{
		//через оператор индексирования
		//[] - оператор индексирования (subscript operator)
		cout << arr[i] << tab;
	}
	cout << endl;
}

int* insert(int* arr, int& n, int value, int index)
{
	int* buffer = new int[n + 1];
	for (int i = 0; i < index; i++)buffer[i] = arr[i];
	for (int i = index; i<n; i++)buffer[i + 1] = arr[i];
	buffer[index] = value;
	delete[] arr;
	arr = buffer;
	n++;
	return arr;
}

int* pop_back(int* arr, int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}

int* pop_front(int* arr, int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

int* erase(int* arr, int& n, int index)
{
	int* buffer = new int[--n];
	for (int i = 0; i < index; i++)buffer[i] = arr[i];
	for (int i = index; i < n; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	arr = buffer;
	return arr;
}
