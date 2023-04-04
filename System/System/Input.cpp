#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;
using namespace std;
using namespace fs;

struct User {
    string username;
    string password;
};

void processCSVFile(const path& file_path) {
    ifstream in;
    in.open(file_path);
    if (!in.is_open()) { 
        cout << "Cannot open file" << endl;
        return;
    }

    string header;              // xoa dong 1
    getline(in, header);

    string line;
    string username, password;

    while (getline(in, line)) {
        stringstream ss(line);

        getline(ss, username, ',');
        getline(ss, password, ',');

        User user = { username, password };
        cout << user.username << ", " << user.password << endl;
    }
    in.close();
}

void read_files(const path& path) {
    string name;

    for (const auto& entry : directory_iterator(path)) {
        if (entry.is_directory()) {    // if is folder
            name = entry.path().filename().string();
            cout << name << endl;
            read_files(entry.path());  // recursion
        }
        else {
            name = entry.path().filename().stem().string();     // filename (-.txt)
            cout << name << endl;
            processCSVFile(entry.path());
        }
    }
}

int main() {
    path root_path("Data");
    read_files(root_path);      // input all files in "Data";
    return 0;
}

/*
 directory_iterator(path) : Hàm này nhận vào đường dẫn của một thư mục và trả về một iterator đại diện cho tất cả các tệp tin và thư mục trong thư mục đó.

entry.is_directory() : Hàm này kiểm tra xem một entry có phải là một thư mục hay không.

getline(file, header) và getline(ss, username, ',') : Hàm này đọc một dòng văn bản trong tệp tin.

read_files(path) : Hàm này nhận vào đường dẫn của một thư mục và đọc tất cả các tệp tin và thư mục trong đó bằng cách đệ quy gọi chính nó với đường dẫn của các thư mục con.

path root_path("Data") : Hàm này tạo một đối tượng path từ đường dẫn "Data".
*/