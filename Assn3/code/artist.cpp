#include "artist.h"
#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

artist::artist(int _width, int _height, const std::vector<int>& pixel_data)
{
	width = _width;
	height = _height;

	pixel_arr = new int* [height];
	for (int i = 0; i < height; i++) {
		pixel_arr[i] = new int[width];
	}

	int index = 0;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			pixel_arr[j][i] = pixel_data[index];
			index += 1;
		}
	}
}

int artist::find_pixel(int y, int x) // 픽셀값 반환
{
	return pixel_arr[y][x];
}

int artist::find_end(int y, int x)
{
	if (x == width-1 && y == height-1) return 3;
	else if (y == height-1) return 2;
	else if (x == width-1) return 1;
	else return 0;
}

char artist::mapper(int y, int x) { return' '; } // Virtual 함수

char classic::mapper(int y, int x)
{
	int num = artist::find_pixel(y, x);
	if (num < 0) return '?';
	else if (num < 17) return '@';
	else if (num < 34) return '&';
	else if (num < 51) return '%';
	else if (num < 68) return 'W';
	else if (num < 85) return 'X';
	else if (num < 102)return 'A';
	else if (num < 119) return 'H';
	else if (num < 136) return 'O';
	else if (num < 153) return 'T';
	else if (num < 170) return '*';
	else if (num < 187) return '^';
	else if (num < 204) return '+';
	else if (num < 221) return '-';
	else if (num < 238) return '.';
	else if (num < 256) return ' ';
	else return '?';
}

char iclassic::mapper(int y, int x)
{
	int num = artist::find_pixel(y, x);
	if (num < 0) return '?';
	else if (num < 17) return ' ';
	else if (num < 34) return '.';
	else if (num < 51) return '-';
	else if (num < 68) return '+';
	else if (num < 85) return '^';
	else if (num < 102)return '*';
	else if (num < 119) return 'T';
	else if (num < 136) return 'O';
	else if (num < 153) return 'H';
	else if (num < 170) return 'A';
	else if (num < 187) return 'X';
	else if (num < 204) return 'W';
	else if (num < 221) return '%';
	else if (num < 238) return '&';
	else if (num < 256) return '@';
	else return '?';
}

char sobelx::mapper(int y, int x)
{
	int curr = artist::find_pixel(y, x);
	if (artist::find_end(y, x)==1) return ' ';

	int next = artist::find_pixel(y, x+1);
	int diff = curr - next;

	if (abs(diff)>=50) return '|';
	else return ' ';
}

char sobely::mapper(int y, int x)
{
	int curr = artist::find_pixel(y, x);
	if (artist::find_end(y, x) == 2) return ' ';

	int next = artist::find_pixel(y+1, x);
	int diff = curr - next;

	if (abs(diff) >= 50) return '-';
	else return ' ';
}

char gradient::mapper(int y, int x)
{
	int curr = artist::find_pixel(y, x);
	int x_diff; 
	int y_diff;

	// x나 y의 값이 최대인 경우를 예외로 처리한다.
	if (find_end(y, x) == 3) {
		x_diff = 0;
		y_diff = 0;
	}
	else if (find_end(y, x) == 2) {
		x_diff = curr - artist::find_pixel(y, x + 1);
		y_diff = 0;
	}
	else if (find_end(y, x) == 1) {
		x_diff = 0;
		y_diff = curr - artist::find_pixel(y + 1, x);
	}
	else{
		x_diff = curr - artist::find_pixel(y, x + 1);
		y_diff = curr - artist::find_pixel(y + 1, x);
	}

	if (abs(x_diff) >= 50 && abs(y_diff) >= 50) return '+';
	else if (abs(x_diff) >= 50) return '|';
	else if (abs(y_diff) >= 50) return '-';
	else return ' ';
}

char my_style::mapper(int y, int x)
{
	int num = artist::find_pixel(y, x);
	if (num < 127) return '#';
	return ' ';
}