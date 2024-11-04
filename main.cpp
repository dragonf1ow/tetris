#include "tetris.h"

int main(int argc, char** argv)
{
    std::srand(std::time(0));  	
    Tetris* tetris = new Tetris();  	
    tetris -> run();  	
    delete tetris;
    return 0;
}

