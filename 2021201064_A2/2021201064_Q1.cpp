#include<stdlib.h>
#include<iostream>
using namespace std;
template <typename T>
struct node
{
    T val;
    int height;
    int count;
    struct node* left;
    struct node* right;
};
template <class T>
class avl
{
	public:
		node<T> *avlnode;
		avl()
		{
			avlnode=NULL;	
		}	
		int ht(node<T> *root)
		{
			if(root)
			{
				return 1+max(ht(root->left), ht(root->right));
			}
			return -1;
		}
		void updateHt(node<T> *root)
		{
			if(root)
			{
				root->height = 1 + max(ht(root->left), ht(root->right)); 
			}
		}
		int htb(node<T> *root)
		{
			if(root==NULL)
				return 0;
			return ht(root->left)-ht(root->right);
		}
		node<T>* rotateL(node<T> *root)
		{
			node<T>* temp = root->right;
			node<T>* t = temp->left;
			root->right = t;
			temp->left = root;
			updateHt(temp);
			updateHt(root);
			return temp;
		}
		node<T>* rotateR(node<T> *root)
		{
			node<T>* temp = root->left;
			root->left = temp->right;
			temp->right = root;
			updateHt(temp);
			updateHt(root);
			return temp;
		}
		node<T> * addnode(node<T> *root,T val)
		{
			if(!root)
			{
				root = new node<T>;
				root->val = val;
				root->height = 0;
				root->count=1;
				root->left = root->right = NULL;
				return root;
			}
			if(root->val==val)
			{
				(root->count)++;
				return root;
			}
			if(root->val<val)
			{
				root->right=addnode(root->right,val);
			}
			else if(root->val>val)
			{
				root->left=addnode(root->left,val);
			}
			updateHt(root);
			int bal = htb(root);
			if(bal<=-2&&val>root->right->val)
			{
				root=rotateL(root);
			}
			if(bal>=2&&val<root->left->val)
			{
				root=rotateR(root);
			}
			if(bal<=-2&&val<root->right->val)
			{
				root->right=rotateR(root->right);
				root=rotateL(root);
			}
			if(bal>=2&&val>root->left->val)
			{
				root->left=rotateL(root->left);
				root=rotateR(root);
			}
			return root;
		}
		node<T>* deletedriver(node<T> *root,T val)
		{
			if (root==NULL)
		    {
		    	return root;
			}
		    if (val<root->val)
		    {
		    	root->left=deletedriver(root->left,val);
			}
		    else if (val>root->val)
		    {
		    	root->right=deletedriver(root->right, val);
			}
		    else 
			{
		        if (root->count>1) 
				{
		            (root->count)--;
		            return root;
		        }
		        if ((root->left==NULL)||(root->right==NULL)) 
				{
		            node<T>* temp=root->left?root->left:root->right;
		            if (temp==NULL) 
					{
		                temp=root;
		                root=NULL;
		            }
		            else
		            {
		            	*root=*temp;
					}
		            free(temp);
		        }
		        else 
				{
					node<T>* temp=root->right;
					while(temp->left!=NULL)
					{
						temp=temp->left;
					}
		            root->val=temp->val;
		            root->count=temp->count;
		            root->right=deletedriver(root->right, temp->val);
		        }
		    }
		    if (root==NULL)
		    {
		    	return root;
			}
		    updateHt(root);
		    int bal = htb(root);
		    int left=htb(root->left);
		    int right=htb(root->right);
		    if (bal>=2&&left>=0)
		    {
		    	return rotateR(root);
			}
		    if (bal>=2&&left<0) 
			{
		        root->left=rotateL(root->left);
		        return rotateR(root);
		    }
		    if (bal<=-2&&right<=0)
		    {
		    	return rotateL(root);
			}
		    if (bal<=-2&&right>0) 
			{
		        root->right=rotateR(root->right);
		        return rotateL(root);
		    }
		    return root;
		}
		void insert(T key)
		{
			avlnode=addnode(avlnode,key);
		}
		void deletenode(T key)
		{
			avlnode=deletedriver(avlnode,key);
		}
		node<T>* searchdriver(node<T> *root,T val)
		{
			if(root==NULL||root->val==val)
			{
				return root;
			}
			if(val<root->val)
			{
				return searchdriver(root->left,val);
			}
			else
			{
				return searchdriver(root->right,val);
			}
		}
		int search(T key)
		{
			if(!searchdriver(avlnode,key))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		int countdriver(node<T> *root,T val)
		{
			if(root==NULL)
			{
				return 0;
			}
			if(root->val==val)
			{
				return root->count;
			}
			if(val<root->val)
			{
				return countdriver(root->left,val);
			}
			else
			{
				return countdriver(root->right,val);
			}
		}
		int count(T key)
		{
			return countdriver(avlnode,key);
		}
		void nextg(node<T>* root, T key,T *next)
		{
            if(!root)
            {
            	return;
			}
            if(key<root->val)
			{
                *next=root->val;
                nextg(root->left, key,next);
            }
            else
            {
            	nextg(root->right, key,next);
			}
        }
        void nexts(node<T>* root, T key,T *prev)
		{
            if(!root) 
			{
				return;
			}

            if(key > root->val)
			{
                *prev = root->val;
                nexts(root->right, key,prev);
            }
            else nexts(root->left, key,prev);
        }
		T lower_bounddriver(node<T>* root,T key)
		{
            node<T> *temp=searchdriver(root, key);
            if(temp) 
			{
				return key;
			}
			T next;
            nextg(root, key,&next);
            return next;
        }
        T lower_bound(T key)
		{
			T temp1,temp2;
        	node<T> *root=avlnode;
        	while(root->left!=NULL)
        	{
        		root=root->left;
			}
			temp1=root->val;
			root=avlnode;
			while(root->right!=NULL)
			{
				root=root->right;
			}
			temp2=root->val;
			if(key<=temp1)
			{
				return temp1;
			}
			if(key>=temp2)
			{
				return temp2;
			}
            return lower_bounddriver(avlnode, key);
        }
        T upper_bounddriver(node<T>* root, T key)
		{
			T next;
			node<T> *temp=root;
            nextg(root, key,&next);
            return next;
        }
        T upper_bound(T key)
		{
			T temp1,temp2;
        	node<T> *root=avlnode;
        	while(root->left!=NULL)
        	{
        		root=root->left;
			}
			temp1=root->val;
			root=avlnode;
			while(root->right!=NULL)
			{
				root=root->right;
			}
			temp2=root->val;
			if(key<temp1)
			{
				return temp1;
			}
			if(key>=temp2)
			{
				return temp2;
			}
            return upper_bounddriver(avlnode, key);
        }
        T closet(T key)
        {
        	T temp1,temp2;
        	node<T> *root=avlnode;
        	while(root->left!=NULL)
        	{
        		root=root->left;
			}
			temp1=root->val;
			root=avlnode;
			while(root->right!=NULL)
			{
				root=root->right;
			}
			temp2=root->val;
			if(key<=temp1)
			{
				return temp1;
			}
			if(key>=temp2)
			{
				return temp2;
			}
            T x = lower_bound(key);
            T prev;
            nexts(avlnode, key,&prev);
            return key-prev > x-key ? x : prev;  
        }
        void kthdriver(node<T> *root,int key,node<T> **temp,int *c)
        {
        	if(!root||key<=*c)
        	{
        		return;
			}
			kthdriver(root->right,key,temp,c);
			*c+=root->count;
			if(*c>=key&&!(*temp))
			{
				*temp=root;
				return;
			}
			kthdriver(root->left,key,temp,c);
		}
        void kth(int key)
        {
        	node<T> *temp=NULL;
        	int c=0;
        	kthdriver(avlnode,key,&temp,&c);
        	if(temp)
        	{
        		cout<<temp->val<<endl;
			}
			else
			{
				cout<<"not Found\n";
			}
		}
		int countnodedriver(node<T> *root,T start, T end)
		{
		    if (!root)
		    {
		    	return 0;
			}
		    if (root->val==end&&root->val==start)
		    {
		    	return root->count;
			}
		    if (root->val<=end&&root->val>=start)
		    {
		    	return countnodedriver(root->left,start,end)+root->count+countnodedriver(root->right,start,end);

			}
		    else if (root->val<start)
		    {
		    	return countnodedriver(root->right,start,end);
			}
		    else
		    {
		    	return countnodedriver(root->left,start,end);
			}
		}
		int countnode(T start,T end)
		{
			return countnodedriver(avlnode,start,end);
		}
		void inorderdriver(node<T> *root)
		{
			if(root)
			{
				inorderdriver(root->left);
				int x=root->count;
				while(x--)
				{
					cout<<root->val<<" ";
				}
				inorderdriver(root->right);
			}
		}
		void inorder()
		{
			inorderdriver(avlnode);
		}
};
int main()
{
	avl<float> o;
	return 0;
}
