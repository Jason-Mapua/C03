#include <iostream>
#include <unistd.h>
#include <windows.h>
using namespace std;

const int MAX = 10;
int lastResult = 0;

void menu();
void runChoice(int);
void temperature();
void windmill();
void invalid();
void calculator();
void getEquation(char[]);
void drawFrame(int);
void sleepWrapper(int);
void printResult(int);
int getChoice();
int compute(char[]);
int calculateExponent(int, int);
int toCelsius(int, char);
int fromCelsius(int, char);

int charToInt(char c) { return c - '0'; }
int calculateAddition(int a, int b) { return a + b; }
int calculateSubtraction(int a, int b) { return a - b; }
int calculateMultiplication(int a, int b) { return a * b; }
int calculateDivision(int a, int b) { return a / b; }

void menu() {
    cout << " 1 Calculator" << endl;
    cout << " 2 Temperature" << endl;
    cout << " 3 Windmill" << endl;
    cout << " 4 Exit" << endl;
}

int getChoice() {
    int c;
    cout << "Choice: ";
    cin >> c;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        return -1;
    }
    return c;
}

void runChoice(int c) {
    if (c == 1) calculator();
    else if (c == 2) temperature();
    else if (c == 3) windmill();
    else if (c == 4) exit(0);
    else invalid();
}

void invalid() {
    cout << "Invalid input" << endl;
}

void getEquation(char eq[]) {
    cout << "Enter equation (0-9 + - * / ^ =) NOTE: Only single digits are accepted:" << endl;
    for (int i = 0; i < MAX; i++) {
        cin >> eq[i];
        if (eq[i] == '=') break;
    }
}

int calculateExponent(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) result = calculateMultiplication(result, base);
    return result;
}

int compute(char eq[]) {
    int result = charToInt(eq[0]);
    for (int i = 1; i < MAX; i++) {
        if (eq[i] == '=') break;
        char op = eq[i];
        int next = charToInt(eq[i + 1]);
        if (op == '+') {
            result = calculateAddition(result, next);
        } else if (op == '-') {
            result = calculateSubtraction(result, next);
        } else if (op == '*') {
            result = calculateMultiplication(result, next);
        } else if (op == '/') {
            if (next == 0) return 0;
            result = calculateDivision(result, next);
        } else if (op == '^') {
            result = calculateExponent(result, next);
        }
        i++;
    }
    lastResult = result;
    return result;
}

void printResult(int n) {
    cout << "Result: " << n << endl;
}

void calculator() {
    char eq[MAX];
    getEquation(eq);
    printResult(compute(eq));
}

int toCelsius(int val, char unit) {
    if (unit == 'F') return (val - 32) * 5 / 9;
    if (unit == 'K') return val - 273;
    return val;
}

int fromCelsius(int val, char unit) {
    if (unit == 'F') return val * 9 / 5 + 32;
    if (unit == 'K') return val + 273;
    return val;
}

void temperature() {
    int t1, t2;
    char unit1, unit2, mode, outUnit;
    cout << "Temp 1: "; cin >> t1;
    cout << "Unit (C/F/K): "; cin >> unit1;
    cout << "Temp 2: "; cin >> t2;
    cout << "Unit (C/F/K): "; cin >> unit2;
    cout << "Add or Subtract (A/S): "; cin >> mode;
    cout << "Output unit (C/F/K): "; cin >> outUnit;
    int c1 = toCelsius(t1, unit1);
    int c2 = toCelsius(t2, unit2);
    int res;
    if (mode == 'A') res = calculateAddition(c1, c2);
    else if (mode == 'S') res = calculateSubtraction(c1, c2);
    else { invalid(); return; }
    printResult(fromCelsius(res, outUnit));
}

void sleepWrapper(int microsec) {
    Sleep(microsec / 1000);
}

void drawFrame(int frame) {
    system("cls");
    if (frame % 2 == 0) {
        cout << "  |  " << endl;
        cout << "--+--" << endl;
        cout << "  |  " << endl;
    } else {
        cout << " \\ / " << endl;
        cout << "  +  " << endl;
        cout << " / \\ " << endl;
    }
}

void windmill() {
    int size, speed;
    cout << "Enter size (odd): "; cin >> size;
    if (size % 2 == 0) { invalid(); return; }
    cout << "Enter speed (microseconds): "; cin >> speed;
    if (speed <= 0) { invalid(); return; }
    for (int i = 0; i < 10; i++) {
        drawFrame(i);
        sleepWrapper(speed);
    }
}

int main() {
    int c = 0;
    while (c != 4) {
        menu();
        c = getChoice();
        runChoice(c);
    }
    return 0;
}
