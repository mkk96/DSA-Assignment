#include<stdlib.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
const int inf=1e7;
using namespace std;
int findMin(int n,int distance[],bool visited[])
{
    int min=inf;
    int node=0;
    int i=0;
    while(i<n)
	{
        if(visited[i]==false && min>distance[i]){
            min=distance[i];
            node=i;
        }
        i++;
    }
    return node;
}
bool compare(int x,int y)
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
void dijk(vector<vector<pair<int,int> > > graph,int s,int n)
{
	int distance[n]; 
	bool visited[n];
	int i;
	while(i<n)
	{
		distance[i]=inf;                                 
        visited[i]=false;  
		i++;
	}
    distance[s]=0;
    int count=0;
    vector<int> path[n];
    vector<int> temppath;
    for(count=0;count<n;count++)
	{
        int node = findMin(n,distance,visited);
        visited[node]=true;
        vector<pair<int,int> > :: iterator i;
		for(i=graph[node].begin();i!=graph[node].end();i++)
		{
            if(visited[(*i).first]==false)
			{
				if(distance[(*i).first]>=distance[node]+((*i).second))
                {
            		if(distance[(*i).first]==(distance[node]+((*i).second)))
            		{
            			if(compare(path[(*i).first][path[(*i).first].size()-1],node))
            			{
            				//path[(*i).first].push_back(node);
						}
						else
						{
							path[(*i).first]=path[node];
							path[(*i).first].push_back(node);
						}
					}
					else
					{
						path[(*i).first]=path[node];
            			path[(*i).first].push_back(node);
					}
				}
                distance[(*i).first]=min(distance[(*i).first],distance[node]+((*i).second));
            }
        }
    }
    for(int i=0;i<n;i++)
    {
    	vector<int> ::iterator itr;
    	if(i!=s)
    	{
    		path[i].push_back(i);
    		reverse(path[i].begin(),path[i].end());
    		if(path[i].size()!=1)
    		{
    			for(itr=path[i].begin();itr!=path[i].end();itr++)
		    	{
		    		cout<<*itr<<" ";
				}
				cout<<endl;
			}
		}
	}
}
int main()
{
	int n,e,u,v,w,s;
	cin>>n>>e;
	vector<vector<pair<int,int> > > graph(n);
	for(int i=0;i<e;i++)
	{
		cin>>u>>v>>w;
		graph[u].push_back({v,w});
		graph[v].push_back({u,w});
	}
	cin>>s;
	vector<vector<pair<int,int> > >::iterator itr1;
    for(itr1=graph.begin();itr1!=graph.end();itr1++)
    {
    	sort((*itr1).begin(),(*itr1).end());
	}
	dijk(graph,s,n);
	return 0;
}
