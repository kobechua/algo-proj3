#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


void printFile(string filename){

    ifstream file(filename);

    string line;
    if (file.is_open()){
        while ( getline(file, line)){
            cout << line << '\n';
        }
        file.close();
    }

}

class Maze{
    vector<int> dimensions;
    vector<int> start;
    vector<int> goal;

    vector<int> current;

    vector<vector<int>> getFormat(ifstream& file);

    vector<vector<vector<int>>> initializeMaze(ifstream& file, vector<int>& dimensions, vector<int>& start, vector<int>& goal);

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

vector<vector<vector<int>>> initializeMaze(ifstream& file, vector<vector<int>>){
    vector<vector<vector<int>>> maze;
    return maze;
}



int main(){

    ifstream file("input.txt");

    cout << "getformat" << endl;

    vector<vector<int>> format = getFormat(file);

    cout << "printloop" << endl;

    for (int j = 0; j < 3; j++){
        for (int k = 0; k < 3; k++){
            cout << format[k][j] << " ";
        }
        cout << endl;
    }

    cout << "closefile" << endl;

    file.close();

    return 0;
}