#include <bits/stdc++.h>
//#include <conio.h>
#include <ncurses.h>
#include <string.h>
#include <thread>    // Include for std::this_thread::sleep_for
#include <chrono>
using namespace std;

// 0 for AI(COMPUTER), 1 dor HUMAN

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

int scrLine, scrCol; // 获取屏幕 行 列 数
int my_energy = 4, ai_energy = 4; // 初始生命值为 4
char str[1024];

// Game structures
struct Player {
    int items[Items + 1]; //item counts 1:next bullet  2:double damage  3:chained  4:++hp
    int hp = MaxHealth;
} Players[3]; //Players[0] is AI and Players[1] is the person playing

void smileface(){
    mvprintw(scrLine / 2 -3, scrCol/ 4 - 20 , "    _____    ");
    mvprintw(scrLine / 2 -2, scrCol/ 4 - 20, "  .'     '.  ");
    mvprintw(scrLine / 2 -1, scrCol/ 4 - 20, " /  o   o  \\ ");
    mvprintw(scrLine / 2 , scrCol/ 4 - 20, "|           |");
    mvprintw(scrLine / 2 +1, scrCol/ 4 - 20, "|  \\     /  |");
    mvprintw(scrLine / 2 +2, scrCol/ 4 - 20, " \\  '---'  / ");
    mvprintw(scrLine / 2 +3, scrCol/ 4 - 20, "  '._____.'  ");
    mvprintw(scrLine / 2 +4, scrCol/ 4 - 20, "   /     \\   ");
    mvprintw(scrLine / 2 +5, scrCol/ 4 - 20, "  |  YOU  |   ");

    mvprintw(scrLine / 2 -3, scrCol /4 * 3 + 7, "    _____    ");
    mvprintw(scrLine / 2 -2, scrCol /4 * 3 + 7, "  .'     '.  ");
    mvprintw(scrLine / 2 -1, scrCol /4 * 3 + 7, " /  o   o  \\ ");
    mvprintw(scrLine / 2 , scrCol /4 * 3 + 7, "|           |");
    mvprintw(scrLine / 2 +1, scrCol /4 * 3 + 7, "|  \\     /  |");
    mvprintw(scrLine / 2 +2, scrCol /4 * 3 + 7, " \\  '---'  / ");
    mvprintw(scrLine / 2 +3, scrCol /4 * 3 + 7, "  '._____.'  ");
    mvprintw(scrLine / 2 +4, scrCol /4 * 3 + 7, "   /     \\   ");
    mvprintw(scrLine / 2 +5, scrCol /4 * 3 + 7, "  |  bot  |   ");

    mvhline(scrLine / 2 -5, 0, '_', scrCol);
    mvhline(scrLine / 2 +8, 0, '_', scrCol);


    refresh();
}

void gunright(){
    mvprintw(scrLine / 2 -1, scrCol / 2 - 28, "                     ________________________________, "); //length 56
    mvprintw(scrLine / 2 , scrCol / 2 - 28, "'===-----...__  __,-""  ]____[ _.----------,__________|  "); 
    mvprintw(scrLine / 2 +1, scrCol / 2 - 28, "|             ""   /___________)||||||||||||)_)          ");
    mvprintw(scrLine / 2 +2, scrCol / 2 - 28,   "|                `-'(( ]        '----------`           ");
    mvprintw(scrLine / 2 +3, scrCol / 2 - 28, "|  ___...--,_  `    ''                                 ");
    mvprintw(scrLine / 2 +4, scrCol / 2 - 28, "'''          \\`                                        ");

    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mvprintw(scrLine / 2 -1, scrCol / 2 + 29, "/");
    mvprintw(scrLine / 2 , scrCol / 2 + 29, "-"); 
    mvprintw(scrLine / 2 +1, scrCol / 2 + 29, "\\");
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    //Animation for gun shooting

    //int dbt = 20; // distance_bullet_travel
    //for (int i = 0; i < dbt; i++){
    //    mvprintw(scrLine / 2 -2, scrCol / 2 + 30 + i, "-"); 
    //    mvprintw(scrLine / 2 -2, scrCol / 2 + 29 + i, " "); 
    //    refresh();
    //    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //}
    //mvprintw(scrLine / 2 -2, scrCol / 2 + 30 + dbt - 1, " ");
    mvprintw(scrLine / 2 -1, scrCol / 2 + 29, " ");
    mvprintw(scrLine / 2 , scrCol / 2 + 29, " "); 
    mvprintw(scrLine / 2 +1, scrCol / 2 + 29, " ");
    refresh();

}

