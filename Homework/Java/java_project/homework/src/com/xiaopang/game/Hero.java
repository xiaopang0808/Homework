package com.xiaopang.game;

public class Hero {
    private int hp;
    private int maxAttackPower;

    public Hero() {
        this.hp = 500;
        this.maxAttackPower = 100;
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

    public void attack(Monster monster, int attackPower) {
        monster.beAttack(attackPower);
    }
    public void beAttack(int attackPower) {
        this.hp -= attackPower;
        if(this.hp <= 0){
            this.hp = 0;
        }
    }
}
