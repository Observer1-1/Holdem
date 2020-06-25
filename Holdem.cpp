#include<stdio.h>
struct poker
{
	char decors;
	char cnum; 
	int num;
 } ;
struct holdem
{
	struct poker pokers[5];
	int kind=0;
	int maxMin[5]={0};
	int max=0;			//特殊牌的大小如对子，三条； 
};
struct holdem holdem[2]; 
int kind[2]={7,7};
void looseCard(int i)
{
		if(kind[i]==1)
		holdem[i].kind=1;
}

void Pari(int i)
{
		int pariNum=0;
		for(int k=0;k<4;k++)
		{
			for(int j=k+1;j<5;j++)
			{
				if(holdem[i].maxMin[k]==holdem[i].maxMin[j])
				{
					pariNum++;
					if(holdem[i].maxMin[k]>holdem[i].max)
					{
						holdem[i].max=holdem[i].maxMin[k];
					}
				}
			}
		}
		if(pariNum==1)holdem[i].kind=2;
		if(pariNum==2)holdem[i].kind=3;
}

void three(int i)
{
		for(int j=0;j<3;j++)
		{
			if(holdem[i].maxMin[j]==holdem[i].maxMin[j+1]&&holdem[i].maxMin[j]==holdem[i].maxMin[j+2])
			{
				holdem[i].kind=4;
				holdem[i].max=holdem[i].maxMin[j];
			}
		}
}

int straight(int i)
{
	int k=0;
	for(int j=1;j<5;j++)
	{
		if(holdem[i].maxMin[0]==holdem[i].maxMin[j]+j)k++;
	}
	if(k==4)
	{
		holdem[i].kind=5;
		holdem[i].max=holdem[i].maxMin[0];
		return 1;
	}
	else return 0;
}

int suit(int i)
{
	int flag=1;
	for(int j=0;j<5;j++)
	{
		if(holdem[i].pokers[0].decors!=holdem[i].pokers[j].decors)flag=0;
	}
	if(flag=1)
	{
		holdem[i].kind=6;
		holdem[i].max=holdem[i].maxMin[0];
	}
}
void flush(int i)
{
	if(straight(i)+suit(i)==2)holdem[i].kind=7,holdem[i].max=holdem[i].maxMin[0];
}
int four(int i)
{	
	for(int j=0;j<2;j++)
	{
		int num1=0;
		for(int k=j+1;k<5;k++)
		{
			if(holdem[i].maxMin[j]==holdem[i].maxMin[k])num1++;
		}
		if(num1==3)
		{
			holdem[i].kind=3,holdem[i].max=holdem[i].maxMin[j];
			 return 0;
		}
		if(num1!=3||j==2)return 1;
	}
	
}
void function(int i)
{
	looseCard(i);
	Pari(i);
	three(i);
	straight(i);
	suit(i);
	flush(i);
 } 
void compare()
{
	if(holdem[0].kind==holdem[1].kind)
	{
		if(holdem[0].max>holdem[1].max)printf("Black wins");
		if(holdem[0].max<holdem[1].max)printf("White wins");
		if(holdem[0].max==holdem[1].max)printf("Tie");
	}
	if(holdem[0].kind>holdem[1].kind)printf("Black wins");
	if(holdem[0].kind<holdem[1].kind)printf("White wins");
}
int main()
{
	printf("花色统一用大写字母表示\n");
	printf("花色字母为：方片D\t黑桃S\t红桃H\t梅花C\n") ;
	for(int i=0;i<2;i++)
	{
		if(i==0)printf("请输入黑色手牌Black:");
		if(i==1)printf("请输入白色手牌White:");
		for(int j=0;j<5;j++)
		{
			scanf("%c%c",&holdem[i].pokers[j].cnum,&holdem[i].pokers[j].decors);
			switch( holdem[i].pokers[j].cnum)
			{
				case 2:  holdem[i].pokers[j].num=2;break;
				case 3:  holdem[i].pokers[j].num=3;break;
				case 4:  holdem[i].pokers[j].num=4;break;
				case 5:  holdem[i].pokers[j].num=5;break;
				case 6:  holdem[i].pokers[j].num=6;break;
				case 7:  holdem[i].pokers[j].num=7;break;
				case 8:  holdem[i].pokers[j].num=8;break;
				case 9:  holdem[i].pokers[j].num=9;break;
				case 10: holdem[i].pokers[j].num=10;break;
				case 'J':  holdem[i].pokers[j].num=11;break;
				case 'Q':  holdem[i].pokers[j].num=12;break;
				case 'K':  holdem[i].pokers[j].num=13;break;
			}
			holdem[i].maxMin[j]=holdem[i].pokers[j].num;
		}
		for(int j=0;j<5;j++)
		{
			for(int k=j;k<5;k++)
			{
				if(holdem[i].maxMin[j]<holdem[i].maxMin[k])
				{
					int temp=holdem[i].maxMin[j];
					holdem[i].maxMin[j]=holdem[i].maxMin[k];
					holdem[i].maxMin[k]=temp;
				}
			}
		}
		printf("\n");
	}
	for(int i=0;i<2;i++)
	{
		if(four(i))function(i);
	}
	compare();	
}
