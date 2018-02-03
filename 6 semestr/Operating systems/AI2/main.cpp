/*#include "stdafx.h"*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>

using namespace std;

int N = 10;
int N2 = N * N;
vector<char> ar;
vector< vector<int> > vect;
vector< vector<int> > iter(10);
vector<int>  matrix(N2 * N2);

bool vect_eq(vector<int> v1,vector<int> v2)
{
	bool eq = true;
	for(int i = 0; i < N2; i++)
	{
		if(v1[i]!=v2[i])
		{
			eq=false;
		}
	}
	return eq;
}

void remaster(vector<int> &v)
{
	for(int i=0;i<v.size();i++)
	{
		if(v[i]>=0)
		{
			v[i]=1;
		}else{
			v[i]=-1;
		}
	}
}

vector<int> mult(/*vector< vector<int> > m,*/vector<int> v)
{
	vector<int> result(N2);
	for(int j=0;j<N2;j++)
		{
			result[j]=0;
		}
	for(int j=0;j<N2;j++)
		{
			for(int k=0;k<N2;k++)
			{
				result[j]+=matrix[j*N2+k]*v[k];
			}
		}
	return result;
}

void study()
{
	vector<int> v(N2);
	char A;
	ifstream in("study.txt");
	while(in >> A)
	{
		ar.insert( ar.end(), A);
		/*cout << A << endl;*/
		for(int i = 0; i < N2; i++)
		{
			in >> v[i];
		}
		vect.insert(vect.end(),v);
	}
}

void create_matrix()
{
	for(int i=0;i<N2;i++)
	{
		matrix[i]=0;
	}

	for(int i=0;i<vect.size();i++)
	{
		for(int j=0;j<N2;j++)
		{
			for(int k=0;k<N2;k++)
			{
				matrix[j*N2+k]+=vect[i][j]*vect[i][k];
			}
		}
	}



	/*for(int j=0;j<N2;j++)
		{
			for(int k=0;k<N2;k++)
			{
				cout<<matrix[j*N2+k]<<" ";
			}
			cout<<"\n";
		}
*/
}

int main()
{
	study();
	create_matrix();

	vector<int> v(N2);
	ifstream in("test.txt");
	for(int i=0;i<N2;i++)
		{
			in>>v[i];
		//	cout<<v[i]<<"  ";
		}

	vector<int> temp;
		temp=mult(v);
		remaster(temp);
		iter[0]=temp;

	for(int i=1; i<10;i++)
	{
		temp=mult(iter[i-1]);
		remaster(temp);
		iter[i]=temp;
	}

	bool cont=true;
	int counter=0;
	while(cont)
	{
		cont=false;

		for(int i=1; i<10;i++)
		{
			if(!vect_eq(temp,iter[i]))
			{
				cont=true;
			}else{

			}
		}
		iter[counter]=temp;
		counter++;
		counter=counter%10;
	}

	temp=iter[counter];
/*
    cout<<"\n";
			for(int j=0; j<10;j++)
		{
        for(int i=0; i<10;i++){
            cout<<temp[10*j+i]<<"  ";
        }cout<<"\n";
		}
*/
		bool found=false;
	for(int i=0;i<vect.size();i++)
	{
			if(vect_eq(temp,vect[i]))
			{
				cout<<"\nResult:"<<ar[i]<<"\n";
				found=true;
			}
	}
	if(!found)
	{
		cout<<"\n????\n";
	}
	system("pause");
	return 0;
}

