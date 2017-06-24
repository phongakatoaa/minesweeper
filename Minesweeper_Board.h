#ifndef BOARD_H

#include <iostream>
#include <vector>

enum TYPE {
    NOT_REVEALED = 1, MINE, BLANK
};

const int BOARD_WIDTH = 15;
const int BOARD_HEIGHT = 15;

bool inBoard( const int x, const int y ) {
    if ( x < 0 || x >= BOARD_WIDTH ) return false;
    if ( y < 0 || y >= BOARD_HEIGHT ) return false;
    return true;
}

class Block {
public:
    Block( const int _x = 0, const int _y = 0 );
    ~Block();
    void print() const;
    void changeState( const TYPE& t );
    void flag();
    void unflag();
    void select();
    void unselect();
    void reveal();
//========================================
    bool flagged;
    bool selected;
    bool revealed;
    TYPE type;
    int x, y;
};

Block::Block( const int _x, const int _y )
{
    type = NOT_REVEALED;
    flagged = false;
    x = _x;
    y = _y;
    selected = false;
    flagged = false;
    revealed = false;
    //std::cout << "block initialized" << std::endl;
}

Block::~Block()
{
    //std::cout << "block destroyed" << std::endl;
}

void Block::print() const
{
    std::cout << "type: " << type << "|" << " flagged: " << flagged << " selected: " << selected << " revealed: " << revealed << " |(" << x << "," << y << ")" << std::endl;
}

void Block::changeState( const TYPE& t )
{
    type = t;
}

void Block::flag()
{
    flagged = true;
}

void Block::unflag()
{
    flagged = false;
}

void Block::select()
{
    selected = true;
}

void Block::unselect()
{
    selected = false;
}

void Block::reveal()
{
    revealed = true;
}

class Board {
public:
    Board();
    ~Board();
    void print() const;
    void placeMines( const int& maximum_mines );
    Block    getSelectedBlock() const;
//==============================================================
    std::vector < std::vector < Block > > board;
    int selected_x;
    int selected_y;
    friend void selectBlock( Board& board, Control& control );
    friend void renderBoard( const Board& board );

};

int surroundMines( const Board& board, const int x, const int y );

Board::Board()
{
    std::cout << "board initialized" << std::endl;
    board.resize( BOARD_WIDTH, std::vector < Block > ( BOARD_HEIGHT ) );
    for ( int width = 0; width < BOARD_WIDTH; width++ ) {
        for ( int height = 0; height < BOARD_HEIGHT; height++ ) {
            board[width][height] = Block( width, height );
        }
    }
    selected_x = selected_y = 0;
    board[selected_x][selected_y].select();
}

Board::~Board()
{
    std::cout << "board destroyed" << std::endl;
}

void Board::print() const
{
    for ( int width = 0; width < BOARD_WIDTH; width++ ) {
        for ( int height = 0; height < BOARD_HEIGHT; height++ ) {
            board[width][height].print();
        }
    }
    std::cout << "selected block: " << "(" << selected_x << "," << selected_y << ")" << std::endl;
}

void Board::placeMines( const int& maximum_mines )
{
    int temp = 0;
    while ( temp < maximum_mines )
    {
        int mine_x = rand() % BOARD_WIDTH;
        int mine_y = rand() % BOARD_HEIGHT;
        if ( board[mine_x][mine_y].type != MINE ) {
            board[mine_x][mine_y].type = MINE;
            temp++;
        }
    }
}

Block Board::getSelectedBlock() const {
    return board[selected_x][selected_y];
}

void selectBlock( Board& board, Control& control ) {
    KEYS getKey[] = { D, W, A, S };
    int m_x[] = { 1, 0, -1, 0 };
    int m_y[] = { 0, -1, 0, 1 };
    for ( int temp = 0; temp < 4; temp++ ) {
        if ( control.getKey() == getKey[temp] ) {
            int new_selected_x = board.selected_x + m_x[temp];
            int new_selected_y = board.selected_y + m_y[temp];

            //std::cout << "(" << new_selected_x << "," << new_selected_y << ")" << std::endl;
            if ( !inBoard( new_selected_x, new_selected_y ) ) return;
            board.board[board.selected_x][board.selected_y].unselect();

            board.selected_x = new_selected_x;
            board.selected_y = new_selected_y;

            board.board[new_selected_x][new_selected_y].select();
            //board.getSelectedBlock().print();

            control.resetKey();
            return;
        }
    }
}

int surroundMines( const Board& board, const int x, const int y )
{
    int count = 0;
    int _x[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int _y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for ( int temp = 0; temp < 8; temp++ ) {
        int temp_x = x + _x[temp];
        int temp_y = y + _y[temp];
        if ( inBoard( temp_x, temp_y ) ) {
            if ( board.board[temp_x][temp_y].type == MINE ) count++;
        }
    }
    return count;
}

void expand( Board& board, const int x, const int y ) {
    if ( board.board[x][y].revealed ) return;
    if ( board.board[x][y].type != MINE ) {
        board.board[x][y].reveal();
        //board.board[x][y].type == BLANK;
    }
    int getSurroundMines = surroundMines( board, x, y );
    board.board[x][y].print();
    if ( getSurroundMines == 0 ) {
        int _x[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int _y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

        for ( int temp = 0; temp < 8; temp++ ) {
            int temp_x = x + _x[temp];
            int temp_y = y + _y[temp];
            if ( inBoard( temp_x, temp_y ) )
                expand( board, temp_x, temp_y );
        }
    }
    return;
}

void revealAllMines ( Board& board )
{
    for ( int width = 0; width < BOARD_WIDTH; width++ ) {
        for ( int height = 0; height < BOARD_HEIGHT; height++ ) {
            if ( board.board[width][height].type == MINE) board.board[width][height].reveal();
        }
    }
}
#endif // BOARD_H
