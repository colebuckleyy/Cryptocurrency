#include "Transaction.h"

Transaction::Transaction(std::string from, std::string to, uint32_t amt)
	: fromAddress(from), toAddress(to), amount(amt)
{
}
std::string Transaction::transactString()
{
	std::stringstream ss;
	ss << fromAddress << toAddress << amount;
	return ss.str();
}

std::string Transaction::getFromAddress()
{
	return fromAddress;
}

std::string Transaction::getToAddress()
{
	return toAddress;
}

uint32_t Transaction::getAmount()
{
	return amount;
}

std::ostream& operator<<(std::ostream& os, const std::stringstream& obj)
{
	os << obj;

	return os;
}

unsigned char* Transaction::hashTransaction()
{
	std::stringstream ss;
	ss << transactString() << time(nullptr);

	std::string toHash = ss.str();
	std::string strHash = sha256(toHash);

	unsigned char* md = new unsigned char[strHash.length() + 1];
	strcpy((char*)md, strHash.c_str());

	return md;
}

/*void Transaction::signTransaction(EC_KEY* ecKey)
{
	EC_GROUP* ecgroup = EC_GROUP_new_by_curve_name(NID_secp192k1);
	point_conversion_form_t form;

	char addressChar[fromAddress.size() + 1];
	strcpy(addressChar, fromAddress.c_str());

	if (EC_POINT_point2hex(ecgroup, EC_KEY_get0_public_key(ecKey), form, NULL) != addressChar)
		std::cerr << "Cannot sign transactions for other wallets.";

	std::cout << "we good";
	std::string hashTx = hashTransaction();
	unsigned char* hashChar = new unsigned char[hashTx.length() + 1];
	strcpy((char*)hashChar, hashTx.c_str());
	const ECDSA_SIG* signature = ECDSA_do_sign(hashChar, strlen(reinterpret_cast<const char*>(hashChar)), ecKey);

	if (!(ECDSA_do_verify(hashChar, strlen(reinterpret_cast<const char*>(hashChar)), signature, ecKey)))
		std::cout << "Error" << std::endl;

	EC_GROUP_free(ecgroup);
	delete[]hashChar;
	std::cout << "Good";
}*/



bool Transaction::transactionSigner(Account signer)
{
	EVP_PKEY_CTX* ctx;
	unsigned char* sig;
	size_t mdlen = 32, siglen;

	ctx = EVP_PKEY_CTX_new(signer.getPrivate(), NULL);
	if (!ctx)
	{
		std::cerr << "ERROR: COULD NOT CREATE SIGNATURE CONTEXT" << std::endl;
		return false;
	}
	if (EVP_PKEY_sign_init(ctx) <= 0)
	{
		std::cerr << "ERROR: COULD NOT INITIALIZE SIGNATURE1" << std::endl;
		return false;
	}
	if (EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha256()) <= 0)
	{
		std::cerr << "ERROR: COULD NOT INITIALIZE SIGNATURE2" << std::endl;
		return false;
	}
	if (EVP_PKEY_sign(ctx, sig, &siglen, hashTransaction(), mdlen) <= 0)
	{
		std::cerr << "ERROR: COULD NOT INITIALIZE SIGNATURE3" << std::endl;
		return false;
	}
	std::cout << "Success" << std::endl;
	return true;
}
