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
struct fList 
{
    int currentSize; 
    DLLNode *head,*tail; 
    fList() 
	{
        head=new DLLNode(0,0); 
        tail=new DLLNode(0,0); 
        head->next=tail;
        tail->prev=head; 
        currentSize=0;
    }
    void deleteN(DLLNode* node) 
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
        currentSize--; 
    }
    void add(DLLNode *node) 
	{
        DLLNode* temp=head->next;
        node->next=temp;
        node->prev=head;
        head->next=node;
        temp->prev=node;
        currentSize++; 
    }
};
class LFUCache 
{
    map<int, DLLNode*> cache; 
    map<int, fList*> fListMap; 
    int capacity,currentSize;
    int minFrequency; 
public:
    LFUCache(int capacity) 
	{
        this->minFrequency = 0; 
        this->capacity=capacity;
        this->currentSize=0;
    }
    void update(DLLNode *node) 
	{
        cache.erase(node->key); 
        fListMap[node->freq]->deleteN(node); 
        if(node->freq == minFrequency && fListMap[node->freq]->currentSize == 0) 
		{
            minFrequency++; 
        }
        
        fList* newhf = new fList();
        if(fListMap.find(node->freq + 1) != fListMap.end()) 
		{
            newhf = fListMap[node->freq + 1];
        } 
        node->freq += 1; 
        newhf->add(node); 
        fListMap[node->freq] = newhf; 
        cache[node->key] = node;
    }
    int get(int key) 
	{
        if(cache.find(key) != cache.end()) 
		{
            DLLNode* node = cache[key]; 
            int val = node->value; 
            update(node); 
            return val; 
        }
        return -1; 
    }
    void set(int key, int value) 
	{
        if (capacity == 0) 
		{
            return;
        }
        if(cache.find(key) != cache.end()) 
		{
            DLLNode* node = cache[key]; 
            node->value = value; 
            update(node); 
        }
        else {
            if(currentSize == capacity) 
			{
                fList* list = fListMap[minFrequency]; 
                cache.erase(list->tail->prev->key); 
                fListMap[minFrequency]->deleteN(list->tail->prev);
                currentSize--; 
            }
            currentSize++; 
            minFrequency = 1; 
            fList* listFreq = new fList(); 
            if(fListMap.find(minFrequency) != fListMap.end()) 
			{
                listFreq = fListMap[minFrequency]; 
            }
            DLLNode* node = new DLLNode(key, value); 
            listFreq->add(node);
            cache[key] = node; 
            fListMap[minFrequency] = listFreq; 
        }
    }
};
int main()
{
	int capacity;
	cout<<"Enter the capacity of LRU Cashe\t";
	cin>>capacity;
	LFUCache * cache = new LFUCache(capacity);
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
				cout<<"Wrong Answer\n";
				break;
		}
	}
	return 0;
}
