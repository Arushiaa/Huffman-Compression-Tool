#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Node
{
    char ch;
    int freq;

    Node* left;
    Node* right;

    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
};

struct Compare
{
    bool operator()(Node* a, Node* b)
    {
        return a->freq > b->freq;
    }
};

Node* buildHuffmanTree(map<char, int>& freq)
{
    priority_queue<
        Node*,
        vector<Node*>,
        Compare
    > pq;

    for(auto pair : freq)
    {
        pq.push(
            new Node(pair.first, pair.second)
        );
    }

    while(pq.size() > 1)
    {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* merged =
            new Node('\0',
                     left->freq + right->freq);

        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    return pq.top();
}

void generateCodes(
    Node* root,
    string code,
    map<char,string>& huffmanCode
)
{
    if(root == nullptr)
        return;

    if(root->left == nullptr &&
       root->right == nullptr)
    {
        if(code.empty())
            code = "0";

        huffmanCode[root->ch] = code;
    }

    generateCodes(
        root->left,
        code + "0",
        huffmanCode
    );

    generateCodes(
        root->right,
        code + "1",
        huffmanCode
    );
}

string decodeText(
    Node* root,
    string encodedText
)
{
    string decoded = "";

    Node* current = root;

    for(char bit : encodedText)
    {
        if(bit == '0')
            current = current->left;
        else
            current = current->right;

        if(current->left == nullptr &&
           current->right == nullptr)
        {
            decoded += current->ch;
            current = root;
        }
    }

    return decoded;
}

void deleteTree(Node* root)
{
    if(root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

void encodeFile()
{
    string filename;

    cout << "\nEnter input filename: ";
    cin >> filename;

    ifstream inputFile(filename);

    if(!inputFile)
    {
        cout << "Could not open file!\n";
        return;
    }

    string text = "";
    char ch;

    while(inputFile.get(ch))
    {
        text += ch;
    }

    inputFile.close();

    map<char,int> freq;

    for(char c : text)
    {
        freq[c]++;
    }

    Node* root =
        buildHuffmanTree(freq);

    map<char,string> huffmanCode;

    generateCodes(
        root,
        "",
        huffmanCode
    );

    string encodedText = "";

    for(char c : text)
    {
        encodedText += huffmanCode[c];
    }

    ofstream compressedFile("compressed.txt");

    compressedFile
        << freq.size()
        << endl;

    for(auto pair : freq)
    {
        compressedFile
            << (int)pair.first
            << " "
            << pair.second
            << endl;
    }

    compressedFile
        << "###"
        << endl;

    compressedFile
        << encodedText;

    compressedFile.close();

    cout << "\nHuffman Codes:\n";

    for(auto pair : huffmanCode)
    {
        if(pair.first == ' ')
            cout << "[space]";
        else if(pair.first == '\n')
            cout << "[newline]";
        else
            cout << pair.first;

        cout
            << " -> "
            << pair.second
            << endl;
    }

    cout << "\nCompression Statistics\n";

    cout
        << "Original Size: "
        << text.size() * 8
        << " bits\n";

    cout
        << "Compressed Size: "
        << encodedText.size()
        << " bits\n";

    double ratio =
    (
        (double)encodedText.size()
        /
        (text.size() * 8)
    ) * 100;

    cout
        << "Compression Ratio: "
        << ratio
        << "%\n";

    cout
        << "\nCompressed data saved to compressed.txt\n";

    deleteTree(root);
}

void decodeFile()
{
    string filename;

    cout << "\nEnter compressed filename: ";
    cin >> filename;

    ifstream file(filename);

    if(!file)
    {
        cout << "Could not open file!\n";
        return;
    }

    int uniqueChars;

    file >> uniqueChars;

    map<char,int> freq;

    for(int i = 0; i < uniqueChars; i++)
    {
        int ascii;
        int frequency;

        file >> ascii >> frequency;

        freq[(char)ascii] =
            frequency;
    }

    string marker;

    file >> marker;

    string encodedText;
    file >> encodedText;

    file.close();

    Node* root =
        buildHuffmanTree(freq);

    string decodedText =
        decodeText(root,
                   encodedText);

    ofstream outputFile("output.txt");

    outputFile
        << decodedText;

    outputFile.close();

    cout
        << "\nDecoded text written to output.txt\n";

    deleteTree(root);
}

int main()
{
    int choice;

    while(true)
    {
        cout
            << "\n===== HUFFMAN COMPRESSION TOOL =====\n";

        cout
            << "1. Encode File\n";

        cout
            << "2. Decode File\n";

        cout
            << "3. Exit\n";

        cout
            << "\nEnter choice: ";

        cin >> choice;

        switch(choice)
        {
            case 1:
                encodeFile();
                break;

            case 2:
                decodeFile();
                break;

            case 3:
                cout << "Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice\n";
        }
    }
}