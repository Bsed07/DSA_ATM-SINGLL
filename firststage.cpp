#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

struct Account{
    string acc_No;
    string acc_Name;
    string b_day;
    string c_Num;
    string pin;
    double balance;

    Account(string a, string n, string b, string c, string p, double bal){
        acc_No = a;
        acc_Name = n;
        b_day = b;
        c_Num = c;
        pin = p;
        balance = bal;
    }

    Account(){
        balance = 0.0;
    }
};

struct Node{
    Account data;
    Node* next;
    Node(Account acc){
        data = acc;
        next = NULL;
    }
};


class Account_List{
    private:
        Node *head;
        int PIN_SHIFT_KEY = 3;

        Node* Search_node(string accNo){
            Node *curr = head;
            while(curr != NULL){
                if(curr->data.acc_No == accNo){
                    return curr;
                }
                curr = curr->next;
            }
            return NULL;
        }

    public:
    Account_List(){
        head = NULL;
    }

    void Insert_Node(Account s){
        Node* newNode = new Node(s);
        if(head == NULL){
            head = newNode;
            return;
        }
        Node* curr = head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = newNode;
    }

    bool AccountExists(string accNo){
        if(Search_node(accNo) == NULL){
            return false;
        }
        return true;
    }


    string GetBirthday(){
        int month, day, year;
        char slash1, slash2;
        bool ValidDate = false;
        int daysInMonth[] = { 31, 100, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        do {
            cout << "Enter birthday (MM/DD/YYYY): ";
            cin >> month >> slash1 >> day >> slash2 >> year;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input format. Use numbers and slashes." << endl;
                continue;
            }

            if (slash1 != '/' || slash2 != '/') {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid format. You must use slashes (/). Example: 02/12/2000" << endl;
                continue;
            }

            if (month < 1 || month > 12) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid month. Please try again." << endl;
                continue;
            }

            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (isLeapYear && month == 2) {
                daysInMonth[1] = 29;
            } else {
                daysInMonth[1] = 28;
            }

            if (day < 1 || day > daysInMonth[month - 1]) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid day for the given month. Please try again." << endl;
                continue;
            }

