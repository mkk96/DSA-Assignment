#include<stdlib.h>
#include<iostream>
#include <string>
#include<vector>
#include<math.h>
#include<algorithm>
using namespace std;
long long int length=64;
struct trie
{
	bool endhere;
	trie *node[2];
};
trie *newnode()
{
	trie *temp=new trie;
	for(long long int i=0;i<2;i++)
	{
		temp->node[i]=NULL;
	}
	temp->endhere=false;
	return temp;
}
void insert(trie **root,string s)
{
	trie *temp=*root;
	long long int len=s.size(),index;
	for(long long int i=0;i<len;i++)
	{
		index=s[i]-'0';
		if(temp->node[index]==NULL)
		{
			temp->node[index]=newnode();
		}
		temp=temp->node[index];
	}
	temp->endhere=true;
}
trie *initialize()
{
	trie *root=new trie;
	for(long long int i=0;i<2;i++)
	{
		root->node[i]=NULL;
	}
	root->endhere=false;
	return root;
}
string binary(long long int temp)
{
	string s="";
	while(temp>0)
	{
		if(temp%2==0)
		{
			s+='0';
		}
		else
		{
			s+='1';
		}
		temp/=2;
	}
	reverse(s.begin(), s.end());
	s.insert(0,length-s.size(),'0');
	return s;
}
long long int getmaxvalue(trie *root,string s)
{
	long long int result=0;
	for(long long int i=0;i<length;i++)
	{
		if(s[i]=='1')
		{
			if(root->node[0]!=NULL)
			{
				result+=pow(2,length-1-i);
				root=root->node[0];
			}
			else
			{
				if(root->node[1]!=NULL)
				{
					root=root->node[1];
				}
				else
				{
					return result;
				}
			}
		}
		else
		{
			if(root->node[1]!=NULL)
			{
				result+=pow(2,length-1-i);
				root=root->node[1];
			}
			else
			{
				if(root->node[0]!=NULL)
				{
					root=root->node[0];
				}
				else
				{
					return result;
				}
			}
		}
	}
	return result;
}
int main()
{
	long long int n,temp,q;
	cin>>n>>q;
	trie *root=initialize();
	for(long long int i=0;i<n;i++)
	{
		cin>>temp;
		string s=binary(temp);
		insert(&root,s);
	}
	while(q--)
	{
		long long int m;
		cin>>m;
		string s=binary(m);
		long long int result=getmaxvalue(root,s);
		cout<<(result)<<endl;
	}
}
