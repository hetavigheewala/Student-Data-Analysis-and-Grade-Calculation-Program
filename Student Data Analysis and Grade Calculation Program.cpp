// Student Data Analysis and Grade Calculation Program

/// @brief This program reads a student data file into an array of records
/// and then calculates the average score, and determines the GPA & grade.

// preprocessor directives
// library includes
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

// set namespace
using namespace std;


// Global constant definition(s)
const int SCORE_CNT = 15;           // the number of scores
const int STUDENT_CNT = 10;         // the number of students

// Structure definition(s)
struct student_t {                  // structure to hold student data
    string fName;                   // student first name
    string lName;                   // student last name
    int scores[SCORE_CNT] = {0};    // student scores
    double average = 0;             // calculated average score
    double gpa = 0;                 // determined grade point average
    string grade;                   // determined letter grade
};


/// -------------------------------------------------------------------------
/// Function Prototype(s)
/// -------------------------------------------------------------------------
void printStudentData(const student_t dataSet[]);
bool readStudentData(const string& FN, student_t dataSet[]);
void setGradeNGpa(student_t dataSet[], int idx);
void runCalcs(student_t dataSet[]);
void printGradeReport(const student_t dataSet[]);

/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main(int argc, const char * argv[]) {
    // Local constant definition(s)

    // Variable declaration(s)
    int exitState;              // tracks the exit code for the process
    exitState = EXIT_SUCCESS;   // set state to successful run

    string fn;                          // command line arg input var file name
    student_t students[STUDENT_CNT];    // holds an array of student data

    // If the minimum number of arguments are available,
    // process the datafile them
    if (argc > 1) {
        // get the file name from the command line
        fn = argv[1];

        // read the data file. If successful, run the calculations
        // print the student data table, and print the grade report
        if (readStudentData(fn, students)) {        // read file
            // calculate individual grades and gpa
            runCalcs(students);

            printStudentData(students);             // print data set
            cout << endl;

            printGradeReport(students);             // output the grade report

        } else {
            // if the file cannot be opened or read, set a fail state
            // and message user
            exitState = EXIT_FAILURE;
            cout << "Unable to process data file: " << fn << endl;
            cout << endl;
        }

    } else {
        cout
        << setw(40) << "Expected a data file name, such as: "
        << "pa09-data0.csv\n"
        << setw(40) << "Launch Syntax: "
        << "./pa09 <filename.ext>\n\n";
        exitState = EXIT_FAILURE;
    }

    return exitState;
}

/// -------------------------------------------------------------------------
/// Function Implementation(s)
/// -------------------------------------------------------------------------

/// This function prints a tabulated grade report of individual scores
/// @param dataSet is an array of student records
void printStudentData(const student_t dataSet[]) {
    int record = 0;     // initialize record idx
    string name;        // holds the name string for output

    cout << endl;
    // loop through all the records and print the data set.
    while (record < STUDENT_CNT) {
        // concatenate the last and first name to make output formatting
        // easier, then print the name
        name = dataSet[record].fName + " " + dataSet[record].lName;
        cout << right << setw(4) << record + 1 << ". ";
        cout << left << setw(18) << name << ": ";

        // print the scores
        for (int scoreIdx = 0; scoreIdx < SCORE_CNT; ++scoreIdx) {
            cout << right << setw(3) << dataSet[record].scores[scoreIdx] << ' ';
        }
        cout << endl;

        // increment record pointer
        record++;
    }
    cout << endl;
}


/// This function reads the student data from a comma delimited file organized
/// as First Name, Last Name, and 15 scores and places the data into the
/// data model
/// @param FN is the name of the file containing the data
/// @param dataSet is an array of student records
/// @return true if successful, otherwise false
bool readStudentData(const string& FN, student_t dataSet[]) {
    bool didOpen = true;    // success flag
    ifstream fin;           // declare the file stream handler
    int record;             // current record from file

    fin.open(FN);           // attempt to open the data file

    // If the file was successfully opened...
    if (fin.is_open()) {
        record = 0;         // set record counter to first record

        // loop through all the records in the file
        // extract the data and place in data model
        while (record < STUDENT_CNT) {
            getline(fin, dataSet[record].fName, ',');  // get the first name
            getline(fin, dataSet[record].lName, ',');  // get the last name

            // get student scores
            for (int scoreIdx = 0; scoreIdx < SCORE_CNT; ++scoreIdx) {
                fin >> dataSet[record].scores[scoreIdx];
                fin.ignore();
            }
            // increment record pointer
            record++;
        }
    } else {    // the file wasn't open
        didOpen = false;
    }

    fin.close();

    return didOpen;
}


