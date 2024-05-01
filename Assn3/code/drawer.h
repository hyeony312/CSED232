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

class downsample :public drawer{ // 그림의 크기를 2배 줄여 출력
public:
	downsample(artist*);
	string draw();
};

class upsample :public drawer { // 그림의 크기를 2배 늘려 출력
public:
	upsample(artist*);
	string draw();
};

class scale :public drawer { // scale 수치를 입력 받은대로 그림의 크기를 조절하여 출력
private:
	int _W, _H;
public:
	scale(artist*, int, int);
	string draw();
};