#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<string>
#define prime1 7919
#define prime2 79
using namespace std;
template <typename T,typename V>
struct node
{
	T key;
	V value;
	node<T,V> *next;
};
template <class T, class V>
class unordered_map
{
	public:
		node<T,V> *arr[prime1];
		unordered_map()
	    {
	        for(int i=0;i<prime1;i++)
	        {
	        	arr[i]=NULL;
			}
	    }
	    int createhash(T key)
	    {
	        int fun = 1;
	        ostringstream cal;
	        int hash = 0;
	        cal<<key;
	        string s = cal.str();
	        for(int i=0;i<s.size();i++)
	        {
	        	hash += (s[i]*fun*23);
	            hash %= prime1;
	            fun *= prime2;
			}
	        return hash;
	    }
	    node<T,V> *addnode(T key,V value)
	    {
	    	node<T,V> *temp=new node<T,V>;
	    	temp->key=key;
	    	temp->value=value;
	    	temp->next=NULL;
	    	return temp;
		}
		void deletenode(node<T,V> **head,T key)
		{
			node<T,V>* temp=*head;
			node<T,V>* prev=NULL;
			if (temp!=NULL&&temp->key==key)
			{
				*head=temp->next;
				return;
			}
		    else
			{
				while(temp!=NULL&&temp->key!=key)
				{
					prev=temp;
					temp=temp->next;
				}
				if (temp==NULL)
					return;
				prev->next=temp->next;
				delete temp;
			}
		}
	    void insert(T key, V value)
	    {
	    	int index=createhash(key);
	    	if(arr[index]==NULL)
	    	{
	    		arr[index]=addnode(key,value);
			}
			else
			{
				node<T,V> *temp=arr[index];
				while(temp->next!=NULL)
				{
					if(temp->key==key)
					{
						temp->value=value;
						return;
					}
					temp=temp->next;
				}
				if(temp->key==key)
				{
					temp->value=value;
					return;
				}
				temp->next=addnode(key,value);
			}
		}
		void erase(T key)
		{
			int index=createhash(key);
			node<T,V> *temp=arr[index];
			if(arr[index]==NULL)
			{
				return;
			}
			deletenode(&arr[index],key);
		}
		void find(T key)
		{
			int index=createhash(key);
			if(arr[index]==NULL)
			{
				cout<<"Not Found\n";
				return;
			}
			else
			{
				node<T,V> *temp=arr[index];
				while(temp!=NULL)
				{
					if(temp->key==key)
					{
						cout<<temp->value<<endl;
						return;
					}
					temp=temp->next;
				}
			}
			cout<<"Not Found"<<endl;
		}
		V operator[](T key)
		{
			int index=createhash(key);
			if(arr[index]==NULL)
			{
				insert(key,NULL);
				return NULL;
			}
			else
			{
				node<T,V> *temp=arr[index];
				while(temp!=NULL)
				{
					if(temp->key==key)
					{
						return temp->value;
					}
					temp=temp->next;
				}
			}
			insert(key,NULL);
			return NULL;
		}
		void display()
		{
			cout<<"Key"<<" "<<"Value"<<endl;
			for(int i=0;i<prime1;i++)
			{
				if(arr[i]!=NULL)
				{
					node<T,V> *temp=arr[i];
					while(temp!=NULL)
					{
						cout<<temp->key<<" "<<temp->value<<endl;
						temp=temp->next;
					}
				}
			}
		}
};
template <typename T>
void countDistinct(T arr[], int k, int n)
{
    unordered_map<T, int> map;
    int count=0;
    for (int i=0;i<k;i++) 
	{
        if (map[arr[i]]==0) 
		{
            count++;
        }
        int temp=map[arr[i]]+1;
        map.insert(arr[i],temp);
    }
    cout<<count<<endl;
    for (int i=k;i<n;i++) 
	{
        if (map[arr[i-k]]==1) 
		{
            count--;
        }
        int temp=map[arr[i-k]]-1;
        map.insert(arr[i-k],temp);
        if (map[arr[i]]==0) 
		{
            count++;
        }
        temp=map[arr[i]]+1;
        map.insert(arr[i],temp);
        cout<<count<<endl;
    }
}
int main()
{
    int n;
    cin>>n;
    float array[n];
    for(int i=0;i<n;i++)
    {
    	cin>>array[i];
	}
	int k;
	cin>>k;
	countDistinct(array,k,n);
	return 0;
}
