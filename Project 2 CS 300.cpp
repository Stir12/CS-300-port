#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

// Define a structure for the course
struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

// Function to load data from the list into the data structure
void loadDataStructure(const std::vector<std::string>& courseData, std::vector<Course>& courses) {
    for (const auto& data : courseData) {
        std::istringstream iss(data);
        Course course;
        iss >> course.courseNumber >> std::ws;
        std::getline(iss, course.courseTitle, ',');

        // Read prerequisites and split by comma
        std::string prerequisitesStr;
        std::getline(iss, prerequisitesStr);
        std::istringstream prerequisitesStream(prerequisitesStr);
        while (prerequisitesStream >> std::ws, !prerequisitesStream.eof()) {
            std::string prereq;
            std::getline(prerequisitesStream, prereq, ',');
            course.prerequisites.push_back(prereq);
        }

        courses.push_back(course);
    }
}

// Function to print the course list with prerequisites
void printCourseList(const std::vector<Course>& courses) {
    std::vector<Course> sortedCourses = courses;
    // Sort the courses based on courseNumber
    std::sort(sortedCourses.begin(), sortedCourses.end(),
        [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
        });

    // Print the sorted course list with prerequisites
    for (const auto& course : sortedCourses) {
        std::cout << course.courseNumber << ", " << course.courseTitle;
        if (!course.prerequisites.empty()) {
            std::cout << " (Prerequisites: ";
            for (const auto& prereq : course.prerequisites) {
                std::cout << prereq << " ";
            }
            std::cout << ")";
        }
        std::cout << std::endl;
    }
}

// Function to display prerequisites for a specific course
void displayPrerequisites(const std::vector<Course>& courses, const std::string& courseNumber) {
    // Search for the course by courseNumber
    auto it = std::find_if(courses.begin(), courses.end(),
        [courseNumber](const Course& course) {
            return course.courseNumber == courseNumber;
        });

    // Check if the course is found
    if (it != courses.end()) {
        // Print prerequisites
        if (!it->prerequisites.empty()) {
            std::cout << "Prerequisites for " << it->courseNumber << ": ";
            for (const auto& prereq : it->prerequisites) {
                std::cout << prereq << " ";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "No prerequisites for " << it->courseNumber << std::endl;
        }
    }
    else {
        std::cout << "Course not found." << std::endl;
    }
}

// Function to print course information
void printCourse(const std::vector<Course>& courses) {
    std::string courseNumber;
    std::cout << "What course do you want to know about? ";
    std::cin >> courseNumber;

    // Search for the course by courseNumber
    auto it = std::find_if(courses.begin(), courses.end(),
        [courseNumber](const Course& course) {
            return course.courseNumber == courseNumber;
        });

    // Check if the course is found
    if (it != courses.end()) {
        // Print course information
        std::cout << it->courseNumber << ", " << it->courseTitle << std::endl;
        displayPrerequisites(courses, it->courseNumber);
    }
    else {
        std::cout << "Course not found." << std::endl;
    }
}

int main() {
    // Vector to hold course objects
    std::vector<Course> courses;

    // course data with prerequisites
    std::vector<std::string> courseData = {
        "MATH201 Discrete Mathematics",
        "CSCI300 Introduction to Algorithms,CSCI200, MATH201",
        "CSCI350 Operating Systems,CSCI300",
        "CSCI101 Introduction to Programming in C++,CSCI100",
        "CSCI100 Introduction to Computer Science",
        "CSCI301 Advanced Programming in C++,CSCI101",
        "CSCI400 Large Software Development,CSCI301,CSCI350",
        "CSCI200 Data Structures, CSCI101"
    };

    int choice;
    do {
        // Display menu
        std::cout << "Welcome to the course planner." << std::endl;
        std::cout << "1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        // Perform action based on user's choice
        switch (choice) {
        case 1:
            // Load data structure from the list
            loadDataStructure(courseData, courses);
            break;
        case 2:
            // Print course list
            printCourseList(courses);
            break;
        case 3:
            // Print course information
            printCourse(courses);
            break;
        case 9:
            // Exit the program
            std::cout << "Thank you for using the course planner!" << std::endl;
            break;
        default:
            // Display an error message for invalid choices
            std::cout << choice << " is not a valid option." << std::endl;
        }
    } while (choice != 9);

    return 0;
}
