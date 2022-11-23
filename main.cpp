#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

//DEBUG FUNCTIONS

void printFile(ifstream &file){

    string line;
    if (file.is_open()){
        while ( getline(file, line)){
            cout << line << '\n';
        }
        file.close();
    }

}

void printFormat(vector<vector<int>> format){
    for (int a = 0;a < 3; a++){
        for (int b = 0; b < 3; b++){
            cout << format[b][a] << " ";
        }
        cout << endl;
    }
}

void printMaze(vector<vector<vector<string>>> maze){
        for (int k = 0; k < 5; k++){
            for (int j = 0; j < 4; j++){
                for (int i = 0; i < 4; i++){
                    cout << maze[k][i][j] << " ";
                }
                cout << endl;
            }    
            cout << endl;
        }
}

//

class Maze{
    vector<int> dimensions;
    vector<int> start;
    vector<int> goal;

    vector<int> current;

    vector<vector<int>> getFormat(ifstream& file);

    vector<vector<vector<string>>> initializeMaze(ifstream& file, vector<int>& dimensions, vector<int>& start, vector<int>& goal);

    void moveCurrent(int move, vector<int>& current);

};

//Gets formatting 3x3 input
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

//Get next move indices of maze cell
vector<int> getIndices(string input){
    vector<int> indices;
    for(size_t i = 0; i < input.size(); i++){
        if(input.substr(i, 1) == "1"){
            indices.emplace_back(i);
        }
    }
    return indices;
}

//move current maze based on input "move" and current location
vector<int> moveCurrent(int move, vector<int>& current){
    vector<int> destination;
    cout << "Moving: " << current[0] << ", " << current[1] << ", " << current[2] << endl;
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
    cout << "Moved to: " << current[0] << ", " << current[1] << ", " << current[2]<< endl;
    destination = current;
    return destination;
}

//find path from start coordinates to goal coordinates
vector<string> solve(vector<vector<int>> format, vector<vector<vector<string>>> maze){
    vector<int> current(3);
    vector<int> start(3);
    vector<int> goal(3);

    vector<vector<vector<int>>> discovered(format[0][0], vector<vector<int>>(format[1][0],vector<int>(format[2][0], 0)));



    vector<string> answer(format[0][0]*format[1][0]*format[2][0]);


    for (int i = 0; i < 3; i++){
        current[i] = format[i][1];
        start[i] = format[i][1];
        goal[i] = format[i][2];
    }

    stack<vector<int>> childrenStack;

    while (current != goal || childrenStack.empty()){
        int option = maze[current[0]][current[1]][current[2]].find('1', 0);

        vector<int> children = getIndices(maze[current[0]][current[1]][current[2]]);

        cout << option << endl;

        if(discovered[current[0]][current[1]][current[2]] == 1){
                continue;
         }

        for (size_t i = children.size(); i > 0;i--){
            if (discovered[current[0]][current[1]][current[2]] == 0){
                discovered[current[0]][current[1]][current[2]] = 1;
                childrenStack.push(moveCurrent(i, current));
            }
        }

        // if(discovered[current[0]][current[1]][current[2]] == 0){
        //     discovered[current[0]][current[1]][current[2]] = 1;
        //     // option = maze[current[0]][current[1]][current[2]].find('1');
        //     moveCurrent(option, current);
        //     cout << option << endl;
        // }
        // else if(discovered[current[0]][current[1]][current[2]] == 1){
        //     moveCurrent(option, current);
        //     int newOption = maze[current[0]][current[1]][current[2]].find('1', option+1);
        //     moveCurrent(newOption, current);
        //     cout << option << endl;
        // }

    }
    return answer;
}

//read file, run solve, return output
int main(){

    ifstream file("input.txt");

    vector<vector<int>> format = getFormat(file);

    printFormat(format);

    vector<vector<vector<string>>> maze = initializeMaze(file, format);
    
    printMaze(maze);

    vector<int> current(3);

    vector<int> indices = getIndices("010001"); 

    for (size_t i = 0; i< indices.size(); i++){
        cout << indices[i] << endl;
    }

    // vector<string> answer = solve(format, maze);

    file.close();

    return 0;
}