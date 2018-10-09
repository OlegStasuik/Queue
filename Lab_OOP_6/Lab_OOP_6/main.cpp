//
//  main.cpp
//  Lab_OOP_6
//
//  Created by Oleg Stasuik on 04.05.18.
//  Copyright © 2018 Oleg Stasuik. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

struct Timer{
    chrono::time_point<chrono::steady_clock> start, end;
    chrono::duration<float> duration;
    
    Timer(){
        start = chrono::high_resolution_clock::now();
    }
    ~Timer(){
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        
        float ms = duration.count() * 1000.0f;
        cout << "Timer took: " << ms << "ms" << endl;
    }
};

template <typename T>
class Queue{
private:
    vector<T> queuet;
    int size;
    int prtTmp = 0;
public:
    void add(T tmp){
        queuet.push_back(tmp);
        size++;
    }
    
    void printConsole () {
        for (int i = prtTmp; i < size; i++)
            cout << queuet[i] << " ";
        cout << endl;
    }
    
    int minElInQueue () {
        int min = queuet[prtTmp];
        
        for (int i = 0; i < size; i++)
            if (min > queuet[i])
                min = queuet[i];
        return min;
    }
    
    int del(){
        if (size == 0)
            return 0;
        int tmp = queuet[prtTmp];
        
        prtTmp++;
        if (prtTmp == 10) {
            size--;
            prtTmp = 0;
            Timer a;
            for (int i = 0; i < size; i++)
                queuet[i] = queuet[i+1];
        }
        return tmp;
    }
    
    void saveInFile(){
        
        char *name = (char*)malloc(128);
        
        cout << "Enter file: ";
        gets(name);
        
        FILE *tmp;
        tmp = fopen(name, "w");
        
        fprintf(tmp, "%d\n", size);
        
        for (int i = 0; i < size; i++)
            fprintf(tmp, "%d ", queuet[i]);
        
        fclose(tmp);
    }
    
    void getDataFile(){
        
        char *name = (char*)malloc(128);
        
        cout << "Enter file: ";
        gets(name);
        
        FILE *file;
        file = fopen(name, "r");
        int tmp;
        
        fscanf(file, "%d", &size);
        printf("\nFile read.\n");
        
        for (int i = 0; i < size; i++) {
            fscanf(file, "%d", &tmp);
            queuet.push_back(tmp);
        }
        
        fclose(file);
    }
};


int main(int argc, const char * argv[]) {
    
    Queue<int> tmp;
    
    tmp.getDataFile();
    
    for (int i = 0; i < 100; i++)
        tmp.add(i+100);
    
    
    
    tmp.printConsole();
    cout << tmp.minElInQueue() << endl;
    for (int i = 0; i < 11; i++){
        tmp.del();
        tmp.printConsole();
    }
    
    tmp.saveInFile();
    
    return 0;
}
