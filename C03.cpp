#include <iostream>
#include <unistd.h>

using namespace std;

const int MAX = 10;

void menu();
void runChoice(int);
void temperature();
void windmill();
void invalid();
void calculator();
void getEquation(char[]);
void windmill();
void drawFrame(int frame);
void sleepWrapper(int microsec);
void temperature();
int getChoice();
int compute(char eq[]);
int charToInt(char c) { return c - '0'; };
int calculateAddition(int a, int b) { return a + b; };
int calculateSubtraction(int a, int b) { return a - b; };
int calculateMultiplication(int a, int b) { return a * b; };
int calculateDivision(int a, int b) { return a / b; };
int toCelsius(int val, char unit);



void menu() {
    cout << " 1 Calculator" << endl;
    cout << " 2 Temperature" << endl;
    cout << " 3 Windmill" << endl;
    cout << " 4 Exit" << endl;
}

int getChoice() {
    int c;
    cin >> c;
    return c;
}

void runChoice(int c) {
    if (c==1) calculator();
    else if (c==2) temperature();
    else if (c==3) windmill();
    else if (c==4) exit(0);
    else invalid();

}

void invalid() {
    cout << "Invalid input" << endl;
}

void calculator() {
    char eq[MAX];
    getEquation(eq);
    cout<<"Result: "<<compute(eq)<<endl;
}

void getEquation(char eq[]) {
    for(int i = 0; i < MAX; i++)
    {
        cin>>eq[i];
        if(eq[i]=='=') break;
    }
}

int compute(char eq[]) {
    int result = charToInt(eq[0]);
    for (int i = 1; i < MAX; i++) {
        if (eq[i] == '=') break;
        char op = eq[i];
        int nextNum = charToInt(eq[i + 1]);
        if (op == '+') {
            result = calculateAddition(result, nextNum);
        } else if (op == '-') {
            result = calculateSubtraction(result, nextNum);
        } else if (op == '*') {
            result = calculateMultiplication(result, nextNum);
        } else if (op == '/') {
            if (nextNum == 0) return 0;
            result = calculateDivision(result, nextNum);
        } 
        i++;
    }
    return result;
}

void sleepWrapper(int microsec) {
    usleep(microsec); 
}

void drawFrame(int frame) {
    system("cls"); // Clear screen for animation
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
    cout << "Enter speed (microseconds): "; cin >> speed;
    for(int i = 0; i < 10; i++) {
        drawFrame(i);
        sleepWrapper(speed);
    }
}

int toCelsius(int val, char unit) {
    if (unit == 'F') return (val - 32) * 5 / 9;
    if (unit == 'K') return val - 273;
    return val;
}

void temperature(){
    int t1, t2;
    char mode;
    cout << "Temp 1: "; cin >> t1;
    cout << "Temp 2: "; cin >> t2;
    cout << "ADD or SUBTRACT (A/S): "; cin >> mode;
    if (mode == 'A') {
        cout << "Result: " << t1 + t2 << endl;
    } else {
        cout << "Result: " << t1 - t2 << endl;
    }
}

int main(){
    int c = 0;
    while (c !=4) {
        menu();
        c = getChoice();
        runChoice(c);
    }
    return 0;
}

    