void gunleft(){
    mvprintw(scrLine / 2 -1, scrCol / 2 - 28, " ,________________________________                     ");
    mvprintw(scrLine / 2 , scrCol / 2 - 28, "|__________,----------._ [____]  ""-,__  __...-----==='  ");
    mvprintw(scrLine / 2 +1, scrCol / 2 - 28, "        (_(||||||||||||)___________/   ''             |");
    mvprintw(scrLine / 2 +2, scrCol / 2 - 28,   "           `----------'        [ ))'-,                |");
    mvprintw(scrLine / 2 +3, scrCol / 2 - 28, "                                ''    `,  _,--...___  |");
    mvprintw(scrLine / 2 +4, scrCol / 2 - 28, "                                        `/          '''");

    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    mvprintw(scrLine / 2 -1, scrCol / 2 - 29, "\\");
    mvprintw(scrLine / 2 , scrCol / 2 - 30, "--"); 
    mvprintw(scrLine / 2 +1, scrCol / 2 - 29, "/");
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    mvprintw(scrLine / 2 -1, scrCol / 2 - 29, " ");
    mvprintw(scrLine / 2 , scrCol / 2 - 30, "  "); 
    mvprintw(scrLine / 2 +1, scrCol / 2 - 29, " ");
    refresh();
}

void energy(int my_energy, int ai_energy){
    for (int i = 0; i < 5; i++){
        move(scrLine / 2 - 7 - i, 0);
        clrtoeol();
    }
    refresh();
    for(int i = 0; i < my_energy; i++){
        mvprintw(scrLine / 2 -11, scrCol /4 - 20 + 8*i,"  /|   ");
        mvprintw(scrLine / 2 -10, scrCol /4 - 20 + 8*i," / |___");
        mvprintw(scrLine / 2 -9, scrCol /4 - 20 + 8*i,"/__   /");
        mvprintw(scrLine / 2 -8, scrCol /4 - 20 + 8*i,"   | / ");
        mvprintw(scrLine / 2 -7, scrCol /4 - 20 + 8*i,"   |/  ");
    }
    for(int i = 0; i < 41; i++){
        mvprintw(scrLine / 2 -12, scrCol/4 -21 + i, "_");
        mvprintw(scrLine / 2 -6, scrCol/4 -21 + i, "_");
        mvprintw(scrLine / 2 -12, scrCol/4 * 3 -21 + i, "_");
        mvprintw(scrLine / 2 -6, scrCol/4 * 3 -21 + i, "_");
        }
    for(int i = 0; i < 6; i++){
        mvprintw(scrLine / 2 -11 + i, scrCol/4 -21, "|");
        mvprintw(scrLine / 2 -11 + i, scrCol/4 -21 + 41, "|");
        mvprintw(scrLine / 2 -11 + i, scrCol/4 * 3 -21, "|");
        mvprintw(scrLine / 2 -11 + i, scrCol/4 * 3 -21 + 41, "|");
    }
    mvprintw(scrLine / 2 - 6, scrCol /4 - 20,"You have %d energy left", my_energy);
    for(int i = 0; i < ai_energy; i++){
        mvprintw(scrLine / 2 -11, scrCol /4 * 3 - 20 + 8*i,"  /|   ");
        mvprintw(scrLine / 2 -10, scrCol /4 * 3 - 20 + 8*i," / |___");
        mvprintw(scrLine / 2 -9, scrCol /4 * 3 - 20 + 8*i,"/__   /");
        mvprintw(scrLine / 2 -8, scrCol /4 * 3 - 20 + 8*i,"   | / ");
        mvprintw(scrLine / 2 -7, scrCol /4 * 3 - 20 + 8*i,"   |/  ");
    }
    mvprintw(scrLine / 2 - 6, scrCol /4 * 3 - 20,"Bot has %d energy left", ai_energy);
}

