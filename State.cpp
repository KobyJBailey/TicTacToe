#include "State.h"
#include <math.h>
#include <iostream>
using namespace std;

State::State() {
    board = new vector<vector<char>*>();
    depth = 0;
    for(int i = 0; i < 3; i++) {
        vector<char>* newRow = new vector<char>();
        for(int j = 0; j < 3; j++) {
            newRow->push_back('-');
        }
        board->push_back(newRow);
    }
}

State::State(vector<vector<char>*> prevBoard, int i, int j, char piece, int parDepth) {
    board = new vector<vector<char>*>();
    for(int i = 0; i < prevBoard.size(); i++) {
        vector<char>* newRow = new vector<char>();
        for(int j = 0; j < prevBoard[i]->size(); j++) {
            newRow->push_back(prevBoard[i]->at(j));
        }
        board->push_back(newRow);
    }
    board->at(i)->at(j) = piece;
    depth = parDepth + 1;
}

State::~State() {
    delete board;
    board = nullptr;
}

vector<State*>* State::ProduceNextMoves(bool player) {
    vector<State*>* nextMoves = new vector<State*>();
    char piece;
    if(player) {
        piece = 'O';
    }
    else {
        piece = 'X';
    }
    int parDepth = depth;
    for(int i = 0; i < board->size(); i++) {
        for(int j = 0; j < board->at(i)->size(); j++) {
            char currSpace = board->at(i)->at(j);
            if(currSpace == '-') {
                State* potentialMove = new State(*board, i, j, piece, parDepth);
                nextMoves->push_back(potentialMove);
            }
        }
    }
    
    return nextMoves;
}

void State::PrintState() {
    for(int i = 0; i < board->size(); i++) {
        for(int j = 0; j < board->at(i)->size(); j++) {
            cout << board->at(i)->at(j) << " ";
        }
        cout << endl;
    }
}

double State::ComputeCost(string gameState) {
    if(gameState[0] == 'X') {
        return 1-0.1*depth;
    }
    if(gameState[0] == 'O') {
        return -1+0.1*depth;
    }
    return 0;
}

int State::GetDepth() {
    return depth;
}

void State::SetDepth(int d) {
    depth = d;
}

void State::AddPiece(char piece, char row, char col) {
    int rowNum;
    switch (row) {
        case 'A':
        rowNum = 0;
        break;
        case 'B':
        rowNum = 1;
        break;
        case 'C':
        rowNum = 2;
        break;
    }

    int colNum;
     switch (col) {
        case '1':
        colNum = 0;
        break;
        case '2':
        colNum = 1;
        break;
        case '3':
        colNum = 2;
        break;
    }

    board->at(rowNum)->at(colNum) = piece;
}

bool State::IsRowEqual(int rowNum) {
    char piece = board->at(rowNum)->at(0);
    if(piece == '-') {
        return false;
    }
    for(int i = 0; i < board->size(); i++) {
        if(board->at(rowNum)->at(i) != piece) {
            return false;
        }
    }
    return true;
}

bool State::IsColumnEqual(int colNum) {
    char piece = board->at(0)->at(colNum);
    if(piece == '-') {
        return false;
    }
    for(int i = 0; i < board->size(); i++) {
        if(board->at(i)->at(colNum) != piece) {
            return false;
        }
    }
    return true;
}

bool State::IsDiagonal1Equal() {
    char piece = board->at(0)->at(0);
    if(piece == '-') {
        return false;
    }
    for(int i = 0; i < board->size(); i++) {
        if(board->at(i)->at(i) != piece) {
            return false;
        }
    }
    return true;
}

bool State::IsDiagonal2Equal() {
    int boardSize = board->size();
    char piece = board->at(0)->at(boardSize-1);
    if(piece == '-') {
        return false;
    }
    for(int i = 0; i < boardSize; i++) {
        if(board->at(i)->at((boardSize-1)-i) != piece) {
            return false;
        }
    }
    return true;
}

bool State::NoMoreMoves() {
    for(int i = 0; i < board->size(); i++) {
        for(int j = 0; j < board->at(i)->size(); j++) {
            if(board->at(i)->at(j) == '-') {
                return false;
            }
        }
    }
    return true;
}

bool State::GameEnd(string& gameState) {
    int boardSize = board->size();
    char winningPiece;
    for(int i = 0; i < boardSize; i++) { //Check Rows
        if(IsRowEqual(i)) {
            winningPiece = board->at(i)->at(0);
            gameState.push_back(winningPiece);
            gameState += " wins!";
            return true;
        }
    }
    
    for(int i = 0; i < boardSize; i++) { //Check Columns
        if(IsColumnEqual(i)) {
            winningPiece = board->at(0)->at(i);
            gameState.push_back(winningPiece);
            gameState += " wins!";
            return true;
        }
    }

    if(IsDiagonal1Equal()) { //Check Diagonal from left to right
        winningPiece = board->at(0)->at(0);
        gameState.push_back(winningPiece);
        gameState += " wins!";
        return true;
    }

    if(IsDiagonal2Equal()) { //Check Diagonal from right to left
        winningPiece = board->at(0)->at(boardSize-1);
        gameState.push_back(winningPiece);
        gameState += " wins!";
        return true;
    }

    if(NoMoreMoves()) {
        gameState = "Draw";
        return true;
    }

    return false;

}

// bool operator==(State& lhs, State& rhs) {
//     for(int i = 0; i < lhs.stacks->size(); i++) {
//         if(rhs.stacks->size() > i) {
//             if(*rhs.stacks->at(i) != *lhs.stacks->at(i)) {
//                 return false;
//             }
//         }
//         else {
//             return false;
//         }
//     }
//     return true;
// }