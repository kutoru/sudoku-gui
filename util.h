#pragma once

#include <fstream>
#include <chrono>
#include <string>
#include <random>
#include "hashdyn.h"  // Delete this if you don't want to compile hashdyn

#ifndef AVAL_CHARS
#define AVAL_CHARS "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#$%&-_\0"
#endif

class exep: public std::exception {
public:
	std::string msg;

	exep(std::string message) noexcept {
		this->msg = message;
	}
};

inline void resetlog() {
	return;
	std::fstream file("log.txt", std::ios::out);
	file.close();
}

template <class T>
inline void logl(T o, bool newline = false) {
	return;
	std::fstream file("log.txt", std::ios::app);
	file << o;
	if (newline) {
		file << '\n';
	}
	file.close();
}

inline std::string conv(System::String^ str) {
	int size = str->Length;
	std::string newStr(size, '\0');
	char ch;

	for (int i = 0; i < size; i++) {
		ch = str[i];
		newStr[i] = ch;
	}

	return newStr;
}

inline System::String^ conv(std::string str) {
	System::String^ newStr = gcnew System::String(str.c_str());
	return newStr;
}

inline System::String^ conv(char ch) {
	System::String^ newStr;
	if (ch) {
		newStr = gcnew System::String(&ch);
	}
	else {
		newStr = L"";
	}
	return newStr;
}

inline std::string _GetNewKey() {
	int seed = std::chrono::system_clock::now().time_since_epoch().count();
	auto gen = std::default_random_engine(seed);
	auto distr = std::uniform_int_distribution<>(1000000000, 9999999999);
	return std::to_string(distr(gen));
}

inline std::string GetNewKey() {
	int key = std::chrono::system_clock::now().time_since_epoch().count();
	key = ((key % 727) * (key / 69));
	if (key < 0) {
		key *= -1;
	}

	auto sKey = std::to_string(key);
	int keySize = sKey.size();
	if (keySize < 10) {
		return GetNewKey();
	}
	else {
		sKey = sKey.substr(keySize - 10, keySize);
		return sKey;
	}
}

inline bool IsIn(int num, std::string key) {
	char n = std::to_string(num)[0];
	for (int i = 0; i < key.size(); i++) {
		if (n == key[i]) {
			return true;
		}
	}
	return false;
}

inline std::string EncryptPassword(std::string password, std::string key) {
	int passSize = password.size();
	int iKey = atoi(key.c_str());

	auto gen = std::default_random_engine(iKey);
	auto distrNum = std::uniform_int_distribution<>(0, 9);
	auto distrPass = std::uniform_int_distribution<>(0, passSize - 1);
	auto distrAval = std::uniform_int_distribution<>(0, 68);

	std::string newPass = password;
	std::shuffle(newPass.begin(), newPass.end(), gen);

	for (int i = 0; i < passSize - 1; i++) {
		if (IsIn(distrNum(gen), key)) {
			std::string ch = "";
			ch += AVAL_CHARS[distrAval(gen)];
			newPass.insert(distrPass(gen), ch);
		}
	}

	// Delete the following 6 lines if you don't care about the encryption
	char* charHash = get_sha256(newPass.c_str(), newPass.size());
	int hashSize = 64;  // sha256 is always 64 characters long, everything else is trash
	std::string hash(hashSize, '_');
	for (int i = 0; i < hashSize; i++) {
		hash[i] = charHash[i];
	}

	return hash;
}
