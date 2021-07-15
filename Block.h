#pragma once

#include "Transaction.h"

class Block
{
private:
	uint32_t nonce;
	time_t timestamp;

public:
	Block(time_t ts, Transaction t, std::string previousHash);

	std::string hash;
	std::string prevHash;

	std::string transactionString;
	Transaction transaction;

	std::string calculateHash();

	void mineBlock(uint32_t nDifficulty);
	
};
