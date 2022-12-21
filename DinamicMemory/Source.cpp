#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n------------------------------------\n"

void FillRand(int arr[], const int n);
void FillRand(int** arr, const int rows, const int cols);
void Print(int* arr, const int n);
void Print(int** arr, const int rows, const int cols);

int* push_back(int* arr, int& n, int value);
int* push_front(int* arr, int& n, int value);
int* insert(int* arr, int& n, int value, int index);
int* pop_back(int* arr, int& n);
int* pop_front(int* arr, int& n);

int** push_row_back(int** arr, int& rows, const int cols);

//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(LC_ALL, "");
#ifdef DYNAMIC_MEMORY_1
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

	cout << "¬ведите добавл€емое значение: "; cin >> value;
	int index;
	cout << "¬ведите индекс добавл€емого значени€: "; cin >> index;
	arr = insert(arr, n, value, index);
	Print(arr, n);

	arr = pop_back(arr, n);
	Print(arr, n);

	arr = pop_front(arr, n);
	Print(arr, n);

	delete[] arr;
	//Memory leak  
#endif // DYNAMIC_MEMORY_1

	int rows; //количество строк
	int cols; //количество столбцов (количество элементов строки)
	cout << "¬ведите количество строк: "; cin >> rows;
	cout << "¬ведите количество элементов строки: "; cin >> cols;

	int** arr = new int* [rows];   //сщздаем массив указателей
	for (int i = 0; i < rows; i++)
	{
		//создаем строки двумерного массива:
		arr[i] = new int[cols];
	}

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimeter << endl;
	arr = push_row_back(arr, rows, cols);
	Print(arr, rows, cols);

	//удал€ем строки двумерного массива
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2) удал€ем массив указателей:
	delete[] arr;

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

int* insert(int* arr, int& n, int value, int index)
{
	int* buffer = new int[n + 1];
	//for (int i = 0; i < index; i++)buffer[i] = arr[i];
	//for (int i = index; i<n; i++)buffer[i + 1] = arr[i];
	for (int i = 0; i < n; i++)
	{
		//if (i < index)buffer[i] = arr[i];else buffer[i + 1] = arr[i]; 
		//(i < index ? buffer[i] : buffer[i + 1]) = arr[i];
		buffer[i < index ? i : i + 1] = arr[i];
	}
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

int** push_row_back(int** arr, int& rows, const int cols)
{
	//1) сщздаем буферный массив указателей
	int** buffer = new int* [rows + 1];
	// 2) копируем адреса строк в новый масссив указателей
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i];
	}
	//3) удал€ем исходный массив указателей
	delete[] arr;
	//4) подмен€ем адрес указател€ 'arr' адресом нового массива
	arr = buffer;
	// 5) сщздаем новую сроку
	arr[rows] = new int[cols] {};
	//6) после добавлени€ строки, количество строк увеличиваетс€ на одну
	rows++;
	//7) строка добавлена, возвращаем новым массив
	return arr;
}
