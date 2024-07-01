#ifndef BASECLASS_H
#define BASECLASS_H

#include <string>
#include <unordered_map>
#include <list>
#include <unordered_set>
#include <array>
#include <deque>
#include <vector>

struct Account {
    std::string id;
    int balance;
};

class BaseClass {
public:
    virtual void createNewAccount(std::string id, int initialBalance) = 0;
    virtual std::vector<int> getTopBalances(int k) = 0;
    virtual int getAccountBalance(std::string id) = 0;
    virtual void addTransaction(std::string id, int amount) = 0;
    virtual bool checkAccountExistence(std::string id) = 0;
    virtual bool removeAccountRecord(std::string id) = 0;
    virtual int countAllEntries() = 0;
    virtual int calculateIdHash(std::string id) = 0;

protected:
    std::unordered_map<std::string, Account> accountsMap;
    std::list<Account> accountList;
    std::unordered_set<Account> accountSet;
    std::array<Account, 100> accountArray;
    std::deque<Account> accountDeque;
};

#endif // BASECLASS_H

