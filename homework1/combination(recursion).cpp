//201824520_An_JuHyeon

#include <stdio.h>

long long bin(int n, int k)
{
	if( k==0 || n==k )
		return 1;
	else
		return ( bin(n-1, k-1) + bin(n-1, k) );
}

int main(void)
{
	printf("%lld", bin(45,10));
	
	return 0;
}
