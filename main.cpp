#include <iostream>
#include <stdexcept>
#include "functions.h"

int main() {
    try {
        createBinaryStudents("students.txt", "students.bin");
        createBinaryGrades("grades.txt", "grades.bin");

        mergeStudentGrades("students.bin", "grades.bin", "merged_students.bin");
        calculateAverage("merged_students.bin", "average_students.bin");
        binaryToText("average_students.bin", "average_students.txt");

        createFailingList("average_students.bin", "failing_list.bin");
        binaryToText("failing_list.bin", "failing_list.txt");

        writeToBinAndSort("failing_list.bin", compareSurnames);
        binaryToText("failing_list.bin", "failing_list_sort.txt");
        std::cout << "sort failing list by Surnames:" << std::endl;
        printStudentsList("failing_list.bin");

        std::cout << "---------------------------------" << std::endl;
        createGoodList("average_students.bin", "good_list.bin");
        binaryToText("good_list.bin", "good_list.txt");

        writeToBinAndSort("good_list.bin", compareAverage);
        binaryToText("good_list.bin", "good_list_sort.txt");
        std::cout << "sort good list by Surnames" << std::endl;
        printStudentsList("good_list.bin");

        int targetGroup = 2;
        std::cout << "GroupStudents " << targetGroup << " sort by Surnames" << std::endl;
        GroupSorted("average_students.bin", targetGroup, compareSurnames);
        binaryToText("average_students.bin", "group_sort_surnames.txt");
        printStudentsList("average_students.bin");
    }
    catch (const std::runtime_error& e) 
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
