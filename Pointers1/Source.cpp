#include<iostream>
using namespace std;
using std::cout;

void main()
{
	setlocale(LC_ALL, "");
	//int a = 2;
	//int* pa = &a;
	//cout << a << endl;
	//cout << &a << endl;

	const int n = 5;
	int arr[n] = { 3,5,8,13,21 };
	cout << arr << endl;
	cout << *arr << endl;
	for (int i = 0; i < n; i++)
	{
		cout << *(arr + i) << "\t";
	}
	cout << endl;
}