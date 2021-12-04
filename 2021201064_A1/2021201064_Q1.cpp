#include<stdlib.h>       
#include<string.h>
#include<iostream>
using namespace std;
int compareq(string a,string b);
int priority(char op);
string multi(string a,string b);
string exponent(long long a,long long n);
void exponentiationdriver();
void factorial();
string addition(string a,string b);
string subtraction(string a,string b);
string module(string b,string a);
void gcd();
void calculator();
int main()
{
	int n;
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			exponentiationdriver();
			break;
		case 2:
			gcd();
			break;
		case 3:
			factorial();
			break;
		case 4:
			calculator();
			break;
		default:
			break;
	}
	return 0;
}
int compareq(string a,string b)
{
	int x=a.length();
	int y=b.length();
	if(x>y)
	{
		return 1;
	}
	else if(x<y)
	{
		return -1;
	}
	else
	{
		for(int i=0;i<y;i++)
		{
			int q=a[i]-'0';
			int w=b[i]-'0';
			if(q>w)
			{
				return 1;
			}
			else if(w>q)
			{
				return -1;
			}
		}
	}
	return 0;
}
int priority(char op)
{
	if(op=='/' ||op=='x')
		return 1;
	return 0;
}
string multi(string a,string b)
{
	int alength=a.length();
	int blength=b.length();
	int flaga=1,flagb=1;
	for(int i=0;i<alength;i++)
	{
		if(a[i]!='0')
		{
			flaga=0;
			break;
		}
	}
	for(int i=0;i<blength;i++)
	{
		if(b[i]!='0')
		{
			flagb=0;
			break;
		}
	}
	if(flaga||flagb)
	{
		return "0";
	}
	int i, j;
	string res;
	int c[alength + blength+1];
	memset(c, 0, sizeof(int) * (alength + blength+1));
	for (i =alength-1;i>= 0;i--)
	{
		for (j=blength-1;j >=0;j--)					
		{
			c[i+j+1]+=(b[j]-'0')*(a[i]-'0');
		}
	}
	for (i=alength+blength-1;i>=0;i--)
	{
		if (c[i]>=10)
		{
			c[i-1]+=c[i]/10;
			c[i]%=10;
		}
	}	
	i=0;
	while(c[i]==0)
	{
		i++;
	}
	while (i<alength+blength)
	{
		res.push_back(c[i]+'0');
		i++;
	}
	return res;
}
string exponent(long long a,long long n)
{
	if(n==0)
	{
		return "1";
	}
	if(n==1)
	{
		string result;
		string a1;
		while(a>0)
		{
			result.push_back(a%10+48);
			a/=10;
		}
		int resultlength = result.length();
		for(int j=0;j<resultlength;j++)
		{
			a1.push_back(result[resultlength-1-j]);
		}
		result=a1;
		return result;
	}
	string r=exponent(a,n/2);
	if(n%2==0)
	{
		string result=multi(r,r);
		return result;
	}
	else
	{
		string temp;
		string a1;
		while(a>0)
		{
			temp.push_back(a%10+48);
			a/=10;
		}
		int templength = temp.length();
		for(int j=0;j<templength;j++)
		{
			a1.push_back(temp[templength-1-j]);
		}
		temp=a1;
		string result=multi(r,r);
		result=multi(result,temp);
		return result;;
	}
}

