#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <string>
#include <fstream>

struct StudentFull {
    int id;
    int group;
    char lastName[30];
    char firstName[30];
    char patronymic[30];
    int math;
    int geo;
    int prog;
    double average;
};

void CheckInputFile(std::ifstream& in);
void CheckOutputFile(std::ofstream& out);
void calculateAverage(const std::string&, const std::string&);
void mergeStudentGrades(const std::string&, const std::string&, const std::string&);
void createBinaryGrades(const std::string&, const std::string&);
void createBinaryStudents(const std::string&, const std::string&);
void createFailingList(const std::string&, const std::string&);
bool compareSurnames(const StudentFull& a, const StudentFull& b);
bool compareAverage(const StudentFull& a, const StudentFull& b);
bool compareGroupAndSurnames(const StudentFull& a, const StudentFull& b);
int countSizeBin(const std::string&);
template<typename T> void copyArray(T* arr, T*& newArr, int oldSize);
template<typename T> void addElementToArray(T*& arr, int& size, T element);
template<class Compare> void writeToBinAndSort(const std::string&, Compare);
void printStudentsList(const std::string&);
template<class Compare> void GroupSorted(const std::string&, int, Compare);
void readStudents(const std::string&, StudentFull*, int);
void writeStudentsToFile(const std::string&, StudentFull*, int);
StudentFull* readGroupFromFile(const std::string&, int, int&);
void createGoodList(const std::string&, const std::string&);
void binaryToText(const std::string&, const std::string&);
template<class T>
void copyArray(T* arr, T*& newArr, int oldSize) {
    newArr = new T[oldSize + 1];
    for (int i = 0; i < oldSize; ++i) {
        newArr[i] = arr[i];
    }
}
template<class T>
void addElementToArray(T*& arr, int& size, T element) {
    T* tempArr = nullptr;
    copyArray(arr, tempArr, size);
    tempArr[size] = element;
    delete[] arr;
    arr = tempArr;
    ++size;
}
template<class Compare>
void writeToBinAndSort(const std::string& failingBin, Compare comp) {
    int size = countSizeBin(failingBin);

    StudentFull* arr = new StudentFull[size];


    readStudents(failingBin, arr, size);

    std::sort(arr, arr + size, comp);

    writeStudentsToFile(failingBin, arr, size);

    delete[] arr;
}
template<class Compare>
void GroupSorted(const std::string& mergedBin, int targetGroup, Compare comp) {
    int size{};
    StudentFull* arr = readGroupFromFile(mergedBin, targetGroup, size);

    std::sort(arr, arr + size, comp);
    writeStudentsToFile(mergedBin, arr, size);

    delete[] arr;
}
