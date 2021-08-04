
#include<iostream>
#include<unordered_map>
#include<queue>
#include<string>
using namespace std;
#define int long long
#define ff first
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define ss second

// To make tree for Huffman Coding
class treeNode{
public:
    char ch;
    int freq;
    treeNode *left,*right;
    
};

// To make a new treeNode
treeNode* makeNode(char ch, int freq, treeNode* left, treeNode* right){
    treeNode* temp = new treeNode;
    temp->ch = ch;
    temp->freq = freq;
    temp->left = left;
    temp->right = right;
    return temp;
}

// Compare function for priority queue containing treeNodes
// We need Nodes with high frequency to have lowest priority
struct comp{
    bool operator()(treeNode *A, treeNode* B){
        return A->freq > B->freq;}
};

// Funciton to retreive all the Binary Codes from the tree
void retreiveBinaryStrings(treeNode* root, string s, unordered_map<char, string> &binaryCodes){
    //    Can't do anything if root is NULL
    if(root==NULL)
        return;
    
    //    If it's a leaf Node
    if((root->left==NULL)&&(root->right==NULL)){
        binaryCodes[root->ch] = s;
        return;
    }
    
    //    Calling function to child nodes
    retreiveBinaryStrings(root->left,s+"0",binaryCodes);
    retreiveBinaryStrings(root->right,s+"1",binaryCodes);
}

// Traverse in the encoded string and print the output
void decode(unordered_map<string,char> decodingMap, string output){
    string temp;
    int i=0;
    while(i<=output.size()){
        
        //        Character found corresponding to the current string
        if(decodingMap.count(temp)){
            cout<<decodingMap[temp];
            //        CLear the current string
            temp = "";
            continue;
        }
        
        temp += output[i];
        i++;
    }
    return;
}

//To build huffman code and decode it!
void huffman(string input){
    
    //    Count the frequency of every character and store it in a map.
    unordered_map<char,int> freqMap;
    for(int i=0;i<input.size();i++){
        freqMap[input[i]]++;
    }
    
    unordered_map<char,string> huffmanBinaryCodes;
    
    if(freqMap.size()==1){
        //    If there's only one character in the whole input file, we assign 1 as it's binary code.
        huffmanBinaryCodes[(*freqMap.begin()).ff] = "1";
    }else{
        //    Pushing frequencies of characters into a priority queue
        priority_queue<treeNode*, vector<treeNode*>, comp> que;
        
        //    Pushing all the nodes into the tree
        for(auto i:freqMap){
            que.push(makeNode(i.ff, i.ss, NULL, NULL));
        }
        
        //    Creating the Tree
        while(que.size()>1){
            
            treeNode* left = que.top();
            que.pop();
            treeNode* right = que.top();
            que.pop();
            
            que.push(makeNode(NULL, (left->freq+right->freq), left, right));
        }
        
        //    The only node in the priority queue is the root node
        treeNode* root = que.top();
        
        //    We created the tree!
        
        //    Retreiving the new binary codes for all the characters
        retreiveBinaryStrings(root,"",huffmanBinaryCodes);
        
    }
    
    
    //    Let's print code for every character
    cout<<"\nCharacters in the string and their respective new Binary Codes are:\n";
    for(auto i:huffmanBinaryCodes){
        cout<<i.ff<<" : "<<i.ss<<"\n";
    }
    cout<<"\n";
    
    //    Print the original string
    cout<<"Original String:\n";
    cout<<input<<"\n\n";
    
    //    encoding
    string output;
    for(int i=0;i<input.size();i++){
        output += huffmanBinaryCodes[input[i]];
    }
    cout<<"The new compressed string is:\n"<<output<<"\n\n";
    
    
    //    Let's decode the compressed string to get the original string and print it
    //    First create a map containing strings as key and respective character as value
    unordered_map<string,char> decodingMap;
    cout<<"The decoded string is:\n";
    for(auto x:huffmanBinaryCodes){
        decodingMap[x.ss] = x.ff;
    }
    decode(decodingMap, output);
    cout<<"\n\n";
    
    //    Finding out the Compression Ratio
    long double original = input.size()*8;
    long double compressed = ceil((double)output.size()/(double)8);
    long double compRate = compressed/original;
    
    cout<<"The compressed string was "<<compRate*100<<"% of the input string\n";
    
}

signed main(){
    
    fastIO;
    
    string str;
    
    //    Taking Input
    cout<<"Please enter the string to be compressed!\n";
    getline(cin,str);
    
    huffman(str);
    
    return 0;
}
