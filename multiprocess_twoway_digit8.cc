#include<everything>
#include<boost/progress.hpp>
#include<sys/mman.h>
typedef array<int,9> digit8;
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
void  bfs(digit8 src, digit8 des, int* used, const int* used_other)
{
	queue<digit8> que;
	que.push(src);
	used[perfect_hash(src)] = 0;
	while(!que.empty())
	{
		digit8 current = que.front();
		int current_hash = perfect_hash(current);
		int depth = used[current_hash];
		if(used_other[current_hash])
		{
			cout<<"depth "<<depth+used_other[current_hash]<<endl;
			return;
		}
		que.pop();
		auto it0 = find(current.begin(), current.end(), 0);
		int index = it0 - current.begin();
		auto func = [&](int i, int j)
		{
			swap(current[i], current[j]);
			int cur_hash = perfect_hash(current);
			if(!used[cur_hash])
			{
				que.push(current);
				used[cur_hash] = depth+1;
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
	cout<<-1<<endl;
	return;
}
void init_fact()
{
	for(int i=0; i!=factorial.size(); ++i)
		factorial[i] = fact(i);
}
int main()
{
	boost::progress_timer timer;
	init_fact();
	const digit8 a{{2, 6, 4, 1, 3, 7, 0, 5, 8}};
	const digit8 b{{8, 1, 5, 7, 3, 6, 4, 0, 2}};
	constexpr int fact9 = 362880;
	int *ma = (int *)mmap(0, 4*fact9, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);
	int *mb = (int *)mmap(0, 4*fact9, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);
	if(fork() == 0)
		bfs(a, b, ma, mb);
	else
		bfs(b, a, mb, ma);
}
