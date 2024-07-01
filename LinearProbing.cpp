#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <string>

struct Account {
    std::string id;
    int balance;
};

class UniqueBank {
private:
    int M;
    std::vector<std::list<Account>> separateChaining;
    std::vector<Account> quadraticProbing;
    std::unordered_map<std::string, int> hashMap;
    std::vector<Account*> binarySearchTree;
    std::vector<Account> simpleHashTable;
    int size;

    int hash(std::string id) {
        // Custom hash function combining various methods
        int hashValue = 0;
        for (char c : id) {
            hashValue += int(c);
        }
        return hashValue % M;
    }

    void insertNode(Account* node, Account acc) {
        if (node == nullptr) {
            node = new Account(acc);
        } else if (acc.id < node->id) {
            insertNode(node->left, acc);
        } else if (acc.id > node->id) {
            insertNode(node->right, acc);
        } else {
            // Handle duplicate IDs
        }
    }

    void getTopKHelper(Account* node, std::vector<int>& balances, int& k) {
        if (node == nullptr || k <= 0) return;
        getTopKHelper(node->right, balances, k);
        if (k > 0) {
            balances.push_back(node->balance);
            k--;
        }
        getTopKHelper(node->left, balances, k);
    }

public:
    UniqueBank() : M(100), separateChaining(M), quadraticProbing(M, {"", -1}), size(0) {}

    void createAccount(std::string id, int count) {
        int index = hash(id);
        int probe = 1;
        while (quadraticProbing[index].balance != -1) {
            index = (index + probe * probe) % M;
            probe++;
        }
        quadraticProbing[index] = {id, count};

        separateChaining[index].push_back({id, count});
        hashMap[id] = count;

        Account* bstNode = nullptr;
        insertNode(bstNode, {id, count});
        binarySearchTree.push_back(bstNode);

        int simpleIndex = id.length() % M;
        while (simpleHashTable[simpleIndex].balance != -1) {
            simpleIndex = (simpleIndex + 1) % M;
        }
        simpleHashTable[simpleIndex] = {id, count};

        size++;
    }

    std::vector<int> getTopK(int k) {
        std::vector<int> balances;
        
        // Quadratic Probing
        for (const auto& acc : quadraticProbing) {
            if (acc.balance != -1) {
                balances.push_back(acc.balance);
            }
        }
        
        // Separate Chaining
        for (const auto& bucket : separateChaining) {
            for (const auto& acc : bucket) {
                balances.push_back(acc.balance);
            }
        }
        
        // Hash Map
        for (const auto& pair : hashMap) {
            balances.push_back(pair.second);
        }
        
        // Binary Search Tree
        for (const auto& node : binarySearchTree) {
            if (node != nullptr) {
                getTopKHelper(node, balances, k);
            }
        }
        
        // Simple Hash Table
        for (const auto& acc : simpleHashTable) {
            if (acc.balance != -1) {
                balances.push_back(acc.balance);
            }
        }
        
        // Custom sorting logic
        std::sort(balances.begin(), balances.end(), std::greater<int>());
        balances.resize(std::min(k, int(balances.size())));
        
        return balances;
    }

    // Implementations of other methods like addTransaction, getBalance, etc.
};

int main() {
    UniqueBank bank;

    // Example usage
    bank.createAccount("JohnDoe12345", 1000);
    bank.createAccount("JaneSmith67890", 500);
    bank.createAccount("AliceWonderland24680", 1200);

    std::vector<int> topBalances = bank.getTopK(2);
    std::cout << "Top balances: ";
    for (int balance : topBalances) {
        std::cout << balance << " ";
    }
    std::cout << std::endl;

    return 0;
}


