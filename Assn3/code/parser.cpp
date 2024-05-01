#include"parser.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

vector<int> parser::load_image(const char* filename)
{
    vector<int> image_data;
    char separator;
    ifstream file(filename); // 파일을 연다

    if (!file.is_open()) {
        cout << "파일을 열 수 없습니다.";
    }
    else {
        int width, height;
        file >> width >> separator; // 너비
        file >> height >> separator; // 높이
        image_data.push_back(width);
        image_data.push_back(height);

        for (int i = 0; i < width * height; i++) { // 픽셀값을 벡터에 저장
            int pixel;
            file >> pixel >> separator;
            image_data.push_back(pixel);
        }
    }
    file.close();
	return image_data;
}
vector<string> parser::load_config(const char* configname) 
{
    vector<string> config_data;
    string artist, drawer;
    char c;
    ifstream file(configname); // 파일을 연다
    if (!file.is_open()) {
        cout << "파일을 열 수 없습니다.";
    }
    else {
        while (1) {
            file >> c;
            if (c == '|') break;
            artist = artist + c;
        }
        while (1) {
            file >> c;
            if (c == '|' || file.eof()) break;
            drawer = drawer + c;
        }
        config_data.push_back(artist);
        config_data.push_back(drawer);
        if (drawer == "scale") {
            string x, y;
            while (1) {
                file >> c;
                if (c == '|') break;
                x = x + c;
            }
            while (1) {
                file >> c;
                if (c == '|' || file.eof()) break;
                y = y + c;
            }
            config_data.push_back(x);
            config_data.push_back(y);
        }
    }
    file.close();
    return config_data;
}
void parser::write_result(const char* filename, const string& contents)
{
    ofstream file(filename);
    file << contents;
    file.close();
}