            if (year < 1900 || year > 2026) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid year. Please try again." << endl;
                continue;
            }

            ValidDate = true;
            cin.ignore(1000, '\n');

        } while (!ValidDate);

        string monthStr = (month < 10) ? "0" + to_string(month) : to_string(month);
        string dayStr = (day < 10) ? "0" + to_string(day) : to_string(day);
        string yearStr = to_string(year);
        return monthStr + "/" + dayStr + "/" + yearStr;
    }

    string GenerateAccountNum(){
       string accNo;
       do {
            int num = rand() % 90000 + 10000;
            accNo = to_string(num);
        } while (Search_node(accNo) != NULL);

        return accNo;
    }

    string GetMaskedPin() {
        char pin[7];
        int pinLength = 0;
        char ch;

        cout << "Enter PIN (4-6 digits, then press ENTER): ";

        while(true){
            ch = _getch();

            if(ch == '\r'){
                if(pinLength >= 4){
                    cout << endl;
                    break;
                }
                else{
                 continue;
                }
            }
            else if(ch == '\b'){
                if(pinLength == 0){
                    continue;
                }
                pinLength = pinLength - 1;
                cout << "\b \b";
            }
            else if(ch >= '0' && ch <= '9'){
                if(pinLength < 6){
                    pin[pinLength] = ch;
                    pinLength = pinLength + 1;
                    cout << '*';
                }
            }
        }

        pin[pinLength] = '\0';
        return string(pin);
    }

    string encryptPin(string plainPin){
        string encryptedPin = plainPin;
        for(size_t i = 0; i < encryptedPin.size(); i++){
             int originalDigit = encryptedPin[i] - '0';
             int shiftedDigit = (originalDigit + PIN_SHIFT_KEY) % 10;
             encryptedPin[i] = char('0' + shiftedDigit);
        }
        return encryptedPin;
    }

    string decryptPin(string encryptedPin){
        string decryptedPin = encryptedPin;
        for(size_t i = 0; i < decryptedPin.size(); i++){
            int shiftedDigit = decryptedPin[i] - '0';                         
            int originalDigit = (shiftedDigit - PIN_SHIFT_KEY + 10) % 10;     
            decryptedPin[i] = char('0' + originalDigit);                      
        }
        return decryptedPin;
    }
    

    string GetContactNumber(){
        string contact;
        bool isValid = false;

        do {
            cout << "Enter Contact Number (11 digits, e.g., 09171234567):";
            getline(cin, contact);

            if (contact.size()!=11){
                cout << "Invalid Length. The number must be exactly 11 digits long.\n";
                continue;
            }

            if (contact[0] != '0' || contact[1] != '9'){
                cout << "invalid prefix. Philippine mobile numbers must start with '09'.\n" << endl;
                continue;
            }

            bool hasNoneDigit = false;
            for (size_t i = 0; i < contact.size(); i++){
                if (contact[i] < '0' || contact[i] > '9') {
                    hasNoneDigit = true;
                    break;
                }
            }
            if (hasNoneDigit) {
                cout << "Invalid characters detected. The number must only contain digits.\n" << endl;
                continue;
            }

            isValid = true;

        } while (!isValid);

        return contact;
    }

    double GetInitialDeposit() {
        double deposit;
        bool isValid = false;

        do {
            cout << "Enter Initial Deposit Amount (Minimum PHP 5,000.00): PHP ";
            cin >> deposit;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid numeric format. Please enter a valid number.\n" << endl;
                continue;
            }

            if (deposit < 5000.0) {
                cout << "Deposit denied. The minimum initial deposit required is PHP 5,000.00.\n" << endl;
                continue;
            }

            cin.ignore(1000, '\n');
            isValid = true;

        } while (!isValid);

        return deposit;
    }

    void CreateAccount() {
        string name;


        cout << "=== CREATE NEW ACCOUNT ===\n";
        cout << "Enter Full Name: ";
        cin.ignore();
        getline(cin, name);

        string bday = GetBirthday();
        string contact = GetContactNumber();

        string pin = GetMaskedPin();
        string encryptedPin = encryptPin(pin);

        double initialDeposit = GetInitialDeposit();

        string generatedNo = GenerateAccountNum();

        Account newAcc(generatedNo, name, bday, contact, encryptedPin, initialDeposit);
        Insert_Node(newAcc);

        cout << "\nAccount created successfully! Saved Account No: " << generatedNo << endl;
    }

    void Display_All() {
        if (head == NULL) {
            cout << "No accounts found in the system.\n";
            return;
        }

        Node* curr = head;
        cout << "\n================ ALL ACCOUNTS ================\n";
        while (curr != NULL) {
            cout << "Account No : " << curr->data.acc_No << endl;
            cout << "Name       : " << curr->data.acc_Name << endl;
            cout << "Birthday   : " << curr->data.b_day << endl;
            cout << "Contact    : " << curr->data.c_Num << endl;
            cout << "Balance    : PHP " << fixed << setprecision(2) << curr->data.balance << endl;
            cout << "PIN (Secure): " << curr->data.pin << " (Encrypted)" << endl;
            cout << "----------------------------------------------\n";
            curr = curr->next;
        }
    }

    void SaveInfo(){
        ofstream outFile("ATMDATA.csv");

        Node* curr = head;
        while(curr != NULL){
            outFile << curr->data.acc_No << ","
                    << curr->data.acc_Name << ","
                    << curr->data.b_day << ","
                    << curr->data.c_Num << ","
                    << curr->data.pin << ","
                    << curr->data.balance << endl;
                curr = curr->next;
            }

            outFile.close();
        }

    void RetrieveInfo(){
        ifstream inFile("ATMDATA.csv");

        if(!inFile){
            return; // no save file yet - nothing to load, list just stays empty
        }

        string line;
        while(getline(inFile, line)){
            if(line.empty()){
                continue; // skip blank lines
            }

            stringstream ss(line);
            string accNo, accName, bday, cNum, pin, balanceStr;

            getline(ss, accNo, ',');
            getline(ss, accName, ',');
            getline(ss, bday, ',');
            getline(ss, cNum, ',');
            getline(ss, pin, ',');
            getline(ss, balanceStr, ',');

            // crash-guard: if any field failed to parse, skip this row instead of crashing
            if(accNo.empty() || balanceStr.empty()){
                cout << "Skipped a corrupted row: " << line << endl;
                continue;
            }

            double balance = stod(balanceStr);
            Insert_Node(Account(accNo, accName, bday, cNum, pin, balance));
        }

        inFile.close();
    }

};

int main(){
    srand(time(0));
    Account_List ATM;
    ATM.RetrieveInfo();

    string cardPath = "ATMCard.txt"; // will later point at a real USB path

    // ============================================================
    // CARD GATE - nothing below this loop is reachable without a card
    // ============================================================
    bool cardFound = false;
    while(!cardFound){
        ifstream cardCheck(cardPath);

        if(!cardCheck){
            cout << "Please insert card." << endl;
            cout << "Press ENTER once your card is inserted, or type 3 then ENTER to exit: ";
            string response;
            getline(cin, response);

            if(response == "3"){
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            }
            continue; // check again
        }

        cardFound = true;
        cardCheck.close();
    }

    cout << "Card detected." << endl;

    // ============================================================
    // BLANK vs. ALREADY-REGISTERED CARD DETECTION
    // ============================================================
    ifstream cardContent(cardPath);
    string cardLine;
    getline(cardContent, cardLine); // reads the first (and only) line on the card
    cardContent.close();

    if(cardLine.empty()){
        cout << "This card has no account on it yet. (New registration flow goes here.)" << endl;
    }
    else{
        stringstream cardStream(cardLine);
        string cardAccNo, cardPin;
        getline(cardStream, cardAccNo, ',');
        getline(cardStream, cardPin, ',');

        cout << "Card claims account number: " << cardAccNo << endl;

        if(ATM.AccountExists(cardAccNo)){
            cout << "This account number exists in our records. (PIN check goes here next.)" << endl;
        }
        else{
            cout << "No account with this number exists in our records. Card rejected." << endl;
        }
    }

    while (true) {
        cout << "\n=== ATM SYSTEM ===\n";
        cout << "1. Create New Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Exit\n";
        cout << "Select an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                ATM.CreateAccount();
                ATM.SaveInfo();
                break;
            case 2:
                ATM.Display_All();
                break;
            case 3:
                cout << "Exiting the system. Goodbye!"<< endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}