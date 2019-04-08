#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;
class Spell {
public:
    Spell() {
        int n = rand()%10;
        for (int i = 0; i < n; ++i) {
            curse.insert(curse.end(), static_cast<char>('0' + rand()%10));
        }
    }
private:
    string curse;
};
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
    MapSite* GetSite(Direction d) const {
        return _sides[d];
    }
    void SetSide(Direction d, MapSite* m){
        _sides[d] = m;
    }
    virtual void Enter() override {}
protected:
    MapSite* _sides[4];
    int _roomNumber;
};
class EnchantedRoom : public Room {
public:
    EnchantedRoom(int roomNo, Spell* s) : Room(roomNo), _spell(s){}
protected:
    Spell* _spell;
};
class Wall : public MapSite {
public:
    Wall(){}
    virtual void Enter() override {}
};
class Door : public MapSite {
public:
    Door(Room* r1 = 0, Room* r2 = 0){
        _room1 = r1;
        _room2 = r2;
    }
    virtual void Enter() override {}
    Room* OtherSideFrom(Room* r){
        if (r == _room2) return _room1;
        else return _room2;
    }

protected:
    Room* _room1;
    Room* _room2;
    bool isOpen;
};
class DoorNeedingSpell : public Door {
public:
    DoorNeedingSpell(Room* r1, Room* r2) : Door(r1,r2){}
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
        Maze* aMaze = MakeMaze();
        Room* r1 = MakeRoom(1);
        Room* r2 = MakeRoom(2);
        Door* aDoor = MakeDoor(r1,r2);
        aMaze->AddRoom(r1);
        aMaze->AddRoom(r2);
        r1->SetSide(NORTH, MakeWall());
        r1->SetSide(EAST, aDoor);
        r1->SetSide(SOUTH, MakeWall());
        r1->SetSide(WEST, MakeWall());

        r2->SetSide(NORTH, MakeWall());
        r2->SetSide(EAST, MakeWall());
        r2->SetSide(SOUTH, MakeWall());
        r2->SetSide(WEST, aDoor);

        return aMaze;
    }

    virtual Maze* MakeMaze() const { return new Maze;}
    virtual Room* MakeRoom(int n) const {return new Room(n);}
    virtual Wall* MakeWall() const {
        return new Wall;
    }
    virtual Door* MakeDoor(Room* r1, Room* r2) const {return new Door(r1,r2);}

};

class EnchanedMazeGame : public MazeGame {
public:
    EnchanedMazeGame(){}
    virtual Room* MakeRoom(int n) const {
        return new EnchantedRoom(n, new Spell());
    }
    virtual Door* MakeDoor(Room *r1, Room *r2) const {
        return new DoorNeedingSpell(r1, r2);
    }
};

int main() {
    EnchanedMazeGame mg;
    Maze* m = mg.CreateMaze();
}
