#include <string>

struct transaction
{
	transaction(int amt, std::string sender,std::string receiver);
	void generateNonce();
	std::string toString();
	double amount;
	std::string sender;
	std::string receiver;
	std::string nonce = "";
	std::string hash = "";
	transaction *next; 
};