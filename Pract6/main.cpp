#include <iostream>
#include <Windows.h>
#include <fcntl.h>
#include <vector>
#include <map>

using namespace std;

class Practice {
public:
    wstring discipline;
    wstring studentName;
    wstring studentSurname;
    wstring studentGroup;
    wstring professorName;
    wstring professorSurname;
    unsigned score;

    Practice(wstring &discipline, wstring &studentName, wstring &studentSurname, wstring &studentGroup,
             wstring &professorName, wstring &professorSurname)
            : discipline(discipline), studentName(studentName), studentSurname(studentSurname),
              studentGroup(studentGroup), professorName(professorName), professorSurname(professorSurname) {}
};

class People {
public:
    wstring _surname;
    wstring _firstName;
    wstring _middleName;
    unsigned _age;

    People(wstring &surname, wstring &firstName, wstring &middleName, unsigned &age) : _surname(surname), _firstName(firstName), _middleName(middleName), _age(age) {}

    virtual void Main() {}
};

class Professor : public People {
public:
    wstring discipline;

    Professor(wstring &surname, wstring &firstName, wstring &middleName, unsigned &age, wstring &discipline) : People(
            surname, firstName, middleName, age), discipline(discipline) {
        wcout << L"Вы зарегестрировали нового преподователя: " << endl;
        wcout << L"Дисциплина -- " << this->discipline << endl <<
              L"Имя --" << this->_firstName << endl <<
              L"Фамилия --" << this->_surname << endl <<
              L"Отчество --" << this->_middleName << endl <<
              L"Возраст -- " << this->_age << endl;
    }

    void Main(vector<Practice> &Practices) {
        wcout << L"Выберите какую практическую вы хотите проверить:" << endl;
        int i = 0;
        for (Practice practice: Practices) {
            wcout << i << L" . " << practice.studentName << " " << practice.professorSurname << endl;
            i++;
        }
        wcout << endl;
        wcin >> i;

        wcout << L"Вы выбрали практическую" << Practices[i].studentName << " " << Practices[i].studentSurname << endl;
        wcout << endl;
        wcout << L"Поставьте оценцу от 1 до 5 за практическую" << endl;
        wcin >> Practices[i].score;
        wcout << L"Вы поставлили " << Practices[i].score << L"На практическую " << Practices[i].studentName << L" "
              << Practices[i].studentSurname << endl;
    }

    void Display() {
        wcout << L"Дисциплина: " << this->discipline << L"\nПрепод: " << this->_surname << " " << this->_firstName
              << " " << this->_middleName;
    }

    map<wstring, wstring> GetInfo() {
        map<wstring, wstring> ProfessorData;
        ProfessorData[L"firstName"] = this->_firstName;
        ProfessorData[L"surname"] = this->_surname;
        ProfessorData[L"middleName"] = this->_middleName;
        ProfessorData[L"discipline"] = this->discipline;
        return ProfessorData;
    }
};

class Student : People {
public:
    wstring groupe;
    wstring faculty;
    unsigned attendance;

    Student(wstring &surname, wstring &firstName, wstring &middleName, unsigned &age, wstring &groupe, wstring &faculty)
            : People(surname, firstName, middleName, age), groupe(groupe), faculty(faculty) {
        wcout << L"Вы зарегестрировали нового студента" << endl;
        wcout << L"Факультет -- " << this->faculty << endl
              << L"Группа -- " << this->groupe << endl
              << L"Фамилия -- " << this->_surname << endl
              << L"Имя -- " << this->_firstName << endl
              << L"Отчество -- " << this->_middleName << endl
              << L"Возраст -- " << this->_age << endl;
    }

    Practice Main(vector<Professor> &professors) {
        wcout << L"Выберите кому хотите сдать практос:\n";
        for (int i = 0; i < professors.size(); i++) {
            wcout << i + 1;
            professors[i].Display();
        }

        unsigned num;
        wcin >> num;

        map<wstring, wstring> professorData = professors[num - 1].GetInfo();

        return Practice(professorData[L"discipline"], this->_firstName, this->_surname, this->groupe, professorData[L"firstName"], professorData[L"surname"]);
    }


};

Student createStudent() {
    wstring surname;
    wcout << L"Введите фамилия студунта" << endl;
    wcin >> surname;

    wstring firstName;
    wcout << L"Введите имя студунта" << endl;
    wcin >> firstName;

    wstring middleName;
    wcout << L"Введите отчество студунта" << endl;
    wcin >> middleName;

    unsigned age;
    wcout << L"Введите возраст студунта" << endl;
    wcin >> age;

    wstring groupe;
    wcout << L"Введите группу студунта" << endl;
    wcin >> groupe;

    wstring faculty;
    wcout << L"Введите факультет студунта" << endl;
    wcin >> faculty;

    return Student(surname, firstName, middleName, age, groupe, faculty);
}

Professor createProfessor() {
    wstring firstName;
    wcout << L"Введите имя препода" << endl;
    wcin >> firstName;

    wstring surname;
    wcout << L"Введите фамилия препода" << endl;
    wcin >> surname;

    wstring middleName;
    wcout << L"Введите отчество препода" << endl;
    wcin >> middleName;

    unsigned age;
    wcout << L"Введите возраст препода" << endl;
    wcin >> age;

    wstring discipline;
    wcout << L"Введите дисциплина препода" << endl;
    wcin >> discipline;

    return Professor(surname, firstName, middleName, age, discipline);
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);

    vector<Professor> listProfessors;
    vector<Student> listStudents;

    unsigned choise;
    while (choise != 3) {
        //system("cls");
        wcout << L"Выберите за кого хотите зайти: " << endl;
        wcout << L"1. Препод" << endl;
        wcout << L"2. Студент" << endl;
        wcout << L"3. Выйти" << endl;
        wcin >> choise;

        switch (choise) {
            case 1:
                listProfessors.push_back(createProfessor());
                break;
            case 2:
                listStudents.push_back(createStudent());
                break;
            case 3:
                wcout << L"Выход" << endl;
            default:
                wcout << L"Выберите числов от 1 до 3" << endl;
                break;
        }
    }
    //войти за студента или не за студента создать практос, проверить его и тд
    return 0;
}