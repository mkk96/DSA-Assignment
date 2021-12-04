#include<stdlib.h>
#include<iostream>
#include <string>
#include<vector>
#include<algorithm>
using namespace std;
struct triplet 
{
	int x,y,w;
};
void bfs(string grid[],int n,int m)
{
	vector<triplet> q;
	q.push_back({1,0,0});
	int weight[n][m];
	bool visit[n][m];
	int x,y,w;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			weight[i][j]=-1;
			visit[i][j]=false;
		}
	}
	weight[1][0]=0;
	visit[1][0]=true;
	while(!q.empty())
	{
		x=(q.front()).x;
		y=(q.front()).y;
		w=(q.front()).w;
		q.erase(q.begin());
		if((x-1)>=0)
		{
			if((grid[x-1][y]=='.'||grid[x-1][y]=='A'||grid[x-1][y]=='R')&&!visit[x-1][y])
			{
				q.push_back({x-1,y,w+1});
				visit[x-1][y]=true;
				weight[x-1][y]=w+1;
			}
		}
		if((x+1)<n)
		{
			if((grid[x+1][y]=='.'||grid[x+1][y]=='A'||grid[x+1][y]=='R')&&!visit[x+1][y])
			{
				q.push_back({x+1,y,w+1});
				visit[x+1][y]=true;
				weight[x+1][y]=w+1;
			}
		}
		if((y+1)<m)
		{
			if((grid[x][y+1]=='.'||grid[x][y+1]=='A'||grid[x][y+1]=='R')&&!visit[x][y+1])
			{
				q.push_back({x,y+1,w+1});
				visit[x][y+1]=true;
				weight[x][y+1]=w+1;
			}
		}
		if((y-1)>=0)
		{
			if((grid[x][y-1]=='.'||grid[x][y-1]=='A'||grid[x][y-1]=='R')&&!visit[x][y-1])
			{
				q.push_back({x,y-1,w+1});
				visit[x][y-1]=true;
				weight[x][y-1]=w+1;
			}
		}
	}
	int Aweight=weight[n-2][m-2];
	int flag=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(grid[i][j]=='R')
			{
				if(weight[i][j]<Aweight&&weight[i][j]!=-1)
				{
					flag=1;
				}
			}
		}
	}
	if(flag)
	{
		cout<<"No";
	}
	else
	{
		cout<<"Yes"<<endl;
		cout<<weight[n-2][m-2];		
	}
}
int main()
{
	int n,m;
	cin>>n>>m;
	string grid[n];
	for(int i=0;i<n;i++)
	{
		cin>>grid[i];
	}
	bfs(grid,n,m);
	return 0;
}
