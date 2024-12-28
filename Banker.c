#include<stdio.h>
int N;
int M;
int Available[10];
int TempAvailable[10];
int Max[10][10];
int Alloc[10][10];
int Need[10][10];
int Safeseq[10];

void AcceptInput()
{
	int i;
	int j;
	printf("\nEnter the number of process");
	scanf("%d",&N);
	printf("\nEnter the number of resources type");
	scanf("%d",&M);
	printf("\n Enter Avaliable");
	for(i=0;i<M;i++)
	{
		printf("Enter the number of instance for resource type %c:",65+i);
		scanf("%d",&Available[i]);
		TempAvailable[i]=Available[i];
	}
	printf("\n Enter a max :\n");
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			printf("\nEnter max for process p%d,Res[%c]",i,65+j);
			scanf("\n%d",&Max[i][j]);
		}
	}
	
	printf("\n Enter a Allocaction :\n");
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			printf("\nEnter max for process p%d,Res[%c]",i,65+j);
			scanf("\n%d",&Alloc[i][j]);
		}
	}
	for(i=0;i<N;i++)
	{
		Safeseq[i]=-1;
	}
}

void DisplayMatix(int a[10][10],int N,int M)
{
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			printf("%5d",a[i][j]);
		}
		printf("\n");
	}
}

void CalNeed()
{
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			Need[i][j]=Max[i][j]-Alloc[i][j];
		}
	}
}

int IsFeasible(int pno)
{
	int i;
	for(i=0;i<M;i++)
	{
		if(Need[pno][i] > Available[i])
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

void Banker()
{
	int k=0;
	int i,j;
	int flags[5]={0,0,0,0,0};
	int finish=0;
	while(finish!=1)
	{
		for(i=0;i<N;i++)
		{
			if(IsFeasible(i) && flags[i]!=1)
			{
				for(j=0;j<M;j++)
				{
					Available[j]=Available[j]-Need[i][j];
				}
				for(j=0;j<M;j++)
				{
					Alloc[i][j]=Alloc[i][j]+Need[i][j];
				}
				for(j=0;j<M;j++)
				{
					Available[j]=Available[j]+Alloc[i][j];
				}
				Safeseq[k++]=i;
				flags[i]=1;
			}
		}
		for(i=0;i<N;i++)
		{
			if(flags[i]==1)
			{
				continue;
			}
			else
			{
				break;
			}
		}
		if(i==N)
		{
			finish=1;
		}
	}
}

void PrintSafeseq()
{
	int i;
	printf("\n Safe Seq");
	printf("\n<");
	for(i=0;i<N;i++)
	{
		printf("p%d,",Safeseq[i]);
	}
	printf("\b>\n");
}

void NewRequest()
{
	int i;
	int NewReq[10];
	for(i=0;i<M;i++)
	{
		printf("\n Enter %c:",65+i);
		scanf("%d",&NewReq[i]);
	}
	for(i=0;i<M;i++)
	{
		if(NewReq[i]>TempAvailable[i])
		{
			break;
		}
		else
		{
			continue;
		}
	}
	if(i!=M)
	{
		printf("\n not feasible and request are not granted");
	}
	else
	{
		printf("\n feasible and request are granted");
	}
}

int main()
{
	AcceptInput();
	CalNeed();
	printf("\nMax:\n");
	DisplayMatix(Max,N,M);
	printf("\n Allocaction\n");
	DisplayMatix(Alloc,N,M);
	printf("\n Need\n");
	DisplayMatix(Need,N,M);
	Banker();
	PrintSafeseq();
	NewRequest();
	
	return 0;
}
