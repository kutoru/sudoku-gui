#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "hashdyn.h"
#include <cryptlib.h>
#include <sha.h>
#include <sstream>
#include <iomanip>

char* get_sha256(const char* str, int strSize) {
    CryptoPP::SHA256 sha256;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];

    sha256.CalculateDigest(digest, (CryptoPP::byte*)str, strSize);

    std::stringstream ss;
    for (int i = 0; i < CryptoPP::SHA256::DIGESTSIZE; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }

    int hashSize = 64;
    char* hash = new char[hashSize];
    for (int i = 0; i < hashSize; i++) {
        ss >> hash[i];
    }

    return hash;
}
