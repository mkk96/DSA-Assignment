#include<stdlib.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
using namespace std;
vector<vector<int> > result;
void dfs(vector<vector<pair<int,int> > > &graph,vector<int>& path, int source,int destination,vector<bool> &visited,int *w)
{
	visited[source]=true;
	path.push_back(source);
	if(source==destination)
	{
		path.push_back(*w);
		result.push_back(path);
		path.pop_back();
	}
	else 
	{
		vector<pair<int,int> >:: iterator itr;
		for(itr=graph[source].begin();itr!=graph[source].end();itr++)
		{
			if(!visited[(*itr).first])
			{
				*w+=(*itr).second;
				dfs(graph,path, (*itr).first,destination,visited,w);
				*w-=(*itr).second;
			}
		}
	}
	visited[source]=false;
	path.pop_back();
}
void pathutil(vector<vector<pair<int,int> > > &graph,int n,int source,int destination)
{
	vector<int> path;
    vector<bool> visited(n,false);
	int weight=0;
	dfs(graph,path,source,destination,visited,&weight);
}
void pathdriver(vector<vector<pair<int,int> > > &graph,int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			pathutil(graph,n,i,j);
		}
	}
}
bool lexi(int x,int y)
{
	stack<int> q1,q2;
	while(x>0)
	{
		q1.push(x%10);
		x/=10;
	}
	while(y>0)
	{
		q2.push(y%10);
		y/=10;
	}
	int size1=q1.size();
	int size2=q2.size();
	while(!q1.empty()&&!q2.empty())
	{
		if(q1.top()!=q2.top())
		{
			return q1.top()<q2.top();
		}
		q1.pop();
		q2.pop();
	}
	return size1<size2;
}
bool compare(vector<int>& v1,vector<int>& v2 ) 
{
	if(v1[v1.size()-1]==v2[v2.size()-1])
	{
		vector<int>::iterator itr1,itr2;
		for(itr1=v1.begin(),itr2=v2.begin();itr1!=v1.begin(),itr2!=v2.end();itr1++,itr2++)
		{
			if(*itr1==*itr2)
			{
				
			}
			else
			{
				return lexi(*itr1,*itr2);
			}
			
		}
		return v1.size()<v2.size();
	}
	return v1[v1.size()-1]<v2[v2.size()-1];
}
void abreversekaro()
{
	vector<vector<int> > ::iterator itr;
	for(itr=result.begin();itr!=result.end();itr++)
	{
		if(!lexi((*itr)[0],(*itr)[(*itr).size()-1]))
		{
			reverse((*itr).begin(),(*itr).end());
		}
	}
}
int main()
{
	int n,e,u,v,w,k;
	cin>>n>>e;
	vector<vector<pair<int,int> > > graph(n);
	for(int i=0;i<e;i++)
	{
		cin>>u>>v>>w;
		graph[u].push_back({v,w});
		graph[v].push_back({u,w});
	}
	cin>>k;
	pathdriver(graph,n);
	sort(result.begin(),result.end(),compare);
	//cout<<"-----------------------------------\n";
	/*vector<vector<int> > ::iterator itr;
	for(itr=result.begin();itr!=result.end();itr++)
	{
		vector<int> ::iterator itr1;
		for(itr1=(*itr).begin();itr1!=(*itr).end();itr1++)
		{
			cout<<*itr1<<" ";
		}
		cout<<endl;
	}*/
	vector<vector<int> > ::iterator itr;
	for(itr=result.begin();itr!=result.end();itr++)
	{
		(*itr).pop_back();
	}
	abreversekaro();
	vector<int>::iterator itr1;
	v=result.size();
	k=min(k,v);
	for(int i=0;i<k;i++)
	{
		for(itr1=result[i].begin();itr1!=result[i].end();itr1++)
		{
			cout<<*itr1<<" ";
		}
		cout<<endl;
	}
	return 0;
}
