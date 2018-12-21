#include "blockchain.h"
#include "../sha2/picosha2.h"
#include <iostream>

using namespace std;

//Using picosha2.h from https://github.com/okdshin/PicoSHA2

void blockchain::addTransaction(int amount, string sender, string receiver){
	transaction *newTransaction = new transaction(amount,sender,receiver);
	if(head != NULL){
		//generate a random nonce from the previous one
		head->generateNonce();
		string prevString = to_string(head->amount) + head->sender + head->receiver + head->nonce;

		//hash using picosha2
		vector<unsigned char> hash(picosha2::k_digest_size);
		picosha2::hash256(prevString.begin(), prevString.end(), hash.begin(), hash.end());
		string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());

		//continue hashing until the resulting hash ends with something between 0-4
		char lastDigit = *(hex_str.end()-1);
		while(!(lastDigit == '0' || lastDigit == '1'|| lastDigit == '2' || lastDigit == '3' || lastDigit == '4')){
			head->generateNonce();
			prevString = to_string(head->amount) + head->sender + head->receiver + head->nonce;
			vector<unsigned char> hash(picosha2::k_digest_size);
			picosha2::hash256(prevString.begin(), prevString.end(), hash.begin(), hash.end());
			hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());
			lastDigit = *(hex_str.end()-1);
		}

		//set hash to the generated hash key and set next to the current head
		newTransaction->hash = hex_str;
		newTransaction->next = head;
	}
	//update the head
	head = newTransaction;
}

void blockchain::printSenders(string sender){
	//this function prints only transactions with the input sender
	transaction *current = head;
	cout << "Printing all Transactions with sender " << sender <<" starting with the most recent." << endl;
	bool empty = true;
	while(current != NULL){
		if(current->sender == sender){
			cout << current->toString() << endl << endl;
			empty = false;
		}
		current = current->next;
	}
	if(empty){
		cout << "No transactions with sender " << sender <<" were found." <<endl;
	}
}

void blockchain::printReceivers(string receiver){
	//this function prints only transactions with the input sender
	transaction *current = head;
	cout << "Printing all Transactions with receiver " << receiver <<" starting with the most recent." << endl;
	bool empty = true;
	while(current != NULL){
		if(current->receiver == receiver){
			cout << current->toString() << endl << endl;;
			empty = false;
		}
		current = current->next;
	}
	if(empty){
		cout << "No transactions with receiver " << receiver <<" were found." <<endl;
	}
}

void blockchain::print(){
	//this function prints the entire chain
	transaction *current = head;
	cout << "Printing all Transactions starting with the most recent." << endl;
	if(head == NULL){
		cout << "This blockchain is empty." <<endl;
	}
	while(current != NULL){
		cout << current->toString() << endl << endl;;
		current = current->next;
	}
}

bool blockchain::verify(){
	transaction *current = head;
	transaction *next;
	//check that current isn't null
	if(current != NULL){
		next = head->next;
	}
	cout << "Verifying the chain." << endl;
	//traverse the chain
	while(current != NULL && next != NULL){
		//perform hash on contents of next
		string prevString = to_string(next->amount) + next->sender + next->receiver + next->nonce;
		vector<unsigned char> hash(picosha2::k_digest_size);
		picosha2::hash256(prevString.begin(), prevString.end(), hash.begin(), hash.end());
		string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());

		//compare the hash of the contents to the current hash
		if(current->hash != hex_str){
			cout << "Error found! There was a mismatching hash between these two transactions:" << endl;
			cout << current->toString() << endl
				 << next->toString() << endl;
			return false;
		}

		//update current and next
		current = current->next;
		next = current->next;
	}
	cout << "There are no errors in the chain." << endl;
	return true;
}

blockchain::~blockchain(){
	transaction *current = head;
	transaction *next;
	//check that current isn't null
	if(current != NULL){
		next = head->next;
	}
	while(current != NULL){
		delete current;
		current = next;
		if(current != NULL){
			next = current->next;
		}
	}
}
