#pragma once
#include <vector>
#include<string>

using namespace std;

class parser {
public:
	vector<int> load_image(const char*); // 픽셀값을 읽어 벡터에 저장
	vector<string> load_config(const char*); // config를 읽어 벡터에 저장
	void write_result(const char*, const string&); // 최종적으로 완성된 문자열을 출력
};
