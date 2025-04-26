#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

// Game constants
const int MaxHealth=5;
const int MaxBullets=4;
const int Items = 4;
const int NextBulletItem=1, DoubleDamItem=2, ChainItem=3, HealItem=4;
int MaxChamber=6;
int* Gun = NULL; // Changed to pointer for dynamic allocation
int Bullets=2;
int nowBullet;
int nowSpot;
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
        cout << Players[Code].items[j] << " "; //Output all the items of Players[Code]
    }
    cout << endl << Players[0].hp << " " << Players[1].hp << " " << nowSpot << " " << nowBullet << endl;
}  //Output current status including health and gun progress

void PrintGun(){ //Output Gun Configuration
    for(int i=0;i<MaxChamber;i++){
            cout << Gun[i] <<" ";
        }
        cout << endl;
}

void Damage(int Code, int Num){ //Account for the damage done
    Players[Code].hp-=Num; // Num Damage done to Players[Code] 
    nowSpot+=1; //Move to next bullet
    nowBullet-=1; //Remaining Bullet -1
    PlayerDamage=1; //Reset damage incase DoubleDamItem was used
}

bool GameOver(){ //bool to check whether to end game
    if (Players[0].hp==0 || Players[1].hp==0) //If any player has zero health then game over
        return 0;//return false and stop the game
    return 1; //true then continue
}

double Probability(){ //Probability for our AI to judge its next move
    double probability=nowBullet/(double)(MaxChamber-nowSpot);
    return probability;
}

bool useHealItem(int Code){ //Checks whether Players[Code] has HealItems and use one is available
    if(Players[Code].items[HealItem]!=0 && Players[Code].hp<5){ //Cannot have health over 5
        Players[Code].items[HealItem]-=1;
        Players[Code].hp+=1;
        return true;
    }
    return false;
}

bool useDoubleDamItem(int Code){ //Checks whether Players[Code] has DoubleDamItem
    if(Players[Code].items[DoubleDamItem]!=0){
        Players[Code].items[DoubleDamItem]-=1;
        return true;
    }
    return false;
}

bool useChainItem(int Code){ //Checks whether Players[Code] has ChainItem
    if(Players[Code].items[ChainItem]!=0){
        Players[Code].items[ChainItem]-=1;
        return true;
    }
    return false;
}

bool useNextBulletItem(int Code){ //Checks whether Players[Code] has NextBulletItem
    if(Players[Code].items[NextBulletItem]!=0){
        Players[Code].items[NextBulletItem]-=1;
        return true;
    }
    return false;
}

bool isNextBullet(){ //Check if the next bullet is real
    if(Gun[nowSpot]==1) //Next is real
        return true;
    else
        return false;
}

void RandomItem(){ //For random generated items for Players
    int r1=rand()%4;
    Players[0].items[r1+1]+=1;
    int r2=rand()%4;
    Players[1].items[r2+1]+=1;
}

void InitializeItems(){ //To Initialize the array with 0s
    for(int j=1;j<=4;j++){
        Players[0].items[j]=0;
        Players[1].items[j]=0;
    }
    RandomItem(); //Each player starts with one item
}

void InitializeGun(int Num){ //Dynamic Array Allocation for Gun Configuration because Player can choose the chamber and bullet number
    if (Gun == NULL) { // Allocate gun chamber if not already allocated
        Gun = new int[MaxChamber];
    }
    for(int i=0;i<MaxChamber;i++){ // Initialize all chambers to 0s
        Gun[i]=0;
    }
    while(Num>0){ // Load bullets randomly
        int r=rand()%MaxChamber; 
        if(Gun[r]==0){
            Gun[r]=1;
            Num-=1;
        }
    }
}

void CleanupGun() { //Free the Dynamic Array Momeries
    if (Gun != NULL) {
        delete[] Gun;
        Gun = NULL;
    }
}

int MediumAI(){ //Game's Medium AI
    //Printtest(0);
    useHealItem(0); //Use HealItem whenever possible
    if (useNextBulletItem(0)){ //Use NextBulletItem whenever possible
        if (isNextBullet()){ //Check next Bullet, If Real
            if (useDoubleDamItem(0)){ //If DoubleDamItem is present
                Damage(1,2); //Shoot Players[1] (Human) with two damage
            }
            else
                Damage(1,1); //Shoot Player[1] with one damage if no DoubleDamItem
            return 1; //AI keeps shooting until return 0
        }
        else{ //Next bullet is fake
            nowSpot+=1; //AI shoot itself and move on to next bullet
            return 1;
        }
    }
    else if (useChainItem(0) && Probability()>=0.5){ //Use ChainItem when probability of the next bullet being real is greater or equal 50%
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
        if (Probability()==1){ //All remaining bullets are real (Shoot Human)
            if (useDoubleDamItem(0)){
                Damage(1,2);
            }
            else
                Damage(1,1);
            return 1;
        }
        if (Probability()>=0.5){ //Probability Greater or Equal to 50% (Shoot Human)
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
            if (isNextBullet()){ //Probability lower than 50% (AI Shoot Itself)
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
    if(userInput=='j'){ //ShootAI
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
    else if(userInput=='k'){ //ShootYourself
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
    else if(userInput=='1'){ //Use Item[1] NextBulletItem
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
    else if(userInput=='2'){ //Use Item[2] DoubleDamItem
        if(!useDoubleDamItem(1)){
            cout << "No Double Damage Item" << endl;
        }
        else{
            PlayerDamage=2;
        }
        return 1;
    }
    else if(userInput=='3'){ //Use Item[3] ChainItem
        if(!useChainItem(1)){
            cout << "No Chain Item" << endl;
        }
        AIChained=true;
        return 1;
    }
    else if(userInput=='4'){ //Use Item[4] HealItem
        if(!useHealItem(1)){
            cout << "No Health Item" << endl;
        }
        return 1;
    }
    else
        return 2;
}

void ChangeChamber(){ //Player choose their own Chamber Size and Bullet Number
	cout << "Choose Chamber Size: ";
	int temp = _getch()-'0';
	if (temp>5 && temp<10){ //Min 6 and Max 9
		MaxChamber = temp;
		cout << MaxChamber << endl;
	}
	else{
		cout << "Invalid" <<endl;
	}
	cout << "Choose Bullets Number: ";
	temp = _getch()-'0';
	if (temp>1 && temp<6){ //Min 2 and Max 5
		Bullets = temp;
		cout << Bullets << endl;
	}
	else{
		cout << "Invalid" <<endl;
	}
	
}

int main(){
    srand(time(NULL)); //Random Time Seed
    InitializeItems();
    while(GameOver()){
        RandomItem();
        ChangeChamber();
        Reload=Bullets;
        nowBullet=Bullets;
        nowSpot=0;
        InitializeGun(Reload);
        PrintGun();
        //game logic
        while(nowBullet>0 && nowSpot<MaxChamber){
            int Move=1;
            while(Move!=0 && nowSpot<MaxChamber && nowBullet>0 && GameOver()){
                if(Move==1)
                    cout << "HUMAN:";
                    Printtest(1);
                Move=Human();
            }
            Move=1;
            while(Move!=0 && nowSpot<MaxChamber && nowBullet>0 && GameOver()){
                cout << "AI:";
                Printtest(0);
                Move=MediumAI();
            }
            if(Players[0].hp<=0){
                cout << "You win!";
                return 1;
            }
            if(Players[1].hp<=0){
                cout  << "You lose!";
                return 0;
            }
        }
        cout << "Bullets Finished, Reload The Next Gun" << endl;
        CleanupGun();
    }
    return 0;
}
