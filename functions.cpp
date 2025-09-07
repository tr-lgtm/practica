#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#include <iostream>
#include <string>
#include <fstream>
#include<sstream>
#include <iomanip>
void CheckInputFile(std::ifstream& in) {
    if (!in) {
        throw std::runtime_error("Input file could not be opened.");
    }
    //ƒŒœ»—¿“‹!
}

void CheckOutputFile(std::ofstream& out) {
    if (!out) {
        throw std::runtime_error("Output file could not be created or opened for writing.");
    }
}
void createBinaryStudents(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile);
    CheckInputFile(in);
    std::ofstream out(outputFile, std::ios::binary);
    CheckOutputFile(out);

    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string inlexStr, lastNameStr, firstNameStr, patronymicStr;

        if (std::getline(ss, inlexStr, ';') &&
            std::getline(ss, lastNameStr, ';') &&
            std::getline(ss, firstNameStr, ';') &&
            std::getline(ss, patronymicStr, ';')) {

            StudentFull s{};


            s.id = stoi(inlexStr);
            std::strncpy(s.lastName, lastNameStr.c_str(), sizeof(s.lastName));
            std::strncpy(s.firstName, firstNameStr.c_str(), sizeof(s.firstName));
            std::strncpy(s.patronymic, patronymicStr.c_str(), sizeof(s.patronymic));
            s.group = 0;
            s.math = s.geo = s.prog = 0;
            s.average = 0.0;

            out.write(reinterpret_cast<char*>(&s), sizeof(StudentFull));
        }
    }

    in.close();
    out.close();
}

void createBinaryGrades(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile);
    CheckInputFile(in);
    std::ofstream out(outputFile, std::ios::binary);
    CheckOutputFile(out);

    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string group, index, subj1, grade1, subj2, grade2, subj3, grade3;

        if (std::getline(ss, group, ';') &&
            std::getline(ss, index, ';') &&
            std::getline(ss, subj1, ';') &&
            std::getline(ss, grade1, ';') &&
            std::getline(ss, subj2, ';') &&
            std::getline(ss, grade2, ';') &&
            std::getline(ss, subj3, ';') &&
            std::getline(ss, grade3, ';')) {

            StudentFull s{};
            s.group = stoi(group);
            s.id = stoi(index);
            s.math = stoi(grade1);
            s.geo = stoi(grade2);
            s.prog = stoi(grade3);

            out.write(reinterpret_cast<char*>(&s), sizeof(StudentFull));
        }
    }

    in.close();
    out.close();
}

void mergeStudentGrades(const std::string& studentsBin, const std::string& gradesBin, const std::string& outputBin) {

    std::ifstream students(studentsBin, std::ios::binary);
    CheckInputFile(students);
    std::ifstream grades(gradesBin, std::ios::binary);
    CheckInputFile(grades);
    std::ofstream out(outputBin, std::ios::binary);
    CheckOutputFile(out);

    StudentFull grades_s;
    while (grades.read(reinterpret_cast<char*>(&grades_s), sizeof(StudentFull))) {

        students.clear();
        students.seekg(0);

        StudentFull students_s{};

        while (students.read(reinterpret_cast<char*>(&students_s), sizeof(StudentFull))) {
            if (students_s.id == grades_s.id) {

                strncpy(grades_s.lastName, students_s.lastName, sizeof(grades_s.lastName));
                out.write(reinterpret_cast<char*>(&grades_s), sizeof(StudentFull));

                break;
            }
        }
    }
}

void calculateAverage(const std::string& inputBin, const std::string& outputBin) {
    std::ifstream in(inputBin, std::ios::binary);
    CheckInputFile(in);
    std::ofstream out(outputBin, std::ios::binary);
    CheckOutputFile(out);

    StudentFull s{};
    while (in.read(reinterpret_cast<char*>(&s), sizeof(StudentFull))) {

        s.average = (s.math + s.geo + s.prog) / 3.0;
        out.write(reinterpret_cast<char*>(&s), sizeof(StudentFull));
    }
}

void createFailingList(const std::string& averageBin, const std::string& failingBin) {
    std::ifstream in(averageBin, std::ios::binary);
    CheckInputFile(in);
    std::ofstream out(failingBin, std::ios::binary);
    CheckOutputFile(out);

    StudentFull s{};

    while (in.read(reinterpret_cast<char*>(&s), sizeof(StudentFull))) {
        if (s.average < 4.0) {

            StudentFull fs{};

            fs.id = s.id;
            fs.group = s.group;
            strncpy(fs.lastName, s.lastName, sizeof(fs.lastName));

            out.write(reinterpret_cast<char*>(&fs), sizeof(StudentFull));
        }
    }

    in.close();
    out.close();
}

