#include "my_function.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void list::print_func(int* Age, int count, int num)
{
	float sum = 0, average;
	int Max, Min;
	if (num == 1) { // Average
		for (int i = 0; i < count; i++) {
			sum = sum + Age[i];
		}
		average = sum / count;
		average = round(average * 10) / 10;
		cout << average << endl;
	}
	else if (num == 2) { // Max
		Max = Age[0];
		for (int i = 1; i < count; i++) {
			if (Age[i] > Max) Max = Age[i];
		}
		cout << Max << endl;
	}
	else if (num == 3) { // Min
		Min = Age[0];
		for (int i = 1; i < count; i++) {
			if (Age[i] < Min) Min = Age[i];
		}
		cout << Min << endl;
	}
}

void list::pivot(int num1, int num2) 
{
	int Age[9];
	int group_cnt = 0;
	if (num1 == 1) { // Pivot with dept 
		for (int i = 0; i < dept_cnt; i++) {
			for (node* curr = head; curr != NULL; curr = curr->next) {
				if (dept[i] == curr->data.access_dept()) Age[group_cnt++] = curr->data.access_age(); //add age in Age[] and count
			}
			cout << dept[i] << "\t";
			print_func(Age, group_cnt, num2);
			group_cnt = 0; //Reset
		}
	}
	else if (num1 == 2) { // Pivot with gender
		// Female
		for (node* curr = head; curr != NULL; curr = curr->next) {
			if (curr->data.access_gender() == "F") Age[group_cnt++] = curr->data.access_age();
		}
		cout << "F\t";
		print_func(Age, group_cnt, num2);
		group_cnt = 0; //Reset
		// Male
		for (node* curr = head; curr != NULL; curr = curr->next) {
			if (curr->data.access_gender() == "M") Age[group_cnt++] = curr->data.access_age();
		}
		cout << "M\t";
		print_func(Age, group_cnt, num2);
		group_cnt = 0; //Reset
	}
	else if (num1 == 3) { // Pivot with dept&gender
		for (int i = 0; i < dept_cnt; i++) { // Dept
			//Female
			for (node* curr = head; curr != NULL; curr = curr->next) {
				if (dept[i] == curr->data.access_dept() && curr->data.access_gender() == "F") Age[group_cnt++] = curr->data.access_age();
			}
			if (group_cnt != 0) {
				cout << dept[i] << "\t" << "F\t";
				print_func(Age, group_cnt, num2);
			}
			group_cnt = 0; //Reset
			//Male
			for (node* curr = head; curr != NULL; curr = curr->next) {
				if (dept[i] == curr->data.access_dept() && curr->data.access_gender() == "M") Age[group_cnt++] = curr->data.access_age();
			}
			if (group_cnt != 0) {
				cout << dept[i] << "\t" << "M\t";
				print_func(Age, group_cnt, num2);
			}
			group_cnt = 0; //Reset
		}
	}
}

int list::update_data()
{
	if (head == NULL) {
		return -1;
	}
	// Reset dept data
	for (int i = 0; i < 9; i++) stu_dept[i] = 0;
	dept[0] = head->data.access_dept();
	stu_dept[0] = 1;
	dept_cnt = 1;

	// Update data
	for (node* curr = head->next; curr != NULL; curr = curr->next) {
		for (int i = 0; i <= dept_cnt; i++) {
			if (i == dept_cnt) {
				dept[dept_cnt] = curr->data.access_dept();
				stu_dept[dept_cnt] ++;
				dept_cnt++;
			}
			if (dept[i] == curr->data.access_dept()) {
				stu_dept[i]++;
				break;
			}
		}
	}
	return 0; // update successfuly
}

void list::sort() // Bouble sort
{
	int i, j;
	node* curr;
	if (head == NULL) return; //list가 비어있는 경우

	for (i = 1; i < count; i++) {
		curr = head;
		for (j = 1; j < i; j++) curr = curr->next;
		// compare
		if (curr->data.datacmp(curr->next->data) > 0) {
			student temp = curr->data;
			curr->data = curr->next->data;
			curr->next->data = temp;
		}
	}
}

void list::delete_node(string fdept, string fgender, string fname, int fage)
{
	if (head == NULL) { // list가 비어있는 경우
		cout << "Can't delete it" << endl;
		return;
	}
	else if (head->next == NULL) { // head만 있는 경우
		if (head->data.findnode(fdept, fgender, fname, fage) == 4) {
			delete head;
			head = NULL;
			count--;
			cout << "Deleted!" << endl;
			return;
		}
	}
	else {
		for (node* curr = head; curr != NULL; curr = curr->next) {
			if (curr->next->data.findnode(fdept, fgender, fname, fage) == 4) {//find node to delete
				if (curr->next->next == NULL) {
					delete curr->next;
					curr->next = NULL;
					count--;
					cout << "Deleted!" << endl;
					return;
				}
				node* temp = curr->next->next;
				delete curr->next;
				curr->next = temp;
				count--;
				cout << "Deleted!" << endl;
				return;
			}
		}
		cout << "Can't delete it" << endl;
	}
}

void list::save_node(node* fnode)
{
	if (head == NULL) { //list에 node가 없을 때
		head = fnode;
	}
	else {
		node* curr = head;
		for (int i = count; i > 1; i--) { // Search last node
			curr = curr->next;
		}
		curr->next = fnode;
	}
	count++;
}

void student::print_info()
{
	cout << dept << "\t" << gender << "\t" << name << "\t" << age << endl;
}

int student::datacmp(student data)
{
	if (dept > (data.dept)) return 1;
	else if (dept < (data.dept)) return -1;
	else { // if dept same
		if (gender > (data.gender)) return 1;
		else if (gender < (data.gender)) return -1;
		else { // if gender same
			if (name > (data.name)) return 1;
			else if (name < (data.name)) return -1;
			else { // if name same
				if (age > (data.age)) return 1;
				else if (age < (data.age)) return -1;
				else return 0;
			}
		}
	}
}

int student::findnode(string fdept, string fgender, string fname, int fage) // Return 4 when all values are smae
{
	int output = 0;

	if (dept == fdept) output++;
	if (gender == fgender) output++;
	if (name == fname) output++;
	if (age == fage) output++;

	return output;
}

void student::input_info()
{
	string strage;

	cout << "Dept: ";
	cin.ignore();
	getline(cin, dept);

	cout << "Gender: ";
	getline(cin, gender);

	cout << "Name: ";
	getline(cin, name);

	cout << "Age: ";
	getline(cin, strage);

	// _age에 invalid input이 들어갔는지 확인
	if (strage.length() > 2) {
		age = -1;
		return;
	}
	for (int i = 0; i < strage.length(); i++) {
		if (strage[i] < '0' || strage[i]>'9') {
			age = -1;
			return;
		}
	}
	
	// _age를 int로 변환하여 age에 저장
	if (strage.length() == 1) {
		age = (strage[0] - '0');
	}
	else {
		age = (strage[0] - '0') * 10 + (strage[1] - '0');
	}
}