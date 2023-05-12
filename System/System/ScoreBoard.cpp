#include "Structure.h"
string xiuupxiudown(float f) {
	if (to_string(f).substr(0, 2) == "10") return to_string(f).substr(0, 2) + "  ";
	return to_string(f).substr(0, 3) + " ";
}

void viewScoreBoard(SchoolYear* sy, int numSm, Student* stuInClass) {
	cout << string(50, '-') << "THONG TIN TOM TAT" << string(50, '-') << endl << endl;
	cout << string(18, ' ') << "Thong tin chung" << string(45, ' ') << "Nhom hoc phan" << endl;

	cout << " Ma SV" << string(30, ' ') << stuInClass->StuID;
	cout << string(28 - stuInClass->StuID.length(), ' ') << "BBCS" << string(28, ' ') << "58" << endl;

	cout << " Ho ten SV" << string(26, ' ') << stuInClass->firstName << ' ' << stuInClass->lastName;
	cout << string(28 - (stuInClass->firstName + ' ' + stuInClass->lastName).length(), ' ') << "BBNCS" << string(27, ' ') << "26" << endl;

	cout << " Tong TC tich luy" << string(19, ' ') << stuInClass->accumCredits;
	cout << string(28 - to_string(stuInClass->accumCredits).length(), ' ') << "Math-Physics" << string(20, ' ') << "28" << endl;

	cout << " Diem TB tich luy" << string(19, ' ');
	if (stuInClass->accumScore / stuInClass->accumCredits > 0) cout << to_string(stuInClass->accumScore / stuInClass->accumCredits).substr(0, 3);
	else cout << "N/A";

	cout << string(25, ' ') << "TCCS" << string(28, ' ') << "36" << endl;

	cout << " Du dieu kien tot nghiep" << string(12, ' ') << "N/A";
	cout << string(25, ' ') << "TN" << string(30, ' ') << "10" << endl << endl;

	cout << string(45, '-') << "KET QUA CHI TIET TUNG HOC PHAN" << string(45, '-') << endl << endl;

	cout << "    Hoc Ky    |" << "   Ma MH   |" << string(17, ' ') << "Ten MH" << string(15, ' ') << "| So TC |" << "  Lop  |" << "  GK  |" << " Khac |" << "  CK  |" << "  10  |" << "  ABC  " << endl;

	Course* course = sy->sm[numSm - 1].courseHead;
	while (course) {
		StuInCourse* tmp = course->stuHead;
		while (tmp && tmp->stuInClass != stuInClass) {
			tmp = tmp->stuNext;
		}
		if (tmp != NULL) {
			cout << " HK" << numSm << " " << sy->name << "|";
			cout << "   " << course->ID << string(8 - course->ID.length(), ' ') << "| " << course->name << string(37 - course->name.length(), ' ') << "|   ";
			cout << course->numCredit << "   | " << course->className << string(6 - course->className.length(), ' ');

			cout << "|  " << xiuupxiudown(tmp->midM) << "|  " << xiuupxiudown(tmp->otherM);
			cout << "|  " << xiuupxiudown(tmp->finalM) << "|  " << xiuupxiudown(tmp->totalM) << "|   ";

			if (tmp->totalM < 5) cout << "F";
			else if (tmp->totalM < 6) cout << "C";
			else if (tmp->totalM < 7) cout << "B";
			else if (tmp->totalM < 8) cout << "B+";
			else if (tmp->totalM < 9) cout << "A";
			else cout << "A+";
			cout << endl << endl;
		}
		course = course->courseNext;
	}
	cout << endl;
}


void viewScoreClass(SchoolYear* sy, int numSm, Class* cl) {
	Student* tmpS = cl->stuHead;
	float GPAsm = 0;
	int credits = 0;

	cout << "BANG DIEM TONG HOP HK" << numSm << endl;
	cout << "Curriculum: " << tmpS->curriculum << endl;
	cout << "Class: " << tmpS->className << endl << endl;

	while (tmpS) {
		cout << tmpS->No << ". " << tmpS->StuID << " - " << tmpS->firstName << " " << tmpS->lastName << endl;
		cout << "OVERALL" << endl;
		cout << "     Accumulated credits: " << tmpS->accumCredits << "/165" << endl;
		cout << "     Accumulated GPA: " << to_string(tmpS->accumScore / tmpS->accumCredits).substr(0, 3) << "/4.0" << endl << endl;

		cout << "DETAIL" << endl;
		Course* tmpC = sy->sm[numSm - 1].courseHead;
		while (tmpC) {
			StuInCourse* tmpSIC = checkStuInCourse(tmpC, tmpS);
			if (tmpSIC != NULL) {
				cout << string(5, ' ') << tmpC->name << string(45 - tmpC->name.length(), ' ') << tmpSIC->finalM << endl;
				GPAsm += tmpSIC->totalM * tmpC->numCredit;
				credits += tmpC->numCredit;
			}
			tmpC = tmpC->courseNext;
		}
		cout << string(5, ' ') << "GPA" << " HK" << numSm << ": " << to_string(GPAsm / float(credits)).substr(0, 3) << endl << string(30, '-') << endl << endl;
		GPAsm = 0;
		credits = 0;
		tmpS = tmpS->stuNext;
	}
}

