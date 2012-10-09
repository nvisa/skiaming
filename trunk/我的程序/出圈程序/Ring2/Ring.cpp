#include <iostream>
#include <windows.h>
using namespace std;
int main(int argc, char* argv[])
{
	int iCount, iRing, iNumber = 0;
	cin>>iCount>>iRing;	
	int* pMember = new int[iCount + 1];
	memset(pMember, 1, sizeof(int)* (iCount+1));
	int iAll = iCount;
	for(int i = 1; iCount > 0; i++)
	{
		int iIndex = i%(iAll+1);
		if(iIndex == 0) iIndex = i = 1;
		if(pMember[iIndex] && !(++iNumber%iRing))
		{
			iCount --;
			cout << iIndex << endl;
			Sleep(200);
			pMember[iIndex] = 0;
			iNumber = 0;
		}
	}
	delete [] pMember;
	pMember = NULL;
	getchar();
	return 0;
}