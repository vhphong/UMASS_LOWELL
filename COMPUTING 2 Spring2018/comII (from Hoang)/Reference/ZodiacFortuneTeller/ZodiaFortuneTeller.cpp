#include <iostream>
#include <cctype>
#include <cstdlib>
#include <time.h>
using namespace std;
void showZodiacMenu ();  
int getZodiacIndexByYear (int year);
int getZodiacIndexByWord (string animals[], char word[]);
void UppercaseZodiac (char z[]);
void PrintZodiacByElement (string animals[], string elements[]);
void PrintElementByZodiac (string animal,string elements[]);
void PrintZodiacCompatibility ();
//void UppercaseElement (string element);
//TBD:enter element to determine affinity
//TBD:enter birth year to determine affinity not based on random
const int NUMSIGNS = 12;	// the number of Zodiac signs (use with Animals and Elements arrays)
const int WORDLEN = 80;	// the maximum length of a Zodiac animal word to be entered by the user
const int NUMELEMENTS = 5; 	// the number of different Zodiac elements, i.e. wood, metal, etc.

int main()
{
	
	string zodiac[]={"RAT","OX","TIGER","RABBIT","DRAGON","SNAKE","HORSE","GOAT","MONKEY","ROOSTER","DOG","PIG"};
	string zodiacElem[]={"WATER","WOOD","METAL","FIRE","EARTH"};
	int userChoice,birthYear,birthYear1;
	char zodiacUser[WORDLEN];
	string elementUser[WORDLEN];
	srand(time(NULL));

	do{
	showZodiacMenu();	
	cin>>userChoice;	
	switch(userChoice){
		case 1:
			cout<<"Please enter your birth year: ";
			cin>>birthYear;
			if(getZodiacIndexByYear(birthYear)==-1)
			cout<<"Invalid year"<<endl;
			else{
			
			cout<<endl<<"Your zodiac is "+zodiac[getZodiacIndexByYear(birthYear)]+"."<<endl;
			cout<<"This is your element: "<<endl;
			PrintElementByZodiac(zodiac[getZodiacIndexByYear(birthYear)],zodiacElem);	
			
			}
			break;	
		case 2:
			cout<<"Please enter your birth year: ";
			cin>>birthYear;
			cout<<"Please enter the second person's birth year: ";
			cin>>birthYear1;
			cout<<endl<<"Your zodiac animal is "+zodiac[getZodiacIndexByYear(birthYear)]+"."<<endl;
			cout<<"This is your element: "<<endl;
			PrintElementByZodiac(zodiac[getZodiacIndexByYear(birthYear)],zodiacElem);	
			cout<<"The second person's zodiac animal is "+zodiac[getZodiacIndexByYear(birthYear1)]+"."<<endl;
			cout<<"This is the second person element: "<<endl;
			PrintElementByZodiac(zodiac[getZodiacIndexByYear(birthYear1)],zodiacElem);	
			PrintZodiacCompatibility();
			break;
		case 3:
			cout<<"Please enter your zodiac: ";
			cin>>zodiacUser;
			UppercaseZodiac(zodiacUser);
			if(getZodiacIndexByWord(zodiac,zodiacUser)==-1)
				cout<<"Invalid input"<<endl;
			else
			{
			cout<<endl<<"Your zodiac is "+zodiac[getZodiacIndexByWord(zodiac,zodiacUser)]+"."<<endl;
			PrintElementByZodiac(zodiac[getZodiacIndexByYear(birthYear)],zodiacElem);
			}
			break;
		case 4:
			PrintZodiacByElement(zodiac,zodiacElem);
			break;
		case 5:
			cout<<"Program terminating"<<endl;
			break;
		default:
			cout<<"Invalid choice"<<endl;
	}
	}while(userChoice!=5);
	
	return 0;
} 
void showZodiacMenu (){
	cout<<endl;
	cout<<"Welcome to the Chinese Zodiac Program."<<endl;
	cout<<"What would you like to do?"<<endl;
	cout<<"\t1. Find out your Zodiac Animal and Element from your birth year."<<endl;
	cout<<"\t2. Find out the Zodiac Animals, Elements, and Compatibility of \n\ttwo people from their birth years."<<endl;
	cout<<"\t3. Find out the Zodiac element of an Animal." <<endl;
	cout<<"\t4. Print out the Zodiac Animals by Element." <<endl;
	cout<<"\t5. Quit" <<endl;
	
}

int getZodiacIndexByYear (int year){
	
	int rem,index;
	rem=year%NUMSIGNS;
	switch(rem){
		case 0:index =8;break;//monkey
		case 1:index =9;break;//rooster
		case 2:index =10;break;//dog
		case 3:index =11;break;//pig
		case 4:index =0;break;//rat
		case 5:index =1;break;//ox
		case 6:index =2;break;//tiger
		case 7:index =3;break;//rabbit
		case 8:index =4;break;//dragon
		case 9:index =5;break;//snake
		case 10:index =6;break;//horse
		case 11:index =7;break;//goat
		default:index =-1;
	}
	return index;
}

