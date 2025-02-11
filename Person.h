#ifndef LAB3_PERSON_H
#define LAB3_PERSON_H
struct PersonID {
    int id;
};

class Person {
private:
    PersonID id;
    wstring firstName;
    wstring middleName;
    wstring lastName;

public:
    PersonID GetID() {
        return id;
    };
    wstring GetFirstName() {
        return firstName;
    };
    wstring GetMiddleName() {
        return middleName;
    };
    wstring GetLastName() {
        return lastName;
    };
    void SetID(int id) {
        this->id.id = id;
    }
    void SetFirstName(wstring firstName) {
        this->firstName = firstName;
    };
    void SetMiddleName(wstring middleName) {

        this->middleName = middleName;
    };
    void SetLastName(wstring lastName) {
        this->lastName = lastName;
    };
};
#endif //LAB3_PERSON_H
