#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct _student {

    string fname, lname; // vardas, pavarde
    int n = 0; // kiek namu darbu atliko
    int* hw; // Namu darbai (homework)
    int exam = 0;

};

void addStudent(_student& Student);

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

void generateGrades(int n, int arr[]){

    srand(time(0));

    for(int i = 0; i < n; i++){
        arr[i] = rand() % 10 + 1;
    }

}

int main(){

    int stud_n = 0;
    char choice;
    _student* Students = new _student[stud_n + 1];

    while(true){

        addStudent(Students[stud_n]);
        stud_n++;

        cout << "Ar norite prideti dar 1 studenta? (t/n) "; cin >> choice;
        cin.ignore();
        checkInput(choice);

        if(tolower(choice) == 'n'){
            break;
        }
        else if(tolower(choice) == 't'){
            _student* _temp = new _student[stud_n + 1];

            for(int i = 0; i < stud_n; i++){
                _temp[i] = Students[i];
            }

            delete[] Students;
            Students = _temp;
        }

    }

    cout << "Duomenu irasymas sekmingas." << '\n' << "Kaip rezultata norite matyti vidurki (t) ar mediana (n)? "; cin >> choice;
    checkInput(choice);

    if(tolower(choice) == 't'){
        std::cout << std::left
			<< std::setw(20) << "Pavarde"
			<< std::setw(15) << "Vardas"
			<< std::setw(10) << "Galutinis (Vid.)"
			<< std::endl
			<< std::string(65, '-')
			<< std::endl;

		for (int i = 0; i < stud_n; i++){
			double avg = 0;

			for (int j = 0; j < Students[i].n; j++)
				avg += Students[i].hw[j];

			avg /= Students[i].n;
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

		for (int i = 0; i < stud_n; i++){
			std::sort(Students[i].hw, Students[i].hw + Students[i].n);

			double median = 0;

			if (Students[i].n % 2 == 1)
				median = Students[i].hw[Students[i].n / 2];

			else median = (Students[i].hw[Students[i].n / 2] + Students[i].hw[Students[i].n / 2 - 1]) / 2;

			std::cout << std::left
				<< std::setw(20) << Students[i].lname
				<< std::setw(15) << Students[i].fname
				<< std::setw(15) << std::setprecision(2) << median
				<< std::endl;

		}
    }

    return 0;
}

void addStudent(_student& Student) {

    srand(time(0));

    string fname, lname;
    int n = 0, exam; // n yra kaip iterator toje dalyje, kai yra nezinomas pazymiu kiekis
    int* hw = new int[n + 1];
    char choice;

    cout << "Iveskite studento varda: ";
    getline(cin, fname);
    
    cout << "Iveskite studento pavarde: ";
    getline(cin, lname);

    cout << "Ar yra zinomas namu darbu pazymiu skaicius? (t/n) ";
    cin >> choice;
    checkInput(choice);

    if(tolower(choice) == 't'){

        cout << "Iveskite namu darbu pazymiu kieki: "; cin >> n;
        checkInput(n);

        delete[] hw;
        hw = new int[n];

        cout << "Ar norite patys ivesti pazymius uz namu darbus? (t/n) "; cin >> choice; cout << '\n';
        checkInput(choice);

        if(tolower(choice) == 't'){
            for(int i = 0; i < n; i++){
                cout << "Iveskite " << i + 1 << "-a pazymi: ";
                cin >> hw[i];
                checkInput(hw[i]);
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
                
                cout << "Iveskite " << n + 1 << "-a pazymi: "; cin >> hw[n];
                checkInput(hw[n]);

                if(hw[n] == 0){
                    break;
                }
                else {

                    n++;
                    int* hw_temp = new int[n + 1];

                    for(int i = 0; i < n; i++){
                        hw_temp[i] = hw[i];
                    }

                    delete[] hw;
                    hw = hw_temp;

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
        cout << "Iveskite egzamino vertinima: "; cin >> exam;
        checkInput(exam);
    }
    else if(tolower(choice) == 'n'){
        exam = rand() % 10 + 1;
        cout << "Sugeneruotas egzamino vertinimas: " << exam << '\n';
    }

    Student.fname = fname;
    Student.lname = lname;
    Student.n = n;
    Student.hw = hw;
    Student.exam = exam;

}