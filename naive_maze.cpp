#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;
enum Direction {
    EAST,
    WEST,
    NORTH,
    SOUTH
};
class MapSite {
public:
    virtual void Enter() = 0;
};
class Room : public MapSite {
public:
    Room(int roomNo){
        _roomNumber = roomNo;
    }
    MapSite* GetSite(Direction d) const{
        return _sides[d];
    }
    void SetSide(Direction d, MapSite* m){
        _sides[d] = m;
    }
    virtual void Enter(){}
private:
    MapSite* _sides[4];
    int _roomNumber;
};
class Wall : public MapSite {
public:
    Wall(){}
    virtual void Enter() {}
};
class Door : public MapSite {
public:
    Door(Room* r1 = 0, Room* r2 = 0){
        _room1 = r1;
        _room2 = r2;
    }
    virtual void Enter(){}
    Room* OtherSideFrom(Room* r){
        if (r == _room2) return _room1;
        else return _room2;
    }

private:
    Room* _room1;
    Room* _room2;
    bool isOpen;
};
class Maze {
public:
    Maze(){
        _rooms.clear();
    }
    void AddRoom(Room* r){
        _rooms.push_back(r);
    }
    Room* RoomNo(int idx) const{
        if (idx >= _rooms.size()) return nullptr;
        return _rooms[idx-1];
    }

private:
    vector<Room*> _rooms;
};
class MazeGame {
public:
    Maze* CreateMaze() {
        Maze* aMaze = new Maze;
        Room* r1 = new Room(1);
        Room* r2 = new Room(2);
        Door* theDoor = new Door(r1,r2);
        aMaze->AddRoom(r1);
        aMaze->AddRoom(r2);
        r1->SetSide(NORTH, new Wall);
        r1->SetSide(EAST, theDoor);
        r1->SetSide(SOUTH, new Wall);
        r1->SetSide(WEST, new Wall);

        r2->SetSide(NORTH, new Wall);
        r2->SetSide(EAST, new Wall);
        r2->SetSide(SOUTH, theDoor);
        r2->SetSide(WEST, new Wall);

        return aMaze;
    }

};
int main() {
    MazeGame mg;
    Maze* m = mg.CreateMaze();
}
