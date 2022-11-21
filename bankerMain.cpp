#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void printMatrix(std::vector<std::vector<int>> vect2D);
bool vectorIsLess(std::vector<int> lVec, std::vector<int> rVec);
bool allTrue(std::vector<bool> vecBool);
void printVec(std::vector<int> vec);
void printVecBool(std::vector<bool> vec);

int main(){

std::ifstream matrixIFS;

matrixIFS.open("matrixInput.txt");
if(!matrixIFS.is_open()){
    std::cerr << "Opening file failed\n";
    exit(EXIT_FAILURE);
}
//std::cout << "before avail initialize";
int numFromInput;
//initialize available
std::vector<int> available;
for(int i = 0; i < 3; ++i){
    matrixIFS >> numFromInput;
    available.push_back(numFromInput);
}
//std::cout << "before max initialize";
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
//std::cout << "before alloc initialize";
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
//std::cout << "before need initialize";
temp.resize(3);
std::vector<std::vector<int>> need;
for(int i = 0; i < max.size(); ++i){
    std::transform(max[i].begin(), max[i].end(), allocation[i].begin(),
        temp.begin(), [](int maxEl, int alocEl){return maxEl - alocEl;} );
    need.push_back(temp);
}

//std::cout << std::endl;
//printMatrix(need);

std::vector<int> sequence;
int sequenceItr = 0;
std::vector<int> availableOldState;
std::vector<int> allocationOldState;
std::vector<int> needOldState;
int processNum = 0, resourceNum = 0;
std::vector<bool> finish(5, false);
std::vector<bool> finishOverall(5, false);
std::vector<int> work(3, 0);
std::vector<int> availableReturned;
//std::cout << "got to while loop";
int tempitr = 0;
while(sequence.size() < 5 && tempitr < 20){
    ++tempitr;
    std::cout << "process num is:" << processNum << std::endl;
    //if process needs more than whats available or has already ran, go to next process
    if(!vectorIsLess(need[processNum], available) || finishOverall[processNum]){
        processNum = (processNum + 1) % 5;
        continue;
    }
    
    //save old state
    availableOldState = available;
    allocationOldState = allocation[processNum];
    needOldState = need[processNum];
    /*
    std::cout << std::endl << "need before:";
    printVec(need[processNum]);
    std::cout << std::endl << "avail before:";
    printVec(available);
    */

    if(available.size() != need[processNum].size()){
        std::cerr << need[processNum].size();
        std::cerr << "vectors not same size a.n";
        exit(EXIT_FAILURE);
    }
    //needed resources are taken from available
    std::transform(available.begin(), available.end(), need[processNum].begin(), 
        available.begin(), [](int availE, int needE){return availE - needE;} );
    /*
    std::cout << std::endl << "avail after transform:";
    printVec(available);
    */

    allocation[processNum] = max[processNum]; //process gets all needed resources 
    std::fill(need[processNum].begin(), need[processNum].end(), 0); 
    /*
    std::cout << std::endl << "need after fill:";
    printVec(need[processNum]);
    */
    //check if safe

    finishOverall[processNum] = true;
    finish = finishOverall;

   
    if(available.size() != allocation[processNum].size()){
        std::cerr << "vectors not same size a.a";
        exit(EXIT_FAILURE);
    }
    /*
    std::cout << std::endl << "allocation: ";
    printVec(allocation[processNum]);
    */
    //allocated resources moved back to available(work)
    std::transform(available.begin(), available.end(), allocation[processNum].begin(), 
        work.begin(), [](int availE, int allocE){return availE + allocE;} );
    availableReturned = work;
    
    std::fill(allocation[processNum].begin(), allocation[processNum].end(), 0);

    std::cout << std::endl << "work before loop:";
    printVec(work);
    int k = 0;

    printMatrix(need);
    while(k < 5){
        std::cout << std::endl << "NEED: ";
        printVec(need[k]);
        std::cout << std::endl << "AVAIL: ";
        printVec(work);
        if(finish[k] == false && vectorIsLess(need[k], work)){
            /*
            if(work.size() != allocation[i].size()){
                std::cerr << "vectors not same size w.a";
                exit(EXIT_FAILURE);
            */ 
            
            std::transform(work.begin(), work.end(), allocation[k].begin(), 
                work.begin(), [](int workE, int allocE){return workE + allocE;} );

            finish[k] = true;
            k = 0;
            std::cout << std::endl <<"bool vec:";
            printVecBool(finish);
        }else{
            ++k;
        }
    }

    std::cout << std::endl << "final finish bool vec: ";
    printVecBool(finish);


    //if safe then all of finish should be true after for loop
    if(!allTrue(finish)){ //not safe so restore old state
        available = availableOldState;
        allocation[processNum] = allocationOldState;
        need[processNum] = needOldState;
        finishOverall[processNum] = false;
        
    }else{ //is safe
        std::cout << "process " << processNum << " has finished";
        sequence.push_back(processNum);
        available = availableReturned;
    }

    std::fill(finish.begin(), finish.end(), false);
    processNum = (processNum + 1) % 5;

    std::cout << "got through" << std::endl;

}

//print sequence
for(int i = 0; i < sequence.size(); ++i){
    std::cout << sequence[i] << "  ";

}
std::cout << std::endl;

matrixIFS.close();
}


//function definitions

//print vec.size x 3 matrix to console 
void printMatrix(std::vector<std::vector<int>> vect2D){
    std::string blank = "  ";
    for(int i = 0; i < vect2D.size(); ++i){
        for(int j = 0; j < vect2D[i].size(); ++j){
            std::cout << vect2D[i][j] << blank;
        }
        std::cout << std::endl;
    }
}

//compare int vectors of same size
//return true if lVec[i] <= rVec[i] for all i
bool vectorIsLess(std::vector<int> lVec, std::vector<int> rVec){
    bool result  = true;
    for(int i = 0; i < lVec.size() && result == true; ++i){
        if(lVec[i] > rVec[i]) result = false;
    }
    return result;
}

bool allTrue(std::vector<bool> vecBool){
    bool result = true;
    for(int i = 0; i < vecBool.size() && result == true; ++i){
        if(!vecBool[i]) result = false;
    }
    return result;
}

void printVec(std::vector<int> vec){
    std::cout << "vector size: " << vec.size() << std::endl
                << "vector contents: ";

    for(int i = 0; i < vec.size(); ++i){
        std::cout << vec[i] << "  ";
    }
}

void printVecBool(std::vector<bool> vec){
    std::cout << "vector size: " << vec.size() << std::endl
                << "vector contents: ";

    for(int i = 0; i < vec.size(); ++i){
        std::cout << vec[i] << "  ";
    }
}