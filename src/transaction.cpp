#include "transaction.h"
#include <sstream>
#include <cstdlib> //for rand()
#include <iostream> //for time()
#include <time.h>

using namespace std;

transaction::transaction(int amt, std::string sender,std::string receiver){
	amount = amt;
	this->sender = sender;
	this->receiver = receiver;
}

void transaction::generateNonce(){
	this->nonce = "";
	srand(time(NULL));
	int randLength = rand()%15 + 5;
	int randVal;
	for(int i = 0; i < randLength; i++){
		randVal = rand()% 26 + 97;
		this->nonce += char(randVal);
	}
}

string transaction::toString(){
	ostringstream oss;
  
	oss << "Transaction\n" 
	    << "Amount: " << this->amount << ",\n"
	    << "Sender: " << this->sender << ",\n"
	    << "Receiver: " << this->receiver << ",\n"
	    << "Nonce: " << ((this->nonce == "")?"none":this->nonce) << ",\n"
	    << "Hash: " << ((this->hash == "")?"none":this->hash);
	return oss.str();
}