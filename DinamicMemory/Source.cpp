#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n------------------------------------\n"

void FillRand(int arr[], const int n, int minRand=0, int maxRand=100);
void FillRand(int** arr, const int rows, const int cols);

template<typename T>void Print(T* arr, const int n);
template<typename T>void Print(T** arr, const int rows, const int cols);


template<typename T>T* push_back(T* arr, int& n, T value);
template<typename T>T* push_front(T* arr, int& n, int value);
template<typename T>int* insert(int* arr, int& n, T value, int index);
template<typename T>T* pop_back(T* arr, int& n);
template<typename T>T* pop_front(T* arr, int& n);
template<typename T>T* erase(T* arr, int& n, int index);

template<typename T>T** push_row_back(T** arr, int& rows, const int cols);
template<typename T>T** push_row_front(T** arr, int& rows, const int cols);
template<typename T>
T** insert_row(T** arr, int& rows, const int cols, const int index);

template<typename T>
T** pop_row_back(T** arr, int& rows, const int cols);
template<typename T>
T** pop_row_front(T** arr, int& rows, const int cols);
template<typename T>
T** erase_row(T** arr, int& rows, const int cols, int index);

template<typename T>
void push_col_back(T** arr, const int rows, int& cols);


//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

template<typename T>T** allocate(const int rows, const int cols);
template<typename T>void clear(T** arr, const int rows);

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

	cout << delimeter << endl;
	cout << "¬ведите индекс исключаемого значени€: "; cin >> index;
	arr = erase(arr, n, index);
	Print(arr, n);

	delete[] arr;
	//Memory leak  
#endif // DYNAMIC_MEMORY_1

	int rows; //количество строк
	int cols; //количество столбцов (количество элементов строки)
	cout << "¬ведите количество строк: "; cin >> rows;
	cout << "¬ведите количество элементов строки: "; cin >> cols;

	int** arr = allocate<int>(rows, cols);
	
	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	cout << delimeter << endl;
	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 900, 1000);
	Print(arr, rows, cols);

	cout << delimeter << endl;
	arr = push_row_front(arr, rows, cols);
	FillRand(arr[0], cols, 100, 200);
	Print(arr, rows, cols);

	int index;
	cout << "¬ведите индекс добавл€емой строки: "; cin >> index;
	arr = insert_row(arr, rows, cols, index);
	FillRand(arr[index], cols, 400, 500);
	Print(arr, rows, cols);
	cout << delimeter << endl;

	arr = pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimeter << endl;

	push_col_back(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimeter << endl;

	arr = pop_row_front(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimeter << endl;

	cout << "¬ведите индекс удал€емой строки: "; cin >> index;
	arr = erase_row(arr, rows, cols, index);
	Print(arr, rows, cols);

	clear(arr, rows);
}

template<typename T>T** allocate(const int rows, const int cols)
{
	T** arr = new T* [rows];   //сщздаем массив указателей
	for (int i = 0; i < rows; i++)
	{
		//создаем строки двумерного массива:
		arr[i] = new T[cols];
	}
	return arr;
}

template<typename T>void clear(T** arr, const int rows)
{
	//удал€ем строки двумерного массива
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2) удал€ем массив указателей:
	delete[] arr;
}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	cout << typeid(arr).name() << endl;
	for (int i = 0; i < n; i++)
	{
		//через арифметику указателей и оператор разыменовани€
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
	}
}

template<typename T>void Print(T arr[], const int n)
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

template<typename T>T* push_back(T* arr, int& n, T value)
{
	//1) создаем новый массив нужного размера:
	T* buffer = new T[n + 1];
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

template<typename T>T* push_front(T* arr, int& n, T value)
{
	T* buffer = new T[n + 1];
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

template<typename T>T* insert(T* arr, int& n, T value, int index)
{
	T* buffer = new T[n + 1];
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

template<typename T>T* pop_back(T* arr, int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}
 
template<typename T>T* pop_front(T* arr, int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

template<typename T>T* erase(T* arr, int& n, int index)
{
	T* buffer = new T[--n];
	for (int i = 0; i < index; i++)buffer[i] = arr[i];
	for (int i = index; i < n; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	arr = buffer;
	return arr;
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

template<typename T>void Print(T** arr, const int rows, const int cols)
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

template<typename T>T** push_row_back(T** arr, int& rows, const int cols)
{
	return push_back(arr, rows, new T[cols]{});
	
}

template<typename T>T** push_row_front(T** arr, int& rows, const int cols)
{
	return push_front(arr, rows, new T[cols]{});
}

template<typename T>T** insert_row(T** arr, int& rows, const int cols, const int index)
{
	return insert(arr, rows, new T[cols]{}, index);
	//ќператор new  сщздает массив на 'cols' элементов, 
	//который €вл€етс€ строкой двумерного массива.
}

template<typename T>T** pop_row_back(T** arr, int& rows, const int cols)
{
	//1) удал€ем последнюю строку из пам€ти
	delete[] arr[rows - 1];
	//2) переопредел€ем массив указателей
	return pop_back(arr, rows);
}

template<typename T>T** pop_row_front(T** arr, int& rows, const int cols)
{
	delete[] arr[0];
	//T** buffer = new T* [--rows];
	//for (int i = 0; i < rows; i++)buffer[i] = arr[i + 1];
	//delete[] arr;
	//return buffer;
	return pop_front(arr, rows);
}

template<typename T>T** erase_row(T** arr, int& rows, const int cols, int index)
{
	//T** buffer = new T* [--rows];
	//for (int i = 0; i < index; i++)buffer[i] = arr[i];
	//for (int i = index; i < rows; i++)buffer[i] = arr[i + 1];
	//delete[] arr;
	//arr = buffer;
	//return buffer;
	delete[] arr[index];
	return erase(arr, rows, index);
}

template<typename T>void push_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		arr[i] = push_back(arr[i], cols, T());
		// T() - значение по молчанию дл€ типа 'T'
		cols--;
	}
	cols++;
}

