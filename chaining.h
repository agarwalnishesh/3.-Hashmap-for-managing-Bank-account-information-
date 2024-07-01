#ifndef ADVANCED_CHAINING_H
#define ADVANCED_CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class AdvancedChaining : public BaseClass {
public:
    void initializeAccount(std::string id, int amount) override;
    std::vector<int> findTopK(int k) override;
    int getAccountValue(std::string id) override;
    void logTransaction(std::string id, int amount) override;
    bool isAccountAvailable(std::string id) const override;
    bool removeAccount(std::string id) override;
    int totalSize() const override;
    int computeHash(std::string id) const override;
    AdvancedChaining();
    
private:
    int currentSize=0;
    int hashIndex=0;
    int hashCapacities[14] = {67, 127, 257, 509, 1021, 2053, 4099, 8191, 16381, 32771, 65537, 131071, 262147, 524287};

    void mergeSortTopK(std::vector<int> &result, int start, int end){
        if (end - start <= 1) return;
        int mid = (start + end) / 2;
        mergeSortTopK(result, start, mid);
        mergeSortTopK(result, mid, end);
        std::vector<int> temp(end - start, -1);
        int left = start, right = mid, index = 0;
        while (left < mid && right < end) {
            if (result[left] > result[right]) temp[index++] = result[left++];
            else temp[index++] = result[right++];
        }
        while (left < mid) temp[index++] = result[left++];
        while (right < end) temp[index++] = result[right++];
        for (int i = start; i < end; ++i) result[i] = temp[i - start];
    }

    void resizeHashTable(int newSize){
        hashIndex = newSize;
        std::vector<std::vector<Account>> newTable(hashCapacities[hashIndex]);
        for (int i = 0; i < hashCapacities[hashIndex]; ++i) newTable[i] = std::vector<Account>();
        for (auto &bucket : accountTable) {
            for (Account &acc : bucket) {
                int id_hash = computeHash(acc.id);
                newTable[id_hash].push_back(acc);
            }
        }
        accountTable = newTable;
    }
    
    // Additional private members and methods
    std::vector<std::vector<Account>> accountTable;
};

// Implementation of member functions
AdvancedChaining::AdvancedChaining() {
    // Constructor implementation
}

void AdvancedChaining::initializeAccount(std::string id, int amount) {
    // Implementation of initializeAccount
}

std::vector<int> AdvancedChaining::findTopK(int k) {
    std::vector<int> result;
    // Implementation to find top K
    mergeSortTopK(result, 0, result.size());
    return result;
}

int AdvancedChaining::getAccountValue(std::string id) {
    // Implementation of getAccountValue
    return 0; // Placeholder return
}

void AdvancedChaining::logTransaction(std::string id, int amount) {
    // Implementation of logTransaction
}

bool AdvancedChaining::isAccountAvailable(std::string id) const {
    // Implementation of isAccountAvailable
    return false; // Placeholder return
}

bool AdvancedChaining::removeAccount(std::string id) {
    // Implementation of removeAccount
    return false; // Placeholder return
}

int AdvancedChaining::totalSize() const {
    // Implementation of totalSize
    return currentSize;
}

int AdvancedChaining::computeHash(std::string id) const {
    // Implementation of computeHash
    return 0; // Placeholder return
}

#endif // ADVANCED_CHAINING_H
