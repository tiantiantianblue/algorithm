#include<everything>
#include<boost/progress.hpp>
typedef array<int,10> digit8;
using array99 = array<array<int, 9>, 9>;
array99 table;
void init_table()
{
	for(int i=0; i!=9; ++i)
		for(int j=0; j!=9; ++j)
		{
			table[i][j] = abs(i/3-j/3) + abs(i%3-j%3);
		}
}
inline int priority(const digit8& src, const digit8& des)
{
	int pr=0;
	for(int i=0; i!=9; ++i)
	{
		auto it = find(des.begin(), des.end(), src[i]);
		pr+=table[i][it-des.begin()];
	}
	return pr;
}

struct cmp
{
	bool operator()(const digit8& a, const digit8& b)
	{
		return a[9]>b[9];
	}
};

inline void display(const digit8& dig)
{
	for(int i=0; i!=9; ++i)
	{
		if(dig[i]==0)
			cout<<"  ";
		else
			cout<<dig[i]<<" ";
		if(i%3==2)
			cout<<"\n";
	}
	cout<<"\n";
}
int bfs(const digit8& src, const digit8& des)
{
	priority_queue<digit8, vector<digit8>, cmp> que;
	digit8 src_ = src;
	src_[9] = -1;
	que.push(src_);
	int count = 0;
	map<digit8,int> used;
	used[src_] = 0;
	map<digit8,digit8> parents;
	parents[src_] = {{0}};
	while(!que.empty())
	{
		++count;
		digit8 current = que.top();
		int depth = used[current];
		if(current[9] == 0)
		{
			while(current != digit8{{0}})
			{
				display(current);
				current=parents[current];
			}
			return depth;
		}
		que.pop();
		auto it0 = find(current.begin(), current.end(), 0);
		int index = it0 - current.begin();
		auto func = [&](int i, int j)
		{
			digit8 old = current;
			swap(current[i], current[j]);
			current[9] = priority(current, des);
			if(!used[current])
			{
				que.push(current);
				parents[current] = old;
				used[current] = depth+1;
			}
			swap(current[i], current[j]);
			current[9] = priority(current, des);
		};
		if(index%3 != 2)
			func(index,index+1);
		if(index%3 != 0)
			func(index,index-1);
		if(index<6)
			func(index,index+3);
		if(index>=3)
			func(index,index-3);
	}
	return -1;
}
int main()
{
	boost::progress_timer t;
	init_table();
	digit8 a{{2, 6, 4, 1, 3, 7, 0, 5, 8}};
	digit8 b{{8, 1, 5, 7, 3, 6, 4, 0, 2}};
	cout<<bfs(a,b)<<endl;
}
