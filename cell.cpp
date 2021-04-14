//
// Created by Neron on 10/4/2021.
//

#include "cell.h"

cell::cell() {

}

void cell::setState(char new_state) {
    this->state = new_state;
}

cell::cell(int x, int y, char state) {
    this->x = x;
    this->y = y;
    this->state = state;
}
