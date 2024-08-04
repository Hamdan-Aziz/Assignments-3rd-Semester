
#include<iostream>
#include<string>
#include<ctime>
using namespace std;

template<class T>
class List
{
private:

	class node
	{
	public:
		T data;
		node* next;
		node* prev;

		node(node* n = 0, node* p = 0)
		{
			next = n;
			prev = p;
		}
	};

	node* head;
	node* tail;
	int count;

public:
	class Iterator
	{
	public:
		node* curr;
		Iterator(node* n = nullptr)
		{
			curr = n;
		}
		Iterator(Iterator& rhs)
		{
			curr = rhs.curr;
		}
		Iterator& operator++()
		{
			curr = curr->next;
			return *this;

		}
		Iterator& operator=(const Iterator& rhs)
		{
			curr = rhs.curr;
			return *this;
		}

		T& operator*()
		{
			return curr->data;
		}
		bool operator==(const Iterator& rhs)
		{
			if (curr == rhs.curr)
			{
				return true;
			}
			return false;
		}
		bool operator!=(const Iterator& rhs)
		{
			if (curr != rhs.curr)
			{
				return true;
			}
			return false;
		}
		void Delete()
		{
			node* p = curr;

			p->prev->next = p->next;
			p->next->prev = p->prev;
			curr = p->prev;
			delete p;

		}



	};
	List()
	{
		count = 0;
		head = new node;
		tail = new node;
		head->next = tail;
		tail->prev = head;
		head->prev = nullptr;
		tail->next = nullptr;
	}
	Iterator& insertion(Iterator& it, T& d)
	{
		node* p = it.curr;
		node* t = new node;
		t->data = d;
		t->next = p;
		t->prev = p->prev;
		p->prev->next = t;
		p->prev = t;

		Iterator ret(t);

		return ret;

	}
	Iterator& insertAtHead(T& d)
	{
		count++;
		Iterator it(head->next);
		insertion(it, d);
		return it;
	}
	Iterator& insertAtTail(T& d)
	{
		count++;
		Iterator it(tail);
		insertion(it, d);
		return  it;
	}
	Iterator& begin()
	{
		Iterator it(head->next);
		return it;
	}
	Iterator& end()
	{
		Iterator it(tail);
		return it;
	}
	void deleteItr(const int& accNum)
	{
		Iterator itr = search(accNum);
		if (itr != 0)
		{
			itr.Delete();
			count--;
		}
		else
		{
			cout << "not found , so it could not delete !\n\n";
		}


	}


	Iterator& search(const int& accNum)
	{
		Iterator itr;

		for (itr = begin(); itr != end(); ++itr)
		{
			if ((*itr) == accNum)
			{
				return itr;
			}
		}
		Iterator itr1(0);
		return itr1;
	}
	void sort()
	{
		for (int i = 0; i < count; i++)
		{
			Iterator itr = begin();
			Iterator itr1 = begin();
			++itr1;
			for (int j = 0; j < count - 1; j++)
			{
				if (*(itr1) < *(itr))
				{
					T obj = *(itr);
					*(itr) = *(itr1);
					*(itr1) = obj;
				}
				++itr;
				++itr1;
			}
		}
	}
	void deleteAtStart()
	{
		if (head->next == tail)
		{
			cout << "already null\n";
		}
		else
		{
			Iterator itr(head->next);
			itr.Delete();
			count--;

		}
	}
	void print()
	{
		Iterator itr;

		for (itr = begin(); itr != end(); ++itr)
		{
			(*itr).printAccountDetails();
		}
	}
	~List()
	{

		while (head->next != tail)
		{
			deleteAtStart();

		}
		delete head;
		delete tail;
		head = tail = 0;
	}

};



class bank
{
private:
	class transaction
	{

	private:
		int transactionId;
		string transactionDate;
		string transactionType;
		double transferredAmount;
		int accountNumber;
		time_t systemtime;
	public:
		transaction(const int& id = 0, const string& type = "", double amnt = 0, const int& number = 0)
		{
			transactionId = id;
			transactionType = type;
			transferredAmount = amnt;
			accountNumber = number;
			systemtime = time(nullptr);
		}
		transaction(const transaction& rhs)
		{
			transactionId = rhs.transactionId;
			transactionType = rhs.transactionType;
			transferredAmount = rhs.transferredAmount;
			accountNumber = rhs.accountNumber;
			systemtime = rhs.systemtime;

		}
		const transaction& operator=(const transaction& rhs) {
			transactionId = rhs.transactionId;
			transactionType = rhs.transactionType;
			transferredAmount = rhs.transferredAmount;
			accountNumber = rhs.accountNumber;
			systemtime = rhs.systemtime;
			return *this;
		}
		bool operator<(const transaction& rhs)
		{
			if (transactionId < rhs.transactionId)
			{
				return true;
			}
			return false;
		}
		void printAccountDetails()
		{
			cout << "Transaction history details :\n\n";
			cout << "transaction Id:\t" << transactionId << endl;
			cout << "transaction type:\t" << transactionType << endl;
			cout << "transferred Amount:\t" << transferredAmount << endl;
			cout << "account number:\t" << accountNumber << endl;
			char* arrTime = new char[50];
			ctime_s(arrTime, 50, &systemtime);
			cout << "Date&Time :\t" << arrTime << endl;
		}
	};


