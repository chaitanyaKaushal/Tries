#include <iostream>
#include <string>
#include<vector>

using namespace std;

class TrieNode {
	public :
	char data;
	TrieNode **children;
	bool isTerminal;

	TrieNode(char data) {
		this -> data = data;
		children = new TrieNode*[26];
		for(int i = 0; i < 26; i++) {
			children[i] = NULL;
		}
		isTerminal = false;
	}
};

class Trie {
	TrieNode *root;

	public :
	int count;

	Trie() {
		this->count = 0;
		root = new TrieNode('\0');
	}

	bool insertWord(TrieNode *root, string word) {
		// Base case
		if(word.size() == 0) {
			if (!root->isTerminal) {
				root -> isTerminal = true;
				return true;	
			} else {
				return false;
			}
		}

		// Small Calculation
		int index = word[0] - 'a';
		TrieNode *child;
		if(root -> children[index] != NULL) {
			child = root -> children[index];
		}
		else {
			child = new TrieNode(word[0]);
			root -> children[index] = child;
		}

		// Recursive call
		return insertWord(child, word.substr(1));
	}

	// For user
	void insertWord(string word) {
		if (insertWord(root, word)) {
			this->count++;
		}
	}
private:
    void autoComplete(TrieNode *root,string pattern,string predict){
        if(pattern.size()==0){
            if(root->isTerminal == true){
                cout<<predict<<endl;
            }
            for(int i=0;i<26;i++){
                if(root->children[i]!=NULL)
                    autoComplete(root->children[i],pattern,predict+root->children[i]->data);
            }
            return ;
        }
        int index=pattern[0]-'a';
        // for(int i=0;i<26;i++){
            if(root->children[index] != NULL){
                TrieNode *child=root->children[index];
                autoComplete(child,pattern.substr(1),predict+pattern[0]);
            }   
        // }
    }
public:
    void autoComplete(vector<string> input, string pattern) {
        // Complete this function
        // Print the output as specified in question
        for(int i=0;i<input.size();i++){
            insertWord(input[i]);
        }
        autoComplete(root,pattern,"");
    }
};


int main() {
	Trie t;
    int N;
    cin >> N;
    string pattern;
    vector<string> vect;
    for (int i=0; i < N; i++) {
        string word;
        cin >> word;
        vect.push_back(word);
    }
    cin >> pattern;
    t.autoComplete(vect, pattern);
}
