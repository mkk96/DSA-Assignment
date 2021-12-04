#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <fstream>
#include<algorithm>
#include <string.h>
#include <climits>
#include<math.h>
using namespace std;
long long int maxSizeAllowed=1000000;
void merge(long long int *array,long long int low,long long int mid,long long int high)
{
	long long int i,j,k;
	long long int n1=mid-low +1;
	long long int n2=high-mid;
	long long int *leftArray=new long long int[n1],*rightArray=new long long int[n2];
	for (i = 0; i <n1;i++)
	{
		leftArray[i]=array[low+i];
	}
	for (j=0;j<n2;j++)
	{
		rightArray[j]=array[mid+1+j];
	}
	i=0,j=0,k=low;
	while (i<n1&&j<n2) 
	{
		if (leftArray[i]<=rightArray[j])
		{
			array[k++]=leftArray[i++];
		}
		else
		{
			array[k++]=rightArray[j++];
		}
	}
	while (i<n1)
	{
		array[k++]=leftArray[i++];
	}
	while (j<n2)
	{
		array[k++]=rightArray[j++];
	}
	delete leftArray;
	delete rightArray;
}
void mergeSort(long long int *array,long long int i,long long int j)
{
	long long int mid;
    if(i<j)
    {
        mid=(i+j)/2;
        mergeSort(array,i,mid);
        mergeSort(array,mid+1,j);
        merge(array,i,mid,j);
    }
}
char *changeToChar(long long int temp)
{
	char strtrmp[10];
	long long int i=0;
	while(temp>0)
	{
		strtrmp[i++]=temp%10+'0';
		temp/=10;
	}
	char *str=(char *)malloc(sizeof(char)*10);
	for(long long int j=0;j<i;j++)
	{
		str[j]=strtrmp[i-j-1];
	}
	str[i]='\0';
	return str;
}
void writeIntoFile(long long int *array,long long int size,long long int filenumber)
{
	char *filename= changeToChar(filenumber);
	ofstream out(filename);
	for(long long int i=0;i<size;i++)
	{
		out<<array[i]<<" ";
	}
	out.close();
}
long long int *findMin(long long int *array,long long int split,long long int *completed)
{
	long long int m=(long long int)(pow(2,64)-1),index=-1;
	for(long long int i=1;i<=split;i++)
	{
		if(m>=array[i]&&completed[i]!=1)
		{
			m=array[i];
			index=i;
		}
	}
	long long int *result=(long long int *)malloc(sizeof(long long int)*2);
	result[0]=m;
	result[1]=index;
	return result;
}
void mergeFiles(long long int split,char *outputfile,long long int numberofelement)
{
	ifstream tempFile[split+1];
	for(long long int i=1;i<=split;i++)
	{
		char *filename=changeToChar(i);
		tempFile[i].open(filename);
	}
	long long int *tempData=new long long int[split+1],x;
	long long int *completed=new long long int[split+1];
	for(long long int i=1;i<=split;i++)
	{
		tempFile[i]>>x;
		tempData[i]=x;
		completed[i]=0;
	}
	ofstream out(outputfile);
	while(1)
	{
		long long int *getmin=findMin(tempData,split,completed);
		if(getmin[1]==-1)
		{
			break;
		}
		if(numberofelement==1)
		{
			out<<getmin[0];
		}
		else
		{
			out<<getmin[0]<<",";
		}
		numberofelement--;
		if(tempFile[getmin[1]]>>x)
		{
			tempData[getmin[1]]=x;
		}
		else
		{
			completed[getmin[1]]=1;	
		}
		//cout<<getmin[0]<<" "<<getmin[1]<<endl;
	}
	out.close();
	for(long long int i=1;i<=split;i++)
	{
		tempFile[i].close();
		char *filename=changeToChar(i);
		remove(filename);
	}
}
int main(int argc, char *argv[])
{
	//_setmaxstdio(2048);
	char *inputfile=(char*)malloc(sizeof(argv[1]));
	inputfile=argv[1];
	char *outputfile=(char*)malloc(sizeof(argv[2]));
	outputfile=argv[2];
	ifstream inputFile(inputfile);
	long long int tempData;
	long long int *array=new long long int[maxSizeAllowed];
	long long int i=0,split=0,numberofelement=0;
	while(inputFile>>tempData) 
	{
        array[i++]=tempData;
        if(i==maxSizeAllowed)
        {
        	mergeSort(array,0,i-1);
        	split++;
        	writeIntoFile(array,i,split);
        	i=0;
		}
		numberofelement++;
        inputFile.ignore();
    }
    delete array;
    if(i>0)
    {
    	mergeSort(array,0,i-1);
    	split++;
    	writeIntoFile(array,i,split);
	}
	inputFile.close();
	mergeFiles(split,outputfile,numberofelement);
	return 0;
}
