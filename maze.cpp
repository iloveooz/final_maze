#include "maze.h"
#include<iostream>
#include<stack>
#include<time.h>
#include<cmath>

using namespace std;

void Maze::setWidth(int width)
{
    this->width=width;
}

void Maze::setHeight(int height)
{
    this->height=height;
}

void Maze::setCellSize(int size)
{
    cellSize=size;
    rows=height/cellSize;
    cols=width/cellSize;
}

void Maze::setNotVisitedCellColor(sf::Color color)
{
    notVisitedColor=color;
}

void Maze::setCurrentCellColor(sf::Color color)
{
    currentColor=color;
}

void Maze::setVisitedCellColor(sf::Color start, sf::Color end)
{
    this->start=start;
    this->end=end;
}

void Maze::setBorderColor(sf::Color color)
{
    borderColor=color;
}

void Maze::setBackgroundColor(sf::Color color)
{
    backgroundColor=color;
}

int Maze::neighbourExists(int x,int y,char dir)
{
  
    if(dir=='t' || dir=='b')
    {
        if(x<0 || x>((rows*cols)-1))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if(x<0 || x>((rows*cols)-1) || abs((y/cols)-(x/cols))!=0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

void Maze::checkNeighbour(int current)
{
     vector<char> direction;

    int top=neighbourExists(current-cols,current,'t');
    int right=neighbourExists(current+1,current,'r');
    int bottom=neighbourExists(current+cols,current,'b');
    int left=neighbourExists(current-1,current,'l');

    if(top && !checkBit(maze[current-cols],visitedMask))
    { 
        direction.push_back('t');
    }
    if(right && !checkBit(maze[current+1],visitedMask))
    {
        direction.push_back('r');
    }
    if(bottom && !checkBit(maze[current+cols],visitedMask))
    {
        direction.push_back('b');
    }
    if(left && !checkBit(maze[current-1],visitedMask))
    {
        direction.push_back('l');
    }

    if(direction.size()>0)
    {
        int randomNumber=rand()%direction.size();
        backtrack.push_back(current);

        if(direction[randomNumber]=='t')
        {
            turnOnBit(maze[current-cols],visitedMask);
            backtrack.push_back(current-cols);
            turnOffBit(maze[current],topMask);
            turnOffBit(maze[current-cols],bottomMask);
        }
        else if(direction[randomNumber]=='r')
        {
            turnOnBit(maze[current+1],visitedMask);
            turnOffBit(maze[current],rightMask);
            turnOffBit(maze[current+1],leftMask);
            backtrack.push_back(current+1);
        }
        else if(direction[randomNumber]=='b')
        {
            turnOnBit(maze[current+cols],visitedMask);
            turnOffBit(maze[current],bottomMask);
            turnOffBit(maze[current+cols],topMask);
            backtrack.push_back(current+cols);
        }
        else if(direction[randomNumber]=='l')
        {
            turnOnBit(maze[current-1],visitedMask);
            turnOffBit(maze[current],leftMask);
            backtrack.push_back(current-1);
            turnOffBit(maze[current-1],rightMask);
        }
    }
}

void Maze::dfsBacktrack()
{
    if(animate!=1)
    {
        while(!backtrack.empty())
        {
            int current=backtrack.back();
            backtrack.pop_back();

            checkNeighbour(current);
        }
    }
    else if(animate==1 && !backtrack.empty())
    {
        int current=backtrack.back();
        backtrack.pop_back();

        checkNeighbour(current);
    }
}

void Maze::handleBorder(int borderCounter,sf::Color borderColor,int x,int y,int value)
{
    int index;
    if(animate!=1)
    {
        index=(cols*x)+y;
    }
    else
    {
        index=value;
    }
    
    if(checkBit(maze[index],topMask))
    {
        border[borderCounter].color = this->borderColor;
        border[borderCounter+1].color = this->borderColor;
    }
    else
    {
        border[borderCounter].color =borderColor;
        border[borderCounter+1].color =borderColor;
    }    
    if(checkBit(maze[index],rightMask))
    {
        border[borderCounter+2].color = this->borderColor;
        border[borderCounter+3].color = this->borderColor;
    }
    else
    {
        border[borderCounter+2].color =borderColor;
        border[borderCounter+3].color = borderColor;
    }
    if(checkBit(maze[index],bottomMask))
    {
        border[borderCounter+4].color = this->borderColor;
        border[borderCounter+5].color = this->borderColor;
    }
    else
    {
        border[borderCounter+4].color =borderColor;
        border[borderCounter+5].color = borderColor;
    }
    if(checkBit(maze[index],leftMask))
    {
        border[borderCounter+6].color = this->borderColor;
        border[borderCounter+7].color = this->borderColor;
    }
    else
    {
        border[borderCounter+6].color = borderColor;
        border[borderCounter+7].color =borderColor;
    }
}

void Maze::createVertexArray(int explicitCheck)
{
    int padding=10;
    int counter=0;
    int borderCounter=0;

    float initial=1;
    float p=initial;
  
    if(explicitCheck!=1)
    {
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                quad[counter].position = sf::Vector2f((j*cellSize)+padding, (i*cellSize)+cellSize+padding);
                quad[counter+1].position = sf::Vector2f(j*cellSize+padding, i*cellSize+padding);
                quad[counter+2].position = sf::Vector2f((j*cellSize)+cellSize+padding, i*cellSize+padding);
                quad[counter+3].position = sf::Vector2f((j*cellSize)+cellSize+padding,(i*cellSize)+cellSize+padding);

                border[borderCounter].position = sf::Vector2f((j*cellSize)+padding,(i*cellSize)+padding);
                border[borderCounter+1].position = sf::Vector2f((j*cellSize)+cellSize+padding,i*cellSize+padding);
                border[borderCounter+2].position = sf::Vector2f((j*cellSize)+cellSize+padding,i*cellSize+padding);
                border[borderCounter+3].position = sf::Vector2f((j*cellSize)+cellSize+padding,(i*cellSize)+cellSize+padding);
                border[borderCounter+4].position = sf::Vector2f((j*cellSize)+cellSize+padding,(i*cellSize)+cellSize+padding);
                border[borderCounter+5].position = sf::Vector2f((j*cellSize)+padding,(i*cellSize)+cellSize+padding);
                border[borderCounter+6].position = sf::Vector2f((j*cellSize)+padding,(i*cellSize)+cellSize+padding);
                border[borderCounter+7].position = sf::Vector2f((j*cellSize)+padding,(i*cellSize)+padding);
            
                int visited=checkBit(maze[(cols*i)+j],visitedMask);
                if(!visited)
                {   
                    quad[counter].color = notVisitedColor;
                    quad[counter+1].color = notVisitedColor;
                    quad[counter+2].color = notVisitedColor;
                    quad[counter+3].color =notVisitedColor;
                }
                else
                {
                    sf::Color quadColor;
                    quadColor.r=(start.r*p)+(end.r*(1-p));
                    quadColor.g=(start.g*p)+(end.g*(1-p));
                    quadColor.b=(start.b*p)+(end.b*(1-p));

                    quad[counter].color = quadColor;
                    quad[counter+1].color = quadColor;
                    quad[counter+2].color = quadColor;
                    quad[counter+3].color =quadColor;

                    localBorderColor=quadColor;
                }

                if(!animate)
                {
                    handleBorder(borderCounter,localBorderColor,i,j,-1);
                }
                else
                {
                    handleBorder(borderCounter,borderColor,i,j,-1);
                }

                if((cols*i+j)==backtrack.back())   
                {
                    quad[counter].color = currentColor;
                    quad[counter+1].color =currentColor;
                    quad[counter+2].color = currentColor;
                    quad[counter+3].color =currentColor;
                }      

                counter=counter+4;
                borderCounter=borderCounter+8;
            }
            p=p-((initial/rows));
        }
    }
    else
    {
        if(!backtrack.empty())
        {
            float first=initial-(round(backtrack.back()/cols)) * (initial/rows);
            float second=1 - first;

            quadColor.r=(start.r*first)+(end.r*second);
            quadColor.g=(start.g*first)+(end.g*second);
            quadColor.b=(start.b*first)+(end.b*second);
            
            quad[(backtrack.back()*4)].color = quadColor;
            quad[(backtrack.back()*4)+1].color = quadColor;
            quad[(backtrack.back()*4)+2].color = quadColor;
            quad[(backtrack.back()*4)+3].color =quadColor;

            localBorderColor=quadColor;
            if(backtrack.size()>2)
            {
                handleBorder((backtrack.back()*8),localBorderColor,-1,-1,backtrack.back());

                first=initial-round((backtrack[backtrack.size()-2])/cols) * (initial/rows);
                second=1 -first;

                quadColor.r=(start.r*first)+(end.r*second);
                quadColor.g=(start.g*first)+(end.g*second);
                quadColor.b=(start.b*first)+(end.b*second);
            
                handleBorder((backtrack[(backtrack.size()-2)]*8),localBorderColor,-1,-1,backtrack[(backtrack.size()-2)]);
              
            }
        }
    }
}

void Maze::setAnimation(int animate)
{
    this->animate=animate;
}

void Maze::setFps(int fps)
{
    this->fps=fps;
}

void Maze::saveAsImage()
{
    float initial=1;
    float p=initial;

    sf::Image image;
    image.create((cols*cellSize)+(2*10),(rows*cellSize)+(2*10), backgroundColor);

    for(int x=0;x<rows;x++)
    {
        for(int y=0;y<cols;y++)
        {
            sf::Color quadColor;
            quadColor.r=(start.r*p)+(end.r*(1-p));
            quadColor.g=(start.g*p)+(end.g*(1-p));
            quadColor.b=(start.b*p)+(end.b*(1-p));

            for(int i=(y*cellSize)+10;i<=(y*cellSize)+10+cellSize;i++)
            {
                for(int j=(x*cellSize)+10;j<=(x*cellSize)+10+cellSize;j++)
                {
                    image.setPixel(i,j, quadColor);
                }
            }
            if(checkBit(maze[cols*x+y],topMask))
            {
                for(int i=(y*cellSize)+10;i<=(y*cellSize)+10+cellSize;i++)
                {
                    image.setPixel(i, (x*cellSize)+10, borderColor);
                }
            }
            if(checkBit(maze[cols*x+y],rightMask))
            {
                for(int i=(x*cellSize)+10;i<=(x*cellSize)+10+cellSize;i++)
                {
                    image.setPixel((y*cellSize)+10+cellSize,i, borderColor);
                }
            }
            if(checkBit(maze[cols*x+y],bottomMask))
            {
                for(int i=(y*cellSize)+10;i<=(y*cellSize)+10+cellSize;i++)
                {
                    image.setPixel(i,(x*cellSize)+10+cellSize, borderColor);
                }
            }
            if(checkBit(maze[cols*x+y],leftMask))
            {
                for(int i=(x*cellSize)+10;i<=(x*cellSize)+10+cellSize;i++)
                {
                    image.setPixel((y*cellSize)+10,i, borderColor);
                }
            }
        }
        p=p-(initial/rows);
    }
    if (!image.saveToFile("finally.png"))
        cout<<"unsuccessfull image saving";
    else
        cout<<"successful image save";

    maze.clear();
}

void Maze::drawWindow(string windowName)
{
      int padding=10;
      window.create(sf::VideoMode((cols*cellSize)+(2*padding),(rows*cellSize)+(2*padding)),windowName);
      
      if(animate)
      {
        window.setFramerateLimit(fps);
      }
      
      while(window.isOpen())
      {
          sf::Event event;
          while(window.pollEvent(event))
          {
              if(event.type==sf::Event::Closed)
              {
                  window.close();
              }
          }

          window.clear(backgroundColor);

            if(animate)
            {
                dfsBacktrack();
                createVertexArray(1);
                if(!backtrack.empty())
                {
                    quad[(backtrack.back()*4)].color = currentColor;
                    quad[(backtrack.back()*4)+1].color = currentColor;
                    quad[(backtrack.back()*4)+2].color = currentColor;
                    quad[(backtrack.back()*4)+3].color =currentColor;
                }
            }        

            window.draw(quad);
            window.draw(border);

            window.display();

        if(animate && !backtrack.empty())
        {
            quad[(backtrack.back()*4)].color = quadColor;
            quad[(backtrack.back()*4)+1].color = quadColor;
            quad[(backtrack.back()*4)+2].color = quadColor;
            quad[(backtrack.back()*4)+3].color =quadColor;
        }
      }
}

void Maze::initialize()
{
    maze.resize(rows*cols);
    quad.setPrimitiveType(sf::Quads);
    border.setPrimitiveType(sf::Lines);

    quad.resize(4*rows*cols);
    border.resize(8*rows*cols);
}

void Maze::createMaze(string windowName)
{
    srand(time(NULL));
    unsigned char initial=0b0000'1111;

    initialize();

    for(int i=0;i<rows*cols;i++)
    {
        maze[i]=initial;
    }

    turnOnBit(maze[0],visitedMask);
    backtrack.push_back(0);

    if(animate==-1)
    {
        dfsBacktrack();
        createVertexArray(-1);
        saveAsImage();
    }
    else if(animate==0)
    {
        dfsBacktrack();
        createVertexArray(-1);
        drawWindow(windowName);
        saveAsImage();
    }
    else if(animate==1)
    {
        createVertexArray(-1);
        drawWindow(windowName);
        saveAsImage();
    }

    maze.clear();
    vector<unsigned char>().swap(maze);
}