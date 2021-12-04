#include<iostream> 
#include<stdio.h>
#include<map>
using namespace std;
struct DLLNode 
{
    int key, value, freq;
    DLLNode *next; 
    DLLNode *prev;
    DLLNode(int key, int value) 
	{
        this->key=key;
        this->value=value; 
        this->prev=NULL;
        this->next=NULL;
        freq=1; 
    }
}; 
class LRUCache
{
	public:
	DLLNode *head,*tail;
    int capacity,currentSize;
    map<int,DLLNode *> cache;
    LRUCache(int capacity) 
	{
        this->capacity=capacity;
        this->currentSize=0;
        this->head=NULL;
        this->tail=NULL;
        
    }
    void deleteN(DLLNode *node)
	{
        if(node->prev!=NULL)
		{
            node->prev->next=node->next;
        }
        else
		{
            head=node->next;
        }
        if(node->next!=NULL)
		{
            node->next->prev=node->prev;
        }
        else
		{
            tail=node->prev;
        }
        node->prev=NULL;
        node->next=NULL;
    }
    void add(DLLNode *node)
	{
       if (head == NULL)
        {
            head=node;
			tail=node;
        }
        else
		{
	        tail->next=node;
	        node->prev=tail;
	        tail=node;
        }
    }
    int get(int key) 
	{
        if(cache.find(key) != cache.end()) 
		{
            DLLNode* node = cache[key]; 
            int val = node->value; 
            deleteN(node);
        	add(node); 
            return val; 
        }
        return -1; 
    }
    void set(int key, int value) 
	{
        DLLNode *insert=new DLLNode(key,value);
        if(cache.find(key)!=cache.end())
		{
            cache[key]->value=value;
            deleteN(cache[key]);
            add(cache[key]);
        }
		else
		{
            cache[key]=insert;
            if(currentSize==capacity)
			{
                cache.erase(head->key);
                deleteN(head);
                add(insert);
            }
			else
			{
                currentSize+=1;
                add(insert);
            }
        }
    }
};
int main()
{
	int capacity;
	cout<<"Enter the capacity of LRU Cashe\t";
	cin>>capacity;
	LRUCache * cache = new LRUCache(capacity);
	while(1)
	{
		int option;
		cout<<"1. For Storing new key value pair\n2. For getting value of a key\n";
		cin>>option;
		int key,value;
		switch(option)
		{
			case 1:
				cout<<"Enter Key Value Pair\n";
				cin>>key>>value;
				cache->set(key,value);
				break;
			case 2:
				cout<<"Enter Key to get value\n";
				cin>>key;
				cout<<"Value "<<cache->get(key)<<endl;
				break;
			default:
				cout<<"Wrong Choice\n";
				break;
		}
	}
	return 0;
}
