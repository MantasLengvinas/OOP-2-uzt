#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>
#include <vector>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

struct _student {

    string fname, lname; // vardas, pavarde
    vector<int> hw; // Namu darbai (homework)
    int exam = 0;

};

const char file[] = "kursiokai.txt"; //Duomenu failo pavadinimas
const char outputFile[] = "output.txt"; //Rezultatu failo pavadinimas

bool _check(_student &a, _student &b);
void checkInput(char& choice);
void checkInput(int &input);
void readFile(vector<_student> &Students);
void generateGrades(int n, vector<int> &arr);
void addStudent(vector<_student> &Students);

#endif