bool compareGroupAndSurnames(const StudentFull& a, const StudentFull& b) {

    if (a.group != b.group)
        return a.group < b.group;

    return std::strcmp(a.lastName, b.lastName) < 0;
}

bool compareSurnames(const StudentFull& a, const StudentFull& b) {

    return std::strcmp(a.lastName, b.lastName) < 0;
}

bool compareAverage(const StudentFull& a, const StudentFull& b) {

    return a.average > b.average;
}
int countSizeBin(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary | std::ios::ate);
    CheckInputFile(in);

    std::streamsize size = in.tellg();
    return static_cast<int>(size / sizeof(StudentFull));
}

void readStudents(const std::string& filename, StudentFull* arr, int count) {
    std::ifstream in(filename, std::ios::binary);
    CheckInputFile(in);

    for (int i = 0; i < count; ++i) {
        if (!in.read(reinterpret_cast<char*>(&arr[i]), sizeof(StudentFull)))
            throw std::runtime_error("Error read Students");
    }

    in.close();
}

void writeStudentsToFile(const std::string& filename, StudentFull* arr, int size) {
    std::ofstream out(filename, std::ios::binary);
    CheckOutputFile(out);

    for (int i = 0; i < size; ++i) {
        out.write(reinterpret_cast<char*>(&arr[i]), sizeof(StudentFull));
    }

    out.close();
}
void printStudentsList(const std::string& failingBin) {
    std::ifstream in(failingBin, std::ios::binary);
    CheckInputFile(in);

    StudentFull fs{};
    while (in.read(reinterpret_cast<char*>(&fs), sizeof(StudentFull))) {
        std::cout << "lastName: " << fs.lastName;
        std::cout << " firstName: " << fs.firstName;
        std::cout << " patronymic: " << fs.patronymic;
        std::cout << " group: " << fs.group;
        std::cout << " id: " << fs.id;
        std::cout << " math: " << fs.math;
        std::cout << " geo: " << fs.geo;
        std::cout << " prog: " << fs.prog;
        std::cout << " average: " << std::fixed << std::setprecision(4) << fs.average << std::endl;
    }
}

StudentFull* readGroupFromFile(const std::string& filename, int targetGroup, int& outSize) {
    std::ifstream in(filename, std::ios::binary);
    CheckInputFile(in);

    StudentFull* arr = nullptr;
    outSize = 0;
    StudentFull s{};

    while (in.read(reinterpret_cast<char*>(&s), sizeof(StudentFull))) {
        if (s.group == targetGroup) {
            addElementToArray(arr, outSize, s);
        }
    }

    in.close();
    return arr;
}
void createGoodList(const std::string& inBin, const std::string& outBin) {
    std::ifstream in(inBin, std::ios::binary);
    CheckInputFile(in);
    std::ofstream out(outBin, std::ios::binary);
    CheckOutputFile(out);

    StudentFull s{};
    while (in.read(reinterpret_cast<char*>(&s), sizeof(StudentFull))) {
        if (s.average >= 8.0) {

            StudentFull gs{};

            strncpy(gs.lastName, s.lastName, sizeof(gs.lastName));
            gs.id = s.id;
            gs.group = s.group;

            out.write(reinterpret_cast<char*>(&gs), sizeof(StudentFull));
        }
    }
}

void binaryToText(const std::string& inputBin, const std::string& outputText) {
    std::ifstream in(inputBin, std::ios::binary);
    CheckInputFile(in);

    std::ofstream out(outputText);
    CheckOutputFile(out);

    StudentFull student{};

    while (in.read(reinterpret_cast<char*>(&student), sizeof(StudentFull))) {
        out << student.group << ';'
            << student.id << ';'
            << student.lastName << ';'
            << student.firstName << ';'
            << student.patronymic << ';'
            << "MA" << ';'
            << student.math << ';'
            << "GEO" << ';'
            << student.geo << ';'
            << "PROG" << ';'
            << student.prog << ';'
            << std::fixed << std::setprecision(2) << student.average << std::endl;
    }

    in.close();
    out.close();
}