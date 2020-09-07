// g++ -c main.cpp -o main.o -I"I:/SFML/include"
// g++ -c cell.cpp -o cell.o -I"I:/SFML/include"
// g++ -c maze.cpp -o maze.o -I"I:/SFML/include"

// g++ main.o maze.o cell.o -o main -L"I:/SFML/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lsfml-network-s -lwinmm -lopengl32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lws2_32 -lgdi32 -lkernel32 -luser32 -lwinspool -lshell32 -lole32 -luuid -lcomdlg32 -lfreetype -ladvapi32
//https://www.spoj.com/G7S91HC6/problems/main/sort=0,start=0

#include "Maze.h"

using namespace std;

int main()
{
    sf::Color grey(200,200,200);
    sf::Color start(255,45,80);
    sf::Color end(0,25,51);
    
    Maze maze;
    maze.setAnimation(-1);
    maze.setFps(0);
    maze.setWidth(1000);
    maze.setHeight(700);
    maze.setCellSize(3);
    maze.setBackgroundColor(grey);
    maze.setBorderColor(sf::Color::White);
    maze.setCurrentCellColor(sf::Color::Blue);
    maze.setNotVisitedCellColor(grey);
    maze.setVisitedCellColor(start,end);
   
    maze.createMaze("DFS Backtracking Maze");
  
    return 0;
}