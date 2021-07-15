#pragma once

#include <iostream>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <openssl/ec.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <string.h>
#include "sha256.h"
#include <openssl/bn.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <fstream>
#include <stdio.h>

class Account
{
private:
	EVP_PKEY* public_key;
	EVP_PKEY* private_key;
public:
	int createAccount(const char* username, const char* profile_path);

	int login(Account* account, const char* username, const char* profile_path);

	EVP_PKEY* getPublic();

	EVP_PKEY* getPrivate();
};


