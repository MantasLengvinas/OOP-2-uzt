#include "functions.hpp"

bool _check(_student &a, _student &b){

    return a.lname < b.lname;

}

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

void readFile(vector<_student> &Students){

    try{

        std::ifstream input(file);

        if(!input){
            throw 1;
        }

        if(input.eof()){
            throw 4;
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

            if(!str){
                throw 2;
            }

            int val;
            while(str >> val){

                if(val < 1 || val > 10){
                    throw 3;
                }

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
    catch(int e) {

        switch (e)
        {
        case 1:
            cout << "Nepavyko atidaryti failo" << endl;
            break;
        case 2:
            cout << "Neteisingas failo formatas" << endl;
            break;
        case 3:
            cout << "Pazymys nepriklauso intervalui [1, 10]" << endl;
            break;
        case 4:
            cout << "Failas tuscias" << endl;
            break;
        
        default:
            cout << "Programos klaida" << endl;
            break;
        }

        cout << "Programa baigia darba ";
        exit(1);

    }

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