#include "Structure.h"
#include <iostream>
#include <string.h>

using namespace std;

void inputDate(Date& datee) {
	cin >> datee.day >> datee.month >> datee.year;
}
void inpYears(SchoolYear*& year) {
    SchoolYear* cur = year = nullptr;
    int n;
    cin >> n;
    cin.get();
    while (n--) {
        if (!year) {
            year = new SchoolYear;
            cur = year;
        }
        else {
            cur->yearNext = new SchoolYear;
            cur = cur->yearNext;
        }
        int numberClass;
        cin >> numberClass;
        while (numberClass--) {
            Class* tem = new Class;
            cin >> tem->name;
            tem->classNext = cur->classHead;
            cur->classHead = tem;
        }
    }
}
