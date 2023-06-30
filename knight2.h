#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

class BaseItem;
class Events;
class BaseKnight;
class BaseOpponent;
enum ItemType{Antidote = 0,PhoenixDownI,PhoenixDownII,PhoenixDownIII,PhoenixDownIV};

class BaseItem{
public:
    ItemType item;
    BaseItem *next;
    BaseItem()
    {
        this->next = NULL;
    }
    virtual bool canUse(BaseKnight *knight) = 0;
    virtual void use(BaseKnight *knight) = 0;
};

class BaseBag
{
protected:
    BaseKnight *knight;
    BaseItem *head;
    int count = 0;

public:
    BaseBag()
    {
        this->head = NULL;
    }
    void setHead(BaseItem *head)
    {
        this->head = head;
    }
    BaseItem *getHead()
    {
        return head;
    }
    void setCount(int count)
    {
        this->count = count;
    }
    int getCount()
    {
        return count;
    }
    ~BaseBag(){
        BaseItem* temp = head;
        while(temp!=NULL){
            delete temp;
            temp=temp->next;
        }
        delete head;
    }
    BaseItem *creatNode(ItemType item);
    void insertBag(BaseItem *item);
    void swapItem(ItemType item);
    void deleteItem();
    virtual bool insertFirst(BaseItem *item);
    virtual BaseItem *get(ItemType itemType);
    virtual string toString() const;
};

enum KnightType
{
    PALADIN = 0,
    LANCELOT,
    DRAGON,
    NORMAL
};


class BaseKnight
{
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    bool poisoned=false;
    BaseBag *bag;
    KnightType knightType;

public:
    int getMaxHP()
    {
        return maxhp;
    }
    int getHp()
    {
        return hp;
    }
    void setHP(int hp)
    {
        this->hp = hp;
    }
    void setLevel(int level)
    {
        this->level = level;
    }
    int getLevel()
    {
        return level;
    }
    void setGIls(int gil)
    {
        this->gil = gil;
    }
    int getGIls()
    {
        return gil;
    }
    void setPoisone(bool n){
        this->poisoned=n;
    }
    bool getPoisoned(){ return poisoned; }
    void setAntidote(int antidote)
    {
        this->antidote = antidote;
    }
    int getAntidote()
    {
        return antidote;
    }
    KnightType getType()
    {
        return knightType;
    }
    void setBag(BaseBag *bag)
    {
        this->bag = bag;
    }
    BaseBag *getBag()
    {
        return bag;
    }
    static BaseKnight *create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};

struct cheastsure
{
    int PaladinShield = 0;
    int LancelotSpear = 0;
    int GuinevereHair = 0;
    int ExcaliburSword = 0;
};
class ArmyKnights
{
private:
    BaseKnight **knights;
    cheastsure cheast;
    int sizeofteam;

public:
    ArmyKnights(const string &file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent *opponent);
    bool adventure(Events *events);
    int count() const;
    BaseKnight *lastKnight() const;
    cheastsure getCheast(){
        return cheast;
    }
    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class Events
{
private:
    int *eventcode;
    int numcode;

public:
    Events(const string &file_events);
    int count() const;
    int get(int i) const;
    ~Events();
};

class KnightAdventure
{
private:
    ArmyKnights *armyKnights;
    Events *events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &file_armyknights);
    void loadEvents(const string &file_events);
    void run();
};

