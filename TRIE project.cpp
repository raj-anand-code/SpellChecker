#include<bits/stdc++.h>
using namespace std;

#define UNDERLINE_ON "\033|4m" // to start the underline
#define UNDERLINE_OFF "\033|0m"// to stop the underline

struct TrieNode{
	bool isComplete=false;
	TrieNode* children[26]={NULL};//using array because we will take smallcase only, else use hashmap
};

class Trie{
	TrieNode* root=NULL;
public:
	Trie();//we will need a constructor trienode to declare space to the root node

	void insertWord(string word);//need a func. which can take word to insert
	bool searchWord(string word);//                                 to find & return weather the word is found or not
	bool deleteWord(string word);
	void updateWord(string oldWord,string newWord);
};
// Writing all functions now
Trie::Trie(){				//writing constructor
	root=new TrieNode();
}
void Trie::insertWord(string word){
	TrieNode* currNode=root;//we will make a currNode & will make it root
	for(char c: word){					//then we will iterate on that word & we will check weather that character is already the children of that current or not
							//if yes then continue else if it is pointing to null then their is no node present at that position soo we will allocate new memory their & add that char	

		if(currNode->children[c-'a']==NULL){
			currNode->children[c-'a']=new TrieNode();
		}
		currNode=currNode->children[c-'a'];//then we will make that charNode as a currNode
	}		
	//once we iterate through all the characters,we will set isComplete=true for the last char
	//by this we will know that the word is ending at that char 
	currNode->isComplete=true;
}
bool Trie::searchWord(string word){
	TrieNode* currNode=root;
	for(char c:word){
		if(currNode->children[c-'a']==NULL){
			//if that char is not present as the children of that currNOde that means the word is not present
			return false;
		}
		else{
			//else we will continue
			currNode=currNode->children[c-'a'];
		}
	}
	//once we come out of the loop we will return the isComplete value of the node;
	return currNode->isComplete;

}
bool Trie::deleteWord(string word){
	TrieNode* currNode=root;
	//we have to return false if the word is not present,o while iterating if the
	//the character itself is not present which means word is not present
	for(char c:word){
		if(currNode->children[c-'a']==NULL){
			return false;
		}
		currNode=currNode->children[c-'a'];
		
	}
	//if the word is present set the terminating value as false and then return true;
	currNode->isComplete= false;
		return true;
}
void Trie::updateWord(string oldWord,string newWord){
	//here we will first delete the old word
	this->deleteWord(oldWord);
	//now we will call insertWord
	this->insertWord(newWord);
}






int main(){
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	Trie oTrie;//object of Trie class

	//creating a dictionary
	vector<string> words={"cat","car","bat","cart","ball","bats"};
	for(string word:words){
		oTrie.insertWord(word);
	}
	//FOR CHECKING INSERT,SEARCH,DELETE and UPDATE FUNCTION
	string word="car";
	oTrie.searchWord(word) ? cout<<"present\n" : cout<<"not present\n";
	oTrie.deleteWord(word) ? cout<<"Deleted\n" : cout<<"not deleted\n";
	oTrie.searchWord(word) ? cout<<"present\n" : cout<<"not present\n";

	//spellchecker APPLICATION
	string s ="";
	while(char c=getchar()){//while user is (typing)/(entering any character) loop will continue & dont press control C
		if(c=='\n'){//as soon as the user press enter we will check for final word and exit the program
			oTrie.searchWord(s) ? cout<< s :  cout<<UNDERLINE_ON<< s <<UNDERLINE_OFF;
			break;
		}
		else if(c==' ')//if the user is entering space i will check weather the word is in dictionary or not
			{
				oTrie.searchWord(s) ? cout<< s : cout<<UNDERLINE_ON<< s <<UNDERLINE_OFF;
				s="";//clearing the previous word
				cout<<c; //for additional space
			}
			else{
				s+=c; //adding character in string
			}
			
	} 


}
//I am making a spell checker application in whcih user will type like a normal chating app
//as soon as the word is typed & space is inserted,app will check weather that
//word is correct or not means it is present in dictionary or not if it is present then it will print that word as it is,And
//if the word is not present it will first underline the word then Print it(the underline will convey that the word is incorrect)
//while loop is created under that char input till enter is pressed by the user,if the user will press the enter
//button the last word will get tested weather it is present in dictionary or not, if the user presses space 