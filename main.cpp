#include "Array.h"
int main()
{
	Array<int> a(5);
	a += 7;
	a += 3;
	a += 8;
	a += 12;
	a += 0;
	a[100] = 3;
	a += 15;
	Array<int> b(20);
	b += 100;
	b += 1000;
	b += 10000;
	b.Insert(1, a);
	b.Insert(2, 2);
	b.Insert(4, 20);
	b.Delete(5);
	a.Sort();
	b.Sort(b.compare_mai_mare);
	a.Print();
	b.Print();
	if (a.BinarySearch(3, a.compare_mai_mare) != -1)
		cout << "True" << endl;
	else cout << "False" << endl;
	Compare_Egal<int> *c = nullptr;
	if (b.Find(13, c) != -1)
		cout << "True" << endl;
	else cout << "False" << endl;
	for (auto i : a)
		cout << *i << ' ';
	return 0;
}