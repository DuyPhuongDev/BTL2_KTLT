#include "knight2.h"


/* * * BEGIN implementation of class BaseBag * * */
BaseItem* BaseBag::creatNode(ItemType item){
        BaseItem *node;
        if(item == Antidote) node = new ANTIDOTE;
        else if(item == PhoenixDownI) node = new PHOENIXDOWNI;
        else if(item == PhoenixDownII) node = new PHOENIXDOWNII;
        else if(item == PhoenixDownIII) node = new PHOENIXDOWNIII;
        else if(item == PhoenixDownIV) node = new PHOENIXDOWNIV;
        node->item=item;
        node->next= NULL;
        return node;
    }
bool BaseBag::insertFirst(BaseItem* item) {
        return true;
    }
BaseItem* BaseBag::get(ItemType item){
    BaseItem* pre = head;
    while(pre != NULL){
        if(pre->item==item){
            return pre;
        }
        pre=pre->next;
    }
    return NULL;
} 
string BaseBag::toString() const{
    string typeitem[5]={"Antidote","PhoenixI","PhoenixII","PhoenixIII","PhoenixIV"};
    string s("");
    s += "Bag[count=" + to_string(this->count) + ";";
    BaseItem* p = head;
    while(p!=NULL){
        if(p->item==Antidote) s+= "Antidote";
        else if(p->item==PhoenixDownI) s+= "PhoenixI";
        else if(p->item==PhoenixDownII) s+= "PhoenixII";
        else if(p->item==PhoenixDownIII) s+= "PhoenixIII";
        else if(p->item==PhoenixDownIV) s+= "PhoenixIV";
        if(p->next!=NULL) s+=",";
        p=p->next;
    }
    s+="]";
    return s;
}
void BaseBag::swapItem(ItemType item){
    if(head==NULL || head->next==NULL) return;
    BaseItem* cur = head;
    while(cur->next!=NULL){
        if(cur->item==item){
            swap(head->item,cur->item);
            break;
        }
        cur=cur->next;
    }
}

void BaseBag::deleteItem(){
    BaseItem* temp=head;
    head=head->next;
    this->count-=1;
    delete temp;
}
void BaseBag::insertBag(BaseItem* item){
    if(head==NULL) head=item;
    else{
        item->next = head;
        head = item;
    }
    this->count+=1;
}

bool DragonBag::insertFirst(BaseItem* item){
    if(this->getCount()<this->max_item && item->item!=Antidote) return true;
    return false;
}
void DragonBag::creatBag(){
    for(int i=0;i<this->num_phoenixI;i++){
        BaseItem* temp = creatNode(PhoenixDownI);
    if(this->insertFirst(temp)) this->insertBag(temp);
        else break;
    }
}
BaseItem* DragonBag::get(ItemType item){
    return BaseBag::get(item);
}
string DragonBag::toString() const{
    string s = BaseBag::toString();
    return s;
}

