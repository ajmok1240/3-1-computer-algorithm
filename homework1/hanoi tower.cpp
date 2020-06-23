//201824520_An_JuHyeon

#include <stdio.h>
void hanoi(int n, int from, int by, int to)
{
	//  คั   คั   คั 
	// from  by   to
	
	if (n == 1) {
		//if n is 1, then move a tower from "from" to "to"
		printf("%d -> %d\n", from, to);
	}
	else {  
		//if n is not 1, then move (n-1) towers from "from" to "by" by "to"
		hanoi(n-1, from, to, by);
		
		//after moving (n-1) towers to "by",
		//move remaining one tower from "from" to "to
		printf("%d -> %d\n", from, to);
		
		//after moving one remaining tower,
		//move (n-1) towers from "by" to "to" by "from"
		hanoi(n-1, by, from, to);
	}
}

int main(void)
{
	int n;          //variable for number of tower
	int count = 1;  //variable for total count 
	
	printf("Enter the number of tower : ");
	scanf("%d", &n);
	
	for(int i=0; i<n; i++)  //calculate total count
	{ count *= 2; }
	
	printf("\n%d \n", count-1);  //print total count
	
	hanoi(n, 1, 2, 3);

	return 0;
}

