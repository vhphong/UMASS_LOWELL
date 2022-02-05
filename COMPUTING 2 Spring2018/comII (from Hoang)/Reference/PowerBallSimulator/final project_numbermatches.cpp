// File Name:finalproject_numbermatches
// Written by: Viet Tran Quoc Hoang
// Description:Simulator of the Powerball Lottery game.
// Challenges:Figuring out numbermatches as well as the 9 different scenarios where player can win
// Time Spent:2 weeks
// Given Input: (3 sets)         Expected Output: (3 corresponding sets)
// --------------------          -------------------------
// 1)15 12 19 65 24 25 16		Invalid input, please enter values smaller between 1 and 59
// 2)15 15 1 19 25 12 28		Invalid input, no duplicates allowed for the first number	
// 3)26 4 54 26 29 1 17			Sorry, you did not win anything. Do you want to try again?
// Revision History
// Date:        Revised By:     Action:
// ------------------------------------------------------------------
// 4/19/2015	Viet Tran		Started working on the project
// 4/25/2015	Viet Tran 		Managed to find duplicates without numbermatches. Started on the logics of numbermatches
// 5/1/2015		Viet Tran		Finished the rest of the program
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
void DisplayRules();
void GetPlayerNumbers(int*);
void GetWinningNumbers(int*);
int FindWinningCombo(int*,int*);
bool NumberMatches(int, int*);
bool NumberMatches2(int, int*);
int DisplayPrize(int);
int main()
{char userinput1;
int total=0,prize=0;
const int COLNUM=6;
const int cost=2;
cout<<"Welcome to the Powerball Lottery Simulator!\nPress t for the tutorials or s to start the program"<<endl;
cin>>userinput1;
while (userinput1 == 't'||userinput1 =='T')
	{DisplayRules();
	cout<<"Do you want to start playing?If so , please enter s"<<endl;
	cin>>userinput1;
	}
while (userinput1=='s'||userinput1=='S')
	{int playerNumber[COLNUM]={0,0,0,0,0,0};
	int *playerNumberPointer;
	playerNumberPointer= &playerNumber[0];
	int winningNumber[COLNUM]={0,0,0,0,0,0};
	int *winningNumberPointer;
	winningNumberPointer=&winningNumber[0];
	GetPlayerNumbers(playerNumberPointer);
	srand(time(NULL));
	GetWinningNumbers(winningNumberPointer);
	prize=DisplayPrize(FindWinningCombo(playerNumberPointer,winningNumberPointer));
	total= total+prize-cost;
	cout<<"This is your current winning: $"<<total<<endl;
	cout<<"Do you want to play again?Press S to keep playing or Q to quit the program!"<<endl;
	cin>>userinput1;
	}
return 0;
}
void DisplayRules() 
	{cout<<"Powerball is a combined large jackpot game and a cash game. Every Wednesday and Saturday night at 10:59 p.m. Eastern Time, we draw five white balls out of a    drum with 59 balls and one red ball out of a drum with 35 red balls. Draw sales cut off at least 59 minutes before the draw. Check for local cut-off time.\n" <<endl;
	cout<<"Players win by matching one of the 9 Ways to Win. The jackpot (won by matching  all five white balls in any order and the red Powerball) is either an annuitized prize paid out over 29 years (30 payments) or a lump sum payment. Each ticket  costs $2. If the winner chooses the annuity, the annual payment will be         increased each year by the percentage set out in the Powerball game rules.\n"<<endl;
	cout<<"The second prize (won by matching five white balls in any order) is $1,000,000  paid in cash and any time you match the red Powerball, you win. The overall odds of winning a prize in the game are approximately 1 in 32.\n"<<endl;
	return;
	}
