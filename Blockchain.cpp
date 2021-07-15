#include "Blockchain.h"

Blockchain::Blockchain()
{
	chain.emplace_back(Block(time(nullptr), Transaction("GENESIS", "GENESIS", 0), ""));
	difficulty = 2;
	miningReward = 100;
}

Block Blockchain::getLatestBlock() const
{
	return chain.back();
}

std::string Blockchain::getPrevHash()
{
	return chain.back().hash;
}

void Blockchain::minePendingTransaction(std::string miningRewardAddress)
{
	Block newBlock(time(nullptr), pendingTransactions.at(pendingTransactions.size() - 1), getPrevHash());
	
	newBlock.transactionString = pendingTransactions.at(pendingTransactions.size()-1).transactString();

	newBlock.mineBlock(difficulty);

	chain.emplace_back(newBlock);

	pendingTransactions.pop_back();

	createTransaction(Transaction("", miningRewardAddress, miningReward));
}

void Blockchain::createTransaction(Transaction transaction)
{
	pendingTransactions.emplace_back(transaction);
}

uint32_t Blockchain::getBalanceOfAddress(std::string address)
{
	uint32_t balance = 0;

	for (uint32_t i = 0; i < chain.size(); i++)
	{
		if (chain.at(i).Block::transaction.getFromAddress() == address) 
			balance -= chain.at(i).Block::transaction.getAmount();

		if (chain.at(i).Block::transaction.getToAddress() == address) 
			balance += chain.at(i).Block::transaction.getAmount();
	}

	return balance;
}

bool Blockchain::isChainValid()
{
		for (uint32_t i = 0; i < chain.size(); i++)
		{
			const Block currentBlock = chain.at(i);
			const Block prevBlock = chain.at(i - 1);

			if (currentBlock.prevHash != prevBlock.hash)
				return false;
		}
		return true;
}