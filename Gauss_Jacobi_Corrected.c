#include<stdio.h>
#include<stdlib.h>
#define VARNUM 26
float arr[50][51],varprev[VARNUM],varcurr[VARNUM];
int varcount,iloop,jloop,kloop,lloop;
char varname[VARNUM];
float abs1(float x)
{
	if(x>0.0)
	return x;
	else
	return x*(-1);
}
void initialise()
{
	for(iloop=0;iloop<VARNUM;iloop++)
	{
		varname[iloop]=(char)(97+iloop);
		varprev[iloop]=0.0;
		varcurr[iloop]=0.0;
	}
}
void input()
{
	printf("Enter number of variables:");
	scanf("%d",&varcount);
	for(iloop=0;iloop<varcount;iloop++)
	{
		printf("\nEnter coefficients for equation %d:\n",(iloop+1));
		for(jloop=0;jloop<=varcount;jloop++)
		{
			if(jloop==varcount)
			printf("\nEnter result value for equation %d:\n",(iloop+1));
			scanf("%f",&arr[iloop][jloop]);
		}
	}
}
void preview()
{
	printf("\nHere's the equations you entered:\n");
	for(iloop=0;iloop<varcount;iloop++)
	{
		for(jloop=0;jloop<=varcount;jloop++)
		{
			if(jloop==varcount-1)
			printf("%0.2f%c=",arr[iloop][jloop],varname[jloop]);
			else if(arr[iloop][jloop]<0)
			printf("%0.2f%c",arr[iloop][jloop],varname[jloop]);
			else if(jloop==varcount)
			printf("%0.2f",arr[iloop][jloop]);
			else
			printf("%0.2f%c+",arr[iloop][jloop],varname[jloop]);
		}
		printf("\n");
	}
}
void make_diagonal_dominant(int pos)
{
	int max=pos;
	float temp,sum;
	for(kloop=pos+1;kloop<varcount;kloop++)
	{
		sum=0.0;
		for(lloop=0;lloop<varcount;lloop++)
		{
			if(kloop!=lloop)
			sum=sum+abs1(arr[kloop][lloop]);
		}
		if(sum<arr[kloop][pos])
		max=kloop;
	}
	if(max!=pos)
	{
		for(lloop=0;lloop<varcount+1;lloop++)
		{
			temp=arr[pos][lloop];
			arr[pos][lloop]=arr[max][lloop];
			arr[max][lloop]=temp;
		}
	}
	else
	{
		printf("\nThis system of equations can't be solved by Gauss Jacobi Iterative method.\n");
		exit(0);
	}
}
void check_diagonal_dominant()
{
	float sum;
	for(iloop=0;iloop<varcount;iloop++)
	{
		sum=0.0;
		for(jloop=0;jloop<varcount;jloop++)
		{
			if(iloop!=jloop)
			sum=sum+abs1(arr[iloop][jloop]);
		}
		if(sum>=arr[iloop][iloop])
		make_diagonal_dominant(iloop);
	}
}
int check()
{
	float sum=0.0;
	for(iloop=0;iloop<varcount;iloop++)
	sum=sum+abs1((varcurr[iloop]-varprev[iloop]));
	if(abs1(sum)<0.001)
	return 1;
	else
	return 0;
}
void show_solution()
{
	for(iloop=0;iloop<varcount;iloop++)
	printf("%c = %0.2f\n",varname[iloop],varcurr[iloop]);
}
float reverse(float x)
{
	return x*(-1);
}
void solve()
{
	while(1)
	{
		for(iloop=0;iloop<varcount;iloop++)
		{
			varcurr[iloop]=arr[iloop][varcount];
			for(jloop=0;jloop<varcount;jloop++)
			{
				if(iloop!=jloop)
				varcurr[iloop]=varcurr[iloop]+reverse(arr[iloop][jloop]*varprev[jloop]);
			}
			varcurr[iloop]=varcurr[iloop]/arr[iloop][iloop];
		}
		if(check()==1)
		{
			show_solution();
			exit(0);
		}
		else
		{
			for(iloop=0;iloop<varcount;iloop++)
			varprev[iloop]=varcurr[iloop];
		}
	}
}
int main()
{
	initialise();
	input();
	preview();
	check_diagonal_dominant();
	solve();
}
