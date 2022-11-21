#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int printFile(){

}

int main(){
    ifstream inputFile("input.txt");
    
    string line;
    if (inputFile.is_open()){
        while ( getline(inputFile, line)){
            cout << line << 'n';
        }
        inputFile.close();
    }


    inputFile.close();

    cout << "Hello World!" << endl;

    return 0;
}