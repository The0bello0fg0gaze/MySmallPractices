#include<iostream>
#include<vector>
#include<queue>
using namespace std;
// BFS.cpp
class vector2D{
    public:
    int x;
    int y;
    vector2D* prev = nullptr;
    constexpr vector2D(int x, int y): x(x), y(y) {}

    vector2D operator+(vector2D other) const {
        return vector2D(this->x + other.x, this->y + other.y);
    }
    
    bool operator==(vector2D other) const{
        return (this->x == other.x && this->y == other.y);
    }
};

bool Visited(const vector<vector2D> visited, const vector2D pos);
bool InRange(const vector2D pos);



queue<vector2D> searched;

vector<vector<int>> map = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0}
    };
int rows = map.size();
int cols = map[0].size();

bool InRange(const vector2D pos){
    return ((pos.x < rows && 0 <= pos.x) && (pos.y < cols && 0 <= pos.y));
}
bool Visited(const vector<vector2D> visited, const vector2D pos){
    for(vector2D v: visited){
        if(v == pos){
            return true;
        }
    }
    return false;
}
void bfs(vector<vector2D> &visited,vector2D end){
    // Directions for moving in the grid (right, down, left, up)
    vector<vector2D> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    bool found = false;
    while(!searched.empty()){
        // Get the current position
        for(vector2D dir: directions){
            vector2D neighbour = searched.front() + dir;
            if (InRange(neighbour) && map[neighbour.x][neighbour.y] != 1 && !Visited(visited, neighbour)) {
                neighbour.prev = &searched.front(); // Set the previous node
                searched.push(neighbour);
                if(neighbour == end){
                    found = true;
                    visited.push_back(searched.front());
                    searched.pop();
                    cout << "Found the end at (" << neighbour.x << ", " << neighbour.y << ")" << endl;
                    break;
                }
            }
        }
        visited.push_back(searched.front());
        searched.pop();
    }
    if(!found){
            cout << "End not found" << endl;
    }
}

int main(){
    vector<vector2D> visited;
    searched.push({0,0});
    vector2D end = {4,4};
    bfs(visited,end);
    for(vector2D pos: visited){
        cout << "(" << pos.x << ", " << pos.y << ") "<< endl;
    }
    vector2D* prev = visited[visited.size()-1].prev;
    cout << "Previous: (" << visited[visited.size()-1].x << ", " << visited[visited.size()-1].y << ")" << endl;
    while(prev != nullptr){
        cout << "Previous: (" << prev->x << ", " << prev->y << ")" << endl;
        prev = prev->prev;
    }
    return 0;
}