#include<stdlib.h>
#include<iostream>
#include <string.h>
#include<vector>
using namespace std;
char result[100][100];
int resultlen=0;
int r,c;
struct trie
{
	bool endhere;
	string word;
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
	temp->word=s;
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
void copy(string s)
{
	int len=s.size();
	for(int i=0;i<len;i++)
	{
		result[resultlen][i]=s[i];
	}
	result[resultlen++][len]='\0';
}
void puzzle(char **array,int i,int j,trie *root)
{
	char temp=array[i][j];
	if(array[i][j]=='$'||root->node[array[i][j]-'a']==NULL)  
	{
		return;
	}
	root=root->node[array[i][j]-'a'];
	array[i][j] = '$';
	if(root->endhere)
    {
        copy(root->word);
        root->endhere=false;
    }
    if(i<r-1)
	{
		puzzle(array,i+1,j,root);
	}
	if(i>0)
	{
		puzzle(array,i-1,j,root);
	}
	if(j<c-1)
	{
		puzzle(array,i,j+1,root);
	}
	if(j>0)
	{
		puzzle(array,i,j-1,root);
	}
	array[i][j]=temp;  
}

void merge(int l,int mid,int h)
{
    int left= mid+1-l;
    int right= h-mid;

    char** leftsubstring=(char **)malloc(sizeof(char *)*left);
    char** rightsubstring=(char **)malloc(sizeof(char *)*right);
    for(int i=0;i<left;i++)
    {
        leftsubstring[i]=(char *)malloc(sizeof(result[l+i]));
        strcpy(leftsubstring[i],result[l+i]);
    }
    for(int i=0;i<right;i++)
    {
        rightsubstring[i]=(char *)malloc(sizeof(result[mid+i+1]));
        strcpy(rightsubstring[i],result[mid+i+1]);
    }
    int j=0,k=l,i=0;
    while(i<left&&j<right)
    {
        if(strcmp(leftsubstring[i],rightsubstring[j])<0)
        {
        	strcpy(result[k],leftsubstring[i++]);
		}
        else
        {
        	strcpy(result[k],rightsubstring[j++]);
		}
		k++;
    }
    while(i<left)
    {
    	strcpy(result[k],leftsubstring[i++]);
    	k++;
	}
    while(j<right)
    {
    	strcpy(result[k],rightsubstring[j++]);
    	k++;
	}
}
void mergesort(int low,int high)
{
    if(low<high)
    {
        int mid=(low+high)/2;
        mergesort(low,mid);
        mergesort(mid+1,high);
        merge(low,mid,high);
    }
}
void puzzlesolverdriver(char **array,trie *root)
{
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			puzzle(array,i,j,root);
		}
	}
	mergesort(0,resultlen-1);
	for(int i=0;i<resultlen;i++)
	{
		cout<<result[i]<<" ";
	}
}
int main()
{
	cin>>r>>c;
	char **array=(char **)malloc(r*sizeof(char *));
	for (int i=0;i<r; i++)
	{
		array[i]=(char *)malloc(c*sizeof(char *));
	}
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			cin>>array[i][j];
		}
	}
	int n;
	string s;
	cin>>n;
	trie *root=initialize();
	for(int i=0;i<n;i++)
	{
		cin>>s;
		insert(&root,s);
	}
	puzzlesolverdriver(array,root);
}