void exponentiationdriver()
{
	long long a,b;
	cin>>a>>b;
	if(a==0)
	{
		cout<<0;
		return;
	}
	if(b==0)
	{
		cout<<1;
		return;
	}
	cout<<exponent(a,b);
}
void factorial()
{
	long long a;
	cin>>a;
	if(a==1||a==0)
	{
		cout<<1;
		return;
	}
	string result="1";
	for(long long i=2;i<=a;i++)
	{
		long long temp=i;
		string b="";
		while(temp>0)
		{
			b.push_back(temp%10+48);
			temp/=10;
		}
		int blength = b.length();
		string b1;
		for(int j=0;j<blength;j++)
		{
			b1.push_back(b[blength-1-j]);
		}
		result=multi(result,b1);
	}
	cout<<result;
}
string addition(string a,string b)
{
	int res[30001];
	int alength = a.length();
	int blength = b.length();
	string a1,b1;
	int temp[30001];
	int i,j;
	for(int j=0;j<alength;j++)
	{
		a1.push_back(a[alength-1-j]);
	}
	for(int j=0;j<blength;j++)
	{
		b1.push_back(b[blength-1-j]);
	}
	int lmax = alength;
	if(alength<blength)
	{
		lmax = blength;
	}
	int carry=0,sum=0;
	for(i=0; i< lmax; i++)
	{
		int x=a1[i]-48;
		int y=b1[i]-48;
		if(alength==blength || (i < alength && i < blength))
		{
			sum = carry+x+y;
		}
		else if(i >=alength)
		{
			sum = carry+y;
		}
		else if(i >=blength)
		{
			sum = carry+x;
		}
		res[i] = sum%10;
		carry = sum/10;
	}
	string result;
	if(carry)
	{
		res[i]=carry;
		i++;
	}
	for(j=0; j < i; j++)
	{
		result.push_back(res[i-j-1]+48);
	}
	return result;
}
string subtraction(string a,string b)
{
	swap(a,b);
	string res = "";
	int alength = a.length();
	int blength = b.length();
	string a1,b1;
	for(int j=0;j<alength;j++)
	{
		a1.push_back(a[alength-1-j]);
	}
	for(int j=0;j<blength;j++)
	{
		b1.push_back(b[blength-1-j]);
	}
	int carry = 0;
	for (int i=0; i<blength; i++)
	{
		int sub = ((a1[i]-'0')-(b1[i]-'0')-carry);
		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		res.push_back(sub + '0');
	}
	for (int i=blength; i<alength; i++)
	{
		int sub = ((a1[i]-'0') - carry);
		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		res.push_back(sub + '0');
	}
	string result;
	int x=res.size(),k=0;
	while(res[x-1]=='0')
	{
		x--;
	}
	for(int i=0;i<x;i++)
	{
		result.push_back(res[x-1-i]);
	}
	if(result.size()!=0)
	{
		return result;
	}
	else
	{
		return "0";
	}
}
void gcd()
{
	string a,b;
	cin>>a>>b;
	if(compareq(a,b)==-1)
	{
		swap(a,b);
	}
	int alength=a.length();
	int blength=b.length();
	int flaga=1,flagb=1;
	for(int i=0;i<alength;i++)
	{
		if(a[i]!='0')
		{
			flaga=0;
			break;
		}
	}
	for(int i=0;i<blength;i++)
	{
		if(b[i]!='0')
		{
			flagb=0;
			break;
		}
	}
	if(flaga)
	{
		cout<<b;
		return;
	}
	if(flagb)
	{
		cout<<a;
		return;
	}
	string mod="0";
	for (int i=0;i<alength;i++)
    {
    	string x="";
    	x+=a[i];
    	mod=module(addition(multi(mod,"10"),x),b);
	}
	flagb=1;
	int modlength=mod.length();
	for(int i=0;i<modlength;i++)
	{
		if(mod[i]!='0')
		{
			flagb=0;
			break;
		}
	}
	if(flagb)
	{
		cout<<b;
		return;
	}
	while (compareq(mod,b)!=0)   
	{  
	
		if (compareq(mod,b)==1)  
		{  
			mod=subtraction(b,mod);   
		}  
		else  
		{  
			b=subtraction(mod,b);  
		}     
	
	}   
	cout<<b;
}
string module(string a,string b)
{
	if(compareq(a,b)==-1)
	{
		return a;
	}
	if(compareq(a,b)==0)
	{
		return "1";
	}
	string result="0";
	string temp=a;
	while(1)
	{
		temp=subtraction(b,temp);
		if(compareq(temp,b)<0)
			break;
	}
	return temp;
}
void calculator()
{
	string exp;
	cin>>exp;
	string number[100];
	char op[100];
	int numtop=0,optop=0,i=0;
	string temp="";
	while(exp[i]!='\0')
	{
		if(exp[i]!='+'&&exp[i]!='-'&&exp[i]!='x' &&exp[i]!='/')
		{
			temp+=exp[i++];
		}
		else if(exp[i]=='+'||exp[i]=='-')
		{
			number[numtop++]=temp;
			temp="";
			if(optop==0)
			{
				op[optop++]=exp[i++];
			}
			else
			{
				while(optop>0)
				{
					char x=op[--optop];
					if(x=='x')
					{
						number[numtop-2]=multi(number[numtop-1],number[numtop-2]);
						numtop--;
					}
					/*if(x=='/')
					{
						number[numtop-2]=divide(number[numtop-1],number[numtop-2]);
						numtop--;
					}*/
					if(x=='+')
					{
						number[numtop-2]=addition(number[numtop-1],number[numtop-2]);
						numtop--;
					}
					if(x=='-')
					{
						number[numtop-2]=subtraction(number[numtop-1],number[numtop-2]);
						numtop--;
					}
				}
				op[optop++]=exp[i++];
			}
		}
		else if(exp[i]=='x'||exp[i]=='/')
		{
			number[numtop++]=temp;
			temp="";
			if(optop==0)
			{
				op[optop++]=exp[i++];
			}
			else
			{
				char x=op[optop-1];
				while(optop>0&&priority(x)==priority(exp[i]))
				{
					if(x=='x')
					{
						number[numtop-2]=multi(number[numtop-1],number[numtop-2]);
						numtop--;
						optop--;
					}
					/*if(x=='/')
					{
						number[numtop-2]=divide(number[numtop-1],number[numtop-2]);
						numtop--;
						optop--;
					}*/
					x=op[optop-1];
				}
				op[optop++]=exp[i++];
			}
		}
	}
	number[numtop++]=temp;
	/*for(int j=0;j<numtop;j++)
	{
		cout<<number[j]<<" ";
	}
	for(int j=0;j<optop;j++)
	{
		cout<<op[j]<<" ";
	}
	cout<<endl;*/
	while(optop>0)
	{
		char x=op[--optop];
		if(x=='x')
		{
			number[numtop-2]=multi(number[numtop-1],number[numtop-2]);
			numtop--;
		}
		/*if(x=='/')
		{
			number[numtop-2]=divide(number[numtop-1],number[numtop-2]);
			numtop--;
		}*/
		if(x=='+')
		{
			number[numtop-2]=addition(number[numtop-1],number[numtop-2]);
			numtop--;
		}
		if(x=='-')
		{
			number[numtop-2]=subtraction(number[numtop-1],number[numtop-2]);
			numtop--;
		}
	}
	cout<<number[0];
}
