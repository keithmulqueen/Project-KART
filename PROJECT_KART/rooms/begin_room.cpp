#include "begin_room.h"
#include "ui_begin_room.h"

begin_room::begin_room(Player* player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::begin_room)
{
    this->player = player;
    index = 0;
    index2 = 0;
    ui->setupUi(this);
    loadImages();
    ui->minimapLabel->setPixmap(images[0][0]);
    ui->currentRoomLabel->setPixmap(images[1][0]);
    //label->setPixmap(QPixmap("C:/Users/manolis/Desktop/data/test.png", 0, Qt::AutoColor));

    layer = 1; //change between 1 and 2
    roomCreation();
    currentRoom = rooms[RN_B];
   /* MiniGame1 *mi = new MiniGame1(this);
    mi->exec();
    delete mi;*/

    this->setWindowTitle("KART - Reality");
    setDarkGreyStyle();

    updateInventoryRoom(currentRoom->getInventory());
    updateInventoryDisplay(player->getInventory());

    intention= NOTHING;
}

void begin_room::roomCreation(){
    //rooms.resize(G_MAX_ROOMS);
    char c = 'b';
    string tryme = "";
    char streng[10] = "b";
    for(int i=0;i<G_MAX_ROOMS;i++) {
        tryme = streng;
        rooms.push_back(new Room(tryme));
        streng[0]++;
        rooms[i]->setNumber(i);
    }

    //                   (N, E, S, W)
    rooms[RN_B]->setExits(NULL, rooms[RN_C], NULL, NULL);
    rooms[RN_B]->addItem(new Food("Apple",1,10));


    rooms[RN_C]->setExits(rooms[RN_F], rooms[RN_D], NULL, rooms[RN_B]);
    rooms[RN_C]->addItem(new Food("Carrot",1,10));

    rooms[RN_D]->setExits(NULL, NULL, rooms[RN_E], rooms[RN_C]);
    rooms[RN_E]->setExits(rooms[RN_D], NULL, NULL, NULL);
    rooms[RN_F]->setExits(rooms[RN_G], NULL , rooms[RN_C], NULL);
    rooms[RN_G]->setExits(rooms[RN_H], NULL, rooms[RN_F], NULL);
    rooms[RN_H]->setExits(rooms[RN_L], rooms[RN_I], rooms[RN_G], rooms[RN_J]);
    rooms[RN_I]->setExits(NULL,NULL,NULL, rooms[RN_H]);
    rooms[RN_J]->setExits(rooms[RN_K], rooms[RN_H], NULL,NULL);
    rooms[RN_K]->setExits(NULL,rooms[RN_L], rooms[RN_J], NULL);
    rooms[RN_L]->setExits(NULL, rooms[RN_M], rooms[RN_H], rooms[RN_K]);
    rooms[RN_M]->setExits(rooms[RN_N], NULL,NULL, rooms[RN_L]);
    rooms[RN_N]->setExits(rooms[RN_P],rooms[RN_O] , rooms[RN_M], rooms[RN_S]);
    rooms[RN_O]->setExits(NULL,NULL,NULL, rooms[RN_N]);
    rooms[RN_P]->setExits(NULL, rooms[RN_Q], rooms[RN_N], rooms[RN_R]);
    rooms[RN_Q]->setExits(NULL,NULL,NULL, rooms[RN_P]);
    rooms[RN_R]->setExits(NULL, rooms[RN_P], NULL ,NULL);
    rooms[RN_R]->addItem(new Item("Key"));

    rooms[RN_S]->setExits(NULL, rooms[RN_N], rooms[RN_T], NULL);
    rooms[RN_T]->setExits(rooms[RN_S], NULL,NULL,NULL);
    //                   (N, E, S, W)



}

begin_room::~begin_room()
{
    delete ui;

    //TODO: free rooms from memory
    //for(int i=0;i<G_MAX_ROOMS;i++)
      //  rooms[i]->

}