bool LancelotBag::insertFirst(BaseItem* item){
    if(this->getCount()<this->max_item) return true;
    return false;
}
void LancelotBag::creatBag(){
    for(int i=0;i<this->num_phoenixI;i++){
        BaseItem* temp = creatNode(PhoenixDownI);
        if(this->insertFirst(temp)) this->insertBag(temp);
        else break;
    }
    for(int i=0;i<num_antidote;i++){
        BaseItem* temp = creatNode(Antidote);
        if(this->insertFirst(temp)) this->insertBag(temp);
        else break;
    }
}
BaseItem* LancelotBag::get(ItemType item){
    BaseItem* p= BaseBag::get(item);
    return p;
}
string LancelotBag::toString() const{
    string s = BaseBag::toString();
    return s;
}
bool NormalBag::insertFirst(BaseItem *item){
    if(this->getCount()<this->max_item) return true;
    return false;
}
void NormalBag::creatBag(){
    for(int i=0;i<this->num_phoenixI;i++){
        BaseItem* temp = creatNode(PhoenixDownI);
        if(this->insertFirst(temp)) this->insertBag(temp);
        else break;
    }
    for(int i=0;i<num_antidote;i++){
        BaseItem* temp = creatNode(Antidote);
        if(this->insertFirst(temp)) this->insertBag(temp);
        else break;
    }
}
BaseItem* NormalBag::get(ItemType item){
    return BaseBag::get(item);
}
string NormalBag::toString() const{
    string s= BaseBag::toString();
    return s;
}
bool PaladinBag::insertFirst(BaseItem* item){
    return true;
}
void PaladinBag::creatBag(){
    for(int i=0;i<this->num_phoenixI;i++){
        BaseItem* temp = creatNode(PhoenixDownI);
        if(this->insertFirst(temp)) this->insertBag(temp);
        else break;
    }
    for(int i=0;i<num_antidote;i++){
        BaseItem* temp = creatNode(Antidote);
        if(this->insertFirst(temp)) this->insertBag(temp);
        else break;
    }
}
BaseItem* PaladinBag::get(ItemType item){
    BaseItem* p=BaseBag::get(item);
    return p;
}
string PaladinBag::toString() const{
    string s= BaseBag::toString();
    return s;
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
bool check_prime(int maxhp){
    if(maxhp<2) return false;
    for(int i=2;i<=sqrt(maxhp);i++){
        if(maxhp%i==0) return false;
    }
    return true;
}
bool check_dragon(int maxhp){
    // tach cac chu so
    if(maxhp>=100 && maxhp<=999){
        int arr[3];
        for(int i=0;i<3;i++){
            arr[i]=maxhp%10;
            maxhp/=10;
        }
        if(pow(arr[0],2)==pow(arr[1],2)+pow(arr[2],2)) return true;
        else if(pow(arr[1],2)==pow(arr[0],2)+pow(arr[2],2)) return true;
        else if(pow(arr[2],2)==pow(arr[1],2)+pow(arr[0],2)) return true;
    }
    return false;
}
BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    BaseKnight* knight= new BaseKnight;
    knight->id=id;
    knight->hp=maxhp;
    knight->maxhp=maxhp;
    knight->level=level;
    knight->gil=gil;
    knight->antidote=antidote;
    knight->phoenixdownI=phoenixdownI;
    //phan chia loai hiep si theo yc
    if(check_prime(maxhp)) knight->knightType = PALADIN;
    else if(maxhp==888) knight->knightType=LANCELOT;
    else if(check_dragon(knight->hp)) knight->knightType = DRAGON;
    else knight -> knightType = NORMAL;
    return knight;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}
void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}
ArmyKnights::ArmyKnights(const string & file_armyknights){
    ifstream hsfile(file_armyknights);
    if(hsfile.is_open()){
        hsfile>>sizeofteam;
        knights = new BaseKnight*[sizeofteam];
        for(int i=0;i<sizeofteam;i++){
            knights[i]= new BaseKnight;
            int maxhp, level, gil, antidote, phoenixdownI;
            hsfile>>maxhp>>level>>phoenixdownI>>gil>>antidote;
            knights[i]=BaseKnight::create(i+1,maxhp,level,gil,antidote,phoenixdownI);
            if(knights[i]->getType()==DRAGON){
                DragonBag* newbag = new DragonBag(knights[i],phoenixdownI);
                newbag->creatBag();
                knights[i]->setBag(newbag);
            }else if(knights[i]->getType()==LANCELOT){
                LancelotBag* newbag = new LancelotBag(knights[i], antidote, phoenixdownI);
                newbag->creatBag();
                knights[i]->setBag(newbag);
            }else if(knights[i]->getType()==NORMAL){
                NormalBag* newbag = new NormalBag(knights[i],antidote, phoenixdownI);
                newbag->creatBag();
                knights[i]->setBag(newbag);
            }else if(knights[i]->getType()==PALADIN){
                PaladinBag* newbag = new PaladinBag(knights[i],antidote,phoenixdownI);
                newbag->creatBag();
                knights[i]->setBag(newbag);
            }
        }
    }
    hsfile.close();
}

