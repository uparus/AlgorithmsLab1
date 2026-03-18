#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;


vector<vector<int>> generateField(int sizeX, int sizeY);
void placeShip(vector<vector<int>>& field, int shipLength);
bool canPlace(const vector<vector<int>>& field,int x, int y, int shipLength, bool horizontal);
void printField(const vector<vector<int>>& field);

void saveToFile(const vector<vector<int>>& field,const string& filename);
vector<vector<int>> loadFromFile(const string& filename,int& sizeX, int& sizeY);

int findShipLength(vector<vector<int>>& field,int x, int y);
vector<int> findShipsCount(vector<vector<int>>&field);
void printShipsCount(const vector<int>&ships);
bool validate(vector<int>& ships);


int main() {
    srand(time(0));
    int sizeX = 10;
    int sizeY = 10;
    vector<vector<int>>field = generateField(sizeX,sizeY);

    cout << "Generated field:\n";
    printField(field);
    saveToFile(field,"File.txt");

    field = loadFromFile("task4.txt",sizeX,sizeY);
    vector<int>ships = findShipsCount(field);
    printShipsCount(ships);

    if (validate(ships)) {
        cout << "Field from task 4.2 is valid" << "\n";
    }else {
        cout << "Field from task 4.2 is not valid" << "\n";
    }

    return 0;
}

void placeShip(vector<vector<int>>& field, int shipLength) {
    int sizeX = field.size();
    int sizeY = field[0].size();
    while (true) {
        int x = rand() % sizeX;
        int y = rand() % sizeY;
        bool horizontal = rand() % 2;

        if (canPlace(field,x,y,shipLength,horizontal)) {
            for (int i = 0; i < shipLength; i++) {
                int shipX = x + (horizontal ? 0 : i);
                int shipY = y + (horizontal ? i : 0);
                field[shipX][shipY] = 1;
            }
            return;
        }
    }
}
bool canPlace(const vector<vector<int>>& field,int x, int y, int shipLength, bool horizontal) {
    int sizeX = field.size();
    int sizeY = field[0].size();
    for (size_t i = 0; i < shipLength; i++) {
        int shipX = x + (horizontal ? 0 : i);
        int shipY = y + (horizontal ? i : 0);

        if (shipX < 0 || shipX >= sizeX || shipY < 0 || shipY >= sizeY) return false;
        if (field[shipX][shipY] == 1) return false;

        for (int diagX = -1; diagX <= 1; diagX++) {
            for (int diagY = -1; diagY <= 1; diagY++) {
                int coordX = shipX + diagX;
                int coordY = shipY + diagY;

                if (coordX >= 0 && coordX < sizeX && coordY >= 0 && coordY < sizeY) {
                    if (field[coordX][coordY] == 1) return false;
                }
            }
        }
    }
    return true;
}
vector<vector<int>> generateField(int sizeX, int sizeY) {
    vector<vector<int>> field(sizeX,vector<int>(sizeY,0));

    placeShip(field,4);
    for (int i = 0; i < 2; i++) placeShip(field,3);
    for (int i = 0; i < 3; i++) placeShip(field,2);
    for (int i = 0; i < 4; i++) placeShip(field,1);

    return field;
}
void printField(const vector<vector<int>>& field) {
    int sizeX = field.size();
    int sizeY = field[0].size();
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            cout << field[i][j] << "\t";
        }
        cout << endl;
    }
}

void saveToFile(const vector<vector<int>>& field,const string& filename) {
    ofstream fout(filename);
    fout << field.size() << " " << field[0].size() << endl;
    for (auto& row : field) {
        for (auto cell : row) {
            fout << cell << "\t";
        }
        fout << endl;
    }
}
vector<vector<int>> loadFromFile(const string& filename,int& sizeX, int& sizeY) {
    ifstream fin(filename);
    if (!fin.is_open()) cout << "File not found" << endl;

    fin >> sizeX >> sizeY;
    vector<vector<int>> field(sizeX,vector<int>(sizeY,0));
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            fin >> field[i][j];
        }
    }
    return field;
}

int findShipLength(vector<vector<int>>& field,int x, int y) {
    if (field[x][y] != 1) return 0;

    int sizeX = field.size();
    int sizeY = field[0].size();

    int count = 0;
    if (y + 1 < sizeY && field[x][y + 1] == 1) {
        int j = y;
        while (j < sizeY && field[x][j] == 1) {
            field[x][j] = -1;
            count++;
            j++;
        }
    }
    else if (x + 1 < sizeX && field[x + 1][y] == 1) {
        int i = x;
        while (i < sizeX && field[i][y] == 1) {
            field[i][y] = -1;
            count++;
            i++;
        }
    }
    else {
        field[x][y] = -1;
        count = 1;
    }

    return count;
}
bool validate(vector<int>& ships) {
    if (ships.size() != 5) return false;
    return ships[1] == 4 &&
        ships[2] == 3 &&
        ships[3] == 2 &&
        ships[4] == 1;
}
vector<int> findShipsCount(vector<vector<int>>& field) {
    vector<vector<int>> temp = field;

    int sizeX = temp.size();
    int sizeY = temp[0].size();
    vector<int> ships;

    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {

            if (temp[i][j] != 1) continue;
            if (j > 0 && temp[i][j-1] == 1) continue;
            if (i > 0 && temp[i-1][j] == 1) continue;

            int size = findShipLength(temp,i,j);
            if (size <= 0) continue;
            if(size >= ships.size()){
                ships.resize(size+1,0);
            }
            ships[size]++;
        }
    }
    return ships;
}
void printShipsCount(const vector<int>& ships) {
    for (int i = 1; i < ships.size(); i++) {
        if (ships[i] > 0)
            cout << "Ship with length " << i << ": " << ships[i] << endl;
    }
}