void begin_room::loadImages(){
    string name;

   // name = QCoreApplication::applicationDirPath().toStdString();
   // name =QDir::current().path().toStdString();
   // name =QDir::current().absolutePath().toStdString();
    FILE *file = NULL;
    string pattern1 = ".jpg";
    //must copy all the images to this directory: C:\prj_kart\rooms
    string pattern2 = ".png";
    string pattern0 =  "C:\\prj_kart\\rooms\\"; //i tryed almost everything and googleed, but no better solution found.
    if(images.size() > 0) {
        for(int i=0;i<images.size();i++) {
            images[i].clear();
        }
    }
    images.clear();
    images.resize(I_MAX);

    for(int j=0;j<3;j++) {
        images[j].resize(G_MAX_ROOMS);
        int counter=0;
        for(char i='b' ;i<= 't'; i++,counter++) {
            switch (j) {
                case MAP:
                    // system("cmd");testing
                    name = pattern0+i+pattern2;
                   // file = fopen(name.c_str(),"r"); testing
                    images[j][counter] = QPixmap(QString(name.c_str()), 0, Qt::AutoColor);
                break;
                case BKG1:
                    name = pattern0+i+"1"+pattern1;
                    images[j][counter] = QPixmap(QString(name.c_str()), 0, Qt::AutoColor);
                    break;
                case BKG2:
                    name = pattern0+i+"2"+pattern1;
                    images[j][counter] = QPixmap(QString(name.c_str()), 0, Qt::AutoColor);
                    break;
            }
        }
    }

    images[DRAGON].resize(2);
    images[QUEEN].resize(2);
    images[SOLDIERA].resize(2);
    images[SOLDIERB].resize(2);
    images[SOLDIERC].resize(2);
    images[PLAYERS].resize(4);


    images[DRAGON][0] = QPixmap("C:/prj_kart/NPC/Dragon.png", 0, Qt::AutoColor);
    images[DRAGON][1] = QPixmap("C:/prj_kart/NPC/Dragon2.png", 0, Qt::AutoColor);
    images[QUEEN][0] = QPixmap("C:/prj_kart/NPC/Queen.png", 0, Qt::AutoColor);
    images[QUEEN][1] = QPixmap("C:/prj_kart/NPC/Queen2.png", 0, Qt::AutoColor);
    images[SOLDIERA][0] = QPixmap("C:/prj_kart/NPC/Soldier.png", 0, Qt::AutoColor);
    images[SOLDIERA][1] = QPixmap("C:/prj_kart/NPC/Soldier2.png", 0, Qt::AutoColor);
    images[SOLDIERB][0] = QPixmap("C:/prj_kart/NPC/SoldierB.jpg", 0, Qt::AutoColor);
    images[SOLDIERB][1] = QPixmap("C:/prj_kart/NPC/SoldierB2.jpg", 0, Qt::AutoColor);
    images[SOLDIERC][0] = QPixmap("C:/prj_kart/NPC/SoldierC.jpg", 0, Qt::AutoColor);
    images[SOLDIERC][1] = QPixmap("C:/prj_kart/NPC/SoldierC2.jpg", 0, Qt::AutoColor);
    images[PLAYERS][0] = QPixmap("C:/prj_kart/player/Melee2.png", 0, Qt::AutoColor);
    images[PLAYERS][1] = QPixmap("C:/prj_kart/player/Mage2.png", 0, Qt::AutoColor);
    images[PLAYERS][2] = QPixmap("C:/prj_kart/player/chris.jpg", 0, Qt::AutoColor);
    images[PLAYERS][3] = QPixmap("C:/prj_kart/player/Archer2.png", 0, Qt::AutoColor);

}

void begin_room::on_pushButton_9_clicked()
{
    intention = GETITEM;
}

void begin_room::on_pushButton_clicked()
{
    this->close();
}


void begin_room::on_northButton_clicked()
{
    //north
    go("north");
    //QMessageBox::information(NULL, "Hello World!", "Hi!");
}

void begin_room::on_southButton_clicked()
{
    //south
    go("south");


}

void begin_room::on_eastButton_clicked()
{
    //east
    go("east");
}

void begin_room::on_westButton_clicked()
{
    //west
    go("west");
}

