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

	delete[] arr;
	//Memory leak  
#endif // DYNAMIC_MEMORY_1

	int rows; //���������� �����
	int cols; //���������� �������� (���������� ��������� ������)
	cout << "������� ���������� �����: "; cin >> rows;
	cout << "������� ���������� ��������� ������: "; cin >> cols;

	int** arr = new int* [rows];   //������� ������ ����������
	for (int i = 0; i < rows; i++)
	{
		//������� ������ ���������� �������:
		arr[i] = new int[cols];
	}

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimeter << endl;
	arr = push_row_back(arr, rows, cols);
	Print(arr, rows, cols);

	//������� ������ ���������� �������
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2) ������� ������ ����������:
	delete[] arr;

}

void FillRand(int arr[], const int n)
{
	cout << typeid(arr).name() << endl;
	for (int i = 0; i < n; i++)
	{
		//����� ���������� ���������� � �������� �������������
		*(arr + i) = rand() % 100;
	}
}

void Print(int arr[], const int n)
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

int* push_back(int* arr, int& n, int value)
{
	//1) ������� ����� ������ ������� �������:
	int* buffer = new int[n + 1];
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
	//1) ������� �������� ������ ����������
	int** buffer = new int* [rows + 1];
	// 2) �������� ������ ����� � ����� ������� ����������
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i];
	}
	//3) ������� �������� ������ ����������
	delete[] arr;
	//4) ��������� ����� ��������� 'arr' ������� ������ �������
	arr = buffer;
	// 5) ������� ����� �����
	arr[rows] = new int[cols] {};
	//6) ����� ���������� ������, ���������� ����� ������������� �� ����
	rows++;
	//7) ������ ���������, ���������� ����� ������
	return arr;
}
