#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <iostream>
#include <functional>
#include <initializer_list>

class Trie
{
public:
    class Node
    {
    public:
        std::vector<Node *> children;
        char data;
        bool is_finished;
        Node(char _data, bool _is_finished); // Node Constructor
    };
    Node *root;
    Trie();                                         // defult Consturctor
    Trie(std::initializer_list<std::string> query); // Constructor with List
    Trie(const Trie &trie);                         // copy
    void bfs(std::function<void(Node *&node)> func);
    ~Trie();                      // destructor
    void insert(std::string str); // insert function
    bool search(std::string query);

private:
};

#endif // TRIE_H