bool ArmyKnights::fight(BaseOpponent *opponent){
    // BaseKnight* hs = lastKnight();
    // BaseOpponent* boss = opponent;
    // switch(opponent->getType()){
    //     case MadBear:
    //     case Bandit:
    //     case LordLupin:
    //     case Elf:
    //     case Troll:
    //     case Tornbery:
    //     case QueenOfCards:
    //     case NinaDering:
    //     case DurianGarden:
    //     case OmegaWeapon:
    //         boss->changeInfo(hs);
    //         break;
    //     case Hades:
    //         if(!boss->PK(hs)) hs->setHP(0);
    //         else{
    //             if(!this->hasPaladinShield()) this->cheast.PaladinShield=1;
    //         }
    //         break;
    //     default:
    //         break;
    // }
    if(lastKnight()==NULL) return false;
    return true;
}
bool ArmyKnights::adventure(Events *events){
    // code su kien
    bool rescue=true;
    BaseOpponent* enemy = nullptr;
    int num_code=0;
    bool omega = false;
    bool hadess = false;
    while(rescue && num_code<events->count()){
        BaseKnight* hs = lastKnight();
        switch(events->get(num_code)){
            case 1:
                enemy = new MADBEAR(hs,10,100);
                enemy->setLevelO(events,num_code);
                enemy->changeInfo(hs);
                hoisinh(hs);
                delete enemy;
                break;
            case 2:
                enemy = new BANDIT(hs,15,150);
                enemy->setLevelO(events,num_code);
                enemy->changeInfo(hs);
                hoisinh(hs);
                delete enemy;
                break;
            case 3:
                enemy = new LORDLUPIN(hs,45,450);
                enemy->setLevelO(events,num_code);
                enemy->changeInfo(hs);
                hoisinh(hs);
                delete enemy;
                break;
            case 4:
                enemy = new ELF(hs,75,750);
                enemy->setLevelO(events,num_code);
                enemy->changeInfo(hs);
                hoisinh(hs);
                delete enemy;
                break;
            case 5:
                enemy = new TROLL(hs,95,800);
                enemy->setLevelO(events,num_code);
                enemy->changeInfo(hs);
                hoisinh(hs);
                delete enemy;
                break;
            case 6:
                enemy = new TORNBERY(hs);
                enemy->setLevelO(events,num_code);
                enemy->changeInfo(hs);
                hoisinh(hs);
                if(hs->getPoisoned()){
                    if(hs->getBag()->getCount()<=3){
                        hs->getBag()->setHead(NULL);
                        hs->getBag()->setCount(0);
                    }
                    else{
                        for(int i=0;i<3;i++){
                            hs->getBag()->deleteItem();
                        }
                    }
                    hs->setHP(hs->getHp()-10);
                    hs->setPoisone(false);
                } 
                if(hs->getHp()<=0) hoisinh(hs);
                delete enemy;
                break;
            case 7:
                enemy = new QUEENOFCARDS(hs);
                enemy->setLevelO(events,num_code);
                enemy->changeInfo(hs);
                delete enemy;
                break;
            case 8:
                enemy = new NINADERINGS(hs);
                enemy->changeInfo(hs);
                delete enemy;
                break;
            case 9:
                enemy = new DURIANGARDEN(hs);
                enemy->changeInfo(hs);
                delete enemy;
                break;
            case 10:
                if(!omega){
                    enemy = new OMEGAWEAPON(hs);
                    enemy->changeInfo(hs);
                    hoisinh(hs);
                    omega = enemy->PK(hs);
                    delete enemy;
                }
                break;
            case 11:
                if(!hadess){
                    enemy = new HADES(hs);
                    if(!enemy->PK(hs)) hs->setHP(hs->getHp()-hs->getHp());
                    else{
                        if(!this->hasPaladinShield()) {
                            this->cheast.PaladinShield=1;
                            hadess=true;
                        }
                    }
                    hoisinh(hs);
                    delete enemy;
                }
                break;
            case 112:
                if(hs->getBag()->insertFirst(hs->getBag()->creatNode(PhoenixDownII))) {
                    hs->getBag()->insertBag(hs->getBag()->creatNode(PhoenixDownII));
                }
                break;
            case 113:
                if(hs->getBag()->insertFirst(hs->getBag()->creatNode(PhoenixDownIII))) {
                    hs->getBag()->insertBag(hs->getBag()->creatNode(PhoenixDownIII));
                }
                break;
            case 114:
                if(hs->getBag()->insertFirst(hs->getBag()->creatNode(PhoenixDownIV))) {
                    hs->getBag()->insertBag(hs->getBag()->creatNode(PhoenixDownIV));
                }
                break;
            case 95:
                if(!this->hasPaladinShield()){
                    this->cheast.PaladinShield=1;
                }
                break;
            case 96:
                this->cheast.LancelotSpear+=1;
                break;
            case 97:
                this->cheast.GuinevereHair+=1;
                break;
            case 98:
                if(this->hasGuinevereHair()&&this->hasLancelotSpear()&&this->hasPaladinShield()){
                    this->cheast.ExcaliburSword+=1;
                }
                break;
            case 99:
                if(this->hasExcaliburSword()){
                    printInfo();
                    return true;
                }
                if(this->hasGuinevereHair()&&this->hasLancelotSpear()&&this->hasPaladinShield()){
                    int num_hs = count();
                    int HPboss=5000;
                    double dameHS;
                    for(int i=num_hs-1;i>=0;i--){
                        BaseKnight* current=knights[i];
                        if(current->getType()==DRAGON) dameHS=0.075;
                        else if(current->getType()==LANCELOT) dameHS=0.05;
                        else if(current->getType()==PALADIN) dameHS =0.06;
                        else dameHS=0;
                        int damage=current->getHp()*current->getLevel()*dameHS;
                        HPboss-=damage;
                        if(HPboss>0) {
                            current->setHP(0);
                            rescue=false;
                        }else {
                            printInfo();
                            return true;
                        }
                    }
                }else{
                    for(int i=0;i<count();i++){
                        knights[i]->setHP(0);
                    }
                }
                break;
        default:
            break;
        }
        if(hs->getHp()>hs->getMaxHP()) hs->setHP(hs->getMaxHP());
        if(hs->getLevel()>10) hs->setLevel(10);
        
        /*Gils con du*/
        
        for(int i=count()-1;i>0;i--){
            int ortherGils;
            if(knights[i]->getGIls()>999){
                ortherGils=knights[i]->getGIls()-999;
                knights[i]->setGIls(999);
                knights[i-1]->setGIls(knights[i-1]->getGIls()+ortherGils);
            }
        }
        
        if(knights[0]->getGIls()>999) knights[0]->setGIls(999);

        num_code++;
        /*in thong tin*/

        printInfo();
        if(lastKnight()==NULL) return false;
    }
    return rescue;
}
int ArmyKnights::count() const{
    for(int i=0;i<sizeofteam;i++){
        if(knights[i]->getHp()<=0) return i;
    }
    return sizeofteam;
}
BaseKnight* ArmyKnights::lastKnight() const{
    if(this->count()>0) {
        return knights[count()-1];
    }
    return NULL;
}
ArmyKnights::~ArmyKnights(){
    for(int i=0;i<sizeofteam;i++){
        delete[] knights[i];
    }
    delete[] knights;
}
bool ArmyKnights::hasPaladinShield() const{
    if(cheast.PaladinShield==0) return false;
    return true;
}
bool ArmyKnights::hasLancelotSpear() const{
    if(cheast.LancelotSpear==0) return false;
    return true;
}
bool ArmyKnights::hasGuinevereHair() const{
    if(cheast.GuinevereHair==0) return false;
    return true;
}
bool ArmyKnights::hasExcaliburSword() const{
    if(cheast.ExcaliburSword==0) return false;
    return true;
}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
KnightAdventure::~KnightAdventure(){
    delete armyKnights;
    delete events;
}
void KnightAdventure::loadArmyKnights(const string &file_armyknights){
    armyKnights = new ArmyKnights(file_armyknights);
}
void KnightAdventure::loadEvents(const string &file_events){
    events = new Events(file_events); 
}
void KnightAdventure::run(){
    if(armyKnights->adventure(events)) armyKnights->printResult(true);
    else armyKnights->printResult(false);
}
/* * * END implementation of class KnightAdventure * * */
// class event
Events::Events(const string & file_events){
    ifstream fin(file_events);
        if(fin.is_open()){
            fin>>numcode;
            eventcode = new int[numcode];
            for(int i=0;i<numcode;i++){
                fin>>eventcode[i];
            }
        }else{
            eventcode= nullptr;
            numcode = 0;
        }
    fin.close();
}
int Events::count() const{
    return numcode;
}
int Events::get(int i) const{
    if(i>=0 && i<numcode) return eventcode[i];
    else return -1;
}
Events::~Events(){
    delete[] eventcode;
}

