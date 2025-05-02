# Group101
**Roulette: A Deadly Game of Chance**

COMP2113ENGG1340 Group Project

Team Members: Liew Amanda Nicole Ann (3036440828), Lu Ho Tin (3036458825), Wu Ka Lok (3036293641), Xu Yihang(303638973), Yap Ern Lynn (3036441078), Zhang Yang(3036290766)

Everyone does make contribution, no free rider.

--

TO RUN THE PROGRAMME, PLEASE

1. Download the files. (If you don't know how to download file, please refer to **How To Download Files.png** in this repository)

2. Copy the directory **cxk** and file **main.cpp** to your cs.hku.hk server account directory and put them in the same directory.

3. EXECUTE: 

_____________________________________

$ g++ -o main main.cpp -lncurses

$ ./main

_____________________________________

**Game Description**

Roulette is a strategic game where players face off against an AI bot in a deadly game of roulette. Players and their opponent take turns shooting and can take another shot if you miss on yourself or shoot the opponent. However, the gun is filled with both real and fake bullets and everything is randomized. Use your power-up items and probability calculations boost your chances and outsmart the AI opponent. Every shot could be your last...

**Key Features**
- Gun where players can strategically choose the chamber size (6-9 slots) and bullet count (2-5 bullets)
- Power-up items:
  1. Sharp Eye: Shows if the next bullet is real or fake
  2. Double Damage: Next shot does 2 damage
  3. Hand-Cuffs: Bans the opponent's next round
  4. Heal: Heals 1 energy
- Three Levels of Difficulties where the AI uses different strategies
- Special suprise after beating AI

This programme is verified to be successfully compiled in the Computer Science department's academy server (academy11.cs.hku.hk or academy21.cs.hku.hk).

(If you are running this programme in your own local environment, it may prompt error, as your environment may not be equipped with ncurse. Please Make Sure Your Terminal Size Is Sufficient)

You are suggested to copy the file to your cs.hku.hk directory via FileZilla, and then use command prompt(cmd) / PowerShell to login your account via ssh. (Please see Module 0 if you don't know how to do https://moodle.hku.hk/course/section.php?id=1394825)

Using HKU VPN is more likely to connect to cs.hku.hk server and FileZilla server.
