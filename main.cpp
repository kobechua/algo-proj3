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

    void moveN(){
        current[2] += 1;
    }
    void moveE(){
        current[1] += 1;
    }
    void moveS(){
        current[2] -= 1;
    }
    void moveW(){
        current[1] -= 1;
    }
    void moveU(){
        current[0] += 1;
    }
    void moveD(){
        current[0] -= 1;
    }

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



int main(){

    ifstream file("input.txt");


    vector<vector<int>> format = getFormat(file);

    printFormat(format);



    vector<vector<vector<string>>> maze = initializeMaze(file, format);
    
    printMaze(maze);


    file.close();

    return 0;
}