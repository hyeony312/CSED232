#pragma once
#include <vector>
#include<string>

using namespace std;

class parser {
public:
	vector<int> load_image(const char*); // �ȼ����� �о� ���Ϳ� ����
	vector<string> load_config(const char*); // config�� �о� ���Ϳ� ����
	void write_result(const char*, const string&); // ���������� �ϼ��� ���ڿ��� ���
};
