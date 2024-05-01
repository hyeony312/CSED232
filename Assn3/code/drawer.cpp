#include"drawer.h"
#include <iostream>

using namespace std;

drawer::drawer(artist* A)
{
	_artist = A;
}

string drawer::draw()
{
	string output;

	for (int i = 0; i < _artist->give_height(); i++) {
		for (int j = 0; j < _artist->give_width(); j++) {
			output += _artist->mapper(i, j);
		}
		output += '\n';
	}
	return output;
}

downsample::downsample(artist* A) :drawer::drawer(A){}

string downsample::draw()
{
	string output;
	for (int i = 0; i < pointer()->give_height(); i+=2) {
		for (int j = 0; j < pointer()->give_width(); j+=2) {
			output += pointer()->mapper(i, j);
		}
		output += '\n';
	}
	return output;
}

upsample::upsample(artist* A) :drawer::drawer(A){}

string upsample::draw()
{
	string output;
	for (int i = 0; i < pointer()->give_height(); i ++) {
		for (int j = 0; j < pointer()->give_width(); j ++) {
			output += pointer()->mapper(i, j);
			output += pointer()->mapper(i, j);
		}
		output += '\n';
		for (int j = 0; j < pointer()->give_width(); j++) {
			output += pointer()->mapper(i, j);
			output += pointer()->mapper(i, j);
		}
		output += '\n';
	}
	return output;
}

scale::scale(artist* A, int W, int H):drawer::drawer(A)
{
	_W = W;
	_H = H;
}

string scale::draw()
{
	string output;
	int pX=1,nX=1,pY=1,nY=1; // 차례대로 양수 너비, 음수 너비, 양수 높이, 음수 높이 변화값

	if (_W > 0)  pX = _W;
	else if (_W < 0) nX = -_W;
	else return "error";

	if (_H > 0)  pY = _H;
	else if (_H < 0) nY = -_H;
	else return "error";

	for (int i = 0; i < pointer()->give_height(); i += nY) {
		for (int y = 0; y < pX; y++) {
			for (int j = 0; j < pointer()->give_width(); j += nX) {
				for (int x = 0; x < pY; x++) output += pointer()->mapper(i, j);
			}
			output += '\n';
		}
	}
	return output;
}
