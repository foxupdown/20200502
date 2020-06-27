#include <iostream>
using namespace std;
#include <string>
#include <deque>
#include <algorithm>
#include <vector>
#include <map>
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
class worker
{
	public:
		string name;
		int m_money;
};
enum {RENLI , YANFA , UI};
void create_worker(vector<worker>&workers)
{
	string nameSeed = "ABCDE";
	for(int i = 0 ; i  < 5 ; i ++)
	{
		string name = "员工";
		name += nameSeed[i];
		int money = rand()%10000 + 5000;
		worker w;
		w.name = name;
		w.m_money = money;
		workers.push_back(w);
	}
}
void setGroup(vector<worker>&v , multimap<int , worker>&multWorkers)
{
	cout << "----------------------------------\n";
	for(vector<worker>::iterator it = v.begin() ; it != v.end(); it ++)
	{
		int departmentId = rand()% 3;
		multWorkers.insert(make_pair(departmentId , *it));
	}
}
void showGroup(multimap<int , worker>&multWorkers)
{
	int cnt = multWorkers.count(RENLI);
	int index = 0;
	multimap<int , worker>::iterator it = multWorkers.find(RENLI);
	for(;it != multWorkers.end(),index < cnt ; it ++,index ++ )
	{
		cout << it->second.name << ':' << it->second.m_money << endl;
	}
}
int main()
{
	vector<worker> work;
	create_worker(work);
	for(vector<worker>::iterator it = work.begin();it != work.end() ; it ++)
	{
		cout << it->name << "  " << it -> m_money << endl ;
	}
	cout << "hello world" << endl;
	multimap<int , worker> multWorker;
	setGroup(work , multWorker);
	showGroup(multWorker);
	return 0;
}
