#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void handle_command(const string& command, const string& payload) {
    cout << "> " << command << " " << payload << endl;
    if (command != "AUTH") {
        cout << "invalid command" << endl;
        return;
    }

    if (payload[7] == '1') {
        throw runtime_error("flag{why_so_serious}");
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        cout << "wrong input! usage <input_file>" << endl;
        return 1;    
    }

    ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        cout << "not able to read!" << endl;
        return 1;
    }

    string command;
    string payload;
    string line;

    if (getline(inputFile, line)) {
        istringstream iss(line);
        if (iss >> command >> payload) {
            handle_command(command, payload);
        }
        else {
            cout << "error extracting" << endl;
            return 1;
        }
    } else {
        cout << "failed to read" << endl;
        return 1;
    }

    inputFile.close();
    return 0;
}
