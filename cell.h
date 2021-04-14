//
// Created by Neron on 10/4/2021.
//

/*
 * States:
 * 0 - Dead
 * 1 - Active
 */

#ifndef GRAPHICSAPP3_CELL_H
#define GRAPHICSAPP3_CELL_H


class cell {
private:
    int x{}, y{};
public:
    char state{};
    cell();
    cell(int, int, char);
    void setState(char state);

};


#endif //GRAPHICSAPP3_CELL_H
