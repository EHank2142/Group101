int easyAI() {
	int randomItemToUse = rand() % 4;
	switch(randomItemToUse) { //use a random weapon
		case 0: useNextBulletItem(0); break;
		case 1: useDoubleDamItem(0); break;
		case 2: useChainItem(0); break;
		case 3: useHealItem(0); break;
	}

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
	
	if (Probability() < 0.5) { //shoot itself
		if (isNextBullet()) {
			Damage(0, 1);
			return 0;
		}
		else {
			nowSpot += 1;
			return 1;
		}
	}
	else { //shoot player
		if (isNextBullet()) {
			if (useDoubleDamItem(0)) {
				Damage(1, 2);
			}
			else {
				Damage (1, 1);
			}
			return 1;
		}
		else {
			nowSpot += 1;
			return 0; //chance return to player
		}
	}
}
		



	
  

