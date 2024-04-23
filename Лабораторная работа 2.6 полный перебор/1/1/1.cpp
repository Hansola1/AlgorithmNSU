#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class Field {
public:
    int line, columns;
    std::vector<std::vector<char>> table;

    Field(int linesVal, int columnsVal, std::vector<std::vector<char>>& tableVal) : line(linesVal), columns(columnsVal), table(tableVal)
    {}  

    bool OnRules(int row, int col)
    {
        for (int i = 0; i < columns; i++) 
        {
            if (table[row][i] == 'X') return false;
        }
        for (int i = 0; i < line; i++)
        {
            if (table[i][col] == 'X') return false;
        }

        std::vector<std::vector<int>> tendenc
        {
            {-1, -1}, {-1, 1}, {1, -1},{1, 1}
        };

        for (int i = 0; i < tendenc.size(); i++)
        {
            int x = row + tendenc[i][0]; // 0 - x, y - 1
            int y = col + tendenc[i][1];

            while (x >= 0 && x < line && y >= 0 && y < columns)
            {
                if (table[x][y] == 'X') return false;

                x += tendenc[i][0];
                y += tendenc[i][1];
            }
        }
        return true;
    }

    bool pushQueens(int row)
    {
        if (row == line) return true;

        for (int col = 0; col < columns; col++)
        {
            if (table[row][col] == '?' && OnRules(row, col)) 
            {
                table[row][col] = 'X';
                if (pushQueens(row + 1)) 
                {
                    return true;
                }

                table[row][col] = '?'; //'.';
            }
        }
        return false;
    }

    void IsPlaced(std::ofstream& outputFile)
    {
        if (pushQueens(0))
        {
            outputFile << "YES" << std::endl;
            for (int i = 0; i < line; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    if (table[i][j] == 'X')
                    {
                        outputFile << "X";
                    }
                    else
                    {
                        outputFile << ".";
                    }
                }
                outputFile << std::endl;
            }
        }
        else
        {
            outputFile << "NO" << std::endl;
        }
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int lines, columns;
    inputFile >> lines >> columns;

    std::vector<std::vector<char>> table(lines, std::vector<char>(columns));
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            inputFile >> table[i][j];
        }
    }

    Field field(lines, columns, table);
    field.IsPlaced(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}