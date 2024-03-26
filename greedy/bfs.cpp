#include <deque>
#include <iostream>

//! matrix for 
int adjacentMatrix[10][10];
bool visited[10];


void bfs()
{
    std::deque<int> queue;
    queue.emplace_back(0);
    visited[0] = true;

    while(!queue.empty())
    {
        auto current = queue.front();
        queue.pop_front();
        visited[current] = true;
        std::cout<<"visited:" << current<<std::endl;

        
        for(int i = 0; i < 10; ++i)
        {
            if(adjacentMatrix[current][i] > 0 && visited[i] == false){
                queue.emplace_back(i);
            }
        }
    }
}

void main()
{
    for(int i =0; i < 10; ++i)
        for(int j = 0; j < 10; ++j)
        {
            char input[10];
            gets(input);
            adjacentMatrix[i][j] = atoi(input);
        }

    bfs();
}