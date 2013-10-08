#ifndef RHYTHM_PLAYER_H
#define RHYTHM_PLAYER_H

class RhythmPlayer {
  public:
    RhythmPlayer();
    ~RhythmPlayer();
    bool isAlive() { return (HP != 0); }
    void takeDamage(int dmg) { HP -= dmg; }
    void heal(int value) { HP += value; }
    unsigned int getHP(){ return HP; }
	  void reset();
	private:
    unsigned int HP;
    unsigned int mana;
    unsigned int level;
};

#endif
