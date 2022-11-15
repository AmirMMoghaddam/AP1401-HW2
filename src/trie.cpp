#include "trie.h"

Trie::Node::Node(char _data, bool _is_finished) : data{_data}, is_finished{_is_finished}
{
    std::cout << "Node Constructor" << std::endl;
}

Trie::Trie()
{
    root = new Trie::Node('\0', true);
    std::cout << "Trie Constructor With root : " << root << std::endl;
}

Trie::Trie(const Trie &trie)
{
    root = new Trie::Node('\0', true);
    std::vector<Node *> CurrentLevel;
    std::vector<Node *> _CurrentLevel;
    std::vector<Node *> AllChild;
    std::vector<Node *> _AllChild;
    CurrentLevel.push_back(trie.root);
    _CurrentLevel.push_back(root);
    size_t counter{0};
    counter = 0;
    while (true)
    {
        if (CurrentLevel.size() == 0)
        {
            break;
        }
        for (auto i : CurrentLevel)
        {
            size_t Secondcounter{0};
            for (auto j : i->children)
            {
                Node *a = new Trie::Node(j->data, j->is_finished);
                _CurrentLevel[counter]->children.push_back(a);
                AllChild.push_back(j);
                _AllChild.push_back(_CurrentLevel[counter]->children[Secondcounter]);
                Secondcounter++;
            }
            counter++;
        }
        CurrentLevel.clear();
        CurrentLevel = AllChild;
        AllChild.clear();
        _CurrentLevel.clear();
        _CurrentLevel = _AllChild;
        _AllChild.clear();
        counter = 0;
    }
}

void Trie::insert(std::string str)
{
    Node *currentNode{this->root};

    for (char c : str)
    {

        if (currentNode->is_finished)
        {
            currentNode->children.push_back(new Trie::Node(c, true));
            currentNode->is_finished = false;
            currentNode = currentNode->children[0];
        }
        else
        {
            for (auto i : currentNode->children)
            {
                if (c == i->data)
                {
                    currentNode = i;
                }
            }
            if (currentNode->data != c)
            {
                currentNode->children.push_back(new Trie::Node(c, true));
                currentNode = currentNode->children[currentNode->children.size() - 1];
            }
        }
    }
}

void Trie::bfs(std::function<void(Node *&node)> func)
{
    std::vector<Node *> CurrentLevel;
    std::vector<Node *> AllChild;
    CurrentLevel.push_back(this->root);
    Node *currentNode{CurrentLevel[0]};
    while (true)
    {
        if (CurrentLevel.size() == 0)
        {
            break;
        }
        for (auto i : CurrentLevel)
        {
            func(i);
            for (auto j : i->children)
            {
                AllChild.push_back(j);
            }
        }
        CurrentLevel.clear();
        CurrentLevel = AllChild;
        AllChild.clear();
    }
}

Trie::~Trie()
{
    if (root == nullptr)
        return;
    std::vector<Node *> nodes;
    this->bfs([&nodes](Trie::Node *&node)
              { nodes.push_back(node); });
    for (const auto &node : nodes)
        delete node;
}

bool Trie::search(std::string query)
{
    Node *currentNode{this->root};
    Node *TempNode;
    bool check{false};
    for (char c : query)
    {
        if (currentNode->is_finished)
        {
            return false;
        }
        for (auto i : currentNode->children)
        {

            if (i->data == c)
            {
                check = true;
                TempNode = i;
            }
        }
        if (check)
        {
            currentNode = TempNode;
        }
        else
        {
            return false;
        }
    }
    return true;
}

Trie::Trie(std::initializer_list<std::string> query)
{
    root = new Trie::Node('\0', true);
    std::vector<std::string> v;
    v.insert(v.end(), query.begin(), query.end());
    for (auto i : v)
    {
        this->insert(i);
    }
}
