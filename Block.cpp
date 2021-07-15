#include "Block.h"

Block::Block(time_t ts, Transaction t, std::string previousHash)
	: timestamp(ts), transaction(t), prevHash(" ")
{
	this->hash = calculateHash();
}

void Block::mineBlock(uint32_t nDifficulty)
{
	std::cout << "Mining Block..." << std::endl;
	char* cstr = new char[nDifficulty + 1];
	for (uint32_t i = 0; i < nDifficulty; ++i)
	{
		cstr[i] = '0';
	}
	cstr[nDifficulty] = '\0';

	std::string str(cstr);

	do
	{
		nonce++;
		hash = calculateHash();
	} while (hash.substr(0, nDifficulty) != str);

	std::cout << "Block mined: " << hash << std::endl;
}

inline std::string Block::calculateHash()
{
	std::stringstream ss;
	ss << prevHash << timestamp << transactionString << nonce;

	return sha256(ss.str());
}