class ANTIDOTE : public BaseItem
{
public:
    ANTIDOTE() : BaseItem()
    {
        this->item = Antidote;
    }
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PHOENIXDOWNI : public BaseItem
{
public:
    PHOENIXDOWNI() : BaseItem()
    {
        this->item = PhoenixDownI;
    }
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PHOENIXDOWNII : public BaseItem
{
public:
    PHOENIXDOWNII() : BaseItem()
    {
        this->item = PhoenixDownII;
    }
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PHOENIXDOWNIII : public BaseItem
{
public:
    PHOENIXDOWNIII() : BaseItem()
    {
        this->item = PhoenixDownIII;
    }
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PHOENIXDOWNIV : public BaseItem
{
public:
    PHOENIXDOWNIV() : BaseItem()
    {
        this->item = PhoenixDownIV;
    }
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class DragonBag : public BaseBag
{
private:
    BaseKnight *knight;
    int const max_item = 14;
    int num_antidote;
    int num_phoenixI;

public:
    DragonBag(BaseKnight *knight, int num_phoenixI) : BaseBag()
    {
        this->knight = knight;
        this->num_phoenixI = num_phoenixI;
    }
    void creatBag();
    bool insertFirst(BaseItem *item);
    BaseItem *get(ItemType itemType);
    string toString() const;
};

class LancelotBag : public BaseBag
{
private:
    BaseKnight *knight;
    int const max_item = 16;
    int num_antidote;
    int num_phoenixI;

public:
    LancelotBag(BaseKnight *knight, int num_antidote, int num_phoenixI) : BaseBag()
    {
        this->knight = knight;
        this->num_antidote = num_antidote;
        this->num_phoenixI = num_phoenixI;
    }
    void creatBag();
    bool insertFirst(BaseItem *item);
    BaseItem *get(ItemType itemType);
    string toString() const;
};

class NormalBag : public BaseBag
{
private:
    BaseKnight *knight;
    int const max_item = 19;
    int num_antidote;
    int num_phoenixI;

public:
    NormalBag(BaseKnight *knight, int num_antidote, int num_phoenixI) : BaseBag()
    {
        this->knight = knight;
        this->num_antidote = num_antidote;
        this->num_phoenixI = num_phoenixI;
    }
    void creatBag();
    bool insertFirst(BaseItem *item);
    BaseItem *get(ItemType itemType);
    string toString() const;
};

class PaladinBag : public BaseBag
{
private:
    BaseKnight *knight;
    int num_antidote;
    int num_phoenixI;

public:
    PaladinBag(BaseKnight *knight, int num_antidote, int num_phoenixI) : BaseBag()
    {
        this->knight = knight;
        this->num_antidote = num_antidote;
        this->num_phoenixI = num_phoenixI;
    }
    void creatBag();
    bool insertFirst(BaseItem *item);
    BaseItem *get(ItemType itemType);
    string toString() const;
};

/***OPPONENT CLASS***/
enum typeOpponent
{
    MadBear = 0,
    Bandit,
    LordLupin,
    Elf,
    Troll,
    Tornbery,
    QueenOfCards,
    NinaDering,
    DurianGarden,
    OmegaWeapon,
    Hades
};
class BaseOpponent
{
protected:
    int levelO;
    int basedame;
    int gils;
    typeOpponent type;
    BaseKnight* hs;
public:
    int getLevelO()
    {
        return levelO;
    }
    virtual void setLevelO(Events *events, int i)
    {
        levelO = (i + events->get(i)) % 10 + 1;
    }
    virtual void setDame(int basedame){
        this->basedame=basedame;
    }
    int getDame()
    {
        return basedame;
    }
    virtual void setGil(int gils){
        this->gils=gils;
    }
    int getGil()
    {
        return gils;
    }
    typeOpponent getType()
    {
        return type;
    }
    virtual bool PK(BaseKnight* hs){
        if(hs->getLevel()>=this->getLevelO()) return true;
        return false;
    }
    virtual void changeInfo(BaseKnight* hs)=0;
};

class MADBEAR : public BaseOpponent
{
public:
    MADBEAR(BaseKnight* hs,int basedame, int gils)
    {
        this->hs=hs;
        this->basedame = basedame;
        this->gils = gils;
        this->type = MadBear;
    }
    bool PK(BaseKnight* hs){
        if( hs->getType() ==LANCELOT || hs->getType()==PALADIN) return true;
        if(hs->getLevel()>=this->getLevelO()) return true;
        return false;
    }
    void changeInfo(BaseKnight* hs){
        if(PK(hs)) hs->setGIls(hs->getGIls()+this->getGil());
        else hs->setHP(hs->getHp()-this->getDame()*(this->getLevelO()-hs->getLevel()));
    }
};

class BANDIT:public BaseOpponent{
public:
    BANDIT(BaseKnight* hs,int basedame, int gils){
        this->hs=hs;
        this->basedame=basedame;
        this->gils=gils;
        this->type=Bandit;
    }
    bool PK(BaseKnight* hs){
        if( hs->getType() ==LANCELOT || hs->getType()==PALADIN) return true;
        if(hs->getLevel()>=this->getLevelO()) return true;
        return false;
    }
    void changeInfo(BaseKnight* hs){
        if(PK(hs)) hs->setGIls(hs->getGIls()+this->getGil());
        else hs->setHP(hs->getHp()-this->getDame()*(this->getLevelO()-hs->getLevel()));
    }
};
class LORDLUPIN:public BaseOpponent{
public:
    LORDLUPIN(BaseKnight* hs,int basedame, int gils){
        this->hs=hs;
        this->basedame=basedame;
        this->gils=gils;
        this->type=LordLupin;
    }
    bool PK(BaseKnight* hs){
        if( hs->getType() ==LANCELOT || hs->getType()==PALADIN) return true;
        if(hs->getLevel()>=this->getLevelO()) return true;
        return false;
    }
    void changeInfo(BaseKnight* hs){
        if(PK(hs)) hs->setGIls(hs->getGIls()+this->getGil());
        else hs->setHP(hs->getHp()-this->getDame()*(this->getLevelO()-hs->getLevel()));
    }
};
class ELF : public BaseOpponent{
public:
    ELF(BaseKnight* hs,int basedame, int gils){
        this->hs=hs;
        this->basedame=basedame;
        this->gils=gils;
        this->type=Elf;
    }
    bool PK(BaseKnight* hs){
        if( hs->getType() ==LANCELOT || hs->getType()==PALADIN) return true;
        if(hs->getLevel()>=this->getLevelO()) return true;
        return false;
    }
    void changeInfo(BaseKnight* hs){
        if(PK(hs)) hs->setGIls(hs->getGIls()+this->getGil());
        else hs->setHP(hs->getHp()-this->getDame()*(this->getLevelO()-hs->getLevel()));
    }
};
class TROLL : public BaseOpponent{
public:
    TROLL(BaseKnight* hs,int basedame, int gils){
        this->hs=hs;
        this->basedame=basedame;
        this->gils=gils;
        this->type=Troll;
    }
    bool PK(BaseKnight* hs){
        if( hs->getType() ==LANCELOT || hs->getType()==PALADIN) return true;
        if(hs->getLevel()>=this->getLevelO()) return true;
        return false;
    }
    void changeInfo(BaseKnight* hs){
        if(PK(hs)) hs->setGIls(hs->getGIls()+this->getGil());
        else hs->setHP(hs->getHp()-this->getDame()*(this->getLevelO()-hs->getLevel()));
    }
};
class TORNBERY : public BaseOpponent{
public:
    TORNBERY(BaseKnight* hs){
        this->hs=hs;
        this->type=Tornbery;
    }
    bool PK(BaseKnight* hs){
        if( hs->getType() == DRAGON) return true;
        if(hs->getLevel()>=this->getLevelO()) return true;
        return false;
    }
    void changeInfo(BaseKnight* hs){
        if(PK(hs)){
            hs->setLevel(hs->getLevel()+1);
        }
        else hs->setPoisone(true);
    }
};
class QUEENOFCARDS : public BaseOpponent{
public:
    QUEENOFCARDS(BaseKnight* hs){
        this->hs=hs;
        this->type=QueenOfCards;
    }
    bool PK(BaseKnight* hs){
        if(hs->getLevel()>=this->getLevelO()) return true;
        return false;
    }
    void changeInfo(BaseKnight* hs){
        if(PK(hs)) hs->setGIls(hs->getGIls()*2);
        else{
            if(hs->getType()!=PALADIN) hs->setGIls(hs->getGIls()/2);
        }
    }
};
class NINADERINGS : public BaseOpponent{
public:
    NINADERINGS(BaseKnight* hs){
        this->hs=hs;
        this->type=NinaDering;
    }
    void changeInfo(BaseKnight* hs){
        if(hs->getHp()<hs->getMaxHP()/3){
            if(hs->getType()!=PALADIN  && hs->getGIls()>=50){
                hs->setGIls(hs->getGIls()-50);
                hs->setHP(hs->getHp()+hs->getMaxHP()/5);
            }else hs->setHP(hs->getHp()+hs->getMaxHP()/5);     
        }
    }
};
class DURIANGARDEN : public BaseOpponent{
public:
    DURIANGARDEN(BaseKnight* hs){
        this->hs=hs;
        this->type=DurianGarden;
    }
    void changeInfo(BaseKnight* hs){
        hs->setHP(hs->getMaxHP());
    }
};
class OMEGAWEAPON: public BaseOpponent{
public:
    OMEGAWEAPON(BaseKnight* hs){
        this->hs=hs;
        this->type=OmegaWeapon;
    }
    bool PK(BaseKnight* hs){
        if(hs->getType()==DRAGON || hs->getLevel()==10 && hs->getHp()==hs->getMaxHP()) return true;
        return false;
    }
    void changeInfo(BaseKnight* hs){
        if(PK(hs)) {
            hs->setLevel(10);
            hs->setGIls(999);
        }else hs->setHP(0);
    }
};
class HADES: public BaseOpponent{
public:
    HADES(BaseKnight* hs){
        this->hs=hs;
        this->type=Hades;
    }
    bool PK(BaseKnight* hs){
        if(hs->getLevel()==10 || hs->getType()==PALADIN && hs->getLevel()>=8) return true;
        return false;
    }
    void changeInfo(BaseKnight* hs){
    }
};

/***Start declare some functions***/

bool check_prime(int maxhp);
bool check_dragon(int maxhp);
void hoisinh(BaseKnight* hs);
/***End declare functions***/
#endif // __KNIGHT2_H__