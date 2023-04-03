// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <string>
#include <sstream>
using namespace std;


struct User {
    string username;
    string password;
};

int main() {
    // Đường dẫn đến thư mục chứa các file CSV
    const char* folder_path = "2022-2023";

    // Mở thư mục
    DIR* folder = opendir(folder_path);
    if (folder == nullptr) {
        cout << "Could not open folder " << folder_path << endl;
        return 1;
    }

    string file_path = "2022-2023/demo.txt"; // đường dẫn đến file

    ifstream file (file_path.c_str()); // mở file
    if (!file.good()) { // kiểm tra nếu không thể mở file
        cout << "Cannot open file" << endl;
        return 1;
    }    

    string line;
    string username, password;

     while (getline(file, line)) {
        stringstream ss(line);

        getline(ss, username, ',');
        getline(ss, password, ',');

        User user = { username, password };
        cout << user.username << user.password << std::endl;
     }

    file.close();
    closedir(folder);
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
