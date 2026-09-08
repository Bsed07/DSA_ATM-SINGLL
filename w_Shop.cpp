#include <iostream>
#include <string>

struct Account{

    std::string acc_No;
    std::string acc_Name;
    std::string b_day;
    std::string c_Num;
    std::string pin;
    double balance;

    Account(std::string accNo, std::string accName, std::string bday, std::string cNum, std::string pinCode, double bal){
    acc_No = accNo;
    acc_Name = accName;
    b_day = bday; 
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
        Node *curr, *prev;
        curr = head;

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

    void Delete_Node(std::string accNo){

        if(head == NULL){
            std::cout << "No current account is in the database yet." << std::endl;
            return;
        }

        if(head->data.acc_No == accNo){
            Node* temp = head;
            head = head->next;
            delete temp;
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

    Node* Search_node(std::string accNo){
        Node *curr = head;
        while(curr != NULL){
            if(curr->data.acc_No == accNo){
                return curr;
            }
            curr = curr->next;
        }
        return NULL;
    }

};
