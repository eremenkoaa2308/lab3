#include <iostream>
#include "pipe.h"
#include "cs.h"
#include "gazset.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <limits>
#include <string>
#include <thread>
#include <map>
#include <concepts>
#include <set>
#include <stack>
using namespace std;



void logMessage(string message) {
    ofstream logFile("log.txt", ios::app); // Открываем файл для добавления
    if (logFile.is_open()) {
        // Получаем текущее время
        time_t now = time(nullptr);
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &now); // Используем ctime_s
        logFile << buffer << ": " << message << endl; // Записываем сообщение с меткой времени
        logFile.close();
    }
    else {
        cerr << "Unable to open log file!" << endl;
    }
}
bool isInteger(const string& s) {
    istringstream iss(s);
    int num;
    iss >> num;
    return !iss.fail() && iss.eof();
}

int getChoose() {
    string input;
    int choose;
    while (true) {
        cout << "Choose one of the actions\n";
        cout << "1. Create a pipe\n";
        cout << "2. Create a cs\n";
        cout << "3. Viewing all objects\n";
        cout << "4. Edit the pipe\n";
        cout << "5. Edit the cs\n";
        cout << "6. Save\n";
        cout << "7. Download\n";
        cout << "8. Filter\n";
        cout << "9. Delete\n";
        cout << "10. Create gas trasportation system" << endl;
        cout << "11. Create a new connection in gas transportation system" << endl;
        cout << "12. Show gas transportation system" << endl;
        cout << "0. Exit\n";
        getline(cin, input);
        logMessage(input);
        if (isInteger(input)) {
            stringstream ss(input);
            ss >> choose;
            return choose;
        }
        else {
            cout << "Invalid input. Please enter a valid integer\n";
        }
    }
}
int check_int(int ch, int EntNum) {
    string input1;
    int entLen;
    while (true) {
        if (ch == 1) {
            cout << "Enter a length" << endl;
        }
        else if (ch == 2) {
            cout << "Enter a diameter" << endl;
        }
        else if (ch == 3) {
            cout << "Enter number of factories" << endl;
        }
        else if (ch == 4) {
            cout << "Enter number of working factories" << endl;
        }
        else if (ch == 5) {
            cout << "Enter number of efficiency from 0 to 100" << endl;
        }
        getline(cin, input1);
        logMessage(input1);
        if (isInteger(input1)) {
            stringstream ss(input1);
            ss >> entLen;
            if (ch != 4 && ch != 5) {
                if (entLen > 0) {
                    return entLen;
                }
                else {
                    cout << "Length must be a non-negative integer. Please enter a valid value\n";
                }
            }
            if (ch == 5) {
                if (entLen >= 0 && entLen <= 100) {
                    return entLen;
                }
                else {
                    cout << "Number of efficiency must be a non-negative integer. Please enter a valid value from 0 to 100\n";
                }
            }
            else {
                if (entLen > 0 && entLen <= EntNum) {
                    return entLen;
                }
                else if (entLen <= 0) {
                    cout << "Number of working factories must be a non-negative integer. Please enter a valid value\n";
                }
                else {
                    cout << "Number of working factories can't be more than total number of factories. Please enter a valid value\n";
                }
            }

        }
        else {
            cout << "Invalid input. Please enter a valid integer\n";
        }
    }

}
int check_i(string ch) {
    int entLen;
    if (isInteger(ch)) {
        stringstream ss(ch);
        ss >> entLen;
        if (entLen > 0) {
            return entLen;
        }
    }
}
bool check_bool(int ch) {
    bool entRep;
    string input1;
    bool A;
    while (true) {
        if (ch == 1) {
            cout << "Enter if your pipe is in repair\n";
        }
        if (ch == 2) {
            cout << "Enter + (plus) if you want to add one working factory. Enter - (minus) if you want to remove one working factory\n";
        }
        if (ch != 0) {
            getline(cin, input1);
            logMessage(input1);
        }
        if (ch == 1 || ch == 0) {
            if (input1 == "true" || input1 == "True" || input1 == "T" || input1 == "t") {
                entRep = true;
                return entRep;
            }
            else if (input1 == "false" || input1 == "False" || input1 == "F" || input1 == "f") {
                entRep = false;
                return entRep;
            }
            else {
                cout << "Invalid input for inRepair. It should be boolean. Try again! (true/false)\n";
            }
        }
        else {
            if (input1 == "plus" || input1 == "+" || input1 == "Plus") {
                A = true;
                return A;
            }
            else if (input1 == "Minus" || input1 == "minus" || input1 == "-") {
                A = false;
                return A;
            }
            else {
                cout << "Invalid input for inRepair. It should be boolean. Try again! (+/-)\n";
            }
        }

    }
}

