#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void handle_command(const string& command, const string& payload) {
    cout << "> " << command << " " << payload << endl;
    if (command != "CHECK") {
        cout << "invalid command" << endl;
        return;
    }

    int calculated_checksum = 0;
    int received_checksum = (payload[payload.size() - 2]- 48) * 10 + (payload[payload.size() - 1] - 48);

    for (int i=0; i < payload.size() - 2; i++) {
        calculated_checksum += (unsigned int) payload[i];
    }

    calculated_checksum %= 100;

    // cout << "cal: " << calculated_checksum << endl;
    // cout << "rec: " << received_checksum << endl;

    if (received_checksum != calculated_checksum) {
        cout << "invalid checksum" << endl;
        return;
    }

    if (payload[1] == 'b' && payload[4] == 'i') {
        throw runtime_error("flag{I_will_be_back}");
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
