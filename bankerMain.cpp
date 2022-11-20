#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void printMatrix(std::vector<std::vector<int>> vect2D);

int main(){

std::ifstream matrixIFS;

matrixIFS.open("matrixInput.txt");
if(!matrixIFS.is_open()){
    std::cerr << "Opening file failed\n";
    exit(EXIT_FAILURE);
}

int numFromInput;
//initialize available
std::vector<int> available;
for(int i = 0; i < 3; ++i){
    matrixIFS >> numFromInput;
    available.push_back(numFromInput);
    //std::cout << available[i];
}

std::vector<int> temp;
//initalize max
std::vector<std::vector<int>> max;
for(int i = 0; i < 5; ++i){
    for(int i = 0; i < 3; ++i){
        matrixIFS >> numFromInput;
        temp.push_back(numFromInput);
    }
    max.push_back(temp);
    temp.clear();
}
//printMatrix(max);

//initialize allocation
std::vector<std::vector<int>> allocation;
for(int i = 0; i < 5; ++i){
    for(int i = 0; i < 3; ++i){
        matrixIFS >> numFromInput;
        temp.push_back(numFromInput);
    }
    allocation.push_back(temp);
    temp.clear();
}
//std::cout << std::endl;
//printMatrix(allocation);

temp.resize(3);
std::vector<std::vector<int>> need;
for(int i = 0; i < max.size(); ++i){
    std::transform(max[i].begin(), max[i].end(), allocation[i].begin(),
        temp.begin(), [](int maxEl, int alocEl){return maxEl - alocEl;} );
    need.push_back(temp);
}

//std::cout << std::endl;
//printMatrix(need);






}


//print vec.size x 3 matrix to console 
void printMatrix(std::vector<std::vector<int>> vect2D){
    std::string blank = "  ";
    for(int i = 0; i < vect2D.size(); ++i){
        for(int j = 0; j < 3; ++j){
            std::cout << vect2D[i][j] << blank;
        }
        std::cout << std::endl;
    }
}