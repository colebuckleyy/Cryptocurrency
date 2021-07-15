#pragma once

#include "Account.h"

class Transaction
{
protected:
	std::string fromAddress;
	std::string toAddress;
	uint32_t amount;
public:
	Transaction(std::string fromAddress, std::string toAddress, uint32_t amount);

	std::string transactString();

	std::string getFromAddress();
	std::string getToAddress();
	uint32_t getAmount();

	unsigned char* hashTransaction();

	bool transactionSigner(Account);
};