// These two function are for testing
void Printtest(int Code){  // int Code: 1 for HUMAN, 0 for AI(COMPUTER)

    mvprintw(scrLine / 2 + 9, scrCol/ 4 - 20,"_ _  ___ _  _ __    ___ ___ ___ _  _");
    mvprintw(scrLine / 2 + 10, scrCol/ 4 - 20,"\\_/ |  | |  | |_|    |   |  |_  |\\/|");
    mvprintw(scrLine / 2 + 11, scrCol/ 4 - 20," |  |__| |__| | \\   _|_  |  |__ |  |");

    mvprintw(scrLine / 2 + 12, scrCol/ 4 - 20,"__________");
    mvprintw(scrLine / 2 + 13, scrCol/ 4 - 20, "|   __   |");
    mvprintw(scrLine / 2 + 14, scrCol/ 4 - 20, "|  /  \\  |");
    mvprintw(scrLine / 2 + 15, scrCol/ 4 - 20, "|    _/  |");
    mvprintw(scrLine / 2 + 16, scrCol/ 4 - 20, "|    o   |");
    mvprintw(scrLine / 2 + 17, scrCol/ 4 - 20, "|_______%d|", Players[1].items[1]);
    mvprintw(scrLine / 2 + 19, scrCol/ 4 - 20, "[1]  Sharp");
    mvprintw(scrLine / 2 + 20, scrCol/ 4 - 20, "       Eye");

    mvprintw(scrLine / 2 + 12, scrCol/ 4 - 8, "__________");
    mvprintw(scrLine / 2 + 13, scrCol/ 4 - 8, "|    __  |");
    mvprintw(scrLine / 2 + 14, scrCol/ 4 - 8, "|   /  \\ |");
    mvprintw(scrLine / 2 + 15, scrCol/ 4 - 8, "|--  __/ |");
    mvprintw(scrLine / 2 + 16, scrCol/ 4 - 8, "|   /___ |");
    mvprintw(scrLine / 2 + 17, scrCol/ 4 - 8, "|_______%d|", Players[1].items[2]);
    mvprintw(scrLine / 2 + 19, scrCol/ 4 - 8, "[2] Double");
    mvprintw(scrLine / 2 + 20, scrCol/ 4 - 8, "    Damage");

    mvprintw(scrLine / 2 + 12, scrCol/ 4 + 4, "__________");
    mvprintw(scrLine / 2 + 13, scrCol/ 4 + 4, "|  ____  |");
    mvprintw(scrLine / 2 + 14, scrCol/ 4 + 4, "| /\\   \\ |");
    mvprintw(scrLine / 2 + 15, scrCol/ 4 + 4, "||  \\   ||");
    mvprintw(scrLine / 2 + 16, scrCol/ 4 + 4, "| \\__\\_/ |");
    mvprintw(scrLine / 2 + 17, scrCol/ 4 + 4, "|_______%d|", Players[1].items[3]);
    mvprintw(scrLine / 2 + 19, scrCol/ 4 + 4, "[3]    Ban");

    mvprintw(scrLine / 2 + 12, scrCol/ 4 + 16, "__________");
    mvprintw(scrLine / 2 + 13, scrCol/ 4 + 16, "|   /|   |");
    mvprintw(scrLine / 2 + 14, scrCol/ 4 + 16, "|  / |___|");
    mvprintw(scrLine / 2 + 15, scrCol/ 4 + 16, "| /__+1 /|");
    mvprintw(scrLine / 2 + 16, scrCol/ 4 + 16, "|    | / |");
    mvprintw(scrLine / 2 + 17, scrCol/ 4 + 16, "|____|/_%d|", Players[1].items[4]);
    mvprintw(scrLine / 2 + 19, scrCol/ 4 + 16, "[4] Re-");
    mvprintw(scrLine / 2 + 20, scrCol/ 4 + 16, "    charge");

    mvprintw(scrLine / 2 + 12, scrCol/ 4 * 3 + 5, "Bot's item    Num");
    mvprintw(scrLine / 2 + 13, scrCol/ 4 * 3 + 5, "_________________");
    mvprintw(scrLine / 2 + 14, scrCol/ 4 * 3 + 5, "Sharp Eye      %d   ",Players[0].items[1]);
    mvprintw(scrLine / 2 + 15, scrCol/ 4 * 3 + 5, "Double Damage  %d   ",Players[0].items[2]);
    mvprintw(scrLine / 2 + 16, scrCol/ 4 * 3 + 5, "Chain          %d   ",Players[0].items[3]);
    mvprintw(scrLine / 2 + 17, scrCol/ 4 * 3 + 5, "Healing        %d   ",Players[0].items[4]);


    energy(Players[1].hp, Players[0].hp); //Output the energy of both players
    //cout << endl << Players[0].hp << " " << Players[1].hp << " " << nowSpot << " " << nowBullet << endl;
    mvprintw(scrLine / 2 + 6, scrCol / 2 - 24, "Bullet number:     %d out of %d", nowSpot, MaxChamber);
    mvprintw(scrLine / 2 + 7, scrCol / 2 - 24, "Real bullets left: %d", nowBullet);
    mvprintw(scrLine / 2 + 11, scrCol / 2 - 6 , "[A] shoot yourself    [D] shoot opponent");
    refresh();

}  //Output current status including health and gun progress

