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
class Wall : public MapSite {
public:
    Wall(){}
    virtual void Enter() override {}
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
class MazeBuilder {
public:
    virtual void BuildMaze() {}
    virtual void BuildRoom(int room) {}
    virtual void BuildDoor(int roomFrom, int roomTo) {}
    virtual Maze* GetMaze() { return 0; }

protected:
    MazeBuilder(){}
};
class StandardMazeBuilder : public MazeBuilder {
public:
    StandardMazeBuilder(){ _currentMaze = 0; }
    virtual void BuildMaze() override {
        _currentMaze = new Maze;
    }
    virtual void BuildRoom(int n) override {
        if (!_currentMaze->RoomNo(n)){
            Room* room = new Room(n);
            _currentMaze->AddRoom(room);
            room->SetSide(NORTH, new Wall);
            room->SetSide(EAST, new Wall);
            room->SetSide(SOUTH, new Wall);
            room->SetSide(WEST, new Wall);

        }
    }
    virtual void BuildDoor(int n1, int n2) override {
        Room* r1 = _currentMaze->RoomNo(n1);
        Room* r2 = _currentMaze->RoomNo(n2);
        Door* d = new Door(r1,r2);
        r1->SetSide(CommonWall(r1, r2), d);
        r2->SetSide(CommonWall(r2, r1), d);

    }

private:
    Direction CommonWall(Room* r1, Room* r2) {
        return EAST;
    }
    Maze* _currentMaze;
};
class MazeGame {
public:
    Maze* CreateMaze(MazeBuilder& builder) {
        builder.BuildMaze();
        builder.BuildRoom(1);
        builder.BuildRoom(2);
        builder.BuildDoor(1,2);
        return builder.GetMaze();
    }

};

int main() {
    Maze* maze;
    MazeGame game;
    StandardMazeBuilder builder;
    game.CreateMaze(builder);
    maze = builder.GetMaze();
}
