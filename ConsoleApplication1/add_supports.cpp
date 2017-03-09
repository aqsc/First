#include <stdio.h> 
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

double r;
double point_x[1000000]={};
double point_y[1000000]={};
double point_z[1000000]={};
long edge[1000000][3]={};
long point_l[100000]={};

double pi=3.1415926535898;
	
double leng(long a, long b){
	double ans;
	ans=sqrt((point_x[a]-point_x[b])*(point_x[a]-point_x[b])
			+(point_y[a]-point_y[b])*(point_y[a]-point_y[b])
			+(point_z[a]-point_z[b])*(point_z[a]-point_z[b]));
	return ans;
}

double angle(long t){
	double ans,x,y,z;
	x=point_x[edge[t][0]]-point_x[edge[t][1]];
	y=point_y[edge[t][0]]-point_y[edge[t][1]];
	z=point_z[edge[t][0]]-point_z[edge[t][1]];
	ans=z/sqrt(x*x+y*y+z*z);
	double xx=asin(ans)/pi*360.0;
	if (xx<0) {xx=-xx;}
	return xx;
}
	


long ne,np;


int main(){

	ifstream fin1("point.txt");
	ifstream fin2("edge.txt");
	ofstream fou1("opoint.txt");
	ofstream fou2("oedge.txt");
	
	fin1>>np;
	fin2>>ne;
	double xt=1000,yt=-1000;
	for (long i=0;i<np;i++)
	{
		fin1>>point_x[i]>>point_y[i]>>point_z[i];
		if (point_x[i]>yt) {yt=point_x[i];}
		if (point_x[i]<xt) {xt=point_x[i];}		
		point_z[i]+=1.5;
	}
	cout<<xt<<' '<<yt<<'\n';
	getchar();
	for (long i=0;i<ne;i++)
	{
		fin2>>edge[i][0]>>edge[i][1];
		edge[i][0]--;
		edge[i][1]--;
	}	
	fin1.close();
	fin2.close();
	
	double len,ang;
	long nee=ne,npp=np;

	for (long i=0;i<ne;i++)
	{
	
		long q1=0,q2=0;
		for (long e=0;e<nee;e++)
		{
			if ((edge[e][0]==edge[i][0]) && (point_z[edge[e][1]]<point_z[edge[e][0]]) && (angle(e)>20)) 
			{
				q1=1;
			}
			
			if ((edge[e][1]==edge[i][1]) && (point_z[edge[e][0]]<point_z[edge[e][1]]) && (angle(e)>20)) 
			{
				q2=1;
			}
		}
		
		if (q1==0) 
		{
				long pp=-1;
				double ml=point_z[edge[i][0]];
				edge[nee][0]=edge[i][0];
				for (long k=0;k<npp-1;k++){
					edge[nee][1]=k;
					if ((point_z[k]<point_z[edge[i][0]]) && (angle(nee)>35) && (point_l[k]<4)) 
					{
						if (leng(k,edge[i][0]) < ml)
						{
							ml=leng(k,edge[i][0]);
							pp=k;
						}
					}
				}
				edge[nee][1]=pp;
				if (pp < 0) 
				{
					point_x[npp]=point_x[edge[i][0]];
					point_y[npp]=point_y[edge[i][0]];
					point_z[npp]=0;
					npp++;
					edge[nee][1]=npp-1;
					pp=npp-1;
				}
				point_l[pp]++;
				nee++;
		}

		if (q2=0) 
		{
				long pp=-1;
				double ml=point_z[edge[i][1]];
				edge[nee][0]=edge[i][1];
				for (long k=0;k<npp-1;k++)
				{
					edge[nee][1]=k;
					if ((point_z[k]<point_z[edge[i][1]]) && (angle(nee)>35) && (point_l[k]<4)) 
					{
						if (leng(k,edge[i][1]) < ml)
						{
							ml=leng(k,edge[i][1]);
							pp=k;
						}
					}
				}
				edge[nee][1]=pp;
				if (pp < 0) 
				{
					point_x[npp]=point_x[edge[i][1]];
					point_y[npp]=point_y[edge[i][1]];
					point_z[npp]=0;
					npp++;
					edge[nee][1]=npp-1;pp=npp-1;
				}
				nee++;point_l[pp]++;
		}
	
	
		len=leng(edge[i][0],edge[i][1]);
		ang=angle(i);
		if ((len>ang+10) && (ang<20) && (point_z[edge[i][0]]+point_z[edge[i][1]]>1)) 
		{
			long cu=(int)(len/(ang+10));
			for (long j=0;j<cu; j++)
			{
				double x,y,z;
				x=point_x[edge[i][0]]*(j+1)/(cu+1)+point_x[edge[i][1]]*(cu-j)/(cu+1);
				y=point_y[edge[i][0]]*(j+1)/(cu+1)+point_y[edge[i][1]]*(cu-j)/(cu+1);
				z=point_z[edge[i][0]]*(j+1)/(cu+1)+point_z[edge[i][1]]*(cu-j)/(cu+1);
				point_x[npp]=x;
				point_y[npp]=y;
				point_z[npp]=z;
				npp++;
				long pp=-1;
				double ml=z;
				edge[nee][0]=npp-1;
				for (long k=0;k<npp-1;k++)
				{
					edge[nee][1]=k;
					if ((point_z[k]<point_z[npp-1]) && (k!=edge[i][0]) && 
					(k!=edge[i][1]) && (angle(nee)>35) && (point_l[k]<4)) 
					{
						if (leng(k,npp-1) < ml)
						{
							ml=leng(k,npp-1);
							pp=k;
						}
					}
				}
				edge[nee][1]=pp;
				if (pp < 0) 
				{
					point_x[npp]=x;
					point_y[npp]=y;
					point_z[npp]=0;
					npp++;
					edge[nee][1]=npp-1;pp=npp-1;
				}
				point_l[pp]++;
				nee++;
			}
		}
	}

			
	for (long i=0;i<npp;i++){
		fou1<<point_x[i]<<' '<<point_y[i]<<' '<<point_z[i]<<'\n';
	}
	for (long i=0;i<nee;i++){
		fou2<<edge[i][0]+1<<' '<<edge[i][1]+1<<'\n';
	}	

    fou1.close();
    fou2.close();
    getchar();

}

