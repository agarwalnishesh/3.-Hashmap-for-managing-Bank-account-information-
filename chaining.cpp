#include "Chaining.h"

Chaining::Chaining() {
    dataStorage = std::vector<std::vector<Account>>(sizes[M]);
    for(int index = 0; index < sizes[M]; index++) {
        dataStorage[index] = std::vector<Account>();
    }
    accountCount = 0;
}

void Chaining::initializeAccount(std::string accountId, int initialAmount) {
    if (accountCount + 1 > sizes[M] / 2) {
        adjustCapacity(M + 1);
    }
    int hashCode = generateHash(accountId);
    dataStorage[hashCode].push_back(Account({accountId, initialAmount}));
    accountCount++;
}

std::vector<int> Chaining::retrieveTopBalances(int topK) {
    std::vector<int> balanceList(accountCount);
    int idx = 0;
    for (auto &bucket : dataStorage) {
        for (Account &acc : bucket) {
            if (acc.balance >= 0) balanceList[idx++] = acc.balance;
        }
    }
    sortTopBalances(balanceList, 0, accountCount);
    std::vector<int> topBalances(topK);
    for (int i = 0; i < topK && i < topBalances.size(); i++) topBalances[i] = balanceList[i];
    return topBalances;
}

int Chaining::checkAccountBalance(std::string accountId) {
    int hashCode = generateHash(accountId);
    auto &bucket = dataStorage[hashCode];
    for (Account &acc : bucket) {
        if (acc.id == accountId) return acc.balance;
    }
    return -1;
}

void Chaining::recordTransaction(std::string accountId, int transactionAmount) {
    int hashCode = generateHash(accountId);
    auto &bucket = dataStorage[hashCode];
    for (Account &acc : bucket) {
        if (acc.id == accountId) {
            acc.balance += transactionAmount;
            return;
        }
    }
    initializeAccount(accountId, transactionAmount);
}

bool Chaining::isAccountPresent(std::string accountId) {
    int hashCode = generateHash(accountId);
    auto &bucket = dataStorage[hashCode];
    for (Account &acc : bucket) {
        if (acc.id == accountId) return true;
    }
    return false;
}

bool Chaining::removeAccount(std::string accountId) {
    int hashCode = generateHash(accountId);
    auto &bucket = dataStorage[hashCode];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->id == accountId) {
            bucket.erase(it);
            accountCount--;
            if (accountCount < sizes[M] / 8 && M > 0) {
                adjustCapacity(M - 1);
            }
            return true;
        }
    }
    return false;
}

int Chaining::totalAccounts() {
    return accountCount;
}

int Chaining::generateHash(std::string accountId) {
    long long int hashValue = 0;
    long long int segment1, segment2, segment3;
    segment1 = ((((accountId[0] - 'A') * 26 + (accountId[1] - 'A')) * 26 + (accountId[2] - 'A')) * 26 + (accountId[3] - 'A')) % sizes[M];
    segment2 = (((((((((accountId[4] - '0') * 10) + (accountId[5] - '0')) * 10 + (accountId[6] - '0')) * 10 + (accountId[7] - '0')) * 10) + (accountId[8] - '0')) * 10 + (accountId[9] - '0')) * 10 + (accountId[10] - '0')) % sizes[M];
    segment3 = (((((((((((((accountId[12] - '0') * 10) + (accountId[13] - '0')) * 10 + (accountId[14] - '0')) * 10 + (accountId[15] - '0')) * 10) + (accountId[16] - '0')) * 10 + (accountId[17] - '0')) * 10 + (accountId[18] - '0')) * 10) + (accountId[19] - '0')) * 10 + (accountId[20] - '0')) * 10 + (accountId[21] - '0')) % sizes[M];
    hashValue = (((segment1 + segment2 + segment3) * (segment1 + segment2 + segment3 + 1) * (segment1 + segment2 + segment3 + 2)) / 6) % sizes[M] + (((segment1 + segment2) * (segment1 + segment2 + 1)) / 2) % sizes[M] + segment1;
    return (hashValue % sizes[M] + sizes[M]) % sizes[M];
}

void Chaining::adjustCapacity(int newSize) {
    // This function adjusts the size of the dataStorage vector to newSize
    // Implement resizing logic here based on newSize
}

void Chaining::sortTopBalances(std::vector<int> &balances, int left, int right) {
    // This function sorts the balances in descending order
    // Implement sorting logic here
}