void begin_room::go(string direction) {

    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL) {

    }
    else
    {
        currentRoom = nextRoom;
        ui->minimapLabel->setPixmap(images[MAP][currentRoom->getNumber()]);
        ui->currentRoomLabel->setPixmap(images[layer][currentRoom->getNumber()]);
        updateInventoryRoom(currentRoom->getInventory());
        char r = currentRoom->getNumber();
        switch(r) {
        case RN_B:

            break;
        case RN_C:

            break;
        case RN_D:

            break;
        case RN_E:

            break;
        case RN_F:
            doMiniGame(1);
            break;
        case RN_G:

            break;
        case RN_H:

            break;
        case RN_I:

            break;
        case RN_J:

            break;
        case RN_K:

            break;
        case RN_L:

            break;
        case RN_M:
            doMiniGame(0);
            break;
        case RN_N:
            doMiniGame(0);
            break;
        case RN_O:

            break;
        case RN_P:

            break;
        case RN_Q:

            break;
        case RN_R:

            break;
        case RN_S:

            break;
        case RN_T:

            break;
        }
    }
}

void begin_room::doMiniGame(int witch){
    if(witch == 0) {
        MiniGame1 * mini = new MiniGame1(this);
        mini->exec();
        while(!mini->getDone()) {
            QMessageBox::information(NULL, "Invelid Move!", "You must complete the minigame to proceed!");
            delete mini;
            mini = new MiniGame1(this);
            mini->exec();
        }
        delete mini;
    }
    else {
        Minigame2 * mini = new Minigame2(this);
        mini->exec();
        while(!mini->getDone()) {
            QMessageBox::information(NULL, "Invelid Move!", "You must complete the minigame to proceed!");
            delete mini;
            mini = new Minigame2(this);
            mini->exec();
        }
        delete mini;

    }

}

void begin_room::TESTchangePictures()
{
    index2++;
    if(index2 >= G_MAX_ROOMS) {
        index2=0;
        index++;
    }
    if(index >= I_MAX) {
        index2=0;
        index=0;
    }
    ui->minimapLabel->setPixmap(images[index][index2]);
}

void begin_room::on_pushButton_3_clicked()
{
    intention = DROPITEM;
}

void begin_room::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                delete widget;
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

void begin_room::updateInventoryDisplay(Inventory* inv){
    int size = ui->inventoryDisplay->count();

    clearLayout(ui->inventoryDisplay->layout(),true);
    size = inv->getSizeInv();
    for(int i=0; i < size ; i++) {
        QPushButton *newer = new QPushButton(inv->getItemAt(i)->getDescription().c_str(),this);
        connect(newer, SIGNAL(clicked()),this,SLOT(doIntentionalStuff()));
        ui->inventoryDisplay->addWidget(newer);
    }
}

void begin_room::updateInventoryRoom(Inventory *inv){
    int size = ui->inventoryDisplay->count();

    clearLayout(ui->inventoryRoom->layout(),true);
    size = inv->getSizeInv();
    for(int i=0; i < size ; i++) {
        QPushButton *newer = new QPushButton(inv->getItemAt(i)->getDescription().c_str(),this);
        connect(newer, SIGNAL(clicked()),this,SLOT(doIntentionalStuff()));
        ui->inventoryRoom->addWidget(newer);



    }
}

void begin_room::on_pushButton_4_clicked()
{
    intention = USESOMETHING;
}



void begin_room::on_dreamReality_clicked()
{
    if(layer == BKG2) { //dream
        ui->dreamReality->setText("Reality");
        setDarkGreyStyle();
        layer = BKG1;
        this->setWindowTitle("KART - Dream");
    }
    else { //reality
        setDarkGreyStyle();
        layer = BKG2;
        ui->dreamReality->setText("Dream");
        setLightGreyStyle();
        this->setWindowTitle("KART - Reality");
    }
    ui->currentRoomLabel->setPixmap(images[layer][currentRoom->getNumber()]);
}

void begin_room::on_pushButton_2_clicked()
{
    intention = EATFOOD;
}

void begin_room::doIntentionalStuff() {
    QMessageBox::information(NULL, "hi!", "hi!");

}