void PrintGun(){ //Output Gun Configuration
    for(int i=0;i<MaxChamber;i++){
            //cout << Gun[i] <<" ";
            mvprintw(scrLine /4*3 , scrCol / 2 - 8 + i*2, "%d ", Gun[i]);
        }
        //cout << endl;
    refresh();
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


int HardAI(){
	//this is probably too high we should change it
    int accuracy[] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
    int random = rand() % 100;
    int currentaccuracy = accuracy[nowSpot];
    bool shoot;
    if(random < currentaccuracy) {
        shoot=isNextBullet();
    } else {
        shoot!=isNextBullet();
    }
    if(shoot){
        if(isNextBullet()){
            gunleft(); // gun to left, shoot player.
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            Damage(1,1);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return(1); //打中玩家继续回合
        }
        else{
            nowSpot++;
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            return 0;
        }
    }
    else{
        if(isNextBullet()){
            gunright(); // gun to right, shoot AI.
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            Damage(0,1);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 0;
        }
        else{
            nowSpot++;
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            return 1;
        }
    }
}

int MediumAI(){ //Game's Medium AI
    //Printtest(0);
    useHealItem(0); //Use HealItem whenever possible
    if (useNextBulletItem(0)){ //Use NextBulletItem whenever possible
        if (isNextBullet()){ //Check next Bullet, If Real
            if (useDoubleDamItem(0)){ //If DoubleDamItem is present
                gunleft(); // gun to left, shoot player.
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                Damage(1,2); //Shoot Players[1] (Human) with two damage
            }
            else
                gunleft(); 
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
            gunleft(); 
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
                gunleft(); 
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                Damage(1,2);
            }
            else
                gunleft(); 
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                Damage(1,1);
            return 1;
        }
        if (Probability()>=0.5){ //Probability Greater or Equal to 50% (Shoot Human)
            if (isNextBullet()){
                gunleft(); // gun to left, shoot player.
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
                gunright(); // gun to right, shoot AI.
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
    char userInput = getch();
    if(userInput=='d' || userInput=='D'){ //ShootAI
        gunright();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
    else if(userInput=='a' || userInput=='A'){ //ShootYourself
        gunleft();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
            //cout << "NoNextBulletItem" << endl;
            move(scrLine / 2 + 22, 0);
            clrtoeol();
            for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
                mvprintw(scrLine / 2 + 22, scrCol / 4 - 20, "No Sharp Eye");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                mvprintw(scrLine / 2 + 22, scrCol / 4 - 20, "            ");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
        else{
            if(isNextBullet()){
                //cout << "Real!" << endl;
                move(scrLine / 2 + 22, 0);
                clrtoeol();
                mvprintw(scrLine / 2 + 22, scrCol / 4 - 20, "Real!");
                refresh();
            }
            else{
                //cout << "Fake!" <<endl;
                move(scrLine / 2 + 22, 0);
                clrtoeol();
                mvprintw(scrLine / 2 + 22, scrCol / 4 - 20, "Fake!");
                refresh();
            }
        }
        return 1;
    }
    else if(userInput=='2'){ //Use Item[2] DoubleDamItem
        if(!useDoubleDamItem(1)){
            //cout << "No Double Damage Item" << endl;
            move(scrLine / 2 + 22, 0);
            clrtoeol();
            for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
                mvprintw(scrLine / 2 + 22, scrCol / 4 - 8, "No Double Damage Item");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                mvprintw(scrLine / 2 + 22, scrCol / 4 - 8, "                     ");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
        else{
            PlayerDamage=2;
        }
        return 1;
    }
    else if(userInput=='3'){ //Use Item[3] ChainItem
        if(!useChainItem(1)){
            //cout << "No Chain Item" << endl;
            move(scrLine / 2 + 22, 0);
            clrtoeol();
            for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
                mvprintw(scrLine / 2 + 22, scrCol / 4 + 4, "No Ban Item");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                mvprintw(scrLine / 2 + 22, scrCol / 4 + 4, "            ");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
        AIChained=true;
        return 1;
    }
    else if(userInput=='4'){ //Use Item[4] HealItem
        if(!useHealItem(1)){
            //cout << "No Health Item" << endl;
            move(scrLine / 2 + 22, 0);
            clrtoeol();
            for (int i = 0; i < 3; i++){//如果玩家按下无效键位，则闪烁三次提示语
                mvprintw(scrLine / 2 + 22, scrCol / 4 + 16, "No Recharge Item");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                mvprintw(scrLine / 2 + 22, scrCol / 4 + 16, "                ");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
        return 1;
    }
    else
        return 2;
}

void ChangeChamber(){ //Player choose their own Chamber Size and Bullet Number
	//cout << "Choose Chamber Size: ";
    mvprintw(scrLine / 2 + 10, scrCol / 2 - 10, "                    ");
    mvprintw(scrLine / 2 + 10, scrCol / 2 - 10, "Choose Chamber Size:");
    refresh();
	int temp = getch()-'0';
	if (temp>=6 && temp<=9){ //Min 6 and Max 9
		MaxChamber = temp;
		//cout << MaxChamber << endl;
        mvprintw(scrLine / 2 + 10, scrCol / 2 - 10, "Choose Chamber Size:%d", MaxChamber);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	else{
		//cout << "Invalid" <<endl;
        move(scrLine / 2 + 10, 0);
        clrtoeol();
        mvprintw(scrLine / 2 + 10, scrCol / 2 - 10, "Invalid");
        refresh();
	}
	//cout << "Choose Bullets Number: ";
    mvprintw(scrLine / 2 + 10, scrCol / 2 - 10, "                      ");
    mvprintw(scrLine / 2 + 10, scrCol / 2 - 10, "Choose Bullets Number:");
    refresh();
	temp = getch()-'0';
	if (temp>=2 && temp<=5){ //Min 2 and Max 5
		Bullets = temp;
		//cout << Bullets << endl;
        mvprintw(scrLine / 2 + 10, scrCol / 2 -10, "Choose Bullets Number:%d", Bullets);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        move(scrLine / 2 + 10, 0);
        clrtoeol();
	}
	else{
		//cout << "Invalid" <<endl;
        move(scrLine / 2 + 10, 0);
        clrtoeol();
        mvprintw(scrLine / 2 + 10, scrCol / 2 - 10, "Invalid");
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        move(scrLine / 2 + 10, 0);
        clrtoeol();
	}
}

int main(){

    //设置渲染画面
    initscr();
    raw();
    noecho();
    curs_set(0);

    getmaxyx(stdscr, scrLine, scrCol);       // 获取标准屏幕的行/列数
    mvprintw(scrLine / 2 - 5, scrCol / 2 - 31, "__________                .__             __     __           ");
    mvprintw(scrLine / 2 - 4, scrCol / 2 - 31, "\\______   \\  ____   __ __ |  |    ____  _/  |_ _/  |_   ____  ");
    mvprintw(scrLine / 2 - 3, scrCol / 2 - 31, " |       _/ /  _ \\ |  |  \\|  |  _/ __ \\ \\   __\\   __\\_/ __ \\ ");
    mvprintw(scrLine / 2 - 2, scrCol / 2 - 31, " |    |   \\(  <_> )|  |  /|  |__\\  ___/  |  |   |  |  \\  ___/ ");
    mvprintw(scrLine / 2 - 1, scrCol / 2 - 31, " |____|_  / \\____/ |____/ |____/ \\___  > |__|   |__|   \\___  >");
    mvprintw(scrLine / 2    , scrCol / 2 - 31, "        \\/                           \\/                    \\/ ");

    refresh();
    //1s
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mvprintw(scrLine / 2 + 3, scrCol / 2 - 10, "Press any key to start");
    refresh();
    getch();
    clear();
    refresh();

    smileface();

    srand(time(NULL)); //Random Time Seed
    InitializeItems();
    while(GameOver()){
        RandomItem();
        ChangeChamber();
        Reload=Bullets;
        nowBullet=Bullets;
        nowSpot=0;
        InitializeGun(Reload);
        //PrintGun();
        //game logic
        while(nowBullet>0 && nowSpot<MaxChamber){
            int Move=1;
            while(Move!=0 && nowSpot<MaxChamber && nowBullet>0 && GameOver()){
                if(Move==1)
                    //cout << "HUMAN:";
                    mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "                ");
                    mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "YOUR round");
                    mvprintw(scrLine / 2 +6, scrCol / 4 * 3 + 11, "    ");
                    mvprintw(scrLine / 2 +7, scrCol / 4 * 3 + 11, "    ");
                    mvprintw(scrLine / 2 +6, scrCol / 4 - 15, " /\\ ");
                    mvprintw(scrLine / 2 +7, scrCol / 4 - 15, "/__\\");
                    refresh();
                    Printtest(1);
                Move=Human();
            }
            Move=1;
            while(Move!=0 && nowSpot<MaxChamber && nowBullet>0 && GameOver()){
                //cout << "AI:";
                mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "                ");
                mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "Bot's round");
                mvprintw(scrLine / 2 +6, scrCol / 4 - 15, "    ");
                mvprintw(scrLine / 2 +7, scrCol / 4 - 15, "    ");
                mvprintw(scrLine / 2 +6, scrCol / 4 * 3 + 11, " /\\ ");
                mvprintw(scrLine / 2 +7, scrCol / 4 * 3 + 11, "/__\\");
                refresh();
                Printtest(0);
                Move=MediumAI();
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            if(Players[0].hp<=0){
                //cout << "You win!";
                Printtest(0);
                mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "                ");
                mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "YOU WIN!");
                refresh();
                return 1;
            }
            if(Players[1].hp<=0){
                //cout  << "You lose!";
                Printtest(0);
                mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "                ");
                mvprintw(scrLine / 2 -4, scrCol / 2 - 10, "YOU LOSE!");
                refresh();
                return 0;
            }
        }

        //cout << "Bullets Finished, Reload The Next Gun" << endl;
        move(scrLine / 2 + 10, 0);
        clrtoeol();
        mvprintw(scrLine / 2 + 10, scrCol / 2 - 10, "Bullets Finished, Reload The Next Gun");
        refresh();
        CleanupGun();   
    }
    getch();
    endwin();
    return 0;
}
