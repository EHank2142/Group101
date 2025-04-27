int EasyAI() {
  useHealItem(0); //use heal item whenever possible

  // if next bullet is real, shoot oponent
  if (useNextBulletItem(0)) {
    if (isNextBullet(0)) {
      Damage(1, 1); //shoot human w basic damage
      return 1;
    }
    else {
      nowSpot+=1; //move on to next bullet
      return 1;
    }
  }

//otherwise, just shoot without checking
  if (isNextBullet(0)) {
    Damage(1, 1); //shoot human w basic damage
    return 1;
  }
  else {
    nowSpot+=1;
    return 0;
  }
} //doesn't use DoubleDamItem or ChainItem


  

