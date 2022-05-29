//#include "Node.h"
#include "State.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <unordered_map>
#include <unistd.h>

//Player 1 = false = 'X'
//Player 2 = true = 'O'
using namespace std;
struct Pair {
    double value;
    State* action;
};

int numberNodesEval;
bool pruning = false;
vector<Pair> initialMoves;
int currMove = 1;

Pair MaxValue(State* currState, double alpha, double beta);
Pair MinValue(State* currState, double alpha, double beta);

string GetAction(string command) {
    string action;
    int firstSpace = command.find_first_of(' ');
    action = command.substr(0, firstSpace);
    action[0] = tolower(action[0]);
    return action;
}

void MoveInfo(string command, char& piece, char& row, char& col) {
    int firstSpace = command.find_first_of(' ');
    piece = toupper(command[firstSpace+1]);
    row = toupper(command[firstSpace+3]);
    col = toupper(command[firstSpace+5]);
}

State* MinimaxSearch(State* currState, char player) {
    State* nextMove;
    Pair pair;
    numberNodesEval = 0;
    if(player == 'X') {
        pair = MaxValue(currState, -100000, 100000);
        nextMove = pair.action;
    }
    else {
        pair = MinValue(currState, -100000, 100000);
        nextMove = pair.action;
    }
    cout << "Minimax score: " << pair.value << endl;
    return nextMove;
}

Pair MaxValue(State* currState, double alpha, double beta) {
    string gameState;
    Pair returnPair;
    Pair pair;
    if(currState->GameEnd(gameState)) {

        returnPair.value = currState->ComputeCost(gameState);
        returnPair.action = nullptr;
        return returnPair;
    }

    returnPair.value = -100000;
    vector<State *>* children = currState->ProduceNextMoves(false);
    for(int i = 0; i < children->size(); i++) {
        numberNodesEval++;
        pair = MinValue(children->at(i), alpha, beta);
        if(children->at(i)->GetDepth() == 1) {
            Pair init;
            init.value = pair.value;
            init.action = children->at(i);
            initialMoves.push_back(init);
        }
        if(pair.value > returnPair.value) {
            returnPair.value = pair.value;
            returnPair.action = children->at(i);

            if(pruning) {
                alpha = max(alpha, returnPair.value);
            }
        }
        if(pruning) {
            if(returnPair.value >= beta) {
                return returnPair;
            }
        }

    }

    return returnPair;
}

Pair MinValue(State* currState, double alpha, double beta) {
    string gameState;
    Pair returnPair;
    Pair pair;
    if(currState->GameEnd(gameState)) {
        returnPair.value = currState->ComputeCost(gameState);
        returnPair.action = nullptr;
        return returnPair;
    }
    returnPair.value = 100000;
    vector<State *>* children = currState->ProduceNextMoves(true);
    for(int i = 0; i < children->size(); i++) {
        numberNodesEval++;
        pair = MaxValue(children->at(i), alpha, beta);
        if(children->at(i)->GetDepth() == 1) {
            Pair init;
            init.value = pair.value;
            init.action = children->at(i);
            initialMoves.push_back(init);
        }
        if(pair.value < returnPair.value) {
            returnPair.value = pair.value;
            returnPair.action = children->at(i);

            if(pruning) {
                beta = min(beta, returnPair.value);
            }
        }
        if(pruning) {
            if(returnPair.value <= alpha) {
                return returnPair;
            }
        }
    }

    return returnPair;
}

int main(int argc, char **argv) {
    State* currState = new State();
    currState->PrintState();
    cout << "Welcome to Tic-Tac-Toe" << endl;
    string command;
    string gameState = "";

    while(!currState->GameEnd(gameState)) {
        cout << ">";
        getline(cin, command);
        string action = GetAction(command);
        if(action == "move") {
            char piece, row, col;
            MoveInfo(command, piece, row, col);
            currState->AddPiece(piece, row, col);
        }
        else if (action == "choose") {
            int firstSpace = command.find_first_of(' ');
            char player = toupper(command[firstSpace+1]);
            currState = MinimaxSearch(currState, player);
            currState->SetDepth(0);
            // for(int i = 0; i < initialMoves.size(); i++) {
            //     initialMoves[i].action->PrintState();
            //     cout << "mm_score: " << initialMoves[i].value << endl << endl;
            // }
            initialMoves.clear();
            cout << "Number of nodes evaluated: " << numberNodesEval << endl;
            currMove++;
        }
        else if(action == "pruning") {
            if(command.length() < 9) {
                cout << "Pruning on: " << pruning << endl;
            }
            else {
                int firstF = command.find_first_of('f');
                if(firstF == -1) { 
                    pruning = true;
                    cout << "Pruning on: " << pruning << endl;
                }
                else {
                    pruning = false;
                    cout << "Pruning on: " << pruning << endl;
                }
            }
        }
        else if(action == "reset") {
            delete currState;
            currState = new State();
        }
        else if(action == "show") {
            currState->PrintState();
        }
        else if(action == "quit") {
            return 0;
        }
        else {
            cout << "Invalid command" << endl;
            cout << "Valid commands are: " << endl;
            cout << "\tshow" << endl << "\treset" << endl << "\tmove piece(X,O) row(A,B,C) col(1,2,3)" << endl;
            cout << "\tchoose piece(X,Y)" << endl << "\tpruning optional(on|off)" << endl << "\tquit" << endl;

        }
        cin.clear();
        //currState->PrintState();
    }

    cout << gameState << endl;
    delete currState;
    currState = nullptr;


    

}