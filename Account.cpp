#include "Account.h"

int Account::createAccount(const char* username, const char* profile_path)
{

	EVP_PKEY* key = EVP_PKEY_new();
	EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);

	EVP_PKEY_keygen_init(ctx);
	EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 4096);
	EVP_PKEY_keygen(ctx, &key);

	char path[64] = { 0 };


	strcat(path, username);
	strcat(path, "private");
	strcat(path, ".pem");

	FILE* key_file = fopen(path, "w");
	if (!PEM_write_PrivateKey(key_file, key, NULL, NULL, 0, NULL, NULL))
	{
		std::cerr << "ERROR: FAILED TO WRITE Private Key TO ACCOUNT" << std::endl;
		fclose(key_file);
		EVP_PKEY_CTX_free(ctx);
		return EXIT_FAILURE;
	}

	memset(path, 0, 64);

	strcat(path, username);
	strcat(path, "public");
	strcat(path, ".der");

	key_file = fopen(path, "w");

	if (!i2d_PUBKEY_fp(key_file, key))
	{
		std::cerr << "ERROR: FAILED TO WRITE Public Key TO ACCOUNT" << std::endl;
		fclose(key_file);
		EVP_PKEY_CTX_free(ctx);
		return EXIT_FAILURE;
	}

	fclose(key_file);
	EVP_PKEY_CTX_free(ctx);
	return EXIT_SUCCESS;
}

int Account::login(Account* account, const char* username, const char* profile_path)
{
	account->public_key = EVP_PKEY_new();
	account->private_key = EVP_PKEY_new();

	char path[64] = { 0 };
	strcat(path, profile_path);
	strcat(path, username);
	strcat(path, "public");
	strcat(path, ".der");

	FILE* key_file = fopen(path, "r");
	if (!key_file)
	{
		std::cerr << "ERROR: COULD NOT FIND Public Key FOR ACCOUNT: " << username;
		fclose(key_file);
		return EXIT_FAILURE;
	}

	if (!d2i_PUBKEY_fp(key_file, &account->public_key))
	{
		std::cerr << "ERROR: COULD NOT LOAD Public Key FOR ACCOUNT: " << username;
		fclose(key_file);
		return EXIT_FAILURE;
	}
	fclose(key_file);

	memset(path, 0, 64);
	strcat(path, profile_path);
	strcat(path, username);
	strcat(path, "private");
	strcat(path, ".pem");

	key_file = fopen(path, "r");
	if (!key_file)
	{
		std::cerr << "ERROR: COULD NOT FIND Private Key FOR ACCOUNT: " << username;
		fclose(key_file);
		EVP_PKEY_free(account->private_key);
		EVP_PKEY_free(account->public_key);
		return EXIT_FAILURE;
	}
	std::cout << "Successfuly loaded keys for account user: " << username << std::endl;
	return EXIT_SUCCESS;
}

EVP_PKEY* Account::getPublic()
{
	return public_key;
}

EVP_PKEY* Account::getPrivate()
{
	return private_key;
}