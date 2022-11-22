#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


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

class Maze{
    vector<int> dimensions;
    vector<int> start;
    vector<int> goal;

    vector<int> current;

    vector<vector<int>> getFormat(ifstream& file);

    vector<vector<vector<string>>> initializeMaze(ifstream& file, vector<int>& dimensions, vector<int>& start, vector<int>& goal);

    void moveCurrent(int move, vector<int>& current);

};

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

void moveCurrent(int move, vector<int>& current){
    cout << "Moving: " << current[0] << ", " << current[1] << ", " << current[2] << endl;
    if(move == 0){
        current[2] += 1;
    }
    else if(move == 1){
        current[1] += 1;
    }
    else if(move == 2){
        current[2] -= 1;
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

}

vector<string> solve(vector<vector<int>> format, vector<vector<vector<string>>> maze){
    vector<int> current;
    vector<int> start;
    vector<int> goal;

    vector<vector<vector<int>>> discovered(format[0][0], vector<vector<int>>(format[1][0],vector<int>(format[2][0], 0)));

    vector<string> answer;


    for (int i = 0; i < 3; i++){
        current[i] = format[i][1];
        start[i] = format[i][1];
        goal[i] = format[i][2];
    }

    

    while (current != goal){
        int option = maze[current[0]][current[1]][current[2]].find('1');

        if(discovered[current[0]][current[1]][current[2]] == 0){
            option = maze[current[0]][current[1]][current[2]].find('1');
            moveCurrent(option, current);
        }
        else if(discovered[current[0]][current[1]][current[2]] == 1){
            option = maze[current[0]][current[1]][current[2]].find('1', option+1);
        }
    }

    return answer;

}


int main(){

    ifstream file("input.txt");

    vector<vector<int>> format = getFormat(file);

    printFormat(format);

    vector<vector<vector<string>>> maze = initializeMaze(file, format);
    
    printMaze(maze);

    vector<int> current(3);

    for (int i = 0; i < 3; i++){
        current[i] = format[i][1];
    }

    moveCurrent(2, current);


    file.close();

    return 0;
}