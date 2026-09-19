#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <ctime>

using namespace std;

struct Account{
    string acc_No;     // 5-digit account number
    string acc_Name;   // account holder's name
    string b_day;      // birthday
    string c_Num;      // contact number
    string pin;         // PIN, stored ENCRYPTED
    double balance;     // current balance
 
    // constructor - builds an Account when you already have all the values
    Account(string a, string n, string b, string c, string p, double bal){
        acc_No = a;
        acc_Name = n;
        b_day = b;
        c_Num = c;
        pin = p;
        balance = bal;
    }
 
    // default constructor - builds an empty Account (needed so Node can hold one before it's filled in)
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
        int PIN_SHIFT_KEY = 3; // Shift cipher offset used for encryption
        
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

    string GetBirthday(){
        int month, day, year;
        char slash1, slash2; // Safely catches and holds formatting characters
        bool ValidDate = false;
        int daysInMonth[] = { 31, 100, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        
        do {
            cout << "Enter birthday (MM/DD/YYYY): ";
            cin >> month >> slash1 >> day >> slash2 >> year;
            
            // 1. Check if user typed characters or symbols that broke the stream type
            if (cin.fail()) {
                cin.clear();              
                cin.ignore(1000, '\n');   
                cout << "Invalid input format. Use numbers and slashes." << endl;
                continue;
            }

            // 2. Reject inputs that lack actual forward slashes (fixes continuous number inputs like 02122000)
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
            int num = rand() % 90000 + 10000;   // always 5 digits: 10000–99999
            accNo = to_string(num);
        } while (Search_node(accNo) != NULL);  // regenerate on collision

        return accNo;
    }

    string GetMaskedPin() {
        char pin[7];         // max 6 digits + 1 slot for the terminator
        int pinLength = 0;   // how many digits typed so far
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

            // Rule 1: Catch users typing letters, symbols, or nothing at all
            if (cin.fail()) {
                cin.clear();              // Reset the stream error flags
                cin.ignore(1000, '\n');   // Purge the broken data line completely
                cout << "Invalid numeric format. Please enter a valid number.\n" << endl;
                continue;
            }

            // Rule 2: Enforce the strict business limit of PHP 5,000.00
            if (deposit < 5000.0) {
                cout << "Deposit denied. The minimum initial deposit required is PHP 5,000.00.\n" << endl;
                continue;
            }

            // If it passes both checks, clear the remaining buffer line and break out
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
};

int main(){
    srand(time(0));  
    Account_List ATM;

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
