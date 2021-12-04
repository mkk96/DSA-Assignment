#include<stdlib.h>
#include <iostream>
#include<string>
using namespace std;
template<typename T>
class Deque 
{
	public:
		T *arr;
		int qfront;
		int qrear;
		int qsize;
		Deque()
		{
			arr=new T[0];
			qfront=0;
			qrear=0;
			qsize=0;
		}
		Deque(int n,T x)
		{
			arr= new T[n+1];
			qfront=0;
			qrear=n;
			qsize=n+1;
			for(int i=0;i<n;i++)
			{
				arr[i]=x;
			}
		}
		void push_back(T x)
		{
			if(qsize==0)
			{
				arr=new T[2];
				arr[qrear++]=x;
				qsize=2;
			}
			else
			{
				if((qrear+1)%qsize!=qfront)
				{
					arr[qrear++]=x;
				}
				else
				{
					T *temp=new T[2*qsize];
					for(int i=0;i<qsize;i++)
					{
						temp[i]=arr[(qfront++)%qsize];
					}
					arr=new T[2*qsize];
					for(int i=0;i<qsize;i++)
					{
						arr[i]=temp[i];
					}
					qfront=0;
					qrear=qsize-1;
					qsize=2*qsize;
					arr[qrear++]=x;
				}
				qrear%=qsize;
			}
		}
		void push_front(T x)
		{
			if(qsize==0)
			{
				arr=new T[2];
				arr[qrear++]=x;
				qsize=2;
			}
			else
			{
				int q=qfront-1;
				q=q<0?(q+qsize):q;
				if(q!=(qrear)%qsize)
				{
					arr[q]=x;
					qfront=(qfront-1)<0?(qsize-1):(qfront-1);
				}
				else
				{
					T *temp=new T[2*qsize];
					for(int i=0;i<qsize;i++)
					{
						temp[i]=arr[(qfront++)%qsize];
					}
					arr=new T[2*qsize];
					arr[0]=x;
					for(int i=1;i<=qsize;i++)
					{
						arr[i]=temp[i-1];
					}
					qfront=0;
					qrear=qsize;
					qsize=2*qsize;
				}
				qrear%=qsize;
			}
		}
		void pop_back()
		{
			if(qrear!=qfront&&qsize!=0)
			{
				qrear=((qrear-1)<0?(qsize):(qrear-1))%qsize;
			}
		}
		void pop_front()
		{
			if(qrear!=qfront&&qsize!=0)
			{
				qfront=(qfront+1)%qsize;
			}
		}
		T front()
		{
			if(qrear!=qfront&&qsize!=0)
			{
				return arr[qfront];
			}
		}
		T back()
		{
			if(qrear!=qfront&&qsize!=0)
			{
				return arr[qrear-1];
			}
		}
		bool empty()
		{
			if(qsize==0||qrear==qfront)
			{
				return false;
			}
			return true;
		}
		int size()
		{
			return (qsize-qfront+qrear)%qsize;
		}
		void resize(int x, T d)
		{
			if(x>size())
			{
				T *temp=new T[x+1];
				int i=0;
				while(qrear!=qfront)
				{
					temp[i++]=arr[(qfront++)%qsize];
				}
				for(int j=i;j<=x;j++)
				{
					temp[i++]=d;
				}
				arr=new T[x+1];
				for(int i=0;i<x;i++)
				{
					arr[i]=temp[i];
				}
				qfront=0;
				qrear=x;
				qsize=x+1;
			}
		}
		void clear()
		{
			arr=new T[0];
			qfront=0;
			qrear=0;
		}
		void operator[](int n)
		{
			if(n>size())
			{
				cout<<-1<<endl;
				return;
			}
			int x=(n+qfront)%qsize;
			if((qfront<qrear&&(qfront<=x&&x<qrear))||(x>=0&&x<qrear)||(x<qsize&&x>=qfront))
			{
				cout<<arr[x]<<endl;
				return;
			}
			cout<<-1<<endl;
		}
};
template<typename T>
void display(Deque<T> o)
{
	int x=o.qfront;
	int y=o.qrear;
	while(x!=y)
	{
		cout<<o.arr[x]<<" ";
		x=(x+1)%o.qsize;
	}
}
template<typename T>
void driver(Deque<T> deque)
{
	int n;
	while(1)
	{
		cout<<"\n1. For Push Back\n2. For Pop Back\n3. For Push Front\n4. For Pop Front\n5. For Front\n6. For back\n7. For empty\n8. For Size\n";
		cout<<"9. For Resize\n10. For Clear\n11. D[n]\n12. Display\n13. For Exit()\n";
		cin>>n;
		int temp1;
		T temp2;
		switch(n)
		{
			case 1:
				cout<<"Enter Element\t";
				cin>>temp2;
				deque.push_back(temp2);
				break;
			case 2:
				deque.pop_back();
				break;
			case 3:
				cout<<"Enter Element\t";
				cin>>temp2;
				deque.push_front(temp2);
				break;
			case 4:
				deque.pop_front();
				break;
			case 5:
				cout<<deque.front()<<endl;
				break;
			case 6:
				cout<<deque.back()<<endl;
				break;
			case 7:
				if(deque.empty()==true)
				{
					cout<<"Not Empty"<<endl;
				}
				else
				{
					cout<<"Empty"<<endl;
				}
				break;
			case 8:
				cout<<deque.size()<<endl;
				break;
			case 9:
				cout<<"Enter Size and default value";
				cin>>temp1>>temp2;
				deque.resize(temp1,temp2);
				break;
			case 10:
				deque.clear();
				break;
			case 11:
				cout<<"Enter Index\t";
				cin>>temp1;
				deque[temp1];
				break;
			case 12:
				display(deque);
				break;
			case 13:
				exit(0);
				break;
			default:
				cout<<"wrong Choice"<<endl;
				break;
		}
	}
}
int main()
{
	int n,m;
	cout<<"1. For int\n2. For float\n3. For Char\n";
	cout<<"1. For empty\n2. For size and value\n";
	cin>>n>>m;
	if(n==1&&m==1)
	{
		Deque<int> deque;
		driver(deque);
	}
	if(n==1&&m==2)
	{
		int temp1;
		int temp2;
		cout<<"Enter size and Value\n";
		cin>>temp1>>temp2;
		Deque<int> deque(temp1,temp2);
		driver(deque);
	}
	if(n==2&&m==1)
	{
		Deque<float> deque;
		driver(deque);
	}
	if(n==2&&m==2)
	{
		int temp1;float temp2;
		cout<<"Enter size and Value\n";
		cin>>temp1>>temp2;
		Deque<float> deque(temp1,temp2);
		driver(deque);
	}
	if(n==3&&m==1)
	{
		Deque<string> deque;
		driver(deque);
	}
	if(n==3&&m==2)
	{
		int temp1;string temp2;
		cout<<"Enter size and Value\n";
		cin>>temp1>>temp2;
		Deque<string> deque(temp1,temp2);
		driver(deque);
	}
}
