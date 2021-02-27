#include "functions.hpp"

int main(){

    char choice;
    vector<_student> Students;

    cout << "Duomenys norite irasyti patys (T) ar skaityti is failo (N)? "; cin >> choice;
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

    try{

        std::sort(Students.begin(), Students.end(), _check);

        std::ofstream output(outputFile);

        if(!output){
            throw 1;
        }

        cout << "Duomenu irasymas sekmingas." << '\n' << "Norite matyti vidurki (t) ar mediana (n)? "; cin >> choice;
        checkInput(choice);

        if(tolower(choice) == 't'){
            output << std::left
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
                
                output << std::left
                    << std::setw(20) << Students[i].lname
                    << std::setw(15) << Students[i].fname
                    << std::setw(15) << std::setprecision(2) << avg
                    << std::endl;

            }
        }
        else if (tolower(choice) == 'n'){
            output << std::left
                << std::setw(20) << "Pavarde"
                << std::setw(15) << "Vardas"
                << std::setw(10) << "Galutinis (Med.)"
                << std::endl
                << std::string(65, '-')
                << std::endl;

            for (int i = 0; i < Students.size(); i++){

                double median = 0;
                std::sort(Students[i].hw.begin(), Students[i].hw.end());

                if (Students[i].hw.size() % 2 == 1)
                    median = Students[i].hw[Students[i].hw.size() / 2];

                else median = (Students[i].hw[Students[i].hw.size() / 2] + Students[i].hw[Students[i].hw.size() / 2 - 1]) / 2;

                output << std::left
                    << std::setw(20) << Students[i].lname
                    << std::setw(15) << Students[i].fname
                    << std::setw(15) << std::setprecision(2) << median
                    << std::endl;

            }
        }

        output.close();

    }

    catch(std::exception e){
        cout << "Failu sistemos klaida" << endl;
    }

    return 0;
}

