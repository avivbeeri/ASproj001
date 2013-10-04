class RhythmPlayer {
  public:
    RhythmPlayer();
    ~RhythmPlayer();
    bool isAlive() { return (HP != 0); }
    void takeDamage(int dmg) { HP -= dmg; }
    void heal(int value) { HP += value; }
  private:
    int HP;
    int mana;
    int level;
};
