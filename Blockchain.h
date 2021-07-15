#pragma once

#include "Block.h"

class Blockchain
{
private:
	uint32_t miningReward;
	uint32_t difficulty;

	std::vector<Block> chain;
	std::vector<Transaction> pendingTransactions;
public:
	Blockchain();
	
	std::string getPrevHash();

	void minePendingTransaction(std::string miningRewardAddress);

	void createTransaction(Transaction transaction);

	std::string getTransactionString();

	Block getLatestBlock() const;

	uint32_t getBalanceOfAddress(std::string address);

	bool isChainValid();
};

