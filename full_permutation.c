#include<stdio.h>
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void full_permutation(int *a, int x, int n)
{
	if(x==n-1){
		for(int i=0; i<n; ++i)
			printf("%d",a[i]);
		printf("\n");
	}
	for(int i=x; i<n; ++i)
	{
		swap(a+i, a+x);
		full_permutation(a, x+1, n);
		swap(a+i, a+x);
	}
}
int main()
{
	int a[]={1,2,3,4,5,6,7,8,9,0,'a','b','c','d','e','f'};
	full_permutation(a, 0, 10);
}
