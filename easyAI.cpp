int easyAI() {
	int randomItemToUse = rand() % 4;
	bool UsedDoubleDamage = false;
	bool UsedChainItem = false;
	switch(randomItemToUse) { //use a random weapon
		case 0: 
			if (useNextBulletItem(0)) {
				if (isNextBullet()) {
					Damage(1, 1);
					return 1; //shoot player
				}
				else {
					nowSpot += 1;
					return 1;
				}
			}
			break;
		case 1: useDoubleDamItem(0); 
			UsedDoubleDamage = true;
			break;
		case 2: useChainItem(0); 
			UsedChainItem = true;
			break;
		case 3: useHealItem(0); break;
	}
	
	if (Probability() < 0.5) { //shoot itself
		if (isNextBullet()) {
			Damage(0, 1);
			if (UsedChainDamage) 
				return 1; //skips player's turn
			else
				return 0; //back to player's turn
		}
		else {
			nowSpot += 1;
			return 1;
		}
	}
	else { //shoot player
		if (isNextBullet()) {
			if (UsedDoubleDamage) {
				Damage(1, 2); //double damage
			}
			else {
				Damage (1, 1); //normal damage
			}
			return 1;
		}
		else {
			nowSpot += 1;
			if (UsedChainDamage) 
				return 1; //skips player's turn
			else
				return 0; //back to player's turn
		}
	}
}
		



	
  

