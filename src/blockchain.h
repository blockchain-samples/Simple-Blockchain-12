#include <string>
#include "transaction.h"

class blockchain{
public:
	void addTransaction(int amount, std::string sender, std::string receiver);
	void printSenders(std::string sender);
	void printReceivers(std::string receiver);
	void print();
	bool verify();
	~blockchain();
private:
	transaction *head = NULL;
};