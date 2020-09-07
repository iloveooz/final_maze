#ifndef _MAZE_H_
#define _MAZE_H_

#define SFML_STATIC
#include "cell.h"
#include<stack>
#include<string>
#include<vector>
#include "SFML/Graphics.hpp"

using namespace std;

class Maze
{
    private:
        vector<unsigned char> maze;
        
        int width;
        int height;
        int cellSize;
        int rows;
        int cols;
        int animate;
        int fps;

        sf::Color start;
        sf::Color end;

        sf::Color notVisitedColor;
        sf::Color currentColor;
        sf::Color borderColor;
        sf::Color backgroundColor;
        sf::Color quadColor;
        sf::Color localBorderColor;
        
        sf::RenderWindow window;
        
        sf::VertexArray quad;
        sf::VertexArray border;
        
        vector<int> backtrack;

    public:
        void setAnimation(int animate);
        void setFps(int fps);
        void setVisitedCellColor(sf::Color start,sf::Color end);
        void setNotVisitedCellColor(sf::Color color);
        void setCurrentCellColor(sf::Color color);
        void setBorderColor(sf::Color color);
        void setBackgroundColor(sf::Color color);
        void setWidth(int width);
        void setHeight(int height);
        void setCellSize(int size);
        int neighbourExists(int x,int y,char dir);
        void checkNeighbour(int current);
        void dfsBacktrack();
        void initialize();
        void drawWindow(string windowName);
        void saveAsImage();
        void createMaze(string windowName);
        void handleBorder(int borderCounter,sf::Color borderColor,int x,int y,int value);
        void createVertexArray(int explicitCheck=-1);
};

#endif