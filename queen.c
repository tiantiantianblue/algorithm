#include<stdio.h>
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
int check(int *a, int x)
{
	for(int i=1; i<x; ++i)
	{
		for(int j=0; j<i; ++j)
			if((i-j == a[i]-a[j]) || (i-j == a[j]-a[i]))
				return 0;
	}
	return 1;
}

static int count = 0;
void display(int *a, int n)
{
	++count;
	for(int i=0; i<n; ++i)
	{
		for(int j=1; j<=n; ++j)
			if(a[i]==j)
				printf("#");
			else
				printf("*");
		printf("\n");
	}
	printf("\n");
}
void full_permutation(int *a, int x, int n)
{
	if(!check(a, x))
		return;
	if(x==n)
		display(a,n);
	for(int i=x; i<n; ++i)
	{
		swap(a+i, a+x);
		full_permutation(a, x+1, n);
		swap(a+i, a+x);
	}
}
int main()
{
	int a[]={1,2,3,4,5,6,7,8,9};
	full_permutation(a, 0, 8);
	printf("%d\n",count);
}
