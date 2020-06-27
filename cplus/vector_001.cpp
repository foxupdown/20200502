#include <iostream>
using namespace std;
#include <deque>
#include <algorithm>
void print_enum(deque<int>&d)
{
	for(deque<int>::iterator it = d.begin(); it != d.end(); it ++)
		cout << *it << " ";
	cout << endl;
}
bool my_compare(int v1 , int v2)
{
	return v1 < v2;
}
int main()
{
	deque<int>	d;
	d.push_back(5);
	d.push_front(12);
	d.push_front(15);
	d.push_front(11);
	print_enum(d);
	//sort(d.begin() , d.end());
	sort(d.begin() , d.end() , my_compare);
	d.pop_front();
	d.pop_back();
	print_enum(d);
	cout << "hello world" << endl;
	return 0;
}
