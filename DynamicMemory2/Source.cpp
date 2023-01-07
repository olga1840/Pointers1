#include<iostream>
using namespace std;

#define tab "\t"
#define delimeter "\n------------------------------------\n"

void FillRand(int** arr, const int rows, const int cols);
void Print(int** arr, const int rows, const int cols);
int** push_row_front(int** arr, int& rows, const int cols);
int** insert_row(int** arr, int& rows, const int cols, const int index);

int** pop_row_back(int** arr, int& rows, const int cols);
int** pop_row_front(int** arr, int& rows, const int cols);
int** erase_row(int** arr, int& rows, const int cols, int index);

int** allocate(const int rows, const int cols);
void clear(int** arr, const int rows);


void main()
{
	setlocale(LC_ALL, "");
	int rows; 
	int cols; 
	cout << "¬ведите количество строк: "; cin >> rows;
	cout << "¬ведите количество элементов строки: "; cin >> cols;
	
	int** arr = allocate(rows, cols);

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	cout << delimeter << endl;
	arr = push_row_front(arr, rows, cols);
	Print(arr, rows, cols);

	int index;
	cout << "¬ведите индекс добавл€емой строки: "; cin >> index;
	arr = insert_row(arr, rows, cols, index);
	Print(arr, rows, cols);
	cout << delimeter << endl;

	arr = pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimeter << endl;

	arr = pop_row_front(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimeter << endl;

	cout << "¬ведите индекс удал€емой строки: "; cin >> index;
	arr = erase_row(arr, rows, cols, index);
	Print(arr, rows, cols);

	clear(arr, rows);;
}

int** allocate(const int rows, const int cols)
{
	int** arr = new int * [rows];   //сщздаем массив указателей
	for (int i = 0; i < rows; i++)
	{
		//создаем строки двумерного массива:
		arr[i] = new int[cols];
	}
	return arr;
}

void clear(int** arr, const int rows)
{
	//удал€ем строки двумерного массива
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2) удал€ем массив указателей:
	delete[] arr;
}


void FillRand(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 100;
		}
	}
}

void Print(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << tab;
		}
		cout << endl;
	}
}

int** push_row_front(int** arr, int& rows, const int cols)
{
	int** buffer = new int * [rows + 1];
	for (int i = 0; i < rows; i++)buffer[i + 1] = arr[i];
	delete[] arr;
	arr = buffer;
	arr[0] = new int[cols]{};
	rows++;
	return arr;
}

int** insert_row(int** arr, int& rows, const int cols, const int index)
{
	int** buffer = new int * [rows + 1];
	for (int i = 0; i < index; i++)buffer[i] = arr[i];
	for (int i = index; i < rows; i++)buffer[i + 1] = arr[i];
	delete[] arr;
	arr = buffer;
	arr[index] = new int[cols]{};
	rows++;
	return arr;
}

int** pop_row_back(int** arr, int& rows, const int cols)
{
	//1) удал€ем последнюю строку из пам€ти
	delete[] arr[rows - 1];
	//2) переопредел€ем массив указателей
	int** buffer = new int * [--rows];
	for (int i = 0; i < rows; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}

int** pop_row_front(int** arr, int& rows, const int cols)
{
	delete[] arr[0];
	int** buffer = new int* [--rows];
	for (int i = 0; i < rows; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

int** erase_row(int** arr, int& rows, const int cols, int index)
{
	int** buffer = new int* [--rows];
	for (int i = 0; i < index; i++)buffer[i] = arr[i];
	for (int i = index; i < rows; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	arr = buffer;
	return buffer;
}
