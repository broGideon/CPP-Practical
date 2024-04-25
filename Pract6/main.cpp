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

    Practice(wstring &discipline, wstring &studentName, wstring &studentSurname, wstring &&studentGroup, wstring &professorName, wstring &professorSurname)
            : discipline(discipline), studentName(studentName), studentSurname(studentSurname), studentGroup(studentGroup), professorName(professorName), professorSurname(professorSurname) {}
};

class Human {
public:
    wstring _surname;
    wstring _firstName;
    wstring _middleName;
    unsigned _age;

    Human(wstring &surname, wstring &firstName, wstring &middleName, unsigned &age) : _surname(surname), _firstName(firstName), _middleName(middleName), _age(age) {}

    virtual void Main() {}
    virtual wstring GetName() {
        return  _firstName;
    }
    virtual wstring GetSurname() {
        return _surname;
    }
};

class Professor : public Human {
public:
    wstring discipline;
    vector<Practice>& practices;

    Professor(wstring surname, wstring firstName, wstring middleName, unsigned age, wstring discipline, vector<Practice>& practices)
    : Human(surname, firstName, middleName, age), discipline(discipline), practices(practices) {
        wcout << L"Вы зарегестрировали нового преподователя: " << endl;
        wcout << L"Дисциплина -- " << this->discipline << endl <<
              L"Имя --" << this->_firstName << endl <<
              L"Фамилия --" << this->_surname << endl <<
              L"Отчество --" << this->_middleName << endl <<
              L"Возраст -- " << this->_age << endl;
    }

    void Main() override {
        wcout << L"Выберите какую практическую вы хотите проверить:" << endl;
        int i = 0;
        for (Practice practice : this->practices) {
            wcout << i << L" . " << practice.studentName << " " << practice.professorSurname << endl;
            i++;
        }
        wcout << endl;
        wcin >> i;

        wcout << L"Вы выбрали практическую" << this->practices[i].studentName << " " << this->practices[i].studentSurname << endl;
        wcout << endl;
        wcout << L"Поставьте оценцу от 1 до 5 за практическую" << endl;
        wcin >> this->practices[i].score;
        wcout << L"Вы поставлили " << this->practices[i].score << L"На практическую " << this->practices[i].studentName << L" "
              << this->practices[i].studentSurname << endl;
    }

    wstring GetName() override {
        return this->_firstName;
    }

