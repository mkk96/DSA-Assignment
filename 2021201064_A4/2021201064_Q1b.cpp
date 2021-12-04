#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
const int n =1000001;
int *suffixRank=new int[n], gap, len;
bool cmp(int x, int y) 
{
	if(suffixRank[x]==suffixRank[y])
	{
		x=x+gap;
		y=y+gap;
		return (x<len&&y<len)?suffixRank[x]<suffixRank[y]:x>y;
	}
	else
	{
		return suffixRank[x]<suffixRank[y];
	}
}
void build(string s,vector<int> &suffixArray) 
{
	vector<int> temp(len,0);
	for(int i=0;i<len;++i)
	{
		suffixRank[i] = s[i];
		suffixArray[i] = i;
	}
	for(gap=1;gap<len;gap*=2) 
	{
		sort(suffixArray.begin(),suffixArray.end(),cmp);
		
		for(int i=1;i<len;++i)
		{
			int x=suffixArray[i];
			int y=suffixArray[i-1];
			temp[i]=cmp(y,x)+temp[i-1];
		}
		for(int i = 0;i <len;++i)
		{
			int x=suffixArray[i];
			suffixRank[x]=temp[i];
		}
		if(temp[len-1]==len-1)
		{
			break;
		}
	}
}
int findoutans(string s,int *array,int k)
{
	if(k==1)
	{
		return len;
	}
	int *hash=new int[26];
	for(int i=0;i<26;i++)
	{
		hash[i]=0;
	}
	for(int i=0;i<len;i++)
	{
		hash[s[i]-'a']++;
	}
	for(int i=0;i<26;i++)
	{
		if(hash[i]==len)
		{
			return len-k+1;
		}
	}
	if(k>len)
	{
		return -1;
	}
	int max=-1;
	for(int i=0;i<=len-k;i++)
	{
		int temp=*min_element(array+i,array+i+k-1);
		if(temp>max&&temp>0)
		{
			max=temp;
		}
	}
	return max;
}
int main()
{
	string str;
	int k;
	cin>>str>>k;
	len=str.size();
	vector<int> suffixArray(len,0);
	build(str,suffixArray);
	int h=0;
	int *lcp=new int[len];
	for(int i=0;i<len;i++)
	{
		lcp[i]=0;
	}
	for(int i=0;i<len;i++)
	{
		if(suffixRank[i]>0)
		{
			int temp=suffixArray[suffixRank[i]-1];
			while(str[i+h]==str[temp+h])
			{
				h++;
			}
			lcp[suffixRank[i]]=h;
			if(h>0)
			{
				h--;
			}
		}
	}
	cout<<findoutans(str,lcp,k);
}