void GetPlayerNumbers(int *playerNumberPointer)
	{for (int i=0;i<=4;i++)
		{cout<<"Please enter your ticket number "<<i+1<<" : ";
		cin>> *(playerNumberPointer + i);	
		if(*(playerNumberPointer + i)>59||*(playerNumberPointer + i)<1)
			{cout<<"Please enter only numbers in the range of 1 to 59"<<endl;
			i--;
			continue;
			}
		if (NumberMatches(*(playerNumberPointer+0),playerNumberPointer))
			{cout<<"This is a dupplicate of your first number."<<endl;
			 cout<<"Please enter another number for ticket number "<<i+1<<endl;
			i--;
			continue;
			}
		if (NumberMatches(*(playerNumberPointer+1),playerNumberPointer))
			{cout<<"This is a dupplicate of your second number."<<endl;
			cout<<"Please enter another number for ticket number "<<i+1<<endl;
			i--;
			continue;
			}
		 if (NumberMatches(*(playerNumberPointer+2),playerNumberPointer))
			{cout<<"This is a dupplicate of your third number."<<endl;
			cout<<"Please enter another number for ticket number "<<i+1<<endl;
			i--;
			continue;
			}
		 if (NumberMatches(*(playerNumberPointer+3),playerNumberPointer))
			{cout<<"This is a dupplicate of your fourth number."<<endl;
			cout<<"Please enter another number for ticket number "<<i+1<<endl;
			i--;
			continue;
			}
		}
	for (int i=5;i<6;i++)
		{cout<<"Please enter your ticket number "<<i+1<<" : ";
		cin>> *(playerNumberPointer + i);
		if (*(playerNumberPointer + i)>35||*(playerNumberPointer + i)<1)
			{cout<<"Please enter only numbers in the range from 1 to 35"<<endl;
			i--;
			continue;
			}
		}
	for (int i=0;i<6;i++) 		
		{cout<<"Your ticket number "<<i+1<<" is "<<*(playerNumberPointer + i)<<endl;
		}
	}
void GetWinningNumbers(int *winningNumberPointer)
	{for (int i=0;i<=4;i++)
		{*(winningNumberPointer + i)=((rand()%59)+1);
	
		if (NumberMatches(*(winningNumberPointer+0),winningNumberPointer))
			{i--;
			continue;
			}
		if (NumberMatches(*(winningNumberPointer+1),winningNumberPointer))
			{i--;
			continue;
			}
		if (NumberMatches(*(winningNumberPointer+2),winningNumberPointer))
			{i--;
			continue;
			}
		if (NumberMatches(*(winningNumberPointer+3),winningNumberPointer))
			{i--;
			continue;
			}
		if (NumberMatches(*(winningNumberPointer+4),winningNumberPointer))
			{i--;
			continue;
			}
		}		
	if (*(winningNumberPointer+4)>0)
		{cout<<"First winning number is "<<*(winningNumberPointer)<<endl;
		cout<<"Second winning number is "<<*(winningNumberPointer+1)<<endl;
		cout<<"Third winning number is "<<*(winningNumberPointer+2)<<endl;
		cout<<"Fourth winning number is "<<*(winningNumberPointer+3)<<endl;
		cout<<"Fifth winning number is "<<*(winningNumberPointer+4)<<endl;}
	for ( int i=5; i<6;i++)
		{*(winningNumberPointer + i)=((rand()%35)+1);
		cout<<"Sixth winning number is "<<*(winningNumberPointer + i)<<endl;
		}
	}