/// This function determines the grade and GPA from an average score taken from
/// a record and places the results into the same record
/// @param dataSet is an array of student records
/// @param idx is the index of the record
void setGradeNGpa(student_t dataSet[], int idx) {

    if (dataSet[idx].average < 60) {
        dataSet[idx].grade = "F";
        dataSet[idx].gpa = 0.0;
    } else if (dataSet[idx].average < 63) {
        dataSet[idx].grade = "D-";
        dataSet[idx].gpa = 0.7;
    } else if (dataSet[idx].average < 67) {
        dataSet[idx].grade = "D";
        dataSet[idx].gpa = 1.0;
    } else if (dataSet[idx].average < 70) {
        dataSet[idx].grade = "D+";
        dataSet[idx].gpa = 1.3;
    } else if (dataSet[idx].average < 73) {
        dataSet[idx].grade = "C-";
        dataSet[idx].gpa = 1.7;
    } else if (dataSet[idx].average < 77) {
        dataSet[idx].grade = "C";
        dataSet[idx].gpa = 2.0;
    } else if (dataSet[idx].average < 80) {
        dataSet[idx].grade = "C+";
        dataSet[idx].gpa = 2.3;
    } else if (dataSet[idx].average < 83) {
        dataSet[idx].grade = "B-";
        dataSet[idx].gpa = 2.7;
    } else if (dataSet[idx].average < 87) {
        dataSet[idx].grade = "B";
        dataSet[idx].gpa = 3.0;
    } else if (dataSet[idx].average < 90) {
        dataSet[idx].grade = "B+";
        dataSet[idx].gpa = 3.3;
    } else if (dataSet[idx].average < 95) {
        dataSet[idx].grade = "A-";
        dataSet[idx].gpa = 3.7;
    } else {
        dataSet[idx].grade = "A";
        dataSet[idx].gpa = 4.0;
    }
}


/// This function calculates the average for each student in the data set
/// and places the result into the data model. It calls setGradeNGpa() to
/// populate the grade and GPA into the student's structure
/// @param dataSet is an array of student records
void runCalcs(student_t dataSet[]) {
    int record = 0;     // initialize record idx
    int totalScore;     // score accumulator

    // loop through all the records and process data.
    while (record < STUDENT_CNT) {

        // accumulate score total
        totalScore = 0;
        for (int scoreIdx = 0; scoreIdx < SCORE_CNT; ++scoreIdx) {
            totalScore += dataSet[record].scores[scoreIdx];
        }
        dataSet[record].average = totalScore / static_cast<double>(SCORE_CNT);
        setGradeNGpa(dataSet, record);

        // increment record pointer
        record++;
    }
}


/// This function prints a report of student performance in terms of
/// average, earned grade, and GPA
/// @param dataSet is an array of student records
void printGradeReport(const student_t dataSet[]) {
    int record = 0;     // initialize record idx
    string name;        // holds the name string for output

    cout << "      Name                 GRD  Avg   GPA" << endl;
    cout << "     " << string(37, '-') << endl;

    // loop through all the records and print the data set.
    while (record < STUDENT_CNT) {
        // concatenate the last and first name to make output formatting
        // easier, then print the name
        name = dataSet[record].fName + " " + dataSet[record].lName;
        cout << right << setw(4) << record + 1 << ". ";
        cout << left << setw(18) << name << "| ";

        cout << fixed << setprecision(1) << showpoint
        << ' ' << setw(4) << dataSet[record].grade
        << ' ' << setw(5) <<dataSet[record].average
        << ' ' << setw(5) <<dataSet[record].gpa;
        cout << endl;

        // increment record pointer
        record++;
    }
    cout << endl;
}
