#pragma once
#include "Structure.h"
bool checkStaffPassword(string, string);
bool checkStudentPassword(string, string);
void login(int firstlog, SchoolYear* yearHead);
void menuStaff(string username, SchoolYear*& yearHead);
void menuStudent(string);
void UI();
void UIlite();