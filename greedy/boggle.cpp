#include <iostream>
#include <optional>
#include <algorithm>
#include <deque>
#include <set>
#include <vector>

bool visited[8][8];

bool boggle(int xPos, int yPos, const std::vector<std::vector<char> >& board, const std::string& str, int strIdx)
{
    if(strIdx == str.size())
        return true;

    visited[yPos][xPos] = true;

    bool found = false;
    for(int xIdx = -1; xIdx < 2; ++xIdx)
        for(int yIdx = -1; yIdx < 2; ++yIdx)
        {
            if((xIdx != 0 || yIdx != 0) && !found)
            {
                int curXPos = xPos + xIdx;
                int curYPos = yPos + yIdx;

                if(curXPos >= 0 && curXPos < board.size() && curYPos >= 0 && curYPos < board.size() && visited[curYPos][curXPos] == false)
                {
                    char curLetter = board[curYPos][curXPos];

                    if(board[curYPos][curXPos] == 'q')
                    {
                        if(str[strIdx] == 'q' && str[strIdx + 1] == 'u' && strIdx + 1 < str.size())
                            found = boggle(curXPos, curYPos, board, str, strIdx+2);
                    }
                    else
                    {
                        if(str[strIdx] == board[curYPos][curXPos])
                            found = boggle(curXPos, curYPos, board, str, strIdx+1);
                    }  
                }
            }

        }

    visited[yPos][xPos] = false;
    return found;
}

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(nullptr);
    for(int i =0; i < 8; ++i)
        for(int j=0; j < 8; ++j)
            visited[i][j] = false;

    int numWords;
    int boardSize;
    std::cin>>numWords;

    std::set<std::string> dict;
    
    for(int i =0; i < numWords; ++i)
    {
        std::string word;
        std::cin>>word;
        dict.insert(word);
    }

    std::set<std::string> foundStr;
    std::cin>>boardSize;

    while(boardSize > 0)
    {
        std::vector<std::vector<char> > board(boardSize, std::vector<char>(boardSize, 0));
        
        for(int i =0; i < boardSize; ++i)
        {
            std::string boardStr;
            std::cin >> boardStr;
            for(int j = 0; j < boardSize; ++j)
            {
                board[i][j] = boardStr[j];
            }
        }

        for(const auto& str : dict)
        {
            bool found = false;
            for(int i = 0; i < boardSize; ++i)
                for(int j =0; j < boardSize; ++j)
                {
                    
                    if(board[i][j] == 'q' && found == false)
                    {
                        if(str.size() > 1 && str[0] == 'q' && str[1] == 'u')
                            if(boggle(j, i, board, str, 2))
                            {
                                foundStr.insert(str);
                                found = true;
                            }

                    }
                    else if(board[i][j] == str[0] && found == false)
                    {
                        if(boggle(j, i, board, str, 1))
                        {
                            foundStr.insert(str);
                            found = true;
                        }
                    }
                }
        }

        for(auto str : foundStr)
            std::cout<<str<<"\n";
        std::cout<<"-\n";
        foundStr.clear();
        std::cin>>boardSize;
    }
    return 0;

}
