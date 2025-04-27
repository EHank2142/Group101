
int HardAI(){
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
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
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
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            return 1;
        }
    }
}