template <typename T1, typename T2, typename T3, typename T4>
pipe addPipe(T1 name, T2 length, T3 diameter, T4 inRepair) {
    return pipe(static_cast<std::string>(name),
        static_cast<int>(length),
        static_cast<int>(diameter),
        static_cast<bool>(inRepair));
}

void createPipe(map<int, pipe>& Pipes, int& i) {
    string T;
    cout << "Do you want to create your own pipe? [Y/N]\n";
    getline(cin, T);
    logMessage(T);
    if (T == "Y" || T == "y") {
        string entName;
        int entLen;
        int entDia;
        bool entRep;
        cout << "Enter a name" << endl;
        getline(cin, entName);
        logMessage(entName);
        entLen = check_int(1, 0);
        entDia = check_int(2, 0);
        entRep = check_bool(1);
        Pipes[i] = addPipe(entName, entLen, entDia, entRep);
        i++;
    }
    else {
        Pipes[i] = pipe();
        i++;
    }

}


void createCs(map<int, cs>& Css, int& i) {
    string T;
    cout << "Do you want to create your own cs? [Y/N]\n";
    getline(cin, T);
    logMessage(T);
    if (T == "Y" || T == "y") {
        string entName;
        int entNum;
        int entWork;
        int entEff;
        cout << "Enter a name" << endl;
        getline(cin, entName);
        logMessage(entName);
        entNum = check_int(3, 0);
        entWork = check_int(4, entNum);
        entEff = check_int(5, 0);
        Css[i] = cs(entName, entNum, entWork, entEff);
        cout << "GGG" << endl;
        i++;
    }
    else {
        Css[i] = cs();
        i++;
    }

}
void showPipe(map<int, pipe>& Pipes) {
    if (!Pipes.empty()) {
        cout << "Your's pipes:" << endl;
        for (const auto& pipe : Pipes) {
            cout << "Pipe id = " << pipe.first << endl;
            cout << pipe.second << endl;
        }
    }
    else {
        cout << "You haven't created any pipes yet\n";
    }
}
void showCs(const map<int, cs> Css) {
    if (Css.size() > 0) {
        cout << "Your's css:" << endl;
        for (auto& cs : Css) {
            cout << "Cs id = " << cs.first << endl;
            cout << cs.second << endl;
        }
    }
    else {
        cout << "You haven't created any css yet\n";
    }
}
void editPipe(map<int, pipe>& Pipes) {
    showPipe(Pipes);
    string A;
    string num;
    int a;
    while (true) {
        cout << "Enter the number of pipe, you want to redact (from 1 to inf)" << endl;
        getline(cin, num);
        logMessage(num);
        if (isInteger(num)) {
            a = stoi(num);
            break;
        }
        else {
            cout << "Enter the positive number!";
        }
    }
    bool T;
    T = check_bool(1);
    cout << a << endl;
    if (Pipes.size() >= a) {
        Pipes[a].SetInRepair(T);
    }
    else {
        cout << "Pipe with this number doesn't exsist" << endl;
    }
    showPipe(Pipes);
}
void editCs(map<int, cs>& Css) {
    showCs(Css);
    bool A;
    string num;
    int a;
    string T;
    while (true) {
        cout << "Enter the number of cs, you want to redact (from 1 to inf)" << endl;
        getline(cin, num);
        if (isInteger(num)) {
            a = stoi(num);
            break;
        }
        else {
            cout << "Enter the positive number!";
        }
    }
    A = check_bool(2);
    if (Css.size() >= a) {
        if (Css[a].SetNumWorkFac(A)) {
            showCs(Css);
        }
        else {
            cout << "The error in adding or removing a factory! Check the number of working factories and try again!\n";
            showCs(Css);
        }
    }
    else {
        cout << "Cs with this number doesn't exsist" << endl;
    }
}
void write_file(map<int, pipe> Pipes, map<int, cs> Css) {
    string f;
    cout << "Enter the name of file, that you want save your data" << endl;
    getline(cin, f);
    logMessage(f);
    ofstream out;
    if (f.length() < 4 || f.substr(f.length() - 4) != ".txt") {
        f += ".txt"; 
    }
    out.open(f);
    if (out.is_open())
    {
        if (Pipes.size() > 0) {
            out << "==PIPES==" << endl;
            for (const auto& pipe : Pipes) {
                out << "Pipe id: " << pipe.first << endl;
                out << "Your pipe's name: " << pipe.second.GetName() << "\n";
                out << "Your pipe's length: " << pipe.second.GetLength() << "\n";
                out << "Your pipe's diameter: " << pipe.second.GetDiameter() << "\n";
                out << "Is your pipe in repair: " << pipe.second.GetInRepair() << "\n";
                out << "\n";
            }
        }
        else {
            out << "You haven't created any pipe yet\n";
        }
        if (Css.size() > 0) {
            out << "==CSS==" << endl;
            for (const auto& cs : Css) {
                out << "Cs id: " << cs.first << endl;
                out << "Your cs's name: " << cs.second.GetName() << "\n";
                out << "Your cs's number of factories: " << cs.second.GetNumFac() << "\n";
                out << "Your cs's number of working factories: " << cs.second.GetNumWorkFac() << "\n";
                out << "Your cs's efficiency: " << cs.second.GetEff() << "\n";
                out << "\n";
            }
        }
        else {
            out << "You haven't created a cs yet\n";
        }
    }
    out.close();
    cout << "File has been written\n";
}
void read_file(map<int, pipe>& Pipes, map<int, cs>& Css, int& i, int& ic) {
    string f;
    cout << "Enter the name of file, that you want read data from" << endl;
    getline(cin, f);
    logMessage(f);
    if (f.length() < 4 || f.substr(f.length() - 4) != ".txt") {
        f += ".txt";
    }
    ifstream in(f);
    if (in.is_open()) {
        string line;
        string name1;
        string name2;
        int Num;
        int Num2;
        bool A;
        int Num3;
        int Num4;
        int idP = 0;
        int idC = 0;
        int Num5;
        int numOfLine = 0;
        bool CheckPipeOrCs;
        while (getline(in, line)) {
            numOfLine++;
            if (line == "==PIPES==") {
                CheckPipeOrCs = true;
            }
            else if (line == "==CSS==") {
                CheckPipeOrCs = false;
            }
            size_t pos = line.find(": ");
            if (pos != string::npos) {
                string value = line.substr(pos + 2);
                if (CheckPipeOrCs) {
                    if (numOfLine == 2) {
                        idP = stoi(value);
                    }
                    if (numOfLine == 3) {
                        name1 = value;
                    }
                    if (numOfLine == 4) {
                        Num = stoi(value);
                    }
                    if (numOfLine == 5) {
                        Num2 = stoi(value);
                    }
                    if (numOfLine == 6) {
                        if (value == "1") {
                            A = true;
                        }
                        else if (value == "0") {
                            A = false;
                        }
                        Pipes[idP] = pipe(name1, Num, Num2, A);

                        numOfLine = 0;
                    }
                }
                else {
                    if (numOfLine == 3) {
                        idC = stoi(value);
                    }
                    if (numOfLine == 4) {
                        name2 = value;
                    }
                    if (numOfLine == 5) {
                        Num3 = stoi(value);
                    }
                    if (numOfLine == 6) {
                        Num4 = stoi(value);
                    }
                    if (numOfLine == 7) {
                        Num5 = stoi(value);
                        Css[idC] = cs(name2, Num3, Num4, Num5);
                        numOfLine = 1;
                    }
                }
            }
        }
        i = idP;
        ic = idC;
        in.close();
    }
}
void filt(map<int, pipe>& Pipes, map<int, cs>& Css) {
    string ch;
    string h;
    int choose;
    bool A = false;
    while (true) {
        cout << "Enter what objects you want to filter: pipes or css (p/c)" << endl;
        getline(cin, ch);
        logMessage(ch);
        if (ch == "p" || ch == "P" || ch == "c" || ch == "C") {
            A = true;
            break;
        }
        else {
            cout << "Enter letter p or c!" << endl;
        }
    }
    if (ch == "p" || ch == "P") {
        while (true) {
            cout << "Enter what parameter you want to filter: name or repair. or complex filter" << endl;
            getline(cin, h);
            logMessage(h);
            if (h == "n" || h == "N" || h == "name" || h == "Name") {
                choose = 0;
                break;
            }
            else if (h == "r" || h == "R" || h == "repair" || h == "Repair") {
                choose = 1;
                break;
            }
            if (h == "c" || h == "C") {
                choose = 11;
                break;
            }
            else {
                cout << "Enter a letter n or r" << endl;
            }
        }
        if (choose == 0) {
            cout << "Enter a name, you want to find belong pipes" << endl;
            string n;
            string a;
            string h;
            getline(cin, n);
            for (int i = 0; i < Pipes.size(); i++) {
                if (Pipes[i].GetName().find(n) != string::npos) {
                    cout << (Pipes[i]) << endl;
                }
            }
            cout << "Do you want to redact these pipes? (t/f)" << endl;
            getline(cin, a);
            logMessage(a);
            if (a == "t" || a == "T" || a == "True" || a == "true") {
                cout << "Enter a new name" << endl;
                getline(cin, h);
                logMessage(h);
                for (int i = 0; i < Pipes.size(); i++) {
                    if (Pipes[i].GetName().find(n) != string::npos) {
                        Pipes[i].SetName(h);
                    }
                }
            }

        }
        if (choose == 1) {
            cout << "Enter repair parameter, you want to find belong pipes" << endl;
            string n;
            string a;
            string h;
            bool A;
            bool B;
            getline(cin, n);
            logMessage(n);
            if (n == "t" || n == "T" || n == "true" || n == "True" || n == "1") {
                A = true;
            }
            else {
                A = false;
            }
            for (int i = 0; i < Pipes.size(); i++) {
                if ((Pipes[i].GetInRepair() && A) || (!Pipes[i].GetInRepair() && !A)) {
                    cout << (Pipes[i]) << endl;
                }
            }
            cout << "Do you want to redact these pipes? (t/f)" << endl;
            getline(cin, a);
            logMessage(a);
            if (h == "t" || h == "T" || h == "True" || h == "true") {
                B = true;
            }
            else {
                B = false;
            }
            if (a == "t" || a == "T" || a == "True" || a == "true") {
                cout << "Enter a new inRepair parameter" << endl;
                getline(cin, h);
                logMessage(h);
                for (int i = 0; i < Pipes.size(); i++) {
                    if ((Pipes[i].GetInRepair() && A) || (!Pipes[i].GetInRepair() && !A)) {
                        Pipes[i].SetInRepair(B);
                    }
                }
            }
        }
        if (choose == 11) {
            string input;
            vector<int> numbers;
            string a;
            showPipe(Pipes);
            cout << "Enter numbers of pipes you want to filter (separating them with a space)" << endl;
            getline(cin, input);
            logMessage(input);
            int pos = 0;
            string token;
            while ((pos = input.find(" ")) != string::npos) {
                token = input.substr(0, pos);
                numbers.push_back(stoi(token));
                input.erase(0, pos + 1);
            }
            numbers.push_back(stoi(input));
            for (int i = 0; i < numbers.size(); i++) {
                if (Pipes.find(numbers[i]) != Pipes.end()) {
                    cout << "Pipe id: " << numbers[i] << endl;
                    cout << Pipes[numbers[i]] << endl;
                }
            }
            cout << "Do you want to redact them? (t/f)" << endl;
            getline(cin, a);
            logMessage(a);
            string h;
            string y;
            if (a == "t" || a == "T") {
                cout << "Enter a new name to these pipes or press enter to skip" << endl;
                getline(cin, h);
                if (h != " " && h != "") {
                    for (int i = 0; i < numbers.size(); i++) {
                        if (Pipes.find(numbers[i]) != Pipes.end()) {
                            Pipes[numbers[i]].SetName(h);
                        }
                    }
                }
                cout << "Enter a new name repair parameter to these pipes or press enter to skip (t/f)" << endl;
                getline(cin, y);
                logMessage(y);
                if (y != " " && y != "") {
                    for (int i = 0; i < numbers.size(); i++) {
                        if (Pipes.find(numbers[i]) != Pipes.end()) {
                            if (y == "t") {
                                Pipes[numbers[i]].SetInRepair(true);
                            }
                            else if (y == "f") {
                                Pipes[numbers[i]].SetInRepair(false);
                            }

                        }
                    }
                }
            }

        }
    }
    if (ch == "c" || ch == "C") {
        while (true) {
            cout << "Enter what parameter you want to filter: name or efficiency. Or complex filter" << endl;
            getline(cin, h);
            logMessage(h);
            if (h == "n" || h == "N" || h == "name" || h == "Name") {
                choose = 2;
                break;
            }
            else if (h == "e" || h == "E" || h == "efficiency" || h == "Efficiency") {
                choose = 3;
                break;
            }
            else if (h == "c" || h == "C") {
                choose = 22;
                break;
            }
            else {
                cout << "Enter a letter n or e" << endl;
            }
        }
        if (choose == 2) {
            cout << "Enter a name, you want to find belong css" << endl;
            string n;
            string a;
            string h;
            getline(cin, n);
            logMessage(n);
            for (int i = 0; i < Css.size(); i++) {
                if (Css[i].GetName().find(n) != string::npos) {
                    cout << Css[i] << endl;
                }
            }
            cout << "Do you want to redact these css? (t/f)" << endl;
            getline(cin, a);
            logMessage(a);
            if (a == "t" || a == "T" || a == "True" || a == "true") {
                cout << "Enter a new name" << endl;
                getline(cin, h);
                logMessage(h);
                for (int i = 0; i < Css.size(); i++) {
                    if (Css[i].GetName().find(n) != string::npos) {
                        Css[i].SetName(h);
                    }
                }
            }

        }
        if (choose == 3) {
            cout << "Enter efficiency parameter you want to filter" << endl;
            string n;
            string a;
            string h;
            int e;
            int ef;
            getline(cin, n);
            logMessage(n);
            if (isInteger(n)) {
                ef = stoi(n);
                for (int i = 0; i < Css.size(); i++) {
                    if (Css[i].GetEff() == ef) {
                        cout << Css[i] << endl;
                    }
                }
                cout << "Do you want to redact these css? (t/f)" << endl;
                getline(cin, a);
                logMessage(a);
                if (a == "t" || a == "T" || a == "True" || a == "true") {
                    cout << "Enter a new efficiency" << endl;
                    getline(cin, h);
                    logMessage(h);
                    if (isInteger(h)) {
                        e = stoi(h);
                        for (int i = 0; i < Css.size(); i++) {
                            if (Css[i].GetEff() == ef) {
                                Css[i].SetEff(e);
                            }
                        }

                    }
                }
            }
            else {
                cout << "Error in input data!!!" << endl;
            }

        }
        if (choose == 22) {
            string input;
            vector<int> numbers;
            showPipe(Pipes);
            cout << "Enter numbers of css you want to filter (separating them with a space)" << endl;
            getline(cin, input);
            logMessage(input);
            int pos = 0;
            string token;
            while ((pos = input.find(" ")) != string::npos) {
                token = input.substr(0, pos);
                numbers.push_back(stoi(token));
                input.erase(0, pos + 1);
            }
            numbers.push_back(stoi(input));
            for (int i = 0; i <= numbers.size(); i++) {
                if (Css.find(numbers[i]) != Css.end()) {
                    cout << Css[numbers[i]];
                }
            }
            cout << "Do you want to redact them?" << endl;
            string a;
            getline(cin, a);
            logMessage(a);
            string h;
            string y;
            int ia;
            if (a == "t" || a == "T") {
                cout << "Enter a new name to these css or press enter to skip" << endl;
                getline(cin, h);
                if (h != " " && h != "") {
                    for (int i = 0; i <= numbers.size(); i++) {
                        if (Css.find(numbers[i]) != Css.end()) {
                            Css[numbers[i]].SetName(h);
                        }
                    }
                }
                cout << "Enter a new efficency parameter to these pipes or press enter to skip" << endl;
                getline(cin, y);
                logMessage(y);
                if (y != " " && y != "") {
                    for (int i = 0; i <= Css.size(); i++) {
                        if (Css.find(numbers[i]) != Css.end()) {
                            if (isInteger(y)) {
                                ia = stoi(y);
                                Css[numbers[i]].SetEff(ia);
                            }

                        }
                    }
                }
            }
        }
    }
}


