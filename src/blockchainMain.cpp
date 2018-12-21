#include "blockchain.h"
#include <iostream>
#include <limits>

using namespace std;

int main(){
	blockchain list;
	cout << "Welcome to the transaction-chain application." << endl
		 << "1) Add a transaction to the chain." << endl
		 << "2) Find transactions with name of receiver or sender." << endl
		 << "3) Verify the chain." << endl
		 << "4) Exit" << endl
		 << "Which operation would you like to make? (1, 2, 3 or 4)." << endl;

	string option;
	while(true){
		getline(cin, option);
		if(option == "1"){
			cout << "Adding a transaction." << endl
				 << "Please enter the amount." << endl;
			int amount;
			cin >> amount;
			while(cin.fail()){
				string buffer;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid amount entered. Enter an integer value for amount." << endl;
				cin >> amount;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter the sender." << endl;
			string sender;
			getline(cin, sender);
			cout << "Please enter the receiver." << endl;
			string receiver;
			getline(cin, receiver);
			list.addTransaction(amount, sender, receiver);
			cout << "Transaction from " << sender <<" to " << receiver <<" for $" << amount <<" has been added to the chain." <<endl;
			cout << "Please enter 1, 2, 3 or 4 to continue." << endl;
		}else if(option == "2"){
			cout << "Enter 1 to search by sender, 2 to search by receiver: " << endl;
			string input;
			getline(cin, input);
			while(input != "1" && input != "2"){
				cout << "Invalid input enter 1 or 2." << endl;
				getline(cin, input);
			}
			string name;
			if(input == "1"){
				cout << "Enter name of sender." << endl;
				getline(cin, name);
				list.printSenders(name);
			}else if(input == "2"){
				cout << "Enter name of receiver." << endl;
				getline(cin, name);
				list.printReceivers(name);
			}
			cout << "Please enter 1, 2, 3 or 4 to continue." << endl;
		}else if(option == "3"){
			if(list.verify()){
				list.print();
			}
			cout << "Please enter 1, 2, 3 or 4 to continue." << endl;
		}else if(option == "4"){
			cout << "Exitting application";
			break;
		}else{
			cout << "Invalid input. Please select an option from 1, 2, 3 or 4." << endl;
		}
	}
}