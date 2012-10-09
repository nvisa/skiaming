#include <iostream>
#include <list>
using namespace std;
void main()
{
	list<int> lInt;
	int nCount, nGap;
	cin >> nCount >> nGap;
	for(list<int>::size_type i = 1; i <= nCount; ++i)
		lInt.push_back(i);
	list<int>::iterator iter = lInt.begin();
	int nGapTemp = 0;
	while(iter != lInt.end())
	{
		++nGapTemp;
		if(nGapTemp == nGap)
		{
			cout << *iter << " ";
			iter = lInt.erase(iter);
			if(iter == lInt.end()) iter = lInt.begin();
			nGapTemp = 0;
			continue;
		}
		iter++;
		if(iter == lInt.end()) iter = lInt.begin();
	}
}