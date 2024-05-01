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
    ifstream file(filename); // ������ ����

    if (!file.is_open()) {
        cout << "������ �� �� �����ϴ�.";
    }
    else {
        int width, height;
        file >> width >> separator; // �ʺ�
        file >> height >> separator; // ����
        image_data.push_back(width);
        image_data.push_back(height);

        for (int i = 0; i < width * height; i++) { // �ȼ����� ���Ϳ� ����
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
    ifstream file(configname); // ������ ����
    if (!file.is_open()) {
        cout << "������ �� �� �����ϴ�.";
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