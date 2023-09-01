/*
 * Przepraszam niestety niedoczytalem i od razu zaczalem prace nad koncowa aplikacja. ;//
 *
 * Autor: Igor Jarosz
*/

#include <bits/stdc++.h>

using namespace std;

enum FieldType { AIR, SAND, WALL, INLET };


class Field {
public:
    Field() : type(AIR) {}
    explicit Field(FieldType type) : type(type) {}

    void print_field() {
        switch (type) {
            case AIR:
                cout << ".";
                break;
            case SAND:
                cout << "o";
                break;
            case WALL:
                cout << "#";
                break;
            case INLET:
                cout << "+";
                break;
        }
        cout << " ";
    }

    FieldType getType() {
        return type;
    }

    void setType(FieldType t) {
        this->type = t;
    }

private:
    FieldType type;
};


class GameMap {
public:
    GameMap(int width, int height) : width(width), height(height) {
        sandMap.resize(height, vector<Field>(width));
        inletX = 0;
        inletY = 0;
    }

    void runSimulation() {
        int sandCount = 0;

        while (moveSand()) {
            sandCount++;
        }

        displayMap();
        cout << "Liczba ziarenek: " << sandCount << endl;
    }

    void addWall(int x1, int y1, int x2, int y2) {
        for (int y = y1; y <= y2; y++) {
            for (int x = x1; x <= x2; x++) {
                if (isInMap(x, y)) {
                    sandMap[y][x].setType(WALL);
                }
            }
        }
    }

    bool moveSand() {
        int x = inletX;
        int y = inletY;

        while (true) {
            if (!isInMap(x, y-1)) {
                return false;
            } else if (isAir(x, y-1)) {
                --y;
                continue;
            }

            if (!isInMap(x+1, y-1)) {
                return false;
            } else if (isAir(x+1, y-1)) {
                ++x;
                --y;
                continue;
            }

            if (!isInMap(x-1, y-1)) {
                return false;
            } else if (isAir(x-1, y-1)) {
                --x;
                --y;
                continue;
            }

            if (x != inletX || y != inletY) {
                sandMap[y][x].setType(SAND);
                return true;
            } else {
                return false;
            }

        }
    }

    void addInlet(int x, int y) {
        if (isInMap(x, y)) {
            sandMap[y][x].setType(INLET);
            inletX = x;
            inletY = y;
        }
    }

    void displayMap() {
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                sandMap[y][x].print_field();
            }
            cout << endl;
        }
    }

private:
    int width;
    int height;
    int inletX;
    int inletY;
    vector<vector<Field>> sandMap;

    bool isInMap(int x, int y) {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    bool isAir(int x, int y) {
        return sandMap[y][x].getType() == AIR;
    }
};


void run() {
    int width, height;
    cin >> width >> height;

    GameMap gameMap(width, height);

    while (true) {
        char option;
        cin >> option;
        if (option == 's')
            break;

        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        gameMap.addWall(x1, y1, x2, y2);
    }

    int startX, startY;
    cin >> startX >> startY;
    gameMap.addInlet(startX, startY);

    gameMap.runSimulation();
}


int main() {
    run();
    return 0;
}