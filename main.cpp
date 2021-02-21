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

const char file[] = "students1000000.txt"; //Failo pavadinimas

void addStudent(vector<_student> &Students);
void readFile(vector<_student> &Students);

void checkInput(char& choice) {

	while (cin.fail() || tolower(choice) != 't' && tolower(choice) != 'n'){
		if (cin.fail())
			cout << "Ivestis netinkama (Ivedete skaiciu)" << endl;
		else if(tolower(choice) != 't' && tolower(choice) != 'n')
			cout << "Neteisingas pasirinkimas! Galimi pasirinkimai: t (taip) arba n (ne)!" << endl;

		cin.clear();
		cin.ignore(256, '\n');
		cout << "Pakartokite ivedima (t/n): ";
		cin >> choice;
	}
}

void checkInput(int &input) {

	while (cin.fail() || input < 0 || input > 10){
		if (cin.fail())
			cout << "Ivestis netinkama (Ivedete raide)" << endl;
		else if(input < 0)
			cout << "Skaicius negali buti mazesnis uz 0!" << endl;
        else if(input > 10)
            cout << "Skaicius negali buti didesnis uz 10!" << endl;

		cin.clear();
		cin.ignore(256, '\n');
		cout << "Iveskite skaiciu is naujo: ";
		cin >> input;
	}
}

void generateGrades(int n, vector<int> &arr){

    srand(time(0));

    for(int i = 0; i < n; i++){
        arr.push_back(rand() % 10 + 1);
    }

}

int main(){

    char choice;
    vector<_student> Students;

    cout << "Duomenys norite irasyti patys (T) ar skaityti is failo (N)?"; cin >> choice;
    checkInput(choice);

    if(tolower(choice) == 't'){
	cin.ignore();
        while(true){

            addStudent(Students);

            cout << "Ar norite prideti dar 1 studenta? (t/n) "; cin >> choice;
            cin.ignore();
            checkInput(choice);

            if(tolower(choice) == 'n'){
                break;
            }
            else if(tolower(choice) == 't'){
                continue;
            }

        }
    }
    else if(tolower(choice) == 'n'){
        readFile(Students);
    }

    cout << "Duomenu irasymas sekmingas." << '\n' << "Norite matyti vidurki (t) ar mediana (n)? "; cin >> choice;
    checkInput(choice);

    if(tolower(choice) == 't'){
        std::cout << std::left
			<< std::setw(20) << "Pavarde"
			<< std::setw(15) << "Vardas"
			<< std::setw(10) << "Galutinis (Vid.)"
			<< std::endl
			<< std::string(65, '-')
			<< std::endl;

		for (int i = 0; i < Students.size(); i++){
			double avg = 0;

			for (int j = 0; j < Students[i].hw.size(); j++)
				avg += Students[i].hw[j];

			avg /= Students[i].hw.size();
			avg = 0.4 * avg + 0.6 * Students[i].exam;
			
			std::cout << std::left
				<< std::setw(20) << Students[i].lname
				<< std::setw(15) << Students[i].fname
				<< std::setw(15) << std::setprecision(2) << avg
				<< std::endl;

		}
    }
    else if (tolower(choice) == 'n'){
         std::cout << std::left
			<< std::setw(20) << "Pavarde"
			<< std::setw(15) << "Vardas"
			<< std::setw(10) << "Galutinis (Med.)"
			<< std::endl
			<< std::string(65, '-')
			<< std::endl;

		for (int i = 0; i < Students.size(); i++){
			std::sort(Students[i].hw.begin(), Students[i].hw.end());

			double median = 0;

			if (Students[i].hw.size() % 2 == 1)
				median = Students[i].hw[Students[i].hw.size() / 2];

			else median = (Students[i].hw[Students[i].hw.size() / 2] + Students[i].hw[Students[i].hw.size() / 2 - 1]) / 2;

			std::cout << std::left
				<< std::setw(20) << Students[i].lname
				<< std::setw(15) << Students[i].fname
				<< std::setw(15) << std::setprecision(2) << median
				<< std::endl;

		}
    }

    return 0;
}

void readFile(vector<_student> &Students){

    std::ifstream input(file);

    if(!input){
        cout << "Nurodytas failas neegzistuoja!" <<endl;
        exit(1);
    }

    _student student;

    string line;
    int val;
    vector<int> grades;

    input.ignore(255, '\n');

    while(true){

        input >> student.fname >> student.lname;
        getline(input, line);
        std::istringstream str(line);

        int val;
        while(str >> val){
            grades.push_back(val);
        }

        grades.pop_back();
        student.exam = val;
        student.hw = grades;

        Students.push_back(student);
        grades.clear();

        if(input.eof()){
            break;
        }

    }

    input.close();

}

void addStudent(vector<_student> &Students) {

    srand(time(0));

    _student stud;
    int gr;
    int n = 0; // n yra kaip iterator toje dalyje, kai yra nezinomas pazymiu kiekis
    vector<int> hw;
    char choice;

    cout << "Iveskite studento varda: ";
    getline(cin, stud.fname);
    
    cout << "Iveskite studento pavarde: ";
    getline(cin, stud.lname);

    cout << "Ar yra zinomas namu darbu pazymiu skaicius? (t/n) ";
    cin >> choice;
    checkInput(choice);

    if(tolower(choice) == 't'){

        cout << "Iveskite namu darbu pazymiu kieki: "; cin >> n;
        checkInput(n);

        cout << "Ar norite patys ivesti pazymius uz namu darbus? (t/n) "; cin >> choice; cout << '\n';
        checkInput(choice);

        if(tolower(choice) == 't'){
            for(int i = 0; i < n; i++){
                cout << "Iveskite " << i + 1 << "-a pazymi: ";
                cin >> gr;
                checkInput(gr);
                hw.push_back(gr);
            }
        }
        else if(tolower(choice) == 'n'){
            generateGrades(n, hw);
        }

    }else if(tolower(choice) == 'n'){

        cout << "Ar norite patys ivesti pazymius uz namu darbus? (t/n) "; cin >> choice; cout << '\n';

        if(tolower(choice) == 't'){

            cout << "Noredami baigti pazymiu ivedima, iveskite 0" << endl;

            while(true){
                
                cout << "Iveskite " << n + 1 << "-a pazymi: "; cin >> gr;
                checkInput(gr);

                if(gr == 0){
                    break;
                }
                else {
                    n++;
                    hw.push_back(gr);
                }

            }
        }else if(tolower(choice) == 'n'){
            n = rand() % 11;

            if(n != 0) {
                generateGrades(n, hw);
            }
        }
    }

    cout << "Ar norite patys ivesti egzamino vertinima? (t/n) "; cin >> choice; cout<< '\n';
    checkInput(choice);

    if(tolower(choice) == 't'){
        cout << "Iveskite egzamino vertinima: "; cin >> stud.exam;
        checkInput(stud.exam);
    }
    else if(tolower(choice) == 'n'){
        stud.exam = rand() % 10 + 1;
        cout << "Sugeneruotas egzamino vertinimas: " << stud.exam << '\n';
    }

    stud.hw = hw;

    Students.push_back(stud);

}
