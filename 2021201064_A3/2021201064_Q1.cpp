#include<stdlib.h>
#include<iostream>
#include <string>
#include<vector>
#include<algorithm>
using namespace std;
struct trie
{
	bool endhere;
	trie *node[26];
};
trie *newnode()
{
	trie *temp=new trie;
	for(int i=0;i<26;i++)
	{
		temp->node[i]=NULL;
	}
	temp->endhere=false;
	return temp;
}
void insert(trie **root,string s)
{
	trie *temp=*root;
	int len=s.size(),index;
	for(int i=0;i<len;i++)
	{
		index=s[i]-'a';
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
	for(int i=0;i<26;i++)
	{
		root->node[i]=NULL;
	}
	root->endhere=false;
	return root;
}
bool search(trie *root,string s)
{
	int len=s.size();
	int index;
	for(int i=0;i<len;i++)
	{
		index=s[i]-'a';
		if(root->node[index]==NULL)
		{
			return false;
		}
		root=root->node[index];
	}
	return root->endhere;
}
void autocomplete(trie * root,vector<string> &dict,string words="")
{
	if(root->endhere)
	{
		dict.push_back(words);
	}
    for(int i=0;i<26;i++)
	{
		if(root->node[i]!=NULL)
		{
			words+=i+'a';
			autocomplete(root->node[i],dict,words);
			words.resize(words.size() - 1);
		}
	}
}
void autocompletedriver(trie *root,string s)
{
	int len=s.size();
	int index;
	for(int i=0;i<len;i++)
	{
		index=s[i]-'a';
		if(root->node[index]==NULL)
		{
			cout<<"0";
			return;
		}
		root=root->node[index];
	}
	vector<string> dict;
	autocomplete(root,dict);
	vector<string>:: iterator itr;
	cout<<dict.size();
	sort(dict.begin(),dict.end());
	for(itr=dict.begin();itr!=dict.end();itr++)
	{
		cout<<endl<<(s+*itr);
	}
}
void autocorrect(string word1,string word2,vector<string> &dict)
{
	int len1=word1.size(), len2=word2.size();
    vector<vector<int> > mindist(len1+1, vector<int>(len2+1, 0));
    for (int i=1;i<=len1;i++)
    {
    	mindist[i][0]=i;
	}
    for (int j=1;j<=len2;j++)
    {
    	 mindist[0][j]=j;
	}
    for(int i=1;i<=len1;i++)
    {
        for (int j=1;j<=len2;j++)
        {
			if (word1[i-1]==word2[j-1])
			{
				mindist[i][j]=mindist[i-1][j-1];
			}
			else
			{
				mindist[i][j]=min(mindist[i-1][j-1],min(mindist[i-1][j],mindist[i][j-1]))+1;   
			}
        }
    }
    if(mindist[len1][len2]<=3)
    {
    	dict.push_back(word1);
	}
}
void autocorrectdriver(trie *root,string s)
{
	vector<string> dict,resdict;
	autocomplete(root,dict);
	vector<string>:: iterator itr;
	for(itr=dict.begin();itr!=dict.end();itr++)
	{
		autocorrect(*itr,s,resdict);
	}
	cout<<resdict.size();
	sort(resdict.begin(),resdict.end());
	for(itr=resdict.begin();itr!=resdict.end();itr++)
	{
		cout<<endl<<*itr;
	}
}
int main()
{
	int n;
	string s;
	cin>>n;
	trie *root=initialize();
	for(int i=0;i<n;i++)
	{
		cin>>s;
		insert(&root,s);
	}
	int x;
	string y;
	cin>>x>>y;
	switch(x)
	{
		case 1:
			cout<<search(root,y);
			break;
		case 2:
			autocompletedriver(root,y);
			break;
		case 3:
			autocorrectdriver(root,y);
			break;
	}
	return 0;
}
