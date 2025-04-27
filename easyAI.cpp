int EasyAI(){
useHealItem(0); //Use HealItem if available
  if (useNextBulletItem(0)){ //Use NextBulletItem if available
		if (isNextBullet()){ //Shoot player if next bullet is real
			if (useDoubleDamItem(0)){ // Use DoubleDamItem if available
				gunleft();
				Damage(1,2);
			}
			else {
				gunleft();
				Damage(1,1);
			}
			return 1;
		}
		else { //Next bullet not real so AI shoots itself
			nowSpot +=1;
			return 1;
		}
	}
	else {
		if (useDoubleDamItem(0)){ // Use DoubleDamItem on player if available
			gunleft();
			if (isNextBullet()){
				Damage(1,2);
				return 1;
			}
			else {
				nowSpot+=1;
				return 0;
			}
		}
		else {
			if (useChainItem(0)){ //use ChainItem if available 
				if (isNextBullet()){
					gunleft();
					Damage(1,1);
					return 1;
				}
				else {
					nowSpot+=1;
					return 1;
				}
			}
			else { //AI shoots itself if it has no items
				if (isNextBullet()){
					gunright();
					Damage(0,1);
					return 0;
				}
				else {
					nowSpot+=1;
					return 1;
				}
			}
		}
	}
}
  

