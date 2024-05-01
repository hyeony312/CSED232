#include "my_function.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
	string command; // Command for select menu
	list stu_list;
	stu_list.count = stu_list.dept_cnt = 0; // 0으로 초기화

	while (1) {
		cout << "-----------MENU-----------" << endl
			<< "1. Add a student" << endl
			<< "2. Delete a student" << endl
			<< "3. Print the student's list" << endl
			<< "4. Pivot Table" << endl
			<< "5. Exit" << endl
			<< "---------------------------" << endl;
		cout << "Selection: ";
		cin >> command;
		cout << endl;

		if (command.compare("1")==0) { // Add new student
			node* temp = new node;
			int test = 1;
			temp->data.input_info();

			// Check if input is valid
			int _length = temp->data.access_dept().length();
			for (int i = 0; i < _length; i++) {
				if (temp->data.access_dept()[i] < 'A' || temp->data.access_dept()[i] > 'Z') {
					cout << "Invalid input" << endl;
					test = 0;
					break;
				}
			}
			//Redundancy check
			if (test) {
				for (node* curr = stu_list.head; curr != NULL; curr = curr->next) {
					if (curr->data.datacmp(temp->data) == 0) {
						test = 0;
						cout << "The student already exists" << endl;
						break;
					}
				}
			}
			//Check if Dept is full
			if (test&&stu_list.dept_cnt == 9) {
				test = 0;
				for (int i = 0; i < 9; i++) {
					if (temp->data.access_dept().compare(stu_list.dept[i]) == 0) test = 1;
				}
				if (test == 0) cout << "Too many Dept in list" << endl;
			}
			//Check if number of student of dept over 10000 
			if (test) {
				for (int i = 0; i < stu_list.dept_cnt; i++) {
					if (temp->data.access_dept().compare(stu_list.dept[i]) == 0) {
						if (stu_list.stu_dept[i] >= 9999) {
							test = 0;
							cout << "Too many students in the Dept" << endl;
							break;
						}
					}
				}
			}
			//Check if age is valid
			if (test) {
				if (temp->data.access_age() < 18 || temp->data.access_age() > 30) {
					cout << "Invalid input" << endl;
					test = 0;
				}
			}
			//Check if gender is valid
			if (test) {
				if (temp->data.access_gender()!="M" && temp->data.access_gender()!= "F") {
					cout << "Invalid input" <<endl;
					test = 0;
				}
			}
			// if test is 0, do not add node
			if (test) {
				stu_list.save_node(temp); // add new node
				stu_list.sort();
				cout << "A student is added in table!" << endl;
			}
		}
		else if (command.compare("2") == 0) {
			string dept, gender, name;
			int age;

			cout << "Dept: "; cin >> dept;
			cout << "Gender: "; cin >> gender;
			cout << "Name: "; cin >> name;
			cout << "Age: "; cin >> age;

			stu_list.delete_node(dept, gender, name, age); // delete node
			stu_list.sort();
		}
		else if (command.compare("3") == 0) {
			cout << "Dept\tGender\tName\tAge" << endl;
			for (node* curr = stu_list.head; curr != NULL; curr = curr->next) {
				curr->data.print_info();
			}
		}
		else if (command.compare("4") == 0) {
			int num1, num2;
			stu_list.update_data();
			cout << "-----------Category-----------" << endl
				<< "1. Dept" << endl
				<< "2. Gender" << endl
				<< "3. Dept and Gender" << endl
				<< "------------------------------" << endl
				<< "Selection: ";
			cin >> num1;
			cout << "-----------Function-----------" << endl
				<< "1. Average" << endl
				<< "2. Max" << endl
				<< "3. Min" << endl
				<< "------------------------------" << endl
				<< "Selection: ";
			cin >> num2;

			if (num1 == 1) cout << "Dept\t";
			else if (num1 == 2) cout << "Gender\t";
			else if (num1 == 3) cout << "Dept\tGender\t";

			if (num2 == 1) cout << "Average" << endl;
			else if (num2 == 2) cout << "Max" << endl;
			else if (num2 == 3) cout << "Min" << endl;

			stu_list.pivot(num1, num2);
		}
		else if (command.compare("5") == 0) {
			cout << "Exit!";
			break;
		}
		else cout << "Invalid input" << endl;
		stu_list.update_data();
		cout << endl;
	}
}

