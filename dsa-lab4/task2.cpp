

#include <iostream>
using namespace std;
struct Person {
    int id;
    Person* next;
};

class JosephusCircle {
public:
    Person* head;
    Person* tail;
    JosephusCircle() {
        head = nullptr;
        tail = nullptr;
    }
    void addPerson(int id) {
        Person* newPerson = new Person;
        newPerson->id = id;
        newPerson->next = nullptr;

        if (head == nullptr) {
            head = newPerson;
            tail = newPerson;
            tail->next = head;
        } else {
            tail->next = newPerson;
            tail = newPerson;
            tail->next = head;
        }
    }
    void deletePerson(int id) {
        if (head == nullptr) return;

        Person* current =  head;
        Person* prev = tail;

        do {
            if (current->id == id) {
                if (current == head) {
                    head = head->next;
                    tail->next = head;
                } else {
                    prev->next =  current->next;
                }
                if (current == tail) {
                   tail = prev;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        } while (current != head);
    }

    void displayPersons() {
        if(head == nullptr) 
           return;
        Person* current = head;
        do {
            cout << current->id <<" ";
            current = current->next;
        } while (current != head);
        cout << endl;
    }
};
int main() {
    int N, k;

    cout << "Enter number of people (N): ";
    cin >> N;
    cout << "Enter step count (k): ";
    cin >> k;
    JosephusCircle circle;
    for (int i = 1; i <= N; ++i) {
        circle.addPerson(i);
    }
    cout << "Initial Circle: ";
    circle.displayPersons();

    Person* current = circle.head;
    while (N > 1) {
        for (int count = 1; count < k; ++count) {
            current = current->next;
        }
        cout << "Eliminated: " << current->id << endl;
        int eliminatedId = current->id;
        current = current->next;
        circle.deletePerson(eliminatedId);
        --N;
    }

    cout << "Survivor: " << circle.head->id << endl;
    return 0;
}