    wstring GetSurname() override {
        return this->_surname;
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

class Student : Human {
public:
    wstring group;
    wstring faculty;
    vector<Professor>& professors;

    Student(wstring surname, wstring firstName, wstring middleName, unsigned age, wstring group, wstring faculty, vector<Professor>& professors)
            : Human(surname, firstName, middleName, age), group(group), faculty(faculty), professors(professors) {
        wcout << L"Вы зарегестрировали нового студента" << endl;
        wcout << L"Факультет -- " << this->faculty << endl
              << L"Группа -- " << this->group << endl
              << L"Фамилия -- " << this->_surname << endl
              << L"Имя -- " << this->_firstName << endl
              << L"Отчество -- " << this->_middleName << endl
              << L"Возраст -- " << this->_age << endl;
    }

    void Main() override {
        wcout << L"Выберите кому хотите сдать практос:\n";
        for (int i = 0; i < this->professors.size(); i++) {
            wcout << i + 1;
            this->professors[i].Display();
        }

        unsigned num;
        wcin >> num;

        map<wstring, wstring> professorData = this->professors[num - 1].GetInfo();
        //Сделать создание практоса

        //return Practice(professorData["discipline"], this->_firstName, this->_surname, this->group, professorData["firstName"], professorData["surname"]);
    }

    wstring GetName() override {
        return this->_firstName;
    }

    wstring GetSurname() override {
        return this->_surname;
    }
};

Student createStudent(vector<Professor>& professors) {
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

    wstring group;
    wcout << L"Введите группу студунта" << endl;
    wcin >> group;

    wstring faculty;
    wcout << L"Введите факультет студунта" << endl;
    wcin >> faculty;

    return Student(surname, firstName, middleName, age, group, faculty, professors);
}

Professor createProfessor(vector<Practice>& Practices) {
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

    return Professor(surname, firstName, middleName, age, discipline, Practices);
}

map<wstring, wstring> getAccountData() {
    map<wstring, wstring> accData;
    wcout << L"Введите имя" << endl;
    wcin >> accData[L"Name"];

    wstring surname;
    wcout << L"Введите фамилию" << endl;
    wcin >> accData[L"Surname"];;

    return accData;
}

template<typename T>
short auth(vector<T>& accounts) {
    map<wstring, wstring> accData = getAccountData();
    short i = 0;
    for (auto& account : accounts)
    {
        if (accData[L"Name"] == account.GetName() && accData[L"Surname"] == account.GetSurname()) return i;
        i++;
    }
    throw runtime_error("Аккаунт не найден");
}

void authorization(int& choice, vector<Professor>& listProfessors, vector<Student>& listStudents) {
    choice = 0;
    short checkAuth = -1;
    while (choice != 3) {
        //system("cls");
        wcout << L"Выберите за кого хотите авторизоваться: " << endl;
        wcout << L"1. Препод" << endl;
        wcout << L"2. Студент" << endl;
        wcout << L"3. Выйти" << endl;
        wcin >> choice;

        try {
            switch (choice) {
                case 1:
                    checkAuth = auth(listProfessors);
                    break;
                case 2:
                    checkAuth = auth(listStudents);
                    break;
                case 3:
                    wcout << L"Выход" << endl;
                default:
                    wcout << L"Выберите числов от 1 до 3" << endl;
                    break;
            }
        }
        catch (runtime_error& e) {
            wcout << endl << L"Аккаунт не найден" << endl << endl;
        }

        if (checkAuth != -1 && choice = 1) {
            listProfessors[checkAuth].Main();
        } else if (checkAuth != -1 && choice = 2) {
            listStudents[checkAuth].Main();
        }
    }
}

void registration(int& choice, vector<Professor>& listProfessors, vector<Student>& listStudents, vector<Practice>& listPractices) {
    choice = 0;
    while (choice != 3) {
        //system("cls");
        wcout << L"Выберите за кого хотите создать: " << endl;
        wcout << L"1. Препод" << endl;
        wcout << L"2. Студент" << endl;
        wcout << L"3. Выйти" << endl;
        wcin >> choice;

        switch (choice) {
            case 1:
                listProfessors.push_back(createProfessor(listPractices));
                break;
            case 2:
                listStudents.push_back(createStudent(listProfessors));
                break;
            case 3:
                wcout << L"Выход" << endl;
            default:
                wcout << L"Выберите числов от 1 до 3" << endl;
                break;
        }
    }
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);

    vector<Professor> listProfessors;

    vector<Practice> listPractice;

    vector<Student> listStudents;

    listProfessors.push_back(Professor(L"Фамилия", L"Имя", L"Отчество", 25, L"ОАИП", listPractice));
    listProfessors.push_back(Professor(L"1", L"1", L"1", 25, L"ОАИП", listPractice));
    listProfessors.push_back(Professor(L"2", L"2", L"2", 25, L"ОАИП", listPractice));

    listStudents.push_back(Student(L"Фамилия", L"Имя", L"Отчество", 25, L"П50-3-22", L"ИСИП", listProfessors));
    listStudents.push_back(Student(L"1", L"1", L"1", 25, L"П50-3-22", L"ИСИП", listProfessors));
    listStudents.push_back(Student(L"2", L"2", L"2", 25, L"П50-3-22", L"ИСИП", listProfessors));

    int choice;
    while (choice != 3) {
        wcout << L"Выберите за кого хотите зайти: " << endl;
        wcout << L"1. Авторизоваться" << endl;
        wcout << L"2. Зарегаться" << endl;
        wcout << L"3. Выйти" << endl;
        wcin >> choice;

        switch (choice) {
            case 1:
                authorization(choice, listProfessors, listStudents);
                break;
            case 2:
                registration(choice, listProfessors, listStudents, listPractice);
                break;
            default:
                break;
        }
    }
    //войти за студента или не за студента создать практос, проверить его и тд
    return 0;
}