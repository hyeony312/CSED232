#pragma once
#include<vector>

using namespace std;

class artist { //�׸��� �⺻���� �Ӽ��� �޼ҵ带 ������ �ִ� Ŭ����
private:
	int width; // �׸��� �ʺ�
	int height; // �׸��� ����
	int** pixel_arr; // �׸��� ��Ÿ���� 2���� �迭
public:
	artist(int _width, int _height, const std::vector<int>& _pixel_data);
	~artist() {
		for (int i = 0; i < height; i++) {
			delete[] pixel_arr[i];
		}
		delete[] pixel_arr;
	}
	virtual char mapper(int, int); // �ȼ��� ��ǥ�� �Է¹޾� �ش� ��ǥ�� ���ڸ� ��ȯ
	int find_pixel(int, int); // �ش� ��ǥ�� �ȼ����� ��ȯ
	int find_end(int, int); // �ش� ��ǥ�� x�� ���� ��� 1, y�� ���� ��� 2, ��� �ش�Ǹ� 3�� ��ȯ�Ѵ�. �̿ܿ��� 0�� ��ȯ
	int give_width() { return width; } // �׸��� �ʺ� ��ȯ
	int give_height() { return height; } // �׸��� ���̸� ��ȯ
};

class classic: public artist // ���ڷ� ǥ���� �׸��� �׸��� Ŭ����
{
public:
	classic(int W, int H, const std::vector<int>& V):artist(W,H,V){}
	char mapper(int, int);
};

class iclassic :public artist // classic�� �ݴ��� ���ڷ� �׸��� �׸��� Ŭ����
{
public:
	iclassic(int W, int H, const std::vector<int>& V) :artist(W, H, V) {}
	char mapper(int, int);
};

class sobelx :public artist // x���� sobel ���͸��� �̿��� �׸��� �׸��� Ŭ����
{
public:
	sobelx(int W, int H, const std::vector<int>& V) :artist(W, H, V) {}
	char mapper(int, int);
};

class sobely :public artist // y���� sobel ���͸��� �̿��� �׸��� �׸��� Ŭ����
{
public:
	sobely(int W, int H, const std::vector<int>& V) :artist(W, H, V) {}
	char mapper(int, int);
};

class gradient :public artist // x, y���� sobel ���͸��� �̿��� �׸��� �׸��� Ŭ����
{
public:
	gradient(int W, int H, const std::vector<int>& V) :artist(W, H, V) {}
	char mapper(int, int);
};

class my_style :public artist // �ȼ����� 127 �̻��̸� #�� ��ȯ�Ͽ� �׸��� �׸��� Ŭ����
{
public:
	my_style(int W, int H, const std::vector<int>& V) :artist(W, H, V) {}
	char mapper(int, int);
};