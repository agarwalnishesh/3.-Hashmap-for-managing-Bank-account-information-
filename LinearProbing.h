#ifndef COMBINED_HASHING_H
#define COMBINED_HASHING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

class CombinedHashing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    CombinedHashing();
    
private:
    int size = 0;
    int M = 0;
    std::vector<std::list<Account>> separateChainingTable;
    std::vector<Account> quadraticProbingTable;
    std::vector<Account> doubleHashingTable;
    std::vector<Account> cuckooTable1;
    std::vector<Account> cuckooTable2;
    std::unordered_map<int, std::vector<Account>> bucketHashTable;
    
    // Helper functions for each hashing method
    void resizeSeparateChaining(int new_M);
    void resizeQuadraticProbing(int new_M);
    void resizeDoubleHashing(int new_M);
    void resizeCuckooHashing(int new_M);
    void resizeBucketHashing(int new_M);
    
    void rehashSeparateChaining();
    void rehashQuadraticProbing();
    void rehashDoubleHashing();
    void rehashCuckooHashing();
    void rehashBucketHashing();
    
    void balanceAccountsCuckoo();
    void redistributeAccountsBucket();
};

#endif // COMBINED_HASHING_H

// Implementation

#include "CombinedHashing.h"

CombinedHashing::CombinedHashing() {
    // Initialize tables with initial sizes
    resizeSeparateChaining(67);
    resizeQuadraticProbing(67);
    resizeDoubleHashing(67);
    resizeCuckooHashing(67);
    resizeBucketHashing(67);
}

void CombinedHashing::createAccount(std::string id, int count) {
    // Choose one method for creating account (e.g., separate chaining)
    int index = hash(id) % M;
    separateChainingTable[index].push_back(Account{id, count});
    size++;
    if (size > M * 2)
        rehashSeparateChaining();
}

std::vector<int> CombinedHashing::getTopK(int k) {
    // Implement logic for retrieving top K balances from any method
    std::vector<int> topBalances;
    // Example: Quadratic Probing method
    for (const auto& acc : quadraticProbingTable) {
        if (acc.balance > 0) {
            topBalances.push_back(acc.balance);
        }
    }
    // Sort topBalances vector or use any sorting method
    std::sort(topBalances.begin(), topBalances.end(), std::greater<int>());
    return topBalances;
}

int CombinedHashing::getBalance(std::string id) {
    // Implement logic to retrieve balance from any method (e.g., double hashing)
    int index = hash(id) % M;
    return doubleHashingTable[index].balance;
}

void CombinedHashing::addTransaction(std::string id, int count) {
    // Choose one method for adding transaction (e.g., cuckoo hashing)
    int index = hash(id) % M;
    cuckooTable1[index].balance += count;
}

bool CombinedHashing::doesExist(std::string id) {
    // Implement logic to check existence in any method (e.g., bucket hashing)
    int index = hash(id) % M;
    for (const auto& acc : bucketHashTable[index]) {
        if (acc.id == id) {
            return true;
        }
    }
    return false;
}

bool CombinedHashing::deleteAccount(std::string id) {
    // Implement logic to delete account from any method (e.g., quadratic probing)
    int index = hash(id) % M;
    for (auto& acc : quadraticProbingTable) {
        if (acc.id == id) {
            acc.balance = -1;
            return true;
        }
    }
    return false;
}

int CombinedHashing::databaseSize() {
    // Example: Return total size of any method's database (e.g., separate chaining)
    return size;
}

int CombinedHashing::hash(std::string id) {
    // Example: Hash function for any method
    int hashVal = 0;
    for (char c : id) {
        hashVal = (hashVal * 31 + c) % M;
    }
    return hashVal;
}

void CombinedHashing::resizeSeparateChaining(int new_M) {
    M = new_M;
    separateChainingTable.resize(M);
}

void CombinedHashing::resizeQuadraticProbing(int new_M) {
    M = new_M;
    quadraticProbingTable.resize(M, Account{"", -1});
}

void CombinedHashing::resizeDoubleHashing(int new_M) {
    M = new_M;
    doubleHashingTable.resize(M, Account{"", -1});
}

void CombinedHashing::resizeCuckooHashing(int new_M) {
    M = new_M;
    cuckooTable1.resize(M, Account{"", -1});
    cuckooTable2.resize(M, Account{"", -1});
}

void CombinedHashing::resizeBucketHashing(int new_M) {
    M = new_M;
    bucketHashTable.clear();
}

void CombinedHashing::rehashSeparateChaining() {
    // Implement rehashing logic for separate chaining method
}

void CombinedHashing::rehashQuadraticProbing() {
    // Implement rehashing logic for quadratic probing method
}

void CombinedHashing::rehashDoubleHashing() {
    // Implement rehashing logic for double hashing method
}

void CombinedHashing::rehashCuckooHashing() {
    // Implement rehashing logic for cuckoo hashing method
}

void CombinedHashing::rehashBucketHashing() {
    // Implement rehashing logic for bucket hashing method
}

void CombinedHashing::balanceAccountsCuckoo() {
    // Implement balancing logic for cuckoo hashing
}

void CombinedHashing::redistributeAccountsBucket() {
    // Implement redistributing logic for bucket hashing
}