int FindWinningCombo(int *playerNumberPointer,int *winningNumberPointer)
{int prizeNumber;
int counter1=0;	
		if (NumberMatches2(*(playerNumberPointer+0),winningNumberPointer))
		{counter1++;
		}
		if (NumberMatches2(*(playerNumberPointer+1),winningNumberPointer))
		{counter1++;
		}
		if (NumberMatches2(*(playerNumberPointer+2),winningNumberPointer))
		{counter1++;
		}
		if (NumberMatches2(*(playerNumberPointer+3),winningNumberPointer))
		{counter1++;
		}
		if (NumberMatches2(*(playerNumberPointer+4),winningNumberPointer))
		{counter1++;
		}
		if (*(playerNumberPointer+5)==*(winningNumberPointer+5)&&counter1==5)
		{prizeNumber=9;
		return prizeNumber;
		}
		if (counter1==5)
		{prizeNumber=8;
		return prizeNumber;
		}
		if (*(playerNumberPointer+5)==*(winningNumberPointer+5)&&counter1==4)
		{prizeNumber=7;
		return prizeNumber;
		}
		if (counter1==4)
		{prizeNumber=6;
		return prizeNumber;
		}
		if (*(playerNumberPointer+5)==*(winningNumberPointer+5)&&counter1==3)
		{prizeNumber=5;
		return prizeNumber;
		}
		if (counter1==3)
		{prizeNumber=4;
		return prizeNumber;
		}
		if (*(playerNumberPointer+5)==*(winningNumberPointer+5)&&counter1==2)
		{prizeNumber=3;
		return prizeNumber;
		}
		if (*(playerNumberPointer+5)==*(winningNumberPointer+5)&&counter1==1)
		{prizeNumber=2;
		return prizeNumber;
		}
		if (*(playerNumberPointer+5)==*(winningNumberPointer+5))
		{prizeNumber=1;
		return prizeNumber;
		}
		else 
		prizeNumber=0;
		return prizeNumber;		
}	
bool NumberMatches(int playerNumber, int *playerNumberPointer)
{int counter=0;
	if (*(playerNumberPointer)==playerNumber&& playerNumber!=0)
		{counter++;	
			if (counter ==2)
				{return true;
				}
		}	
	if (*(playerNumberPointer+1)==playerNumber&& playerNumber!=0)
		{counter++;
			if (counter ==2)
				{return true;
				}
			}
	if (*(playerNumberPointer+2)==playerNumber&& playerNumber!=0)
		{counter++;
			if (counter ==2)
				{return true;
				}
		}
	if (*(playerNumberPointer+3)==playerNumber&& playerNumber!=0)
		{counter++;
			if (counter ==2)
				{return true;
				}
		}
	if (*(playerNumberPointer+4)==playerNumber&& playerNumber!=0)
		{counter++;
			if (counter ==2)
				{return true;
				}
		}
	if (*(playerNumberPointer+5)==playerNumber&& playerNumber!=0)
		{counter++;
			if (counter ==2)
				{return true;
				}
		}
	else
		return false;	
}
bool NumberMatches2(int playerNumber, int *playerNumberPointer)
{	if (*(playerNumberPointer)==playerNumber)
		{return true;		
		}	
	if (*(playerNumberPointer+1)==playerNumber)
		{return true;		
		}
	if (*(playerNumberPointer+2)==playerNumber)
		{return true;		
		}
	if (*(playerNumberPointer+3)==playerNumber)
		{return true;		
		}
	if (*(playerNumberPointer+4)==playerNumber)
		{return true;		
		}	
	else
		return false;
}
int DisplayPrize(int x)
{int prize;
switch (x)
	{case 9:
		prize= 80000000;
		cout<<"Congratulations!You won the jackpot!"<<endl;
		cout<<"The odd of winning this prize is 1 in 175,223,510.00"<<endl;
		return prize;
	break;
 	case 8:
 		prize=1000000;
		cout<<"Congratulations!You won $1,000,000!"<<endl;
		cout<<"The odd of winning this prize is 1 in 5,153,632.65"<<endl;
		return prize;	
	break;
	case 7:
		prize=10000;
		cout<<"Congratulations!You won $10,000!"<<endl;
		cout<<"The odd of winning this prize is 1 in 648,975.96"<<endl;
		return prize;	
	break;	
		case 6:
		prize=100;
		cout<<"Congratulations!You won $100!"<<endl;
		cout<<"The odd of winning this prize is 1 in 19,087.53"<<endl;
		return prize;	
	break;
	case 5:
		prize=100;
		cout<<"Congratulations!You won $100!"<<endl;
		cout<<"The odd of winning this prize is 1 in 12,087.53"<<endl;
		return prize;	
	break;
	case 4:
		prize=7;
		cout<<"Congratulations!You won $7!"<<endl;
		cout<<"The odd of winning this prize is 1 in 360.14"<<endl;
		return prize;	
	break;
	case 3:
		prize=7;
		cout<<"Congratulations!You won $7!"<<endl;
		cout<<"The odd of winning this prize is 1 in 706.43"<<endl;
		return prize;
	break;
	case 2:
		prize=4;
		cout<<"Congratulations!You won $4!"<<endl;
		cout<<"The odd of winning this prize is 1 in 110.81"<<endl;
		return prize;
		break;
	case 1:
		prize=4;
		cout<<"Congratulations!You won $4!"<<endl;
		cout<<"The odd of winning this prize is 1 in 55.41"<<endl;
		return prize;
	break;
	case 0:
		prize=0;
		cout<<"Thank you for playing! Good luck next time!"	<<endl;
		return prize;
		break;	
	}
}
