#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <conio.h>
using namespace std;

struct Account{

    string acc_No;
    string acc_Name;
    int b_day, b_month, b_year;
    string c_Num;
    string pin;
    double balance;

    Account(string accNo, string accName, int bday, int b_m, int b_y, string cNum, string pinCode, double bal){
    acc_No = accNo;
    acc_Name = accName;
    b_day = bday;
    b_month = b_m;
    b_year = b_y;
    c_Num = cNum; 
    pin = pinCode;
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
        next = nullptr;
    }
};

class Acc_L{
    private:
    Node *head;

    public:

    Acc_L(){
        head = nullptr;
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

    void Delete_Node(string accNo){

        if(head == NULL){
            cout << "No current account is in the database yet." << endl;
            return;
        }

        if(head->data.acc_No == accNo){
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* prev = head;
        Node* curr = head->next;

        while(curr != NULL){
            if(curr->data.acc_No == accNo){
                prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

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

    string GenerateAccountNum(){
    string accNo;
       // srand(time(0)); 
    do {
        int num = rand() % 90000 + 10000;   // always 5 digits: 10000–99999
        accNo = to_string(num);
    } while (Search_node(accNo) != nullptr);  // regenerate on collision

    return accNo;
}

    string getMaskedPin(){
        string pin = "";
        char ch;
    
        cout << "Enter PIN (4-6 digits, then press ENTER): ";
    
        while(true){
            ch = _getch();
    
            if(ch == '\r'){
                if(pin.length() >= 4){
                    cout << endl;
                    break;
                }
                continue;
            }
            else if(ch == '\b'){
                if(!pin.empty()){
                    pin.pop_back();
                    cout << "\b \b";
                }
            }
            else if(ch >= '0' && ch <= '9'){
                if(pin.length() < 6){
                    pin += ch;
                    cout << '*';
                }
            }
        }
    
        return pin;
    }

    
    const int PIN_SHIFT_KEY = 3;   // how many positions each digit shifts by
    string encryptPin(string plainPin){
        string encryptedPin = plainPin;

        for(size_t i = 0; i < encryptedPin.size(); i++){
            int originalDigit = encryptedPin[i] - '0';               // char '0'-'9' -> int 0-9
            int shiftedDigit = (originalDigit + PIN_SHIFT_KEY) % 10;  // shift forward, wrap past 9
            encryptedPin[i] = char('0' + shiftedDigit);               // int 0-9 -> char '0'-'9'
            }
            return encryptedPin;
        }

    string decryptPin(string encryptedPin){
        string decryptedPin = encryptedPin;

        for(size_t i = 0; i < decryptedPin.size(); i++){
            int shiftedDigit = decryptedPin[i] - '0';                         // char -> int
            int originalDigit = (shiftedDigit - PIN_SHIFT_KEY + 10) % 10;     // shift back, +10 avoids negatives
            decryptedPin[i] = char('0' + originalDigit);                      // int -> char
            }
        return decryptedPin;
        }
    

    void reg_Nacc(){

        string w_name, coNum;
        int day, month, year;
        bool validDate = false;

        cout << "Enter your first name: ";
        cin.ignore(1000, '\n');
        getline(cin, w_name);
        cout << "Your contact number: ";
        getline(cin, coNum);

        do {
            int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
            cout << "Enter your Birthday (MM DD YYYY): ";
            cin >> month >> day >> year;

            if (month < 1 || month > 12) {
                cout << "Invalid month." << endl;
                continue;
            }
            bool l_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (month == 2 && l_year) {
                daysInMonth[1] = 29;
            }

            if (day < 1 || day > daysInMonth[month - 1]) {
                cout << "Invalid day for that month." << endl;
                continue;
            }
            validDate = true;

        } while (!validDate);

        double I_Deposit;

        do{
        cout << "Enter your Initial Deposit (min. 5000): ";
        cin >> I_Deposit;
        if (I_Deposit < 5000) {
            cout << "The deposit must be at least 5000.\n";
        }
        }while (I_Deposit < 5000);

        string accNo = GenerateAccountNum();
        string encryptedPin = encryptPin(getMaskedPin());

        Account newAcc(accNo, w_name,  day,  month,  year, coNum, encryptedPin, I_Deposit);
        Insert_Node(newAcc);

/*        saveInfo();          // rewrite ProjectData.csv with the full updated list
        SaveExternal(accNo, accName, encryptedPin);   // write ATMCard.txt
*/
        cout << "Registration successful! Your account number is " << accNo << endl;


    }

};


