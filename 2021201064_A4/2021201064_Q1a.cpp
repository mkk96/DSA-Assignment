#include<stdlib.h>
#include<iostream>
using namespace std;
int main()
{
	string input;
	cin>>input;
	input=input+input;
	int len=input.size(),rotindex=0,j=1;
	int *array=(int *)malloc(sizeof(int)*len);
	for(int i=0;i<len;i++)
	{
		array[i]=-1;
	}
	while(j<len)
	{
		int index=array[j-rotindex-1];
		char ch=input[j];
		while(ch!=input[rotindex+index+1]&&index!=-1)
		{
			if(input[rotindex+index+1]>ch)
			{
				rotindex=j-1-index;
			}
			index=array[index];
		}
		if(input[rotindex+index+1]!=ch)
		{
			if(input[rotindex]>ch)
			{
				rotindex=j;
			}
			array[j-rotindex]=-1;
		}
		else
		{
			array[j-rotindex]=index+1;
		}
		j++;
	}
	cout<<input.substr(rotindex,len/ 2);
}