// ham nay co the view cua tat ca cac mon trong hoc ky
void viewScoreboard(Course* course) {
	while (course) {
		StuInCourse* tmp = course->stuHead;
		if (tmp == NULL) {
			course = course->courseNext;
			continue;
		}

		cout << endl << string(85, '-') << endl;
		StuInCourse* s = course->stuHead;
		cout << "Course: " << course->name << endl;
		cout << "Credit: " << course->numCredit << endl;
		cout << "Lecturer: " << course->teacherName << endl;
		cout << "Student ID      First name      Last name      Total      Final      Mid      Other" << endl;
		while (s) {
			cout << s->stuInClass->StuID << "	" << s->stuInClass->firstName << string(16 - s->stuInClass->firstName.length(), ' ') << s->stuInClass->lastName << string(15 - s->stuInClass->lastName.length(), ' ');
			cout << xiuupxiudown(s->totalM) << string(7, ' ') << xiuupxiudown(s->finalM) << string(7, ' ');
			cout << xiuupxiudown(s->midM) << string(5, ' ') << xiuupxiudown(s->otherM) << endl;
			s = s->stuNext;
		}
		cout << string(85, '-');
		cout << endl;
		course = course->courseNext;
	}
}

void viewScoreboardCourse(Course* course) {

		StuInCourse* tmp = course->stuHead;
		if (tmp == NULL) {
			course = course->courseNext;
			
		}
		else
		{

			cout << endl << string(85, '-') << endl;
			StuInCourse* s = course->stuHead;
			cout << "Course: " << course->name << endl;
			cout << "Credit: " << course->numCredit << endl;
			cout << "Lecturer: " << course->teacherName << endl;
			cout << "Student ID      First name      Last name      Total      Final      Mid      Other" << endl;
			while (s) {
				cout << s->stuInClass->StuID << "	" << s->stuInClass->firstName << string(16 - s->stuInClass->firstName.length(), ' ') << s->stuInClass->lastName << string(15 - s->stuInClass->lastName.length(), ' ');
				cout << xiuupxiudown(s->totalM) << string(7, ' ') << xiuupxiudown(s->finalM) << string(7, ' ');
				cout << xiuupxiudown(s->midM) << string(5, ' ') << xiuupxiudown(s->otherM) << endl;
				s = s->stuNext;
			}
			cout << string(85, '-');
			cout << endl;
		}

}
/*
int countCntNum(Course*& c) {  //doc file
	ifstream fin(".\\Files\\DSHP\\" + c->ID + "_" + c->className + ".txt");
	if (!fin) return 0;
	// them dong ghi thong tin
	string s;
	int cnt = 0;
	while (!fin.eof()) {
		fin >> s;
		fin >> s;
		fin >> s;
		cnt++;
	}
	fin.close();
	return cnt - 1;
}

bool InfoStu::checkCourseName(Course*& c, string s) { //check if the course ID entered is appropriate or not
	while (c != NULL) {
		if (s == c->ID && ((c->className.length() == 4 && c->className == stuInClass->className.substr(0, 4) && stuInClass->className[4] < '5') || (c->className.substr(0, 2) > stuInClass->className.substr(0, 2) && c->className.substr(2, 2) == stuInClass->className.substr(2, 2) && stuInClass->className.length() >= c->className.length()) || c->className == stuInClass->className)) {
			c->cntStudent = countCntNum(c);
			return 1;
		}
		c = c->courseNext;
	}
	return 0;
}

bool checkIfExist(Course*& c, Student* stuInClass) { //doc file
	ifstream fin(".\\Files\\DSHP\\" + c->ID + "_" + c->className + ".txt");

	if (!fin) return 0;
	string s;
	while (!fin.eof()) {
		fin >> s;
		if (s == stuInClass->StuID) {
			fin.close();
			return 1;
		}
	}
	fin.close();
	return 0;
}

void InfoStu::importStuToCourseCSV(Course*& c) { //Doc file
	ofstream ft(".\\Files\\DSHP\\" + c->ID + "_" + c->className + ".txt", ofstream::app);
	ft << sy->name << " " << stuInClass->className << " " << stuInClass->StuID << endl;
}

void InfoStu::countCredit(Course* c, int& cre, int& numCourse) {
	while (c) {
		if (checkIfExist(c)) {
			numCourse++;
			cre += c->numCredit;
		}
		c = c->courseNext;
	}
}

void InfoStu::printListCourse(Course* c, int cre, int numCourse) {
	cout << stuInClass->firstName << " " << stuInClass->lastName << " - " << stuInClass->StuID << string(30, ' ');
	cout << "Number of credits: " << cre << "/" << "24" << endl;
	cout << string(stuInClass->firstName.length() + stuInClass->lastName.length() + stuInClass->StuID.length() + 34, ' ');
	cout << "Number of courses: " << numCourse << "/" << "6" << endl << endl;

	cout << "ID" << string(9, ' ') << "Course" << string(30, ' ') << "Credits" << string(3, ' ') << "Class" << string(7, ' ') << "Lecturer" << string(8, ' ') << "Day    " << "Session    " << "Registered    " << "State" << endl << endl;
	while (c->courseNext) {
		if ((c->className.length() == 4 && c->className == stuInClass->className.substr(0, 4) && stuInClass->className[4] < '5') || (c->className.substr(0, 2) > stuInClass->className.substr(0, 2) && c->className.substr(2, 2) == stuInClass->className.substr(2, 2) && stuInClass->className.length() >= c->className.length()) || c->className == stuInClass->className) {
			c->cntStudent = countCntNum(c);
			cout << c->ID << string(11 - c->ID.length(), ' ') << c->name << string(36 - c->name.length(), ' ') << "   " << c->numCredit << "      ";
			cout << c->className << string(9 - c->className.length(), ' ') << c->teacherName << string(19 - c->teacherName.length(), ' ') << c->day << string(8, ' ');
			cout << c->session << string(10, ' ') << c->cntStudent << "/" << c->maxStudent << " " << string(9 - to_string(c->cntStudent).length() - to_string(c->maxStudent).length(), ' ');

			if (checkIfExist(c)) cout << "Da chon";
			cout << endl << endl;
		}
		c = c->courseNext;
	}
}

void InfoStu::selectCourse() { //doc file
	ifstream fin(".\\Files\\DSHP\\dshp.txt");
	if (!fin) {
		cout << "Not time for registering course!" << endl;
		return;
	}

	//Print out all courses for the student to choose
	string s;
	fin >> s;
	cout << s << " "; //HK2
	string t = s;
	fin >> s;
	cout << s << endl; //2022-2023

	SchoolYear* tmpsy = sy;
	while (tmpsy->name != s) {
		tmpsy = tmpsy->yearNext;
	}

	Course* c = tmpsy->sm[stoi(t.substr(2, 1)) - 1].courseHead;
	Course* tmpC = c;

	int cre = 0;
	int numCourse = 0;
	countCredit(c, cre, numCourse);
	printListCourse(c, cre, numCourse);

	while (cre < 16 && numCourse < 4) {
		cout << "Register: ";
		getline(cin, s, '\n');
		if (s == "0") return;
		if (checkCourseName(tmpC, s)) {
			if (tmpC->maxStudent == tmpC->cntStudent) cout << "No more slot!" << endl;	// slots <> max && cnt
			else {
				if (!checkIfExist(tmpC)) {		// mo file dskhp
					cre += tmpC->numCredit;
					numCourse++;
					tmpC->cntStudent++;
					importStuToCourseCSV(tmpC);
					system("cls");
					printListCourse(c, cre, numCourse);
				}
				else cout << "Hoc phan " << tmpC->ID << " da duoc dang ky! " << endl;
			}
		}
		else cout << "Invalid ID!" << endl;
		tmpC = c;
	}
	fin.close();
}

dshp- --- (CS161_22CTT1)  ---> file
staff --- beginEroll(CS161_22CTT1->CS161_22CTT1_dsdkhp)---> staff+student : remove/add
																	staff: linked 
														---> staff: remove/add

	semester1 A B_dsdkhp -> dang ky
	---> linked list
	staff stopEroll: _dsdkhp-> file thuong (CS162_22CTT1)
	*/