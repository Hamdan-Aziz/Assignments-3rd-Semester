#include<iostream>
#include<fstream>
#include<list>
using namespace std;

class helper
{
public:
	static void removeChars(string& word)
	{
		for (int i = 0;i < word.length();i++) //hello,how
		{
			if (word[i] == ',' || word[i] == '.' || word[i] == '-' || word[i] == '(' || word[i] == ')'||word[i]==';'||word[i]==':')
			{
				for (int k = i;k < word.length();k++)
				{
					word[k] = word[k + 1];
				}
				word.pop_back();       //last character of string removes
				i--;
			}
		}
	}
	static string convertLowerDigiTword(string& word)
	{
		for (int i = 0;i < word.length();i++)
		{
			if (word[i] >= 'A' && word[i] <= 'Z')
			{
				word[i] = word[i] + 32;
			}
		}
		return word;
	}
};

class Occurrence 
{

	int ChapterNo;
	int PageNo;
	int LineNo;
public:
	
	Occurrence(int chap = 0, int pg = 0, int lin = 0)
	{
		ChapterNo = chap;
		PageNo = pg;
		LineNo = lin;
	}
	friend ostream& operator<<(ostream& out, Occurrence& occurr)
	{
		out << "Chapter Number: " << occurr.ChapterNo<<" ";
		out << "Page number: " << occurr.PageNo << " ";
		out << "Line Number: " << occurr.LineNo << " ";
		return out;
	}

	/*bool operator <(Occurrence& o)
	{
		if (ChapterNo < o.ChapterNo)
		{
			return true;
		}
		else if (ChapterNo > o.ChapterNo)
		{
			return false;
		}
		else
		{
			if (PageNo < o.PageNo)
			{
				return true;
			}
			else if (PageNo > o.PageNo)
			{
				return false;
			}
			else
			{
				if (LineNo < o.LineNo)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}*/

};

template<class T>
class BST
{
private:
	class node
	{
	public:
		T data;
		node* leftchild;
		node* rightchild;
		node(T d = "", node* left = nullptr, node* right = nullptr)
		{
			data = d;
			leftchild = left;
			rightchild = right;
		}
	};
	node* root;
public:
	BST()
	{
		root = nullptr;

	}
	void insertWord(node* &r, T d)
	{
		

		if (r == nullptr)
		{
			r = new node;
			r->data = d;
			r->leftchild = nullptr;
			r->rightchild = nullptr;
			return;
		}
		else if (d < r->data)
		{
			insertWord(r->leftchild, d);
		}
		else if (d > r->data)
		{
			insertWord(r->rightchild, d);
		}
		
	}
	void insert(T str)
	{
		insertWord(root, str);
		
	}
	bool searchStopWord(node* r, T str)
	{
		if (r != nullptr)
		{
			if (r->data == str)
			{
				return true;
			}
			else if (r->data > str)
			{
				return searchStopWord(r->leftchild, str);

			}
			else if (r->data < str)
			{
				return searchStopWord(r->rightchild, str);
			}
		}
		else
		{
			return false;
		}
	}
	bool search(T str)
	{
		return searchStopWord(root, str);
	}
	void printStopWords(node* &r)
	{
		if (r != nullptr)
		{
			printStopWords(r->leftchild);
			cout << r->data << " <-> \n";
			printStopWords(r->rightchild);
		}
		
	}
	void print()
	{
		printStopWords(root);
	}
	void destroy(node* r)
	{
		if (r != nullptr)
		{
			destroy(r->leftchild);
			destroy(r->rightchild);
			delete r;
		}
		else
		{
			return;
		}
	}
	~BST()
	{
		destroy(root);
	}
};

