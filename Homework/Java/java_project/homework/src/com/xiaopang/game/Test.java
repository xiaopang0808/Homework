package com.xiaopang.game;

public class Test {
    public static void main(String[] args) {
        Hero hero = new Hero();
        Monster monster = new Monster();
        Game game = new Game(hero,monster);
        game.start();
    }
}
class Game{
    Hero hero;
    Monster monster;

    public Game(){

    }
    public Game(Hero hero, Monster monster) {
        this.hero = hero;
        this.monster = monster;
    }
    public void start(){
        while(hero.getHp()>0 && monster.getHp()>0){
            int monsterAttackPower = Tool.getRandom(0,monster.getMaxAttackPower());
            int heroAttackPower = Tool.getRandom(0,hero.getMaxAttackPower());
            monster.attack(hero,monsterAttackPower);
            System.out.println("怪兽攻击英雄，英雄掉血"+monsterAttackPower+"，剩余血量"+hero.getHp());
            if(hero.getHp()<=0){
                end();
                return;
            }
            hero.attack(monster,heroAttackPower);
            System.out.println("英雄攻击怪兽，怪兽掉血"+heroAttackPower+"，剩余血量"+monster.getHp());
            if(monster.getHp()<=0){
                end();
                return;
            }
        }
    }
    public void end(){
        if(hero.getHp()>0){
            System.out.println("怪兽被消灭，英雄获胜");
        }
        else{
            System.out.println("英雄被击败，怪兽获胜");
        }
    }
}

class Tool{
    public static int getRandom(int min,int max){
        return (int)(Math.random()*(max-min+1)+min);
    }
}