//201824520_An_JuHyeon

#include <stdio.h>

void swap(int &a, int &b)  //swap 2 values from array by reference
{
	int temp = a;
	a=b;
	b=temp;
}

void myQuickSort(int* arr, int low, int high)
{
	//this (low >= high) condition is true when the seperated array has one value
	//so return from this function
	if(low >= high) return;  
	
	int pivot = arr[low]; //set the pivot value as first value of array
	int left = low + 1;   //pointer, set left value as next value of "low"
	int right = high;     //pointer, set left value as value of "high"
	
	while(!(left>right))  //do while left value is lower than right value
	{
		while(arr[left]<pivot) left++;   //stop at the value which is bigger than pivot value
		while(arr[right]>pivot) right--; //stop at the value which is lower than pivot value
		
		//if pointer "right" intersects pointer "left", do not swap
		//if not, swap "right" value and "left" value
		if(!(left>right)) swap(arr[left], arr[right]);
	}
	
	swap(arr[low], arr[right]); //swap right value and pivot value
	
	myQuickSort(arr, low, right-1);  //do quick sort for left seperated array
	myQuickSort(arr, right+1, high); //do quick sort for right seperated array
	
}

int main(void)
{
	int S[8]={15,22,13,27,12,10,20,25};
	
	printf("Before sorting : ");
	for(int i=0; i<8; i++) printf("[%d] ", S[i]);
	printf("\n");
	
	myQuickSort(S, 0, 7);
	
	printf("After sorting :  ");
	for(int i=0; i<8; i++) printf("[%d] ", S[i]);
	printf("\n");
	
	return 0;
}