template<class k>
class SpecializedBST
{
private:
	class snode
	{
	public:
		k data;
		snode* leftchild;
		snode* rightchild;
		list<Occurrence> occurences;
		snode(k d ="", snode* left = nullptr, snode* right = nullptr, Occurrence ocurr=0)
		{
			data = d;
			leftchild = left;
			rightchild = right;
			occurences.push_back(ocurr);

		}
		/*snode(k d="")
		{
			data = d;
			leftchild = nullptr;
			rightchild = nullptr;
		}*/

		
	};
	snode* root;
	int size;
public:
	SpecializedBST()
	{
		root = nullptr;
		size = 0;
	}
	void deepCopy(snode* thisRoot, snode* RHSroot)
	{
		if (RHSroot != nullptr)
		{
			thisRoot = new snode(RHSroot->data);
			thisRoot->occurences = RHSroot->occurences;
			deepCopy(thisRoot->leftchild, RHSroot->leftchild);
			deepCopy(thisRoot->rightchild, RHSroot->rightchild);
		}
		else
		{
			return;
		}
	}
	SpecializedBST(SpecializedBST& BST)
	{
		root = nullptr;
		size = 0;
		deepCopy(root, BST.root);
		size = BST.size;
	}
	SpecializedBST& operator=(const SpecializedBST& BST)
	{
		deepCopy(root, BST.root);
		size = BST.size;
		return *this;
	}
	void insertWord(snode*& r, k const d,Occurrence& occurr)
	{


		if (r == nullptr)
		{
			r = new snode(d,nullptr,nullptr,occurr);
			size++;
			return;
		}
		else if (d < r->data)
		{
			insertWord(r->leftchild, d,occurr);
		}
		else if (d > r->data)
		{
			insertWord(r->rightchild, d,occurr);
		}
		else
		{
			r->occurences.push_back(occurr);
			return;
		}

	}
	void insert(k str,Occurrence& occurr)
	{
		insertWord(root, str,occurr);

	}
	snode* Max(snode* child)
	{
		while (child->rightchild != nullptr)
		{
			child = child->rightchild;
		}
		return child;
	}
	void removeWord(snode*& r,k str)
	{
		if (r != nullptr)
		{
			if (r->data == str)
			{
				
				if (r->leftchild == nullptr && r->rightchild == nullptr)
				{
					delete r;
					r = nullptr;
				}
				else if (r->leftchild != nullptr && r->rightchild == nullptr)
				{
					snode* temp = r->leftchild;
					delete r;
					r = temp;
				}
				else if (r->leftchild == nullptr && r->rightchild != nullptr)
				{
					snode* temp = r->rightchild;
					delete r;
					r = temp;
				}

				else if (r->leftchild != nullptr && r->rightchild != nullptr)
				{
					snode* maximum = Max(r->leftchild);
					r->data = maximum->data;
					r->occurences = maximum->occurences;

					removeWord(r->leftchild, maximum->data);
					return;
				}
				cout << "succesfully deleted\n";
				size--;
			}
			else if (r->data > str)
			{
				removeWord(r->leftchild, str);
			}
			else if (r->data < str)
			{
				removeWord(r->rightchild, str);
			}
		}
	}
	void DeleteWord(k str)
	{
		removeWord(root, str);
	}
	bool searchWord(snode* r, k str, snode*& word) 
	{
		if (r == nullptr)
		{
			return false; 
		}
		else
		{
			if (r->data == str)
			{
				word = r;
				return true;
			}
			else if (r->data > str)
			{
				return searchWord(r->leftchild, str,word);

			}
			else if (r->data < str)
			{
				return searchWord(r->rightchild, str,word);
			}
		}
	}
	snode* search(k str)
	{
		snode* found = nullptr;
		bool srch = searchWord(root, str,found);

		if (srch != true)
		{
			cout << " this word not exist in specialized BST tree\n\n\n";
		}
		else
		{
			cout << found->data << " <-> \n";
			//cout << found->leftchild << " <-> ";
			//cout << found->rightchild << " <-> ";
			list<Occurrence>::iterator it = found->occurences.begin();
			for (it;it != found->occurences.end();++it)
			{
				cout << *(it) << endl << endl;
			}
		}
		return found;
		
	}
	void printtextFileWords(snode* &r)
	{
		if (r != nullptr)
		{
			printtextFileWords(r->leftchild);
			cout << r->data << " <-> \n";
			
			list<Occurrence>::iterator it = r->occurences.begin();
			for (it; it != r->occurences.end(); ++it)
			{
				cout << *(it) << endl << endl;
			}
			printtextFileWords(r->rightchild);
		}
	/*	else
		{
			cout << "\nnothing in stop words BST\n\n";
		}*/
	}
	void print()
	{
		printtextFileWords(root);
	}
	void MergedArrayToBST(snode*& r, snode* &array, int startNode, int lastNode)
	{
		if (startNode > lastNode)
		{
			return;
		}
		else
		{
			int midNode = (startNode + lastNode +1) / 2;
			size++;
			r = new snode(array[midNode]);
			MergedArrayToBST(r->leftchild, array, startNode, midNode - 1);
			MergedArrayToBST(r->rightchild, array, midNode + 1, lastNode);
		}
	}
	void storeArray(snode* &r, snode*& array, int& arraySize)
	{
		if (r != nullptr)
		{
			storeArray(r->leftchild, array, arraySize);
			array[arraySize].data = r->data;
			array[arraySize].occurences = r->occurences;
			arraySize++;
			storeArray(r->rightchild, array, arraySize);
		}
		
	}
	SpecializedBST* mergeBSTs(SpecializedBST& BST)
	{
		SpecializedBST<string>* MergedBST = new SpecializedBST;
		int array1Size = 0;
		int array2Size = 0;
		int array3Size = 0;

		snode* firstBstArray = new snode[size];
		snode* secondBstArray = new snode[BST.size];
		storeArray(root, firstBstArray, array1Size);
		BST.storeArray(BST.root, secondBstArray, array2Size);

		/*for (int i = 0;i < array1Size;i++)
		{
			cout << firstBstArray[i].data << " ";
		}*/
		snode* mergedArray = new snode[size + BST.size];
		array1Size = 0;
		array2Size = 0;

		while (array1Size < size && array2Size < BST.size)
		{
			
			if(firstBstArray[array1Size].data < secondBstArray[array2Size].data)
			{
				mergedArray[array3Size].data = firstBstArray[array1Size].data;
				mergedArray[array3Size].occurences = firstBstArray[array1Size].occurences;
				array1Size++;
				array3Size++;
			}
			else if (firstBstArray[array1Size].data > secondBstArray[array2Size].data)
			{
				mergedArray[array3Size].data = secondBstArray[array2Size].data;
				mergedArray[array3Size].occurences = secondBstArray[array2Size].occurences;
				array2Size++;
				array3Size++;
			}
			else
			{
				mergedArray[array3Size].data = firstBstArray[array1Size].data;
				mergedArray[array3Size].occurences = firstBstArray[array1Size].occurences;
				array1Size++;
				array2Size++;
				array3Size++;
			}
		}
		while (array1Size < size)
		{
			mergedArray[array3Size].data = firstBstArray[array1Size].data;
			mergedArray[array3Size].occurences = firstBstArray[array1Size].occurences;
			array1Size++;
			array3Size++;
		}
		while (array2Size < BST.size)
		{
			mergedArray[array3Size].data = secondBstArray[array2Size].data;
			mergedArray[array3Size].occurences = secondBstArray[array2Size].occurences;
			array2Size++;
			array3Size++;
		}
		/*for (int i = 0;i < array3Size;i++)
		{
			cout << mergedArray[i].data << "\n";
		}*/
		MergedBST->MergedArrayToBST(MergedBST->root, mergedArray, 0, array3Size - 1);
		//MergedBST->print();
		return MergedBST;

	}
	list<string> commonWordsFrOMBst(SpecializedBST& BST)
	{
		int array1Size = 0;
		int array2Size = 0;
		int array3Size = 0;

		snode* firstBstArray = new snode[size];
		snode* secondBstArray = new snode[BST.size];
		storeArray(root, firstBstArray, array1Size);
		BST.storeArray(BST.root, secondBstArray, array2Size);

		list<string> commonWords;
		array1Size = 0;
		array2Size = 0;

		while (array1Size < size && array2Size < BST.size)
		{
			if (firstBstArray[array1Size].data > secondBstArray[array2Size].data)
			{
				array2Size++;
			}
			else if (firstBstArray[array1Size].data < secondBstArray[array2Size].data)
			{
				array1Size++;
			}
			else
			{
				commonWords.push_back(firstBstArray[array1Size].data);
				array1Size++;
				array2Size++;
			}
		}
		return commonWords;
	}
	void destroy(snode* r)
	{
		if (r != nullptr)
		{
			destroy(r->leftchild);
			destroy(r->rightchild);
			r->occurences.clear();
			delete r;
		}
	}
	~SpecializedBST()
	{
		destroy(root);
	}
};
int main()
{
	BST<string> stopWordsTree;

	fstream fin;
	fin.open("stopWords.txt");
	
	if (!fin.is_open())
	{
		cout << "\n no File Exist\n";
	}
	else
	{
		string word;
		fin >> word;
		while (!fin.eof())
		{
			
			stopWordsTree.insert(word);
			fin >> word;
			
		}
		fin.close();
	}
	//stopWordsTree.print();


	SpecializedBST<string> inputTree;
	
	int chapter = 0, page = 0, line = 0;
	string inputWord;
	Occurrence* occurr = nullptr;
	fstream file;

	file.open("Input.txt");
	if (!file.is_open())
	{
		cout << "\n no file exist\n\n";
	}
	else
	{
		char charctr;
		
		while (!file.eof())
		{
			file.get(charctr);

			if (charctr != ' ' && charctr != '\n')
			{
				inputWord = inputWord + charctr;
			}
			else
			{
				if (charctr == '\n')
				{
					line++;
				}
				else if (inputWord == "Chapter")
				{
					file >> chapter;
				}
				else if (inputWord == "Page")
				{
					file >> page;
				}
				else
				{
					if (inputWord != "")
					{
						helper::removeChars(inputWord);
						string inputWordLower = helper::convertLowerDigiTword(inputWord);
						if ((stopWordsTree.search(inputWord) == false) && (stopWordsTree.search(inputWordLower)==false))
						{
							occurr = new Occurrence(chapter, page, line);
							inputTree.insert(inputWord, *occurr);

						}

					}
				}
				inputWord.clear();

			}

		}
	}
	file.close();
	cout << "==========================================================\n";
	cout << "=====================  FIRST BST  ========================\n";
	cout << "==========================================================\n\n";
	//inputTree.print();
	
	cout << "==========================================================\n";
	cout << "=====================  SEARCH BST  ========================\n";
	cout << "==========================================================\n\n";
	inputTree.search("data");
	inputTree.search("HAMDAN");
	cout << "===========================================================\n";
	cout << "=====================  DELETE BST  ========================\n";
	cout << "==========================================================\n\n";
	inputTree.DeleteWord("a");
	inputTree.DeleteWord("data");
	inputTree.print();
	SpecializedBST<string> inputTree2;

	int chapter1 = 0, page1 = 0, line1 = 0;
	string inputWord1;
	Occurrence* occurr1 = nullptr;
	fstream file1;

	file1.open("Input2.txt");
	if (!file1.is_open())
	{
		cout << "\n no file exist\n\n";
	}
	else
	{
		char charctr1;

		while (!file1.eof())
		{
			file1.get(charctr1);

			if (charctr1 != ' ' && charctr1 != '\n')
			{
				inputWord1 = inputWord1 + charctr1;
			}
			else
			{
				if (charctr1 == '\n')
				{
					line1++;
				}
				else if (inputWord1 == "Chapter")
				{
					file1 >> chapter1;
				}
				else if (inputWord1 == "Page")
				{
					file1 >> page1;
				}
				else
				{
					if (inputWord1 != "")
					{
						helper::removeChars(inputWord1);
						string inputWordLower1 = helper::convertLowerDigiTword(inputWord1);
						if ((stopWordsTree.search(inputWord1) == false) && (stopWordsTree.search(inputWordLower1) == false))
						{
							occurr1 = new Occurrence(chapter1, page1, line1);
							inputTree2.insert(inputWord1, *occurr1);

						}

					}
				}
				inputWord1.clear();

			}

		}
	}
	file1.close();
	//inputTree2.print();
	
	SpecializedBST<string>* inputTree3;

	inputTree3 = inputTree.mergeBSTs(inputTree2);
	cout << "==========================================================\n";
	cout << "=====================  MERGED BST  =======================\n";
	cout << "==========================================================\n\n";
	inputTree3->print();


	cout << "============================================================\n";
	cout << "=====================  COMMON WORDS  =======================\n";
	cout << "============================================================\n\n";
	list<string> commonWords = inputTree.commonWordsFrOMBst(inputTree2);
	list<string>::iterator it = commonWords.begin();
	for (it;it != commonWords.end();++it)
	{
		cout << *(it) << endl;
	}
	
	system("pause");
	return 0;
}












