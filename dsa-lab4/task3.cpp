#include <iostream>
#include <string>

using namespace std;

struct BinaryBit {
    bool value;
    BinaryBit* next;
    BinaryBit* previous;

    explicit BinaryBit(bool bitValue)
        : value(bitValue), next(nullptr), previous(nullptr) {}
};

class BinaryNumber {
private:
    BinaryBit* head;
    BinaryBit* tail;

    void clear() {
        BinaryBit* current = head;
        while (current != nullptr) {
            BinaryBit* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
    }

public:
    BinaryNumber() : head(nullptr), tail(nullptr) {}

    BinaryNumber(const BinaryNumber& other) : head(nullptr), tail(nullptr) {
        BinaryBit* current = other.head;
        while (current != nullptr) {
            addBitAtEnd(current->value);
            current = current->next;
        }
    }
    BinaryNumber& operator=(const BinaryNumber& other) {
        if (this != &other) {
            clear();
            BinaryBit* current = other.head;
            while (current != nullptr) {
                addBitAtEnd(current->value);
                current = current->next;
            }
        }
        return *this;
    }
    ~BinaryNumber() {
        clear();
    }
    void addBitAtEnd(bool bitValue) {
        BinaryBit* newBit = new BinaryBit(bitValue);
        if (head == nullptr) {
            head = tail = newBit;
        } else {
            tail->next = newBit;
            newBit->previous = tail;
            tail = newBit;
        }
    }
    void addBitAtFront(bool bitValue) {
        BinaryBit* newBit = new BinaryBit(bitValue);
        if (head == nullptr) {
            head = tail = newBit;
        } else {
            newBit->next = head;
            head->previous = newBit;
            head = newBit;
        }
    }
    void loadFromString(const string& text) {
        clear();
        for (char ch : text) {
            if (ch == '0' || ch == '1') {
                addBitAtEnd(ch - '0');
            }
        }
        int length = getLength();
        int remainder = length % 8;
        if (remainder != 0 || length == 0) {
            int paddingNeeded = 8 - remainder;
            for (int i = 0; i < paddingNeeded; ++i) {
                addBitAtFront(false);
            }
        }
    }
    int getLength() const {
        int count = 0;
        BinaryBit* current = head;
        while (current != nullptr) {
            ++count;
            current = current->next;
        }
        return count;
    }
    void display() const {
        BinaryBit* current = head;
        int count = 0;
        while (current != nullptr) {
            cout << current->value;
            ++count;
            if (count % 8 == 0 && current->next != nullptr) {
                cout << " ";
            }
            current = current->next;
        }
        cout << endl;
    }
    void invertBits() {
        BinaryBit* current = head;
        while (current != nullptr) {
            current->value = !current->value;
            current = current->next;
        }
    }
    void twoComplement() {
        invertBits();
        BinaryBit* current = tail;
        bool carry = true;

        while (current != nullptr && carry) {
            bool sum = current->value ^ carry;
            carry = current->value && carry;
            current->value = sum;
            current = current->previous;
        }

        if (carry) {
            addBitAtFront(true);
        }
    }
    static BinaryNumber add(const BinaryNumber& left, const BinaryNumber& right) {
        BinaryNumber result;
        BinaryBit* leftBit = left.tail;
        BinaryBit* rightBit = right.tail;
        bool carry = false;

        while (leftBit != nullptr || rightBit != nullptr || carry) {
            int total = carry ? 1 : 0;
            if (leftBit != nullptr) {
                total += leftBit->value;
                leftBit = leftBit->previous;
            }
            if (rightBit != nullptr) {
                total += rightBit->value;
                rightBit = rightBit->previous;
            }

            carry = (total >= 2);
            result.addBitAtFront(total % 2);
        }

        return result;
    }
    static BinaryNumber multiply(const BinaryNumber& left, const BinaryNumber& right) {
        BinaryNumber result;
        result.addBitAtEnd(false);

        BinaryNumber shiftedValue = left;
        BinaryBit* currentRight = right.tail;

        while (currentRight != nullptr) {
            if (currentRight->value == true) {
                result = BinaryNumber::add(result, shiftedValue);
            }
            shiftedValue.addBitAtEnd(false);
            currentRight = currentRight->previous;
        }

        return result;
    }

    long long toDecimal() const {
        BinaryBit* current = tail;
        long long decimalValue = 0;
        long long base = 1;

        while (current != nullptr) {
            if (current->value) {
                decimalValue += base;
            }
            base *= 2;
            current = current->previous;
        }

        return decimalValue;
    }
};

int main() {
    BinaryNumber firstNumber, secondNumber;
    string firstInput, secondInput;

    cout << "enter your first binary number: ";
    cin >> firstInput;
    firstNumber.loadFromString(firstInput);
    cout << "in a clean 8-bit format: ";
    firstNumber.display();

    cout << "enter your second binary number: ";
    cin >> secondInput;
    secondNumber.loadFromString(secondInput);
    cout << "in a clean 8-bit format: ";
    secondNumber.display();

    BinaryNumber firstOnesComplement = firstNumber;
    firstOnesComplement.invertBits();
    cout << "\nFirst number after 1's complement: ";
    firstOnesComplement.display();

    BinaryNumber secondTwosComplement = secondNumber;
    secondTwosComplement.twoComplement();
    cout << "Second number after 2's complement: ";
    secondTwosComplement.display();

    BinaryNumber sum = BinaryNumber::add(firstNumber, secondNumber);
    cout << "\nAddition result: ";
    sum.display();
    cout << "Decimal value of the sum: " << sum.toDecimal() << endl;

    BinaryNumber product = BinaryNumber::multiply(firstNumber, secondNumber);
    cout << "\nMultiplication result: ";
    product.display();
    cout << "Decimal value of the product: " << product.toDecimal() << endl;

    return 0;
}


