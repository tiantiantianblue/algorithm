#include<everything>
#include<boost/progress.hpp>
typedef array<int,9> digit8;
int bfs(const digit8& src, const digit8& des)
{
	boost::progress_timer t;
	queue<digit8> que;
	que.push(src);
	int count = 0;
	map<digit8,int> used;
	used[src] = 0;
	while(!que.empty())
	{
		++count;
		digit8 current = que.front();
		int depth = used[current];
		if(current == des)
			return depth;
		que.pop();
		auto it0 = find(current.begin(), current.end(), 0);
		int index = it0 - current.begin();
		auto func = [&](int i, int j)
		{
			swap(current[i], current[j]);
			if(!used[current])
			{
				que.push(current);
				used[current] = depth+1;
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
int main()
{
	digit8 a{{2, 6, 4, 1, 3, 7, 0, 5, 8}};
	digit8 b{{8, 1, 5, 7, 3, 6, 4, 0, 2}};
	cout<<bfs(a,b)<<endl;
}
