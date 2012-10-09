#include <iostream>
#include <windows.h>
using namespace std;
int main(int argc, char* argv[])
{
	int num, num_ring;
	cin >> num >>num_ring;
	int* ring = new int[num +1];
	int iremainder = 0;
	for(int i = 0; i < num +1; i++) ring[i] = i;
	for(int j = 1; j < num +1; j ++)
	{
		while(ring[j])
		{
			for(int k = j; k < num +1; k++)
			{
				if(ring[k])
				{
					iremainder ++;
					iremainder %= num_ring;
					if(!iremainder)
					{						
						cout << ring[k] << endl;
						//Sleep(100);
						ring[k] = 0;
					}
				}
			}
		}
	}
	delete ring;
	getchar();
	return 0;
}