	class account
	{
	public:
		int accountNumber;
		string accountTitle;
		double accountBalance;
		List<transaction> history;

		account(const int& number = 0, const string& title = "", double amnt = 0)
		{
			accountNumber = number;
			accountTitle = title;
			accountBalance = amnt;
		}
		
		const account& operator=(account& rhs)
		{
			accountNumber = rhs.accountNumber;
			accountBalance = rhs.accountBalance;
			accountTitle = rhs.accountTitle;
			List<transaction>::Iterator itr;


			for (itr = rhs.history.begin(); itr != rhs.history.end(); ++itr) {
				transaction it = *itr;
				history.insertAtTail(it);
			}
			return *this;
		}
		void creditTtransaction(int tranSerial, double amnt)
		{
			accountBalance = accountBalance + amnt;
			transaction creditTrans(tranSerial, "credit", amnt, accountNumber);
			history.insertAtTail(creditTrans);            // added to transaction linkedlist
			cout << "Credit transaction performed successfully !!!\n\n";
		}
		void debitTransaction(int tranSerial, double amnt)
		{
			if (accountBalance >= amnt)
			{
				accountBalance = accountBalance - amnt;
				transaction deditTran(tranSerial, "debit", amnt, accountNumber);
				history.insertAtTail(deditTran);
				cout << "Debit transaction performed successfully !!!\n\n";
			}
			else
			{
				cout << "Not enough money to withdraw , so can't perform this transaction !!!\n\n";
			}
		}

		account mergeTwoAcnts(account& acnt, int serial, const string& title)
		{
			account mergeAcnt(serial, title, accountBalance + acnt.accountBalance);

			List<transaction>::Iterator it;

			for (it = history.begin(); it != history.end(); ++it)
			{

				transaction itr = *it;
				mergeAcnt.history.insertAtTail(itr);
			}
			for (it = acnt.history.begin(); it != acnt.history.end(); ++it)
			{
				transaction itr = *it;
				mergeAcnt.history.insertAtTail(itr);
			}

			mergeAcnt.history.sort();
			return mergeAcnt;
		}
		bool operator==(const int& rhsAccNum)
		{
			if (accountNumber == rhsAccNum)
			{
				return true;
			}
			return false;
		}
		void printAccountDetails()
		{
			cout << "Account information is below :\n\n";
			cout << "account numnber:\t" << accountNumber << endl;
			cout << "account title:\t" << accountTitle << endl;
			cout << "account balance:\t" << accountBalance << endl;
			
			history.print();
		}
	};
	List<account> accounts;
	int acc_serial;
	int trans_serial;
public:
	bank()
	{
		acc_serial = 0;
		trans_serial = 0;

	}
	void performTransaction(const int& accNum, const string& type, double amnt)
	{
		if ((accounts.search(accNum)) != 0)
		{
			if (type == "credit")
			{
				trans_serial++;
				(*accounts.search(accNum)).creditTtransaction(trans_serial, amnt);
			}
			else if (type == "debit")
			{
				trans_serial++;
				(*accounts.search(accNum)).debitTransaction(trans_serial, amnt);
			}
			else
			{
				cout << " no such type of type is present OR check the spellings of types from the code \n";
			}
		}
		else
		{
			cout << "No such account is present ,so can't perfrorm transaction\n";
		}
	}
	void addAcount(const int& number, const string& title, double amnt)
	{
		account acnt(number, title, amnt);
		acc_serial++;
		accounts.insertAtTail(acnt);
	}
	void removeAccount(const int& accNum)
	{
		accounts.deleteItr(accNum);
		//acc_serial--;
	}
	void mergeAccounts(const int& accNum1, const int& accNum2)
	{
		
		if ((accounts.search(accNum1))!=0 && (accounts.search(accNum2)!=0))
		{
			acc_serial++;
			
			account merge = ((*accounts.search(accNum1)).mergeTwoAcnts(*accounts.search(accNum2), acc_serial, "MergedAccount"));

			accounts.insertAtTail(merge);
			accounts.deleteItr(accNum1);
			//acc_serial--;
			accounts.deleteItr(accNum2);
			//acc_serial--;
		}
		else
		{
			cout << "no such account is present , so they cant be merged,INVALID!!\n\n";
		}
	}

	void print()
	{
		cout << " account serial:\t" << acc_serial << endl;
		cout << " transaction serial:\t" << trans_serial << endl;
		accounts.print();

	}
};


int main()
{
	bank HamdanBank;

	HamdanBank.addAcount(1, "Current", 1000);
	HamdanBank.addAcount(2, "saving", 2000);
	HamdanBank.addAcount(3, "Current", 3000);
	HamdanBank.addAcount(4, "Current&saving", 4000);
	


	//HamdanBank.removeAccount(3);
	HamdanBank.removeAccount(5);

	HamdanBank.performTransaction(1, "credit", 5000);
	HamdanBank.performTransaction(2, "debit", 500);
	HamdanBank.performTransaction(2, "credit", 5000);
	HamdanBank.performTransaction(1, "credit", 500);
	HamdanBank.performTransaction(1, "credit", 5000);
	HamdanBank.performTransaction(1, "debit", 5000);

	HamdanBank.mergeAccounts(1, 2);



	HamdanBank.print();

	
	system("pause");
	return 0;
}