void UppercaseZodiac (char z[]){
	char c;
	int i;
	while (i<WORDLEN){
		c = z[i];
		z[i]=toupper(c);
		i++;
	}

}


int getZodiacIndexByWord (string animals[], char word[]){
	int index=0;

	while(index<NUMSIGNS){
		if(animals[index]==word)
		return index;
		index++;	
	}
	return -1;
}
void PrintZodiacByElement (string animals[], string elements[]){
	
		5elements[]={"WATER","WOOD","METAL","FIRE","EARTH"};
		for(int i =0; i<NUMELEMENTS;i++){
			if(elements=5elements[i])
				{
					switch(i)
					{
						case 0:
							cout<<"The "+elements+" animal signs:"<<endl;
							cout<<"\t"<<animals[0]<<endl<<"\t"<<animals[11]<<endl;	
						break;
						
						case 1:
							cout<<"The "+elements+" animal signs:"<<endl;
							cout<<"\t"<<animals[2]<<endl<<"\t"<<animals[3]<<endl;
						break;
							
						case 2:
							cout<<"The "+elements+" animal signs:"<<endl;
							cout<<"\t"<<animals[8]<<endl<<"\t"<<animals[9]<<endl;	
						break;
						
						case 3:
							cout<<"The "+elements+" animal signs:"<<endl;
							cout<<"\t"<<animals[5]<<endl<<"\t"<<animals[6]<<endl;
						break;
						
						case 4:
							cout<<"The "+elements+" animal signs:"<<endl;
							cout<<"\t"<<animals[1]<<endl<<"\t"<<animals[4]<<endl<<"\t"<<animals[7]<<endl<<"\t"<<animals[10]<<endl;
						break;
						
						default:
							cout<<"The "+5elements[0]+" animal signs:"<<endl;
							cout<<"\t"<<animals[0]<<endl<<"\t"<<animals[11]<<endl;	
	
							cout<<"The "+5elements[1]+" animal signs:"<<endl;
							cout<<"\t"<<animals[2]<<endl<<"\t"<<animals[3]<<endl;
					
							cout<<"The "+5elements[2]+" animal signs:"<<endl;
							cout<<"\t"<<animals[8]<<endl<<"\t"<<animals[9]<<endl;
					
							cout<<"The "+5elements[3]+" animal signs:"<<endl;
							cout<<"\t"<<animals[5]<<endl<<"\t"<<animals[6]<<endl;
						
					
							cout<<"The "+5elements[4]+" animal signs:"<<endl;
							cout<<"\t"<<animals[1]<<endl<<"\t"<<animals[4]<<endl<<"\t"<<animals[7]<<endl<<"\t"<<animals[10]<<endl;
					}
				}
			
		}
	
}
void PrintZodiacCompatibility (){
	string message[]={"You two are a Perfect Match!","You two are Pretty Good.","You two are Complementary.","You two are Average.","You Could Go Either Way.","You two are Not So Good."};
	cout<<message[rand()%6]<<endl;
}

void PrintElementByZodiac(string animal,string elements[]){
		string zodiac[]={"RAT","OX","TIGER","RABBIT","DRAGON","SNAKE","HORSE","GOAT","MONKEY","ROOSTER","DOG","PIG"};
		if(animal ==zodiac[0]||animal ==zodiac[11]){
			cout<<"The "+elements[0]+" animal signs:"<<endl;
			cout<<"\t"<<zodiac[0]<<endl<<"\t"<<zodiac[11]<<endl;		
		}
		else if(animal ==zodiac[2]||animal ==zodiac[3]){
			cout<<"The "+elements[1]+" animal signs:"<<endl;
			cout<<"\t"<<zodiac[2]<<endl<<"\t"<<zodiac[3]<<endl;	
		}
		else if(animal ==zodiac[8]||animal ==zodiac[9]){
			cout<<"The "+elements[2]+" animal signs:"<<endl;
			cout<<"\t"<<zodiac[8]<<endl<<"\t"<<zodiac[9]<<endl;
		}
		else if(animal ==zodiac[5]||animal ==zodiac[6]){
			cout<<"The "+elements[3]+" animal signs:"<<endl;
			cout<<"\t"<<zodiac[5]<<endl<<"\t"<<zodiac[6]<<endl;
		}
		else if(animal ==zodiac[1]||animal ==zodiac[4]||animal ==zodiac[7]||animal ==zodiac[10]){
			cout<<"The "+elements[4]+" animal signs:"<<endl;
			cout<<"\t"<<zodiac[1]<<endl<<"\t"<<zodiac[4]<<endl<<"\t"<<zodiac[7]<<endl<<"\t"<<zodiac[10]<<endl;
		}
		else
		cout<<"Invalid input"<<endl;
}
