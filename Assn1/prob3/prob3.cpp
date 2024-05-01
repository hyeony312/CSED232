#include <iostream>
#include <string>
using namespace std;

float Change(char* code);
float Plus(float num1, float num2);
float Minus(float num1, float num2);
float Multiply(float num1, float num2);
float Divide(float num1, float num2);

int main()
{
		char input[10];
		char code1[10], code2[10];
		float num1, num2;
		float output = 0;

		cout << fixed;
		cout.precision(3);

		cin >> input >> code1 >> code2;

		num1 = Change(code1);
		num2 = Change(code2);

		if (strcmp(input, "+") == 0) {
			output = Plus(num1, num2);
		}
		else if (strcmp(input, "-") == 0) {
			output = Minus(num1, num2);
		}
		else if (strcmp(input, "*") == 0) {
			output = Multiply(num1, num2);
		}
		else if (strcmp(input, "/") == 0) {
			output = Divide(num1, num2);
		}
		else return 0;

		output *= 1000;
		output = round(output);
		output /= 1000;

		cout << output;

	return 0;
}

float Change(char* code) 
{
	int i;
	float result = 0;
	int len = strlen(code);
	if (code[1] == 'b') {
		int clen = len - 2;
		for (i = 2; i < len; i++) {
			result += (code[i] - 48) * pow(2, --clen);
		}
	}
	else if (code[1] == 'X') {
		int clen = len - 2;
		for (i = 2; i < len; i++) {
			if (code[i] >= '0' && code[i] <= '9') result += (code[i] - 48) * pow(16, --clen);
			else if (code[i] >= 'a' && code[i] <= 'f') result += (code[i] - 87) * pow(16, --clen);
			else if (code[i] >= 'A' && code[i] <= 'F') result += (code[i] - 55) * pow(16, --clen);
		}
	}
	else {
		int clen = len - 1;
		for (i = 1; i < len; i++) {
			result += (code[i] - 48) * pow(8, --clen);
		}
	}

	return result;
}

float Plus(float num1, float num2)
{
	return num1 + num2;
}

float Minus(float num1, float num2)
{
	return num1 - num2;
}

float Multiply(float num1, float num2)
{
	return num1 * num2;
}

float Divide(float num1, float num2)
{
	return num1 / num2;
}