package com.xiaopang.game;

public class Monster {
    private int hp;
    private int maxAttackPower;

    public Monster() {
        this.hp = 300;
        this.maxAttackPower = 150;
    }

    public int getHp() {
        return hp;
    }

    public void setHp(int hp) {
        this.hp = hp;
    }

    public int getMaxAttackPower() {
        return maxAttackPower;
    }

    public void setMaxAttackPower(int maxAttackPower) {
        this.maxAttackPower = maxAttackPower;
    }

    public void attack(Hero hero, int attackPower) {
        hero.beAttack(attackPower);
    }
    public void beAttack(int attackPower) {
        this.hp -= attackPower;
        if(this.hp <= 0){
            this.hp = 0;
        }
    }
}
