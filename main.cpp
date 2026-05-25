#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <conio.h>
#include <windows.h>
using namespace std;

string selectedSubject = "";
string selectedDifficulty = "";
string playerName = "";
int playerID = 0;

struct Question {
    string question;
    string options[4];
    char correct = ' ';
};

string calculateGrade(int correct, int total) {
    double percent = (double)correct / total * 100;
    if (percent >= 90) return "A+";
    else if (percent >= 80) return "A";
    else if (percent >= 70) return "B";
    else if (percent >= 60) return "C";
    else if (percent >= 50) return "D";
    else return "F";
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gradeComment(const string& grade) {
    if (grade == "A+") { setColor(10); cout << "\nExcellent! You're a quiz master!\n"; }
    else if (grade == "A") { setColor(9); cout << "\nGreat job! You did really well!\n"; }
    else if (grade == "B") { setColor(11); cout << "\nGood effort! Keep improving!\n"; }
    else if (grade == "C") { setColor(14); cout << "\nNot bad, but you can do better!\n"; }
    else if (grade == "D") { setColor(6); cout << "\nNeeds improvement. Keep practicing!\n"; }
    else { setColor(12); cout << "\nFailed. Don't give up, try again!\n"; }
    setColor(7);
}

void instructions() {
    system("cls");
    setColor(11);
    cout << "\t\t\t\t==================== QUIZ INSTRUCTIONS ====================\t\t\t\t\n\n";
    setColor(7);
    Beep(750, 300); Sleep(200);
    cout << "1. Enter your name before starting the quiz.\n"; Beep(650, 200); Sleep(200);
    cout << "2. Select subject and difficulty first (if not already selected).\n"; Beep(700, 200); Sleep(200);
    cout << "3. Each question has 4 options (A-D).\n"; Beep(750, 200); Sleep(200);
    cout << "4. You have 10 seconds per question.\n"; Beep(800, 200); Sleep(200);
    cout << "5. No negative marking.\n"; Beep(850, 300); Sleep(300);

    setColor(11);
    cout << "\n\n\t\t\t\t==================== GRADE CALCULATION ====================\t\t\t\t\n\n";
    setColor(7);
    Beep(900, 200); Sleep(200);
    setColor(10);
    cout << "90% and above -> A+\n";
    setColor(9);
    cout << "80% - 89%     -> A\n";
    setColor(11);
    cout << "70% - 79%     -> B\n";
    setColor(14);
    cout << "60% - 69%     -> C\n";
    setColor(6);
    cout << "50% - 59%     -> D\n";
    setColor(12);
    cout << "Below 50%     -> F\n\n";
    
    Beep(1000, 300); Sleep(300);
    system("pause");
}

string getFileName() {
    string pathBase = "C:\\Users\\user\\source\\repos\\Project PF\\Project PF\\";
    if (selectedSubject == "PF") {
        if (selectedDifficulty == "Easy") return pathBase + "pf easy.txt";
        if (selectedDifficulty == "Medium") return pathBase + "pf med.txt";
        if (selectedDifficulty == "Hard") return pathBase + "pf hard.txt";
    }
    if (selectedSubject == "DLD") {
        if (selectedDifficulty == "Easy") return pathBase + "dld easy.txt";
        if (selectedDifficulty == "Medium") return pathBase + "dld med.txt";
        if (selectedDifficulty == "Hard") return pathBase + "dld hard.txt";
    }
    if (selectedSubject == "Maths") {
        if (selectedDifficulty == "Easy") return pathBase + "maths easy.txt";
        if (selectedDifficulty == "Medium") return pathBase + "maths med.txt";
        if (selectedDifficulty == "Hard") return pathBase + "maths hard.txt";
    }
    return "";
}

void startQuiz() {
    system("cls");
    if (playerName.empty()) {
        cout << "\nEnter your name: ";
        cin.ignore();
        getline(cin, playerName);
        srand(time(0));
        playerID = rand() % 9000 + 1000;
        setColor(10);
        cout << "\nHello " << playerName << "! Your Player ID: " << playerID << endl;
        setColor(7);
        Beep(800, 200); Sleep(200);
    }

    if (selectedSubject.empty()) {
        int ch;
        cout << "\nSELECT SUBJECT:\n\n1. Programming Fundamental (PF)\n2. Digital Logic And Design (DLD)\n3. Maths\n\nEnter choice: ";
        cin >> ch;
        if (ch == 1) selectedSubject = "PF";
        else if (ch == 2) selectedSubject = "DLD";
        else if (ch == 3) selectedSubject = "Maths";
        else { cout << "Invalid choice! Defaulting to PF.\n"; selectedSubject = "PF"; }
        cout << "Subject selected: " << selectedSubject << endl;
        Beep(750, 200); Sleep(200);
    }

    if (selectedDifficulty.empty()) {
        int ch;
        cout << "\nSELECT DIFFICULTY:\n\n1. Easy\n2. Medium\n3. Hard\n\nEnter choice: ";
        cin >> ch;
        if (ch == 1) selectedDifficulty = "Easy";
        else if (ch == 2) selectedDifficulty = "Medium";
        else if (ch == 3) selectedDifficulty = "Hard";
        else { cout << "Invalid choice! Defaulting to Easy.\n"; selectedDifficulty = "Easy"; }
        cout << "Difficulty selected: " << selectedDifficulty << endl;
        if (selectedDifficulty == "Easy") setColor(10);
        else if (selectedDifficulty == "Medium") setColor(14);
        else if (selectedDifficulty == "Hard") setColor(12);
        cout << "Difficulty Highlighted!\n"; setColor(7);
        Beep(750, 200); Sleep(200);
    }

    string filename = getFileName();
    ifstream fin(filename);
    if (!fin) { cout << "Questions file not found!\n"; Beep(1000, 300); Sleep(300); return; }

    int totalQ = 0;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        totalQ++;
        for (int i = 0; i < 5; i++) getline(fin, line);
        getline(fin, line);
    }
    fin.clear();
    fin.seekg(0);

    Question* questions = new Question[totalQ];
    int qIndex = 0;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        questions[qIndex].question = line;
        for (int i = 0; i < 4; i++) getline(fin, questions[qIndex].options[i]);
        getline(fin, line);
        questions[qIndex].correct = toupper(line[0]);
        getline(fin, line);
        qIndex++;
    }
    fin.close();

    srand(time(0));
    for (int i = 0; i < totalQ; i++) swap(questions[i], questions[rand() % totalQ]);

    int quizCount = (totalQ > 10) ? 10 : totalQ;
    int correctCount = 0;
    int attempted = 0;

    for (int i = 0; i < quizCount; i++) {
        system("cls");
        setColor(11);
        cout << "=================== QUESTION " << i + 1 << " ===================\n\n";
        setColor(7);
        cout << questions[i].question << endl;
        cout << "\nA. " << questions[i].options[0] << endl;
        cout << "B. " << questions[i].options[1] << endl;
        cout << "C. " << questions[i].options[2] << endl;
        cout << "D. " << questions[i].options[3] << endl;

        cout << "\nAnswer (A-D) in 10 seconds: ";
        setColor(11);
        char ans = ' ';
        time_t start = time(0);

        while (difftime(time(0), start) < 10) {
            if (_kbhit()) {
                char ch = toupper(_getch());
                if (ch >= 'A' && ch <= 'D') {
                    ans = ch;
                    cout << ans << endl;
                    break;
                }
            }
            Sleep(50);
        }

        if (ans != ' ') attempted++;

        if (ans == ' ') {
            setColor(12);
            cout << "\nTime Over! You did not answer.\n";
            Beep(400, 200);
            setColor(7);
            cout << "Correct answer: " << questions[i].correct << endl;
            Sleep(2000);
        }
        else if (ans == questions[i].correct) {
            setColor(10);
            cout << "Correct!\n";
            Beep(1200, 200);
            setColor(7);
            correctCount++;
            Sleep(1500);
        }
        else {
            setColor(12);
            cout << "Wrong! Correct answer: " << questions[i].correct << endl;
            Beep(400, 200);
            setColor(7);
            Sleep(1500);
        }
    }
    string grade = calculateGrade(correctCount, quizCount);
    system("cls");
    setColor(13);
    cout << "\n=================== QUIZ RESULT ===================\n\n";
    setColor(7);
    cout << "Player Name: " << playerName << endl;
    cout << "Player ID: " << playerID << endl;
    cout << "Subject: " << selectedSubject << endl;
    cout << "Difficulty: " << selectedDifficulty << endl;
    cout << "Total Questions: " << quizCount << endl;
    cout << "Attempted: " << attempted << endl;
    cout << "Correct Answers: " << correctCount << endl;
    cout << "Grade: " << grade << endl;
    gradeComment(grade);
    Beep(1500, 300); Sleep(5000);

    ofstream fout("results.txt", ios::app);
    if (fout) {
        fout << "Player: " << playerName << " | ID: " << playerID
            << " | Subject: " << selectedSubject
            << " | Difficulty: " << selectedDifficulty
            << " | Total Questions: " << quizCount
            << " | Attempted: " << attempted
            << " | Correct: " << correctCount
            << " | Grade: " << grade << endl;
    }
    fout.close();

    delete[] questions;
}

void viewResults() {
    system("cls");
    ifstream fin("results.txt");
    string line;
    setColor(11);
    cout << "\n=================== PREVIOUS RESULTS ===================\n\n";
    setColor(7);
    while (getline(fin, line)) cout << line << endl;
    fin.close();
    system("pause");
}

int main() {
    int choice;
    do {
        system("cls");
        setColor(14);
        cout << "\n\t\t\t\t\t\t=======================================================\t\t\t\t\t\t\n";
        cout << "\t\t\t\t\t\t                WELCOME TO QUIZ GENERATOR              \t\t\t\t\t\t\n";
        cout << "\t\t\t\t\t\t=======================================================\t\t\t\t\t\t\n";
        setColor(7);
        cout << "\n\n1. Start Quiz\n";
        cout << "\n2. Instructions\n";
        cout << "\n3. View Results\n";
        cout << "\n4. Exit\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: startQuiz(); break;
        case 2: instructions(); break;
        case 3: viewResults(); break;
        case 4: cout << "Thank you!\n"; break;
        default: cout << "Invalid choice!\n"; system("pause");
        }
    } while (choice != 4);

    return 0;
}
