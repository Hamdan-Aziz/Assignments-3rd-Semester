

#include<iostream>
#include<fstream>
#include<vector>
#include<list>
using namespace std;

template<class t, class k>
class heapItem
{
public:
	t time;
	k id;
	string prev;
	heapItem()
	{
		time = 0;
		id = "";
	}
};
template<class t, class k>
class Heap
{

	heapItem<t, k>* arr;
	int capacity;
	int heapSize;
public:

	Heap(int cap = 0)
	{
		arr = new heapItem<t, k>[cap];
		capacity = cap;
		heapSize = 0;
	}

	void insert(k ID, t tim)
	{
		if (heapSize == capacity)
		{
			capacity = capacity * 2;
			heapItem<t, k>* newArray = new heapItem<t, k>[capacity];
			for (int i = 1; i <= heapSize; i++)
			{
				newArray[i] = arr[i];
			}
			delete[] arr;
			arr = newArray;

		}

		arr[++heapSize].id = ID;
		arr[heapSize].time = tim;
		int i = heapSize;

		while ((i / 2) > 0 && arr[i / 2].time > arr[i].time)
		{
			swap(arr[i / 2], arr[i]);
			i = i / 2;
		}
	}
	bool isEmpty()
	{
		if (heapSize == 0)
		{
			return true;
		}
		return false;
	}
	void heapify(int i)
	{
		if (i > heapSize)
		{
			return;
		}
		int smallest = i;
		int left = i * 2;
		int right = (i * 2) + 1;

		if (left < heapSize && arr[left].time < arr[smallest].time)
		{
			smallest = left;
		}
		if (right < heapSize && arr[right].time < arr[smallest].time)
		{
			smallest = right;
		}
		if (smallest != i)
		{
			swap(arr[smallest], arr[i]);
			heapify(smallest);
		}
	}
	void decreaseKey(k ID, t tim, string pre)
	{
		if (!isEmpty())
		{

			for (int i = 1; i <= heapSize; i++)
			{
				if (arr[i].id == ID)
				{
					if (arr[i].time > tim)
					{
						arr[i].time = tim;
					}
					
					arr[i].prev = pre;
					heapify(i / 2);
					break;
				}
			}
		}

	}

	heapItem<t, k> deleteInHeap()
	{
		if (!isEmpty())
		{
			heapItem<t, k> hp;
			hp = arr[1];
			arr[1] = arr[heapSize];
			--heapSize;
			heapify(1);
			return hp;
		}
		else
		{
			"\nAlready Empty \n";
		}
	}

	/*heapItem getMinHeapTop()
	{
		if (!isEmpty())
		{
			return arr[1];
		}
		else
		{
			"\nEmpty \n";
		}
	}*/

	void print()
	{
		for (int i = 1; i <= heapSize; i++)
		{
			cout << "( " << arr[i].id << " - " << arr[i].time << " )\n";
		}
		cout << "\n\n";
	}

	~Heap()
	{
		if (arr != 0)
		{
			delete[] arr;
		}
	}
};

template<class t, class k>
class Hospital
{
public:
	string id;
	list<heapItem<t, k>> lst;
};

template<class t, class k>
class routingSystem
{
private:
	vector<Hospital<t, k>> routing;
	int total;

public:

	void ReadDataFromFile()
	{
		ifstream file;
		file.open("data.txt");

		if (file.is_open())
		{
			int n;
			file >> n;
			total = n + 1;
			for (int i = 0; i < total; i++)
			{
				string un;
				file >> un;
				Hospital<t, k> obj;
				obj.id = un;
				char ch;
				file >> ch;
				while (ch != '\n' && !file.eof())
				{
					if (ch == '(')
					{
						char chr[5];
						file.get(chr, 5, ',');
						file.ignore();

						int time;
						file >> time;

						heapItem<t, k> heap;
						heap.id = chr;
						heap.time = time;

						obj.lst.push_back(heap);

					}
					file.get(ch);
				}
				routing.push_back(obj);
			}
		}
		else
		{
			cout << "file is Not oPen\n\n";
		}
		file.close();
	}

	void FindOptimalRoutes()
	{
		Heap<t, k> Queue(total + 1);

		for (int i = 0; i < total; i++) // i=1 because of heap start at 1 index
		{
			if (i == 0)
			{
				Queue.insert(routing[i].id, 0);
			}
			else
			{
				Queue.insert(routing[i].id, INT_MAX);
			}
		}
		int index = 0;
		heapItem<t,k> arr[5];

		for (int i = 0; i < total; i++)
		{
			heapItem<t, k> obj;

			obj = Queue.deleteInHeap();

			class list<heapItem<t, k>>::iterator itr1;
			class list<heapItem<t, k>>::iterator itr2;

			cout << "From UN to .... " << obj.id << " in --> " << obj.time << " <-- Minutes " << endl;

			for (int i = 0; i < total; i++)
			{
				if (routing[i].id == obj.id)
				{
					itr1 = (routing[i].lst).begin();
					itr2 = (routing[i].lst).end();
					break;
				}
			}

			arr[index] = obj;
			index++;

			while (itr1 != itr2)
			{
				Queue.decreaseKey((*itr1).id, (*itr1).time + obj.time, obj.id);
				itr1++;
			}
			
			cout << "PATH of " << arr[i].id << " ... (";
			cout << arr[i].id << " <-- ";

			
			cout << arr[i].prev << " <-- ";
			for (int j = 0;j < 5; j++)
			{
				if (i != j && arr[i].prev == arr[j].id)
				{
					cout << arr[j].prev ;
				}
			}
			cout <<" <-- )"<< endl << endl;

		}
	}

	void print()
	{
		for (int i = 0; i < total; i++)
		{
			auto itr1 = (routing[i].lst).begin();
			auto itr2 = (routing[i].lst).end();
			cout << "=> " << routing[i].id << " <=\n";
			while (itr1 != itr2)
			{

				cout << (*itr1).id << " -- " << (*itr1).time << " |---| ";
				itr1++;
			}
			cout << "\n\n";
		}
	}
};
int main()
{
	routingSystem<int, string> route;

	route.ReadDataFromFile();

	route.FindOptimalRoutes();
	cout << "\n\nPRINTING HOSPITAL ALL ROUTES \n\n";
	route.print();



	system("pause");
	return 0;
}