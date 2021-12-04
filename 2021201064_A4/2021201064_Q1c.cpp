#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
bool ispal(string s)
{
	int len=s.size();
	for(int i=0;i<len/2;i++)
	{
		if(s[i]!=s[len-1-i])
		{
			return false;
		}
	}
	return true;
}
string longestPalindromeSubstring(vector<pair<string,int> >s)
{
	int len=0;
	string result;
	vector<pair<string,int> >::iterator itr;
	for(itr=s.begin();itr!=s.end();itr++)
	{
		if(ispal(itr->first))
		{
			if(len<=(itr->first).size()||(itr->first)<result)
			{
				result=itr->first;
				len=(itr->first).size();
			}
		}
	}
	return result;
}
int main()
{
	string input;
	cin>>input;
	int n=input.size();
	vector<pair<string,int> >s;
	string sub="";
	for(int i=n-1;i>=0;i--)
	{
		sub=input[i]+sub;
		s.push_back({sub,i});
	}
	sort(s.begin(),s.end());
	cout<<longestPalindromeSubstring(s);
}
