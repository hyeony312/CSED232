#pragma once
#include<vector>

using namespace std;

class artist { //그림의 기본적인 속성과 메소드를 가지고 있는 클래스
private:
	int width; // 그림의 너비
	int height; // 그림의 높이
	int** pixel_arr; // 그림을 나타내는 2차원 배열
public:
	artist(int _width, int _height, const std::vector<int>& _pixel_data);
	~artist() {
		for (int i = 0; i < height; i++) {
			delete[] pixel_arr[i];
		}
		delete[] pixel_arr;
	}
	virtual char mapper(int, int); // 픽셀의 좌표를 입력받아 해당 좌표의 문자를 반환
	int find_pixel(int, int); // 해당 좌표의 픽셀값을 반환
	int find_end(int, int); // 해당 좌표가 x축 끝인 경우 1, y축 끝인 경우 2, 모두 해당되면 3을 반환한다. 이외에는 0을 반환
	int give_width() { return width; } // 그림의 너비를 반환
	int give_height() { return height; } // 그림의 높이를 반환
};

class classic: public artist // 문자로 표현된 그림을 그리는 클래스
{
public:
	classic(int W, int H, const std::vector<int>& V):artist(W,H,V){}
	char mapper(int, int);
};

class iclassic :public artist // classic과 반대의 문자로 그림을 그리는 클래스
{
public:
	iclassic(int W, int H, const std::vector<int>& V) :artist(W, H, V) {}
	char mapper(int, int);
};

class sobelx :public artist // x방향 sobel 필터링을 이용해 그림을 그리는 클래스
{
public:
	sobelx(int W, int H, const std::vector<int>& V) :artist(W, H, V) {}
	char mapper(int, int);
};

class sobely :public artist // y방향 sobel 필터링을 이용해 그림을 그리는 클래스
{
public:
	sobely(int W, int H, const std::vector<int>& V) :artist(W, H, V) {}
	char mapper(int, int);
};

class gradient :public artist // x, y방향 sobel 필터링을 이용해 그림을 그리는 클래스
{
public:
	gradient(int W, int H, const std::vector<int>& V) :artist(W, H, V) {}
	char mapper(int, int);
};

class my_style :public artist // 픽셀값이 127 이상이면 #을 반환하여 그림을 그리는 클래스
{
public:
	my_style(int W, int H, const std::vector<int>& V) :artist(W, H, V) {}
	char mapper(int, int);
};