#include<everything>
#include<boost/progress.hpp>
typedef array<unsigned char,9> digit8;
int fact(int n)
{
	int result = 1;
	for(int i=1; i<=n; ++i)
		result *=  i;
	return result;
}
array<int,9> factorial;
inline int perfect_hash(const digit8& dig)
{
	int result = 0;
	for(int i=0; i!=dig.size(); ++i)
	{
		int k = 0;
		for(int j=i+1; j!=dig.size(); ++j)
			if(dig[i]>dig[j])
				++k;
		result += factorial[dig.size()-i-1]*k;
	}
	return result;
}
int bfs(const digit8& src, const digit8& des)
{
	queue<digit8> que;
	que.push(src);
	int count = 0;
	array<int, 362880> used;
	used[perfect_hash(src)] = 0;
	while(!que.empty())
	{
		++count;
		digit8 current = que.front();
		int depth = used[perfect_hash(current)];
		if(current == des)
			return depth;
		que.pop();
		auto it0 = find(current.begin(), current.end(), 0);
		int index = it0 - current.begin();
		auto func = [&](int i, int j)
		{
			swap(current[i], current[j]);
			if(!used[perfect_hash(current)])
			{
				que.push(current);
				used[perfect_hash(current)] = depth+1;
			}
			swap(current[i], current[j]);
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
void init_fact()
{
	for(int i=0; i!=factorial.size(); ++i)
		factorial[i] = fact(i);
}
int main()
{
	boost::progress_timer t;
	init_fact();
	digit8 a{{2, 6, 4, 1, 3, 7, 0, 5, 8}};
	digit8 b{{8, 1, 5, 7, 3, 6, 4, 0, 2}};
	cout<<bfs(a,b)<<endl;
}
