#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
template<typename T>
void displayM(T result[][3])
{
	int row=result[0][0];
	int column=result[0][1];
	int count=1;
	cout<<endl;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			if(result[count][0]==i&&result[count][1]==j)
			{
				cout<<result[count++][2]<<" ";
			}
			else
			{
				cout<<0<<" ";
			}
		}
		cout<<endl;
	}
	cout<<endl;
}
template<typename T>
void displayS(T result[][3])
{
	int resultsize=result[0][2]+1;
	cout<<endl;
	for(int i=0;i<resultsize;i++)
	{
		cout<<result[i][0]<<" "<<result[i][1]<<" "<<result[i][2]<<endl;
	}
	cout<<endl;
}
template<typename T>
void *triplate(T x)
{
	int row,column;
	cin>>row>>column;
	T matrix[row][column];
	int k=1;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			cin>>matrix[i][j];
			if(matrix[i][j]!=0)
			{
				k++;
			}
		}
	}
	T (*a)[3]=new T[k][3];
	int aindex=0;
	a[aindex][0]=row;
	a[aindex][1]=column;
	a[aindex++][2]=k-1;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			if(matrix[i][j]!=0)
			{
				a[aindex][0]=i;
				a[aindex][1]=j;
				a[aindex++][2]=matrix[i][j];
			}
		}
	}
	return a;
}
template<typename T>
void addition(T a[][3],T b[][3])
{
	long long size=a[0][2]+b[0][2];
	T result[size][3];
	long long resultsize=0;
	result[resultsize][0]=a[0][0];
	result[resultsize++][1]=a[0][1];
	int i=1,j=1;
	while(i<=a[0][2]&&j<=b[0][2])
	{
		if(a[i][0]==b[j][0])
		{
			if(a[i][1]==b[j][1])
			{
				result[resultsize][0]=a[i][0];
				result[resultsize][1]=a[i][1];
				if((a[i][2]+b[j][2])!=0)
					result[resultsize++][2]=a[i++][2]+b[j++][2];
			}
			else
			{
				if(a[i][1]>b[j][1])
				{
					result[resultsize][0]=b[j][0];
					result[resultsize][1]=b[j][1];
					result[resultsize++][2]=b[j++][2];
				}
				else
				{
					result[resultsize][0]=a[i][0];
					result[resultsize][1]=a[i][1];
					result[resultsize++][2]=a[i++][2];
				}
			}
		}
		else
		{
			if(a[i][0]>b[j][0])
			{
				result[resultsize][0]=b[j][0];
				result[resultsize][1]=b[j][1];
				result[resultsize++][2]=b[j++][2];
			}
			else
			{
				result[resultsize][0]=a[i][0];
				result[resultsize][1]=a[i][1];
				result[resultsize++][2]=a[i++][2];
			}
		}
	}
	while(i<=a[0][2])
	{
		result[resultsize][0]=a[i][0];
		result[resultsize][1]=a[i][1];
		result[resultsize++][2]=a[i++][2];
	}
	while(j<=b[0][2])
	{
			result[resultsize][0]=b[j][0];
			result[resultsize][1]=b[j][1];
			result[resultsize++][2]=b[j++][2];
	}
	result[0][2]=resultsize-1;
	displayM(result);
	displayS(result);
}
template<typename T>
void additiondriver(T x)
{
	T (*a)[3];
	a=( T (*)[3])triplate(x);
	T (*b)[3];
	b=( T (*)[3])triplate(x);
	if(a[0][0]!=b[0][0]||a[0][1]!=b[0][1])
	{
		cout<<"Dimension not Same cannot do addition\n";
		return;
	}
	addition(a,b);
}
template<typename T>
void *transpose(T a[][3],int row,int column,int k)
{
	T *total=(T *)malloc(column*sizeof(T));
	T *index=(T *)malloc((column+1)*sizeof(T));
	for(int i=0;i<column;i++)
	{
		total[i]=0;
		index[i]=0;
	}
	index[column]=0;
	for(int i=1;i<=k;i++)
	{
		total[(long long)a[i][1]]++;
	}
	index[0]=1;
	for(int i=1;i<=column;i++)
	{
		index[i]=index[i-1]+total[i-1];
	}
	T (*result)[3]=new T[k+1][3];
	result[0][0]=column;
	result[0][1]=row;
	result[0][2]=k;
	int col,loc;
	int count=1;
	for(int i=1;i<=k;i++)
	{
		col=a[i][1];
		loc=index[col];
		result[loc][0]=a[i][1];
		result[loc][1]=a[i][0];
		result[loc][2]=a[i][2];
		index[col]++;
	}
	return result;
}
template<typename T>
void transposedriver(T x)
{
	T (*a)[3];
	a=( T (*)[3])triplate(x);
	T (*result)[3];
	result=( T (*)[3])transpose(a,a[0][0],a[0][1],a[0][2]);
	displayM(result);
	displayS(result);
}
template<typename T>
void multiplydriver(T x)
{
	T (*a)[3];
	a=( T (*)[3])triplate(x);
	T (*b)[3];
	b=( T (*)[3])triplate(x);
	if(a[0][1]!=b[0][0])
	{
		cout<<"Dimesion not compatible for multiply\n";
		return;
	}
	b=( T (*)[3])transpose(b,b[0][0],b[0][1],b[0][2]);
	long long size=a[0][2]*b[0][2]+2;
	T tempresult[size][3];
	int tempresultindex=0;
	int i=1,j=1;
	size=0;
	while(i<=a[0][2])
	{
		j=1;
		while(j<=b[0][2])
		{
			if(a[i][1]==b[j][1])
			{
				tempresult[tempresultindex][0]=a[i][0];
				tempresult[tempresultindex][1]=b[j][0];
				tempresult[tempresultindex++][2]=a[i][2]*b[j][2];
				size++;
			}
			j++;
		}
		i++;
	}
	j=0;
	int count=a[0][0]*b[0][0]+1;
	while(j<tempresultindex)
	{
		int q=j+1;
		while(q<tempresultindex)
		{
			if(tempresult[j][0]==tempresult[q][0]&&tempresult[j][1]==tempresult[q][1])
			{
				tempresult[j][2]=tempresult[j][2]+tempresult[q][2];
				tempresult[q][0]=count++;
				size--;
			}
			q++;
		}
		j++;
	}
	T result[tempresultindex+1][3];
	int resultindex=0;
	result[resultindex][0]=a[0][0];
	result[resultindex++][1]=b[0][0];
	for(int t=0;t<tempresultindex;t++)
	{
		if(tempresult[t][0]<(a[0][0]*b[0][0]+1)&&tempresult[t][2]!=0)
		{
			result[resultindex][0]=tempresult[t][0];
			result[resultindex][1]=tempresult[t][1];
			result[resultindex++][2]=tempresult[t][2];
		}
	}
	result[0][2]=resultindex-1;
	displayM(result);
	displayS(result);
}
void integer()
{
	int choice;
	cout<<"1. For Addition\n2. For Transpose\n3. For multiplication\n";
	cin>>choice;
	switch(choice)
	{
		case 1:
			additiondriver(1);
			break;
		case 2:
			transposedriver(1);
			break;
		case 3:
			multiplydriver(1);
			break;
		default:
			cout<<"Wrong Choice";
			break;
	}
}
void flaotdouble()
{
	int choice;
	cout<<"1. For Addition\n2. For Transpose\n3. For multiplication\n";
	cin>>choice;
	switch(choice)
	{
		case 1:
			additiondriver(1.1);
			break;
		case 2:
			transposedriver(1.1);
			break;
		case 3:
			multiplydriver(1.1);
			break;
		default:
			cout<<"Wrong Choice";
			break;
	}
}
int main()
{
	int n;
	cout<<"1. for Int or Long int\n2. For float and Double\n";
	cin>>n;
	switch(n)
	{
		case 1:
			integer();
			break;
		case 2:
			flaotdouble();
			break;
		default:
			cout<<"wrong choice";
			break;
	}
	return 0;
}
