#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
template <typename T>
struct llist
{
	llist();
	T row;
	T column;
	T value;
	llist<T> *next;
};
template <typename T>
void displayM(llist<T> *head)
{
	int row=head->row;
	int column=head->column;
	head=head->next;
	cout<<endl;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			if(head->row==i&&head->column==j)
			{
				cout<<head->value<<" ";
				head=head->next;
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
void displayS(llist<T> *head)
{
	cout<<endl;
	while(head)
	{
		cout<<head->row<<" "<<head->column<<" "<<head->value<<endl;
		head=head->next;
	}
	cout<<endl;
}
template <typename T>
llist<T> *reversel(llist<T> *head)
{
	llist<T> *current = head;
	llist<T> *prev = NULL, *next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return prev;
}
template <typename T>
bool compare(llist<T> *a,llist<T> *b)
{
	if(a->row<b->row)
	{
		return true;
	}
	else if(a->row>b->row)
	{
		return false;
	}
	else
	{
		if(a->column<b->column)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
template <typename T>
llist<T>* sortedMerge(llist<T>* a,llist<T>* b)
{
    if (a==NULL) 
	{
        return b;
    }
 
    else if(b==NULL) 
	{
        return a;
    }
 
    llist<T>* result=NULL;
    if (compare(a,b))
    {
        result=a;
        result->next=sortedMerge(a->next, b);
    }
    else 
	{
        result=b;
        result->next=sortedMerge(a, b->next);
    }
    return result;
}
template <typename T>
void frontBackSplit(llist<T>* source,llist<T>** frontRef,llist<T>** backRef)
{
    if (source==NULL||source->next==NULL)
    {
        *frontRef=source;
        *backRef=NULL;
        return;
    }
    llist<T>* slow=source;
    llist<T>* fast=source->next;
    while (fast!=NULL)
    {
        fast=fast->next;
        if (fast!=NULL)
        {
            slow=slow->next;
            fast=fast->next;
        }
    }
    *frontRef=source;
    *backRef=slow->next;
    slow->next=NULL;
}
template <typename T>
void mergesort(llist<T>** head)
{
    if (*head==NULL||(*head)->next==NULL) 
	{
        return;
    }
    llist<T>* a;
    llist<T>* b;
    frontBackSplit(*head, &a, &b);
    mergesort(&a);
    mergesort(&b);
    *head=sortedMerge(a, b);
}
template <typename T>
llist<T> *addnode(T x)
{
	int row,column;
	cin>>row>>column;
	llist<T> *head=NULL;
	llist<T> *newnode=(llist<T> *)malloc(sizeof(llist<T>));
	newnode->row=row;
	newnode->column=column;
	newnode->next=NULL;
	head=newnode;
	T temp,k=0;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			cin>>temp;
			if(temp!=0)
			{
				llist<T> *newnode=(llist<T> *)malloc(sizeof(llist<T>));
				newnode->row=i;
				newnode->column=j;
				newnode->value=temp;
				newnode->next=head;
				head=newnode;
				k++;
			}
		}
	}
	head=reversel(head);
	head->value=k;
	return head;
}
template <typename T>
void addition(llist<T> *head1,llist<T> *head2,T row,T column)
{
	llist<T> *temp1=head1;
	llist<T> *temp2=head2;
	llist<T> *resulthead=NULL;
	llist<T> *newnode=(llist<T> *)malloc(sizeof(llist<T>));
	newnode->row=row;
	newnode->column=column;
	newnode->next=NULL;
	resulthead=newnode;
	int k=0;
	temp1=temp1->next;
	temp2=temp2->next;
	while(temp1&&temp2)
	{
		llist<T> *newnode=(llist<T> *)malloc(sizeof(llist<T>));
		k++;
		if(temp1->row==temp2->row)
		{
			if(temp1->column==temp2->column)
			{
				newnode->row=temp1->row;
				newnode->column=temp1->column;
				newnode->value=temp1->value+temp2->value;
				newnode->next=resulthead;
				resulthead=newnode;
				temp1=temp1->next;
				temp2=temp2->next;
			}
			else
			{
				if(temp1->column>temp2->column)
				{
					newnode->row=temp2->row;
					newnode->column=temp2->column;
					newnode->value=temp2->value;
					newnode->next=resulthead;
					resulthead=newnode;
					temp2=temp2->next;
				}
				else
				{
					newnode->row=temp1->row;
					newnode->column=temp1->column;
					newnode->value=temp1->value;
					newnode->next=resulthead;
					resulthead=newnode;
					temp1=temp1->next;
				}
			}
		}
		else
		{
			if(temp1->row>temp2->row)
			{
				newnode->row=temp2->row;
				newnode->column=temp2->column;
				newnode->value=temp2->value;
				newnode->next=resulthead;
				resulthead=newnode;
				temp2=temp2->next;
			}
			else
			{
				newnode->row=temp1->row;
				newnode->column=temp1->column;
				newnode->value=temp1->value;
				newnode->next=resulthead;
				resulthead=newnode;
				temp1=temp1->next;
			}
		}
	}
	while(temp1)
	{
		llist<T> *newnode=(llist<T> *)malloc(sizeof(llist<T>));
		newnode->row=temp1->row;
		newnode->column=temp1->column;
		newnode->value=temp1->value;
		newnode->next=resulthead;
		resulthead=newnode;
		temp1=temp1->next;
		k++;
	}
	while(temp2)
	{
		llist<T> *newnode=(llist<T> *)malloc(sizeof(llist<T>));
		newnode->row=temp2->row;
		newnode->column=temp2->column;
		newnode->value=temp2->value;
		newnode->next=resulthead;
		resulthead=newnode;
		temp2=temp2->next;
		k++;
	}
	resulthead=reversel(resulthead);
	resulthead->value=k;
	llist<T> *temp=resulthead;
	displayS(temp);
	temp=resulthead;
	displayM(temp);
}
template <typename T>
void additiondriver(T x)
{
	llist<T> *head1=addnode(x);
	llist<T> *head2=addnode(x);	
	if(head1->row!=head2->row||head1->column!=head2->column)
	{
		cout<<"Dimension dont match not able add matrix\n";
		return;
	}
	addition(head1,head2,head1->row,head1->column);
}
template <typename T>
llist<T> *transpose(llist<T> *head,T row,T column)
{
	llist<T> *temp=head;
	int k=0;
	while(temp)
	{
		T t=temp->column;
		temp->column=temp->row;
		temp->row=t;
		temp=temp->next;
		k++;
	}
	mergesort(&head);
	llist<T> *newnode=(llist<T> *)malloc(sizeof(llist<T>));
	newnode->row=column;
	newnode->column=row;
	newnode->value=k;
	newnode->next=head;
	head=newnode;
	return head;
}
template <typename T>
void transposedriver(T x)
{
	llist<T> *head=addnode(x);
	T row=head->row;
	T column=head->column;
	head=head->next;
	head=transpose(head,row,column);
	llist<T> *temp=head;
	displayS(temp);
	temp=head;
	displayM(temp);
}
template <typename T>
void multiplydriver(T x)
{
	llist<T> *head1=addnode(x);
	llist<T> *head2=addnode(x);	
	int row=head1->row;
	int column=head2->column;
	if(head1->column!=head2->row)
	{
		cout<<"Dimesion not match not able multipy matrix\n";
		return;
	}
	head2=transpose(head2,head2->row,head2->column);
	head2=head2->next;
	head1=head1->next;
	llist<T> *resulthead=NULL;
	llist<T> *temp1=head1;
	int k=0;
	while(temp1)
	{
		llist<T> *temp2=head2;
		while(temp2)
		{
			if(temp1->column==temp2->column)
			{
				llist<T> *newnode=(llist<T> *)malloc(sizeof(llist<T>));
				newnode->row=temp1->row;
				newnode->column=temp2->row;
				newnode->value=(temp1->value)*(temp2->value);
				newnode->next=resulthead;
				resulthead=newnode;
				k++;
			}
			temp2=temp2->next;
		}
		temp1=temp1->next;
	}
	temp1=resulthead;
	while(temp1)
	{
		llist<T> *temp2=temp1->next;
		llist<T> *prev=temp1;
		while(temp2)
		{
			if(temp1->row==temp2->row&&temp1->column==temp2->column)
			{
				temp1->value=temp1->value+temp2->value;
				k--;
				prev->next=temp2->next;
				free(temp2);
				temp2=prev->next;
			}
			else
			{
				prev=temp2;
				temp2=temp2->next;
			}
		}
		temp1=temp1->next;
	}
	mergesort(&resulthead);
	llist<T> *newnode=(llist <T>*)malloc(sizeof(llist<T>));
	newnode->row=row;
	newnode->column=column;
	newnode->value=k;
	newnode->next=resulthead;
	resulthead=newnode;
	llist<T> *temp=resulthead;
	displayS(temp);
	temp=resulthead;
	displayM(temp);
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
