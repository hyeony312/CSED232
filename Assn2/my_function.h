#pragma once
#include "my_function.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class student {
private:
	string dept, name, gender;
	int age;
public:
	void input_info();
	void print_info();
	int findnode(string dept, string gender, string name, int age); // Find a node that has same data
	int datacmp(student data); // Compare data. Return 1 when next data is smaller.
	string access_dept() {
		return dept;
	}
	string access_gender() {
		return gender;
	}
	int access_age() {
		return age;
	}
};

class node {
public:
	student data;
	node* next;
};

class list {
public:
	int count, dept_cnt;
	string dept[9];
	int stu_dept[9] = { 0 };
	node* head;

	void save_node(node* fnode);
	void delete_node(string fdept, string fgender, string fname, int fage);
	void sort();
	int update_data(); // update data of dept_cnt, dept[]
	void pivot(int num1, int num2);
	void print_func(int* Age, int group, int num);
};