/* * * START implementation of class BaseItem * * */
bool ANTIDOTE::canUse(BaseKnight* knight){
    if(knight->getPoisoned()) return true;
    return false;
}
void ANTIDOTE::use(BaseKnight* knight){
    //knight->getBag()->swapItem(Antidote);
    knight->getBag()->deleteItem();
    knight->setPoisone(false);
}
bool PHOENIXDOWNI::canUse(BaseKnight* knight){
    if(knight->getHp()<=0) return true;
    return false;
}
void PHOENIXDOWNI::use(BaseKnight* knight){
    //knight->getBag()->swapItem(PhoenixDownI);
    knight->getBag()->deleteItem();
    knight->setHP(knight->getMaxHP());
}
bool PHOENIXDOWNII::canUse(BaseKnight* knight){
    if(knight->getHp()<=0||knight->getHp()<knight->getMaxHP()/4) return true;
    return false;
}
void PHOENIXDOWNII::use(BaseKnight* knight){
    //knight->getBag()->swapItem(PhoenixDownII);
    knight->getBag()->deleteItem();
    knight->setHP(knight->getMaxHP());
}
bool PHOENIXDOWNIII::canUse(BaseKnight* knight){
    if(knight->getHp()<=0 || knight->getHp()<knight->getMaxHP()/3) return true;
    return false;
}
void PHOENIXDOWNIII::use(BaseKnight* knight){
    //knight->getBag()->swapItem(PhoenixDownIII);
    knight->getBag()->deleteItem();
    if(knight->getHp()<=0) knight->setHP(knight->getMaxHP()/3);
    else knight->setHP(knight->getHp() + knight->getMaxHP()/4);
}
bool PHOENIXDOWNIV::canUse(BaseKnight* knight){
    if(knight->getHp()<=0 || knight->getHp()<knight->getMaxHP()/2) return true;
    return false;
}
void PHOENIXDOWNIV::use(BaseKnight* knight){
    //knight->getBag()->swapItem(PhoenixDownIV);
    knight->getBag()->deleteItem();
    if(knight->getHp()<=0) knight->setHP(knight->getMaxHP()/2);
    else knight->setHP(knight->getHp() + knight->getMaxHP()/5);
}
/* * * END implementation of class BaseItem * * */
/* * * start implementation of class base opponent * * */
void hoisinh(BaseKnight* hs){
    BaseItem* cur = hs->getBag()->getHead();
    while (cur!=NULL)
    {   
        if(cur->canUse(hs)){
            swap(hs->getBag()->getHead()->item,cur->item);
            cur->use(hs);
            break;
        }
        cur=cur->next;
    }
    if(hs->getHp()<=0 && hs->getGIls()>=100){
        hs->setHP(hs->getMaxHP()/2);
        hs->setGIls(hs->getGIls()-100);
    }
}