#include <iostream>
#include <string>

using namespace std;
const int MAX = 9999;

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}
int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

class road
{
public:
	int length;
	int a, b;
	void print()
	{
		cout << a << " " << b << " " << length;
	}
	bool operator <(const road& right)
	{
		if (length < right.length)
			return true;
		else if (length > right.length)
			return false;
		else if (min(a, b) < min(right.b, right.a))
			return true;
		else if (min(a, b) == min(right.a, right.b) && max(a, b) < max(right.a, right.b))
			return true;
		return false;
	}
};

//road newRoads[MAX];
road *newRoads;
int edges_completed;

class Region
{
public:
	int size;
	int *vertices;
	int nextVertex;
	int root;
	int smallest;
	Region()
	{
		nextVertex = 0;
	}
	~Region()
	{
		//delete[] vertices;
		// delete[] newEdges
	}
	void printRegion()
	{
		for (int i = 0; i < size; i++)
			cout << vertices[i] << endl;
	}
	void initialize_vertices(int n) // n is the value of the first vertex
	{
		smallest = n;
		vertices = new int[size];
		//add(n);
		root = n;
	}
	void add(int n) // add a vertex w/ value n to the region
	{
		if (n < smallest)
			smallest = n;
		vertices[nextVertex] = n;
		nextVertex++;
	}
	void findAndPrintRoads()
	{
		//	road tempCopy[MAX];
	/*	road* tempCopy = new road[edges_completed];

		for (int i = 0; i < edges_completed; i++)
			tempCopy[i] = newRoads[i];*/

		for (int j = 0; j < edges_completed; j++)
		{

			for (int i = 0; i < size; i++)
			{
				if (newRoads[j].a == vertices[i] || newRoads[j].b == vertices[i])
				{
					cout << "<road>";
					if (newRoads[j].b < newRoads[j].a)
						swap(newRoads[j].b, newRoads[j].a);
					newRoads[j].print();
					cout << "</road>" << endl;

					newRoads[j].a = -1;
					newRoads[j].b = -1;
					newRoads[j].length = -1;
				}
			}
		}
	}
	bool operator <(const Region& right)
	{
		if (size < right.size)
			return true;
		else if (size > right.size)
			return false;
		else if (smallest < right.smallest)
			return true;
		return false;
	}

};

void sortRegions(Region *regions, int left, int right) // sorts from left to right w/ left being the smallest and right being the largest
{
	if (left < right)
	{
		int i = left,
			j = right + 1;
		Region pivot = regions[left]; // arbitrarily choose the pivot point
		do
		{
			do i++; while (regions[i] < pivot);
			do j--; while (pivot < regions[j]);
			if (i < j)
				swap(regions[i], regions[j]);
		} while (i < j);
		swap(regions[left], regions[j]);

		sortRegions(regions, left, j - 1);
		sortRegions(regions, j + 1, right);
	}
}


class Set
{
public:
	int *parent;
	int n;
	Region *regions;
	Set(int num)
	{
		n = num;
		parent = new int[n];
		for (int i = 0; i < n; i++)
		{
			parent[i] = -1;
		}
	}
	~Set()
	{
		delete[] parent;
		/*	delete[] parent;
		delete[] regions;*/
	}
	void printRegions()
	{
		// Count the number of regions
		int count = 0; // counter to hold the number of regions

		for (int i = 0; i < n; i++)
		if (parent[i] <= -1)
			count++;

		regions = new Region[count]; // make that many regions

		int regionIndex = 0;
		for (int i = 0; i < count; i++)
		{
			for (int j = regionIndex; j < n; j++)
			{
				if (parent[j] <= -1) // if the parent is a a negative then this is a root.
				{
					regions[i].size = parent[j] * -1; // make it positive
					regions[i].initialize_vertices(j); // create 'size' number of vertices in each region
					regionIndex = j + 1;
					break;
				}
			}
		}

		for (int j = 0; j < count; j++) // add vertices to their appropriate regions
		{
			for (int i = 0; i < n; i++)
			{
				if (parent[i] > -1)
				{
					if (parent[i] == regions[j].root) // if this i is part of this region then add
					{
						regions[j].add(i);
					}
				}
				else if (i == regions[j].root)
				{
					regions[j].add(i);
				}
			}
		}
		regions[count].size = 2147483647;
		sortRegions(regions, 0, count);

		cout << "<?xml version=\"1.5\"?>" << endl;
		cout << "<country>" << endl;
		for (int j = 0; j < count; j++) //print all regions 
		{
			cout << "<region>" << endl;
			regions[j].findAndPrintRoads();
			cout << "</region>" << endl;
		}
		cout << "</country>" << endl;
	}
	void print()
	{
		for (int i = 0; i < n; i++)
		{
			cout << parent[i] << " ";
		}
		cout << endl;
	}
	int setFind(int i)
	{
		int r;
		for (r = i; parent[r] >= 0; r = parent[r]);
		while (i != r)
		{
			int s = parent[i];
			parent[i] = r;
			i = s;
		}
		return r;
	}
	void setUnion(int i, int j)
	{
		int temp = parent[i] + parent[j];
		if (parent[i] > parent[j])
		{
			parent[i] = j;
			parent[j] = temp;
		}
		else
		{
			parent[j] = i;
			parent[i] = temp;
		}
	}
};

class graph
{
public:
	string myString;
	//road myRoads[MAX];
	road *myRoads;
	int nCity, nRoads;
	graph(){}
	~graph()
	{
	}
	void getInput()
	{
		int i = 0;
		cin >> nCity >> nRoads;
		myRoads = new road[nRoads];
		newRoads = new road[nRoads];
		for (int i = 0; i < nRoads; i++)
			std::cin >> myRoads[i].a >> myRoads[i].b >> myRoads[i].length;
	}

	void sortRoads()
	{
		myRoads[nRoads].length = 2147483647;
		_sortRoads(0, nRoads);
	}

	void _sortRoads(int left, int right) // sorts from left to right w/ left being the smallest and right being the largest
	{
		if (left < right)
		{
			int i = left,
				j = right + 1;
			road pivot = myRoads[left];
			do
			{
				do i++; while (myRoads[i] < pivot);
				do j--; while (pivot < myRoads[j]);
				if (i < j)
					swap(myRoads[i], myRoads[j]);
			} while (i < j);
			swap(myRoads[left], myRoads[j]);

			_sortRoads(left, j - 1);
			_sortRoads(j + 1, right);
		}
	}
	void KruskalMST()
	{
		sortRoads();
		edges_completed = 0;
		Set mySet(nCity);

		for (int i = 0; i < nRoads; i++)
		{

			if (mySet.setFind(myRoads[i].a) != mySet.setFind(myRoads[i].b)) // if they're not from the same set then combine
			{
				mySet.setUnion(mySet.setFind(myRoads[i].a), mySet.setFind(myRoads[i].b));
				mySet.setFind(myRoads[i].b); // collapse
				newRoads[edges_completed] = myRoads[i];
				edges_completed++;
			}
		}

		mySet.printRegions();
	}

};


int main(int argc, char *argv[])
{
	graph mygraph;
	mygraph.getInput();
	mygraph.KruskalMST();
}
