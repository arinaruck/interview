#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

const int alphabetSize = 26;

class Node {
public:
    std::vector<std::shared_ptr<Node>> children;
    std::vector<int> isFinal;
    Node() {
        children.resize(alphabetSize);
        isFinal.resize(alphabetSize);
    }
};

bool findWord(std::string& word, std::shared_ptr<Node> root, int& keys) {
    std::shared_ptr<Node> currNode = root;
    int wordLen = word.length();
    char c;
    int letters;
    if (currNode->isFinal[word[0] - 'a'] == 1 && currNode->children[word[0] - 'a'] != nullptr) {
            keys = 2;
    }
    for (size_t i = 0; i < wordLen - 1; ++i) {
        c = word[i];
        if (!currNode->children[c - 'a']) {
            keys = wordLen;
            return false;
        }
        letters = 0;
        for (size_t i = 0; i < alphabetSize; ++i) {
            letters += int(currNode->isFinal[i] == 1);
            letters += int(currNode->children[i] != nullptr);
        }
        if (letters > 1 && i > 0) {
            keys = i + 1 + currNode->isFinal[c - 'a'];
        }
        currNode = currNode->children[c - 'a'];

    }
    c = word[wordLen - 1];
    if (currNode->isFinal[c - 'a']) {
        letters = 0;
        for (size_t i = 0; i < alphabetSize; ++i) {
            letters += int(currNode->isFinal[i] == 1);
            letters += int(currNode->children[i] != nullptr);
        }
        if (letters > 1 ) {
            keys = wordLen;
        }
        return true;
    }
    keys = wordLen;
    return false;
}

void addWord(std::string& word, std::shared_ptr<Node> root) {
    std::shared_ptr<Node> currNode = root;
    int wordLen = word.length();
    char c;
    for (size_t i = 0; i < wordLen - 1; ++i) {
        c = word[i];
        if (!currNode->children[c - 'a']) {
            currNode->children[c - 'a'] = std::make_shared<Node>();
        }
        currNode = currNode->children[c - 'a'];
    }
    c = word[wordLen - 1];
    currNode->isFinal[c - 'a'] = 1;
}

int main() {
    int n, keysPressed, keys;
    std::cin >> n;
    keysPressed = 0;
    std::shared_ptr<Node> root = std::make_shared<Node>();
    for (size_t i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        keys = 1;
        if (!findWord(word, root, keys)) {
            addWord(word, root);
        }
        keysPressed += keys;
    }
   /* std::cout << std::count(root->children.begin(), root->children.end(), nullptr) << "\n";
    root = root->children[0];
    std::cout << std::count(root->children.begin(), root->children.end(), nullptr) << "\n";
    std::shared_ptr<Node> next_root = root->children['p'-'a'];
    std::cout << std::count(root->children.begin(), root->children.end(), nullptr) << "\n";
    std::shared_ptr<Node> other_root = root->children['n'-'a'];
    std::cout << std::count(root->children.begin(), root->children.end(), nullptr) << "\n";*/
    std::cout << keysPressed << "\n";
}

/*
3
abc a abc

6

6
a abc abc bb bb bc
11

 */
