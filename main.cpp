#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Gets the maze formatting 3x3 input
vector<vector<int>> getFormat(ifstream& file){
    vector<vector<int>> format(3, vector<int>(3)); 
    int number = 0;
    for (int j = 0; j < 3; j++){
        for (int i = 0; i < 3; i++){
            file >> number;
            file.ignore(1, ' ');
            format[i][j] = number;
        }
    }
    return format;
}

//Get maze information, formats to l x r x c
vector<vector<vector<string>>> initializeMaze(ifstream& file, vector<vector<int>> format){
    vector<vector<vector<string>>> maze(format[0][0], vector<vector<string>>(format[2][0], vector<string>(format[1][0], ""))); 

    string number = "";
    for (int k = 0; k < format[0][0]; k++){
        for (int j = 0; j < format[2][0]; j++){
            for (int i = 0; i < format[1][0]; i++){
                file >> number;
                maze[k][i][j] = number;
            }
        }
    }
    return maze;
}

//Gets the indices of all the cell's possible next moves
vector<int> getIndices(string input){
    vector<int> indices;
    for(size_t i = 0; i < input.size(); i++){
        if(input.substr(i, 1) == "1"){
            indices.emplace_back(i);
        }
    }
    return indices;
}

//This converts the move/direction to its associated character counterpart
string convertMove(int move){
    if(move == 0){
        return "N";
    }
    else if(move == 1){
        return "E";
    }
    else if(move == 2){
        return "S";
    }
    else if(move == 3){
        return "W";
    }
    else if(move == 4){
        return "U";
    }
    else if(move == 5){
        return "D";
    }
    else return ":(";
}

//move the "spider" based on input move and current cell location
vector<int> moveCurrent(int move, vector<int> current){
    if(move == 0){
        current[2] -= 1;
    }
    else if(move == 1){
        current[1] += 1;
    }
    else if(move == 2){
        current[2] += 1;
    }
    else if(move == 3){
        current[1] -= 1;
    }
    else if(move == 4){
        current[0] += 1;
    }
    else if(move == 5){
        current[0] -= 1;
    }
    return current;
}

//Recursive DFS + Backtracking function, returns 1 as true and 0 as false. Backtracks when a call returns false.
int DFS(vector<int> current, vector<vector<vector<string>>> maze, vector<int> goal, vector<vector<vector<int>>>& discovered, vector<string>& path, string moveused){
    
    discovered[current[0]][current[1]][current[2]] = 1;
    
    path.push_back(moveused);

    if (current == goal){
        return 1;
    }

    vector<int> children = getIndices(maze[current[0]][current[1]][current[2]]);

    for(size_t i = 0; i < children.size(); i++){
        vector<int> child = moveCurrent(children[i], current);
        if (discovered[child[0]][child[1]][child[2]] != 1){
            if (DFS(child, maze, goal, discovered, path, convertMove(children[i])) == 1) return 1;
        }
    }
    path.pop_back();
    return 0;
}

//Driver code, opens files, initializes the maze and its format, calls the DFS functions and puts the output in the output.txt file
int main(){

    ifstream file("input.txt");
    ofstream output("output.txt");

    int mazes = 0;
    file >> mazes;

    
    if (file.is_open()){
        for (int i = 0;i < mazes; i++){
            vector<vector<int>> format = getFormat(file);
            vector<vector<vector<string>>> maze = initializeMaze(file, format);

            vector<int> start = {format[0][1],format[1][1], format[2][1]};
            vector<int> goal = {format[0][2],format[1][2], format[2][2]};
            vector<vector<vector<int>>> discovered(format[0][0], vector<vector<int>>(format[1][0],vector<int>(format[2][0], 0)));
            
            vector<string> answer;

            DFS(start, maze, goal, discovered, answer, "");    

            output << "Maze " << i+1 << ": ";

            for (size_t i = 1; i < answer.size(); i++){
                output << answer[i] << " ";
            }
            output << "\n";
        }
        output.close();
    }
    else{
        cout << "Unable to open file";
        return -1;
    }

    file.close();
    
    return 0;
}