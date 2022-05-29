#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include <stack>
#include <string>

class State {
    public:
    State();
    State(std::vector<std::vector<char>*> prevBoard, int i, int j, char piece, int parDepth);
    ~State();
    std::vector<State*>* ProduceNextMoves(bool player);
    void PrintState();
    double ComputeCost(std::string gameState);
    int GetDepth();
    void SetDepth(int d);
    void AddPiece(char piece, char row, char col);
    bool IsColumnEqual(int colNum);
    bool IsRowEqual(int rowNum);
    bool IsDiagonal1Equal();
    bool IsDiagonal2Equal();
    bool NoMoreMoves();
    bool GameEnd(std::string& gameState);
    //friend bool operator==(State& lhs, State& rhs);
    private:
        std::vector<std::vector<char>*>* board;
        int depth;
};

#endif