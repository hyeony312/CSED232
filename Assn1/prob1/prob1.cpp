#include <iostream>
using namespace std;

int d2b(int num, int* arr, int* i); // ������ -> ������
int d2o(int num, int* arr, int* i); // ������ -> ������
int d2h(int num, char* arr, int* i); // ������ -> ��������
int prtarr(int* arr, int* i); // ������ ���

int main()
{

		int num, i = 0; // Decimal, ������ �ڸ���
		int sellect; // 2, 8, 16 �� �ϳ�
		int arr[100];
		char hexarr[100];

		cin >> num >> sellect;

		if (sellect == 2) { // 2���� ��ȯ
			d2b(num, arr, &i);
			prtarr(arr, &i);
		}
		else if (sellect == 8) { // 8���� ��ȯ
			d2o(num, arr, &i);
			prtarr(arr, &i);
		}
		else if (sellect == 16) { // 16���� ��ȯ
			d2h(num, hexarr, &i);
			
			for (i ; i >= 0; i--) {
				cout << hexarr[i];
			}
			cout << endl;
		}

	return 0;
}

int prtarr(int* arr, int* i)
{
	for (int j = (*i); j >= 0; j--) {
		cout << arr[j];
	}
	cout << endl;

	return 0;
}

int d2h(int num, char* arr, int* i)
{
	char hex[16]{ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	do {
		arr[*i] = hex[num % 16];
		num /= 16;
		(*i)++;
	} while (num >= 16);
	arr[*i] = hex[num];

	return 0;
}

int d2o(int num, int* arr, int* i)
{
	do {
		arr[*i] = num % 8;
		num /= 8;
		(*i)++;
	} while (num >= 8);
	arr[*i] = num;

	return 0;
}


int d2b(int num, int* arr, int* i)
{
	do {
		arr[*i] = num % 2;
		num = (num - (num % 2)) / 2;
		(*i)++;
	} while (num >= 2);
	arr[*i] = num;

	return 0;
}