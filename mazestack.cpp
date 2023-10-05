//
//  mazestack.cpp
//  HW2
//
//  Created by Drew Wan on 4/29/23.
//


#include <stdio.h>
#include <iostream>
#include <stack>
using namespace std;



class Coord {
public:
  Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
  int r() const { return m_r; }
  int c() const { return m_c; }
//  void print() {
//      cout << m_r << " , " << m_c << endl;
//    }
private:
  int m_r;
  int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    stack<Coord> coordStack;
    
    Coord start(sr, sc);
    coordStack.push(start);
    maze[sr][sc] = ' ';
//    int i = 1;
    
    while (!coordStack.empty()) {
        //Pop top cord of stack to get current
        
        Coord curr = coordStack.top();
        
        coordStack.pop();
        
        if(curr.r() == er && curr.c() == ec) {
            return true;
        }
        
        if(maze[curr.r() + 1][curr.c()] == '.') {
            Coord currPoint(curr.r() + 1, curr.c());
            coordStack.push(currPoint);
            maze[curr.r() + 1][curr.c()] = ' ';
            
        }
        if(maze[curr.r()][curr.c() + 1] == '.') {
            Coord currPoint(curr.r(), curr.c() + 1);
            coordStack.push(currPoint);
            maze[curr.r()][curr.c() + 1] = ' ';
            
        }
        if(maze[curr.r() - 1][curr.c()] == '.') {
            Coord currPoint(curr.r() - 1, curr.c());
            coordStack.push(currPoint);
            maze[curr.r() - 1][curr.c()] = ' ';
            
        }
        if(maze[curr.r()][curr.c() - 1] == '.') {
            Coord currPoint(curr.r(), curr.c() - 1);
            coordStack.push(currPoint);
            maze[curr.r()][curr.c() - 1] = ' ';
            
        }
//        cout << i << ": ";
//        i++;
//        curr.print();

           
        
        
        
        
    }
    return false;
}




int main() {
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','X','.','.','.','.','X' },
        { 'X','.','.','X','X','.','X','X','.','X' },
        { 'X','.','X','.','.','.','.','X','X','X' },
        { 'X','X','X','X','.','X','X','X','.','X' },
        { 'X','.','.','X','.','.','.','X','.','X' },
        { 'X','.','.','X','.','X','.','.','.','X' },
        { 'X','X','.','X','.','X','X','X','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3,4, 8,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    
}



