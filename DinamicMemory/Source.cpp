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
	cout << "������� ���������� ���������: "; cin >> n;
	int* arr = new int[n];

	FillRand(arr, n);
	Print(arr, n);

	int value;
	cout << "������� ����������� ��������: "; cin >> value;
	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "������� ����������� ��������: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	cout << "������� ����������� ��������: "; cin >> value;
	int index;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	arr = insert(arr, n, value, index);
	Print(arr, n);

	arr = pop_back(arr, n);
	Print(arr, n);

	arr = pop_front(arr, n);
	Print(arr, n);

	cout << delimeter << endl;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	arr = erase(arr, n, index);
	Print(arr, n);

	delete[] arr;
	//Memory leak  
#endif // DYNAMIC_MEMORY_1

	int rows; //���������� �����
	int cols; //���������� �������� (���������� ��������� ������)
	cout << "������� ���������� �����: "; cin >> rows;
	cout << "������� ���������� ��������� ������: "; cin >> cols;

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
	cout << "������� ������ ����������� ������: "; cin >> index;
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

	cout << "������� ������ ��������� ������: "; cin >> index;
	arr = erase_row(arr, rows, cols, index);
	Print(arr, rows, cols);

	clear(arr, rows);
}

template<typename T>T** allocate(const int rows, const int cols)
{
	T** arr = new T* [rows];   //������� ������ ����������
	for (int i = 0; i < rows; i++)
	{
		//������� ������ ���������� �������:
		arr[i] = new T[cols];
	}
	return arr;
}

template<typename T>void clear(T** arr, const int rows)
{
	//������� ������ ���������� �������
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2) ������� ������ ����������:
	delete[] arr;
}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	cout << typeid(arr).name() << endl;
	for (int i = 0; i < n; i++)
	{
		//����� ���������� ���������� � �������� �������������
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
	}
}

template<typename T>void Print(T arr[], const int n)
{
	cout << typeid(arr).name() << endl;
	for (int i = 0; i < n; i++)
	{
		//����� �������� ��������������
		//[] - �������� �������������� (subscript operator)
		cout << arr[i] << tab;
	}
	cout << endl;
}

template<typename T>T* push_back(T* arr, int& n, T value)
{
	//1) ������� ����� ������ ������� �������:
	T* buffer = new T[n + 1];
	//2) �������� ��� ���������� ��������� ������� � ��������:
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//3) ������� �������� ������:
	delete[] arr;
	//4) ��������� ����� � ��������� 'arr' ������� ������ �������:
	arr = buffer;
	//5) ������ ����� ����� ����� � ����� ������� 'arr' ����� �������� �������� value
	arr[n] = value;
	//6) ����� ���������� � ������ 'arr' ��������, ���������� ��� ��������� �������������
	n++;
	//7) mission complete - ������� ��������!
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
	//�������� new  ������� ������ �� 'cols' ���������, 
	//������� �������� ������� ���������� �������.
}

template<typename T>T** pop_row_back(T** arr, int& rows, const int cols)
{
	//1) ������� ��������� ������ �� ������
	delete[] arr[rows - 1];
	//2) �������������� ������ ����������
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
		// T() - �������� �� �������� ��� ���� 'T'
		cols--;
	}
	cols++;
}

