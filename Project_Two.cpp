//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Justin Hartwick
// Version     : 1.0
// Copyright   : Copyright � 2025 SNHU COCE
// Description : CS 300 Project Two - Advising Assistance Program
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>  // For sorting

using namespace std;

// Course structure to store course data
struct Course {
    string courseID;
    string title;
    vector<string> prerequisites;
};

// Node structure for the Binary Search Tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) {
        course = c;
        left = nullptr;
        right = nullptr;
    }
};

// BST Class
class BST {
public:
    Node* root;

    BST() { root = nullptr; }

    void Insert(Course course) {
        root = InsertNode(root, course);
    }

    void PrintInOrder() {
        PrintInOrderTraversal(root);
    }

    Course* Search(string courseID) {
        return SearchCourse(root, courseID);
    }

private:
    Node* InsertNode(Node* node, Course course) {
        if (node == nullptr) {
            return new Node(course);
        }
        if (course.courseID < node->course.courseID) {
            node->left = InsertNode(node->left, course);
        }
        else {
            node->right = InsertNode(node->right, course);
        }
        return node;
    }

    void PrintInOrderTraversal(Node* node) {
        if (node == nullptr) return;
        PrintInOrderTraversal(node->left);
        cout << node->course.courseID << ", " << node->course.title << endl;
        PrintInOrderTraversal(node->right);
    }

    Course* SearchCourse(Node* node, string courseID) {
        if (node == nullptr) return nullptr;
        if (node->course.courseID == courseID) return &node->course;
        if (courseID < node->course.courseID) {
            return SearchCourse(node->left, courseID);
        }
        else {
            return SearchCourse(node->right, courseID);
        }
    }
};

/**
 * Function: DisplayMenu
 * Purpose: Displays the menu options for the course planner.
 */
void DisplayMenu() {
    cout << "\nWelcome to the course planner.\n";
    cout << "1. Load Data Structure.\n";
    cout << "2. Print Course List.\n";
    cout << "3. Print Course.\n";
    cout << "9. Exit.\n";
    cout << "What would you like to do? ";
}

/**
 * Function: LoadDataFromCSV
 * Purpose: Reads course data from a CSV file and loads it into a BST.
 */
void LoadDataFromCSV(BST& course_tree) {
    string file_path;
    cout << "\nEnter the name of the course data file: ";
    cin.ignore();
    getline(cin, file_path);

	string full_path = file_path;  // Use the name/path the user entered
    cout << "Trying to open: " << full_path << endl;
    ifstream file(full_path);


    if (!file.is_open()) {
        cout << "Error: Could not open file " << file_path << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string course_id, title, prereq;
        vector<string> prerequisites;

        getline(ss, course_id, ',');
        getline(ss, title, ',');

        while (getline(ss, prereq, ',')) {
            prerequisites.push_back(prereq);
        }

        Course course = { course_id, title, prerequisites };
        course_tree.Insert(course);
    }

    file.close();
    cout << "Successfully loaded file: " << file_path << endl;
}

/**
 * Function: FindAndPrintCourse
 * Purpose: Searches for a course and prints its details.
 */
void FindAndPrintCourse(BST& course_tree) {
    string course_id;
    cout << "\nEnter course ID: ";
    cin >> course_id;

    Course* course = course_tree.Search(course_id);
    if (course) {
        cout << course->courseID << ", " << course->title << endl;
        if (course->prerequisites.empty()) {
            cout << "Prerequisites: None" << endl;
        }
        else {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course->prerequisites.size(); i++) {
                cout << course->prerequisites[i];
                if (i != course->prerequisites.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    }
    else {
        cout << "Course not found." << endl;
    }
}

/**
 * Function: PrintCourseList
 * Purpose: Prints all courses in sorted order (in-order traversal).
 */
void PrintCourseList(BST& course_tree) {
    cout << "\nHere is a sample schedule:\n";
    course_tree.PrintInOrder();
}

/**
 * Function: main
 * Purpose: Runs the Advising Assistance Program, handling user input.
 */
int main() {
    int user_choice;
    BST course_tree;  // Binary Search Tree for storing courses

    while (true) {
        DisplayMenu();
        cin >> user_choice;

        // Handle invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }

        switch (user_choice) {
        case 1:
            LoadDataFromCSV(course_tree);
            break;
        case 2:
            PrintCourseList(course_tree);
            break;
        case 3:
            FindAndPrintCourse(course_tree);
            break;
        case 9:
            cout << "\nThank you for using the course planner!\n";
            return 0;
        default:
            cout << "\n" << user_choice << " is not a valid option.\n";
        }
    }
}
