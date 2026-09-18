#include <iostream>
#include <string>
#include <iomanip>
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
        bool ValidDate = false;
        int daysInMonth[] = { 31, 100, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        do {
            cout << "Enter birthday (MM/DD/YYYY): ";
            cin >> month >> day >> year;
            if (month < 1 || month > 12) {
                cout << "Invalid month. Please try again." << endl;
                continue;
            }
            // Check for leap year under construction
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (isLeapYear && month == 2) {
                daysInMonth[1] = 29; // February gets 29 days in a leap year
            } else {
                daysInMonth[1] = 28; // Reset February to 28 days 
            }

            if (day < 1 || day > daysInMonth[month - 1]) {
                cout << "Invalid day for the given month. Please try again." << endl;
                continue;
            }

            if (year < 1900 || year > 2025) {
                cout << "Invalid year. Please try again." << endl;
                continue;
            }
           
        } while (!ValidDate);
        return to_string(month) + "/" + to_string(day) + "/" + to_string(year);
    }

    string GenerateAccountNum(){
       string accNo;
       // srand(time(0));  put this at top of main()
        do {
        int num = rand() % 90000 + 10000;   // always 5 digits: 10000–99999
        accNo = to_string(num);
    } while (Search_node(accNo) != NULL);  // regenerate on collision

    return accNo;
}


void CreateAccount() {
    string name, bday, contact, pin;
    double initialDeposit;

    cout << "=== CREATE NEW ACCOUNT ===\n";
    cout << "Enter Full Name: ";
    cin.ignore(); // Clear input buffer
    getline(cin, name);
    cout << "Enter Birthday (MM/DD/YYYY): ";
    getline(cin, bday);
    cout << "Enter Contact Number: ";
    getline(cin, contact);
    cout << "Enter PIN(4-6 characters): ";
    getline(cin, pin);
    cout << "Enter Initial Deposit Amount: PHP ";
    cin >> initialDeposit;

    // 1. Automatically generate the unique 5-digit ID
    string generatedNo = GenerateAccountNum();

    // TODO: Encrypt your PIN here before saving it!

    // 2. Create the Account object
    Account newAcc(generatedNo, name, bday, contact, pin, initialDeposit);

    // 3. Insert it into the linked list
    Insert_Node(newAcc);

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
        cout << "----------------------------------------------\n";
        curr = curr->next; // Move to the next account
    }
}

};




int main(){
    srand(time(0));  // seed random number generator
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
                cout << "Account created successfully!" << endl;
                break;
            case 2:
                ATM.Display_All();
                break;
            case 3:
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
 
    return 0;
}

