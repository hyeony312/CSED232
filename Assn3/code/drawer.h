#pragma once
#include "artist.h"
#include <string>

using namespace std;

class drawer {
private:
	artist* _artist;
public:
	drawer(artist*);
	~drawer() { delete[] _artist; }
	artist* pointer() { return _artist; }
	virtual string draw();
};

class downsample :public drawer{ // �׸��� ũ�⸦ 2�� �ٿ� ���
public:
	downsample(artist*);
	string draw();
};

class upsample :public drawer { // �׸��� ũ�⸦ 2�� �÷� ���
public:
	upsample(artist*);
	string draw();
};

class scale :public drawer { // scale ��ġ�� �Է� ������� �׸��� ũ�⸦ �����Ͽ� ���
private:
	int _W, _H;
public:
	scale(artist*, int, int);
	string draw();
};