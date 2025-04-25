#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

// Game constants
const int MaxHealth=5;
const int MaxChamber=6;
const int MaxBullets=4;
const int Items = 4;
const int NextBulletItem=1, DoubleDamItem=2, ChainItem=3, HealItem=4;
int Gun[7];
int Bullets=2;
int nowBullet=2;
int nowSpot=0;
int Reload=Bullets;
int PlayerDamage=1;
bool AIChained=false;
// Game structures
struct Player {
    int items[Items + 1]; //item counts 1:next bullet  2:double damage  3:chained  4:++hp
    int hp = MaxHealth;
} Players[3]; //Players[0] is AI and Players[1] is the person playing
// These two function are for testing
void Printtest(int Code){
	for(int j=1;j<=4;j++){
		cout << Players[Code].items[j] << " ";
	}
	cout << endl << Players[0].hp << " " << Players[1].hp << " " << nowSpot << endl;
}
void PrintGun(){
	for(int i=0;i<=5;i++){
			cout << Gun[i] <<" ";
		}
		cout << endl;
}

void Damage(int Code, int Num){
	Players[Code].hp-=Num; // Num Damage done to Players[Code] 
	nowSpot+=1;
	nowBullet-=1;
	PlayerDamage=1;
}

bool GameOver(){
	if (Players[0].hp==0 || Players[1].hp==0)
		return 0;
	return 1;
}

double Probability(){
	double probability=nowBullet/(6.0-nowSpot);
	return probability;
}

bool useHealItem(int Code){ //HealItem
	if(Players[Code].items[HealItem]!=0 && Players[Code].hp<5){
		Players[Code].items[HealItem]-=1;
		Players[Code].hp+=1;
		return true;
	}
	return false;
}

bool useDoubleDamItem(int Code){
	if(Players[Code].items[DoubleDamItem]!=0){
		Players[Code].items[DoubleDamItem]-=1;
		return true;
	}
	return false;
}

bool useChainItem(int Code){
	if(Players[Code].items[ChainItem]!=0){
		Players[Code].items[ChainItem]-=1;
		return true;
	}
	return false;
}

bool useNextBulletItem(int Code){
	if(Players[Code].items[NextBulletItem]!=0){
		Players[Code].items[NextBulletItem]-=1;
		return true;
	}
	return false;
}

bool isNextBullet(){
	if(Gun[nowSpot]==1) //Next is real bullet
		return true;
	else
		return false;
}


void RandomItem(){
	int r1=rand()%4;
	Players[0].items[r1+1]+=1;
	int r2=rand()%4;
	Players[1].items[r2+1]+=1;
}

void InitializeItems(){
	for(int j=1;j<=4;j++){
		Players[0].items[j]=0;
		Players[1].items[j]=0;
	}
	RandomItem();
}

void InitializeGun(int Num){
	for(int i=0;i<=5;i++){
		Gun[i]=0;
	}
	while(Num>0){
		int r=rand()%6; 
		if(Gun[r]==0){
			Gun[r]=1;
			Num-=1;
		}
	}
}

int MediumAI(){
	//Printtest(0);
	useHealItem(0);
	if (useNextBulletItem(0)){
		if (isNextBullet()){
			if (useDoubleDamItem(0)){
				Damage(1,2);
			}
			else
				Damage(1,1);
			return 1;
		}
		else{
			nowSpot+=1; 
			return 1;
		}
	}
	else if (useChainItem(0) && Probability()>=0.5){
		if (isNextBullet()){
			Damage(1,1);
			return 1;
		}
		else{
			nowSpot+=1;
			return 1;
		}
	}
	else{
		if (Probability()==1){
			if (useDoubleDamItem(0)){
				Damage(1,2);
			}
			else
				Damage(1,1);
			return 1;
		}
		if (Probability()>=0.5){
			if (isNextBullet()){
				Damage(1,1);
				return 1;
			}
			else{
				nowSpot+=1;
				return 0;
			}
		}
		else{
			if (isNextBullet()){
				Damage(0,1);
				return 0;
			}
			else{
				nowSpot+=1;
				return 1;
			}
		}
	}
	
}

int Human(){
	char userInput = _getch();
	if(userInput=='j'){//ShootAI
		if(isNextBullet()){
			Damage(0,PlayerDamage);
			AIChained=false;
			return 1;
		}
		else{
			nowSpot+=1;
			PlayerDamage=1;
			if (AIChained){
				AIChained=false;
				return 1;
			}
			return 0;
		}
	}
	else if(userInput=='k'){//ShootYourself
		if(isNextBullet()){
			Damage(1,PlayerDamage);
			if (AIChained){
				AIChained=false;
				return 1;
			}
			return 0;
		}
		else{
			nowSpot+=1;
			PlayerDamage=1;
			AIChained=false;
			return 1;
		}
	}
	else if(userInput=='1'){
		if(!useNextBulletItem(1)){
			cout << "NoNextBulletItem" << endl;
		}
		else{
			if(isNextBullet()){
				cout << "Real!" << endl;
			}
			else{
				cout << "Fake!" <<endl;
			}
		}
		return 1;
	}
	else if(userInput=='2'){
		if(!useDoubleDamItem(1)){
			cout << "No Double Damage Item" << endl;
		}
		else{
			PlayerDamage=2;
		}
		return 1;
	}
	else if(userInput=='3'){
		if(!useChainItem(1)){
			cout << "No Chain Item" << endl;
		}
		AIChained=true;
		return 1;
	}
	else if(userInput=='4'){
		if(!useHealItem(1)){
			cout << "No Health Item" << endl;
		}
		return 1;
	}
	else
		return 2;
}

int main(){
	srand(time(NULL));
	InitializeItems();
	while(GameOver()){
		RandomItem();
		InitializeGun(Reload);
		PrintGun();
		//game logic
		while(nowBullet>0 && nowSpot<6){
			int Move=1;
			while(Move!=0 && nowSpot<6 && nowBullet>0 && GameOver()){
				if(Move==1)
					cout << "HUMAN:";
					Printtest(1);
				Move=Human();
			}
			Move=1;
			while(Move!=0 && nowSpot<6 && nowBullet>0 && GameOver()){
				cout << "AI:";
				Printtest(0);
				Move=MediumAI();
			}
			if(Players[0].hp<=0){
				cout << "You win!";
				break;
			}
			if(Players[1].hp<=0){
				cout  << "You lose!";
				break;
			}
		}
		if(Bullets<MaxBullets){
			Bullets+=1;
		}
		Reload=Bullets;
		nowBullet=Bullets;
		nowSpot=0;
	}
	return 0;
}
