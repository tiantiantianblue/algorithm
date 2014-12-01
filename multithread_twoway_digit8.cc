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
typedef array<int, 362880> DigitDepth;
void  bfs(digit8 src, digit8 des, DigitDepth& used, DigitDepth& used_other)
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
	digit8 a{{2, 6, 4, 1, 3, 7, 0, 5, 8}};
	digit8 b{{8, 1, 5, 7, 3, 6, 4, 0, 2}};
	DigitDepth used1{{0}};
	DigitDepth used2{{0}};
	thread t1(bfs, a, b, ref(used1), ref(used2));
	thread t2(bfs, b, a, ref(used2), ref(used1));
	t1.join();
	t2.join();
}
