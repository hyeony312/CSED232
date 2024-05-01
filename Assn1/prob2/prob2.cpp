#include <iostream>
#include <string>
using namespace std;

float Plus(float num1, float num2);
float Minus(float num1, float num2);
float Multiply(float num1, float num2);
float Divide(float num1, float num2);
float Sqrt(float num);
float Square(float num);

int main()
{
		char input[10];
		float num1, num2;
		float output = 0;

		cout << fixed;
		cout.precision(3);

		cin >> input;

		if (strcmp(input, "+") == 0) {
			cin >> num1 >> num2;
			output = Plus(num1, num2);
		}
		else if (strcmp(input, "-") == 0) {
			cin >> num1 >> num2;
			output = Minus(num1, num2);
		}
		else if (strcmp(input, "*") == 0) {
			cin >> num1 >> num2;
			output = Multiply(num1, num2);
		}
		else if (strcmp(input, "/") == 0) {
			cin >> num1 >> num2;
			output = Divide(num1, num2);
		}
		else if (strcmp(input, "sqrt") == 0) {
			cin >> num1;
			output = Sqrt(num1);
		}
		else if (strcmp(input, "square") == 0) {
			cin >> num1;
			output = Square(num1);
		}
		else return 0;

		output *= 1000;
		output = round(output);
		output /= 1000;

		cout << output;

	return 0;
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

float Sqrt(float num)
{
	return sqrt(num);
}
float Square(float num)
{
	return num * num;
}