void delPC(map<int, pipe>& Pipes, map<int, cs>& Css) {
    string ch;
    string h;
    bool A;
    int number;
    string input;
    vector<int> numbers;
    istringstream iss(input);
    while (true) {
        cout << "Enter what objects you want to delete: pipes or css (p/c)" << endl;
        getline(cin, ch);
        logMessage(ch);
        if (ch == "p" || ch == "P") {
            A = true;
            break;
        }
        else if (ch == "c" || ch == "C") {
            A = false;
            break;
        }
        else {
            cout << "Enter letter p or c!" << endl;
        }
    }

    if (A) {

        showPipe(Pipes);
        cout << "Enter id's of pipes you want to delete (separated by a space)" << endl;
    }
    else {
        showCs(Css);
        cout << "Enter id's of css you want to delete (separated by a space)" << endl;
    }
    getline(cin, input);
    logMessage(input);
    int pos = 0;
    string token;
    while ((pos = input.find(" ")) != string::npos) {
        token = input.substr(0, pos);
        numbers.push_back(stoi(token));
        input.erase(0, pos + 1);
    }
    numbers.push_back(stoi(input));
    if (numbers.size() != 0) {
        if (A) {
            if (Pipes.size() != 0) {
                for (int i = 0; i <= Pipes.size(); i++) {
                    if (Pipes.find(numbers[i]) != Pipes.end()) {
                        Pipes.erase(numbers[i]);
                    }
                }
            }
            else {
                cout << "You don't have pipes!!!" << endl;
            }
        }
        else {
            if (Css.size() != 0) {
                for (int i = 0; i <= Css.size() + 1; i++) {
                    if ((numbers[i]) <= Css.size()) {
                        Css.erase(numbers[i]);
                    }
                }
            }
            else {
                cout << "You don't have css!!!" << endl;
            }
        }
    }
    else {
        cout << "Entered numbers are incorrect! Try again!!!" << endl;
    }

}
void createGazSet(map<int, gazset>& Gaz, map<int, pipe>& Pipes, map<int, cs>& Css,
    int& i, int& ic, int& ig, set<int>& usedPipes, set<int>& usedCs) {
    cout << "Creating a gas transportation network" << endl;
    if (Pipes.size() < 1 || Css.size() < 2) {
        cout << "You can't create a gas transportation network." << endl;
        if (Pipes.size() < 1) {
            createPipe(Pipes, i);
        }
        else {
            createCs(Css, ic);
        }
    }

    if (usedPipes.size() == Pipes.size()) {
        cout << "All pipes are in use. Creating a new pipe..." << endl;
        createPipe(Pipes, i);
    }

    showPipe(Pipes);
    string sid;
    int id;
    cout << "Enter id of pipe you want to use to create gas transportation system" << endl;

    while (true) {
        getline(cin, sid);
        id = stoi(sid);
        if (id <= (i - 1) && usedPipes.find(id) == usedPipes.end()) {
            break;
        }
        else if (usedPipes.find(id) != usedPipes.end()) {
            cout << "This pipe is already in use. Choose another one." << endl;
        }
        else {
            cout << "Enter a valid id for the pipe." << endl;
        }
    }

    usedPipes.insert(id);
    Gaz[ig].setpipe(Pipes[id], ig);

    if (usedCs.size() == Css.size()) {
        cout << "All compressor stations are in use. Creating a new compressor station..." << endl;
        createCs(Css, ic);
    }

    showCs(Css);
    string sc1id, sc2id;
    int c1id, c2id;

    cout << "Enter id of the first cs that will be the start of the gas transportation system" << endl;
    while (true) {
        getline(cin, sc1id);
        c1id = stoi(sc1id);
        if (c1id <= (ic - 1) && usedCs.find(c1id) == usedCs.end()) {
            break;
        }
        else if (usedCs.find(c1id) != usedCs.end()) {
            cout << "This cs is already in use. Choose another one." << endl;
        }
        else {
            cout << "Enter a valid id for the cs." << endl;
        }
    }

    usedCs.insert(c1id);
    Gaz[ig].setStartCs(Css[c1id], ig);
    if (usedCs.size() == Css.size()) {
        cout << "All compressor stations are in use. Creating a new compressor station..." << endl;
        createCs(Css, ic);
    }
    showCs(Css);
    cout << "Enter id of the second cs that will be the end of the gas transportation system" << endl;
    while (true) {
        getline(cin, sc2id);
        c2id = stoi(sc2id);
        if (c2id <= (ic - 1) && c2id != c1id && usedCs.find(c2id) == usedCs.end()) {
            break;
        }
        else if (usedCs.find(c2id) != usedCs.end()) {
            cout << "This cs is already in use. Choose another one." << endl;
        }
        else {
            cout << "Enter a valid id for the cs and ensure it is not the same as the first cs." << endl;
        }
    }

    usedCs.insert(c2id);
    Gaz[ig].setEndCs(Css[c2id], ig);

    cout << "Your gas transportation system has been created." << endl;
    cout << Gaz[ig].getPipe(ig) << endl;
    cout << Gaz[ig].getStartCs(ig) << endl;
    cout << Gaz[ig].getEndCs(ig) << endl;

    ig++;
}
void createConnect(map<int, gazset>& Gaz, map<int, pipe>& Pipes, map<int, cs>& Css,
    set<int>& usedPipes, set<int>& usedCs, int& ic, int& i, int& ig) {
    cout << "Creating a new connection between compressor stations." << endl;

    // Проверка наличия gazset
    if (Gaz.empty()) {
        cout << "No gas transportation systems exist yet. Create one first!" << endl;
        return;
    }

    // Выбор gazset
    cout << "Available gas transportation systems:" << endl;
    for (const auto& g : Gaz) {
        cout << "Gazset ID: " << g.first << endl;
    }

    int gazsetId;
    while (true) {
        cout << "Enter the ID of an existing gazset:" << endl;
        string input;
        getline(cin, input);

        if (isInteger(input)) {
            gazsetId = stoi(input);
            if (Gaz.find(gazsetId) != Gaz.end()) {
                break;
            }
        }
        cout << "Invalid gazset ID. Try again." << endl;
    }

    gazset& selectedGaz = Gaz[gazsetId];

    // Выбор cs, принадлежащей gazset
    int startCsId;
    while (true) {
        cout << "Enter the ID of a compressor station belonging to this gazset (it can be either cs1 or cs2):" << endl;
        string input;
        getline(cin, input);

        if (isInteger(input)) {
            startCsId = stoi(input);

            // Проверяем принадлежность к Cs1
            if (usedCs.count(startCsId)) {  // Используем count для проверки наличия
                cout << "Compressor station belongs to Cs1 of the selected gazset." << endl;
                break;
            }
        }

        cout << "Invalid compressor station ID. Try again." << endl;
    }

    // Проверка наличия доступных cs
    vector<int> availableCs;
    for (const auto& c : Css) {
        if (usedCs.find(c.first) == usedCs.end() &&
            !selectedGaz.Cs1.count(c.first) && !selectedGaz.Cs2.count(c.first)) {
            availableCs.push_back(c.first);
        }
    }

    int endCsId;
    if (availableCs.empty()) {
        cout << "No available compressor stations found. Creating a new one..." << endl;
        createCs(Css, ic);
        endCsId = ic - 1; // ID только что созданной станции
    }
    else {
        cout << "Available compressor stations:" << endl;
        for (int csId : availableCs) {
            cout << "Cs ID: " << csId << endl;
        }

        while (true) {
            cout << "Enter the ID of a compressor station not belonging to this gazset:" << endl;
            string input;
            getline(cin, input);

            if (isInteger(input)) {
                endCsId = stoi(input);
                if (find(availableCs.begin(), availableCs.end(), endCsId) != availableCs.end()) {
                    break;
                }
            }
            cout << "Invalid compressor station ID. Try again." << endl;
        }
    }

    // Проверка наличия доступных труб
    vector<int> availablePipes;
    for (const auto& p : Pipes) {
        if (usedPipes.find(p.first) == usedPipes.end()) {
            availablePipes.push_back(p.first);
        }
    }

    int pipeId;
    if (availablePipes.empty()) {
        cout << "No available pipes found. Creating a new one..." << endl;
        createPipe(Pipes, i);
        pipeId = i - 1; // ID только что созданной трубы
    }
    else {
        cout << "Available pipes:" << endl;
        for (int pipe : availablePipes) {
            cout << "Pipe ID: " << pipe << endl;
        }

        while (true) {
            cout << "Enter the ID of a pipe not belonging to this gazset:" << endl;
            string input;
            getline(cin, input);

            if (isInteger(input)) {
                pipeId = stoi(input);
                if (find(availablePipes.begin(), availablePipes.end(), pipeId) != availablePipes.end()) {
                    break;
                }
            }
            cout << "Invalid or already used pipe ID. Try again." << endl;
        }
    }

    // Обновление gazset
    selectedGaz.createCon(Pipes[pipeId], Css[startCsId], Css[endCsId], ig);
    usedPipes.insert(pipeId);
    usedCs.insert(startCsId);
    usedCs.insert(endCsId);

    cout << "New connection successfully created within gazset ID " << gazsetId << "." << endl;
}
void getGaz(map<int, gazset>& Gaz) {
    if (Gaz.empty()) {
        cout << "No gas transportation systems exist." << endl;
        return;
    }

    cout << "Displaying all connections in gas transportation networks:" << endl;

    for (const auto& g : Gaz) {
        cout << "Gazset ID: " << g.first << endl;

        // Перебор всех труб в данном gazset
        for (const auto& p : g.second.Pipe) {
            cout << "  Pipe ID: " << p.first << " connects:" << endl;

            // Найти компрессорные станции, соединенные данной трубой
            auto cs1It = g.second.Cs1.find(p.first);
            auto cs2It = g.second.Cs2.find(p.first);

            if (cs1It != g.second.Cs1.end() && cs2It != g.second.Cs2.end()) {
                cout << "    CS1 ID: " << cs1It->first << ", Name: " << cs1It->second.GetName() << endl;
                cout << "    CS2 ID: " << cs2It->first << ", Name: " << cs2It->second.GetName() << endl;
            }
            else {
                cout << "    Connection information is incomplete." << endl;
            }
        }
    }
}
void topolsort(map<int, gazset>& Gaz) {
    cout << "Creating a new connection between compressor stations." << endl;

    // Проверка наличия gazset
    if (Gaz.empty()) {
        cout << "No gas transportation systems exist yet. Create one first!" << endl;
        return;
    }

    // Выбор gazset
    cout << "Available gas transportation systems:" << endl;
    for (const auto& g : Gaz) {
        cout << "Gazset ID: " << g.first << endl;
    }

    int gazsetId;
    while (true) {
        cout << "Enter the ID of an existing gazset:" << endl;
        string input;
        getline(cin, input);

        if (isInteger(input)) {
            gazsetId = stoi(input);
            if (Gaz.find(gazsetId) != Gaz.end()) {
                break;
            }
        }
        cout << "Invalid gazset ID. Try again." << endl;
    }

    gazset& selectedGaz = Gaz[gazsetId];
    selectedGaz.topologicalSort();
}
int main() {
    int i = 0;
    int ic = 0;
    int ig = 0;
    logMessage("Program started");
    string line;
    map<int, pipe> Pipes;
    map<int, cs> Css;
    map<int, gazset> Gaz;
    set<int> usedPipes;
    set<int> usedCs;
    while (true) {
        int choose = getChoose();
        switch (choose) {
        case 1: {
            createPipe(Pipes, i);
            break;
        }
        case 2:
            createCs(Css, ic);
            break;
        case 3:
            showPipe(Pipes);
            showCs(Css);
            break;
        case 4: {
            editPipe(Pipes);
            break;
        }
        case 5:
            editCs(Css);
            break;
        case 6:
            write_file(Pipes, Css);
            break;
        case 7:
        {
            read_file(Pipes, Css, i, ic);
            break;
        }
        case 8: {
            filt(Pipes, Css);
            break;
        }
        case 9: {
            delPC(Pipes, Css);
            break;
        }
        case 10: {
            createGazSet(Gaz,Pipes, Css,i,ic,ig,usedPipes,usedCs);
            break;
        }
        case 11: {
            createConnect(Gaz, Pipes, Css, usedPipes, usedCs, ic,i, ig);
            break;
        }
        case 12: {
            getGaz(Gaz);
            break;
        }
        case 13: {
            topolsort(Gaz);
            break;
        }
        case 0:
            logMessage("Program finished");
            return 0;
        }
    }
    return 0;
}


