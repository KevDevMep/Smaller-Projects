#include <iostream>
#include <fstream> // char 26 / SUB causes extraction failure
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>
using namespace std;
unordered_map<char,int> Frequencies;
unordered_map<char,vector<bool>> CW;
vector<bool> ENC{}, DEC{};

struct Node
{
    char symbol;
    int value;
    Node* left = NULL;
    Node* right = NULL;
    vector<bool> codeWord{};
};

Node* prefixTree;
auto my_comp = [](const Node* n1, const Node* n2) {return n1->value > n2->value;};
void merge(vector<bool>& v1, const vector<bool>& v2) {for (const bool& b : v2) v1.push_back(b);};

void findFrequencies()
{
    ifstream fin ("Huffman_Input.txt");
    if (!fin)
    {
        cerr << "Input file not found";
        throw;
    }
    while (fin) {Frequencies[fin.get()]++;}
    Frequencies.erase(255);
    fin.close();
}

void buildTree()
{
    priority_queue<Node*,vector<Node*>,decltype(my_comp)> pq;
    for (const auto& n : Frequencies) pq.push(new Node{n.first,n.second});
    Node* left;
    Node* right;
    while (pq.size() > 1)
    {
        prefixTree = new Node();
        left = pq.top();
        pq.pop();
        right = pq.top();
        pq.pop();
        prefixTree->value = left->value + right->value;
        prefixTree->left = left;
        prefixTree->right = right;
        pq.push(prefixTree);
    }
}

void generateCodeWord(Node* root)
{
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        CW[node->symbol] = node->codeWord;
        q.pop();
        if (node->left != NULL) {
            q.push(node->left);
            node->left->codeWord = node->codeWord;
            node->left->codeWord.push_back(0);
        }
        if (node->right != NULL) {
            q.push(node->right);
            node->right->codeWord = node->codeWord;
            node->right->codeWord.push_back(1);
        }
    }
}

void printBits(const vector<bool>& bits)
{
    for (const auto& b : bits) cout << b;
    cout << '\n';
}

void printCodeWord(const Node* node)
{
    if (node == NULL) return;
    if (node->symbol != 0) {
        cout << node->symbol << ": ";
        printBits(node->codeWord);
    }
    printCodeWord(node->left);
    printCodeWord(node->right);
}

void toBinaryE()
{
    ifstream fin ("Huffman_Input.txt");
    if (!fin)
    {
        cerr << "Input file not found";
        throw;
    }
    vector<bool> b;
    while (fin)
    {
        b = CW[fin.get()];
        merge(ENC,b);
    }
    fin.close();
}

void encode()
{
    toBinaryE();
    ofstream fout("Encoded.txt");
    bitset<8> b{0};
    int count = 0;
    for (const auto& iter : ENC)
    {
        b[7 - count] = iter;
        count++;
        if (count == 8) {
            fout << (char)b.to_ulong();
            count = 0;
            b = {0};
        }
    }
    if (ENC.size()%8 != 0) fout << (char)b.to_ulong();
    fout.close();
}

vector<bool> numtoBinary(int num)
{
    int i = 7, x = 128;
    vector<bool> ans{};
    while(num != 0 || i > -1) {
        if (num >= x)
        {
            ans.push_back(1);
            num = num - x;
        }
        else ans.push_back(0);
        x /= 2;
        --i;
    }
    return ans;
}

void toBinaryD()
{
    ifstream fin("Encoded.txt");
    vector<bool> b;
    unsigned char c;
    if (!fin)
    {
        cerr << "Input file not found";
        throw;
    }
    while (fin)
    {
        c = fin.get();
        b = numtoBinary(c);
        merge(DEC,b);
    }
    for(int i = 0; i < 8; i++) DEC.pop_back();
    fin.close();
}

void transverseTree(const vector<bool>& b)
{
    ofstream fout("Huffman_Output.txt");
    Node* iter = prefixTree;
    for (const auto& x : b) {
        if (x) iter = iter->right;
        else iter = iter->left;
        if (iter->symbol != 0) {
            fout << iter->symbol;
            iter = prefixTree;
        }
    }
    fout.close();
}

void printFrequencies()
{
    cout << "Frequencies:\n";
    int total = 0;
    for (const auto& iter : Frequencies) {
        total += iter.second;
        cout << "char: " << iter.first << ", freq: " << iter.second << '\n';
    }
    cout << "Total chars: " << total << '\n';
}

void printPreorder(const Node* node)
{
    if (node == NULL) return;
    cout << '(' << node->symbol << ',' << node->value << ") ";
    printPreorder(node->left);
    printPreorder(node->right);
}

void Huffman()
{
    findFrequencies();
    printFrequencies();
    buildTree();
    cout << "PreFix Tree: (in preorder)\n";
    printPreorder(prefixTree);
    generateCodeWord(prefixTree);
    cout << "\nCode Words:\n";
    printCodeWord(prefixTree);
    encode();
    //toBinaryD();
    //transverseTree(DEC);
    transverseTree(ENC);
}

int main()
{
    Huffman();

    return 0;
}