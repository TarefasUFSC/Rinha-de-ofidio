#include "gameenv.h"
#include <QPointF>
bool is_player_here(int x, int y, const Snake *player){

    for(BodyPart * part : player->myBody){
        if(part->pos().x() == x && part->pos().y() == y) return true;
    }
    return false;
}
bool am_i_there(int x, int y, const Snake * me){
    for(BodyPart * part : me->myBody){
        if(part->pos().x() == x && part->pos().y() == y) return true;
    }
    return false;
}
void GameEnv::agentBoss(Estado estado)
{
    int min = 0;
    QPointF head = enemy->myBody.at(0)->pos();
    for(size_t i = 0; i< estado.food.size();i++){
        QPointF pMin = estado.food.at(min)->pos();
        int minD = sqrt( pow(head.x() - pMin.x(),2)  + pow(head.y() - pMin.y(),2)  );
        QPointF p2 = estado.food.at(i)->pos();
        int dist = sqrt( pow(head.x() - p2.x(),2)  + pow(head.y() - p2.y(),2)  );
        if(dist < minD) min = i;
    }
    vector<string> possibleMoves = {"Left","Right","Up","Down"};
    string last = enemy->myBody.at(0)->lastAction;
    int pp = 0;

    for(size_t i= 0; i<possibleMoves.size();i++){
        if( enemy->isOpposite(possibleMoves.at(i)) ) {
            pp = i;
            break;
        }
    }
    possibleMoves.erase(possibleMoves.begin()+pp);
    // verifica left
    if(head.x() - 32 <= 32 || is_player_here(head.x()-32,head.y(),player)|| am_i_there(head.x()-32,head.y(),enemy)){
        pp = 0;
        //cout << "Sai left"<<endl;
        for(size_t i= 0; i<possibleMoves.size();i++){
            if(possibleMoves.at(i) == "Left") {
                pp = i;
                possibleMoves.erase(possibleMoves.begin()+pp);
                break;
            }
        }

    }
    // verifica right
    if(head.x() + 32 >= (704-32) || is_player_here(head.x()+32,head.y(),player)|| am_i_there(head.x()+32,head.y(),enemy)){
        //cout << "Sai right"<<endl;
        pp = 0;
        for(size_t i= 0; i<possibleMoves.size();i++){
            if(possibleMoves.at(i) == "Right") {
                pp = i;
                possibleMoves.erase(possibleMoves.begin()+pp);
                break;
            }
        }

    }
    // verifica up
    if(head.y() -32<= 32 || is_player_here(head.x(),head.y()-32,player)|| am_i_there(head.x(),head.y()-32,enemy)){
        pp = 0;
        //cout << "Sai up"<<endl;
        for(size_t i= 0; i<possibleMoves.size();i++){
            if(possibleMoves.at(i) == "Up") {
                pp = i;
                possibleMoves.erase(possibleMoves.begin()+pp);
                break;
            }
        }

    }
    // verifica down
    if(head.y() +32>= (704-32) || is_player_here(head.x(),head.y()+32,player)|| am_i_there(head.x(),head.y()+32,enemy)){
        pp = 0;
        //cout << "Sai down"<<endl;
        for(size_t i= 0; i<possibleMoves.size();i++){
            if(possibleMoves.at(i) == "Down") {
                pp = i;
                possibleMoves.erase(possibleMoves.begin()+pp);
                break;
            }
        }

    }
    if(possibleMoves.size()>0){
        int minM = 0;
        QPointF pMin = estado.food.at(min)->pos();
        int minD = 704*704;
        for(size_t i = 0;i<possibleMoves.size();i++){
            string move  = possibleMoves.at(i);
            //cout << move << ": ";
            int fX = head.x();
            int fY = head.y();
            if(move == "Left")
                fX = fX - 32;
            if(move == "Right")
                fX = fX + 32;
            if(move == "Up")
                fY = fY -32;
            if(move == "Down")
                fY = fY +32;
            int dist = sqrt( pow(fX - pMin.x(),2)  + pow(fY - pMin.y(),2)  );
            //cout << dist << " - ";
            if(dist < minD) {
                minM = i;
                minD = dist;
            }
        }

        //cout << " | "<<possibleMoves.at(minM)<< endl;
        enemy->move(possibleMoves.at(minM));
        return;
    }
    enemy->move("Up");
}
