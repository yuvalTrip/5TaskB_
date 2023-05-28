////
//// Created by yuvalbs on 5/28/23.
////
//
////#include "MagicalContainer.h"
//#include <iostream>
//#include <vector>
//#include <cmath>
//
//class MagicalContainer {
//private:
//    std::vector<int> elements;
//
//public:
//    // Add an element to the container
//    void addElement(int element) {
//        elements.push_back(element);
//    }
//
//    // Remove an element from the container
//    void removeElement(int element) {
//        for (auto it = elements.begin(); it != elements.end(); ++it) {
//            if (*it == element) {
//                elements.erase(it);
//                break;
//            }
//        }
//    }
//
//    // Get the size of the container
//    size_t size() const {
//        return elements.size();
//    }
//
//    // Iterator class for ascending order traversal
//    class AscendingIterator {
//    private:
//        const MagicalContainer& container;
//        size_t index;
//
//    public:
//        AscendingIterator(const MagicalContainer& container) : container(container), index(0) {}
//
//        int operator*() const {
//            return container.elements[index];
//        }
//
//        AscendingIterator& operator++() {
//            ++index;
//            return *this;
//        }
//
//        bool operator==(const AscendingIterator& other) const {
//            return &container == &other.container && index == other.index;
//        }
//
//        bool operator!=(const AscendingIterator& other) const {
//            return !(*this == other);
//        }
//    };
//
//    // Iterator class for cross order traversal
//    class SideCrossIterator {
//    private:
//        const MagicalContainer& container;
//        size_t frontIndex;
//        size_t backIndex;
//        bool isFront;
//
//    public:
//        SideCrossIterator(const MagicalContainer& container) : container(container), frontIndex(0), backIndex(container.size() - 1), isFront(true) {}
//
//        int operator*() const {
//            if (isFront) {
//                return container.elements[frontIndex];
//            } else {
//                return container.elements[backIndex];
//            }
//        }
//
//        SideCrossIterator& operator++() {
//            if (isFront) {
//                ++frontIndex;
//            } else {
//                --backIndex;
//            }
//            isFront = !isFront;
//            return *this;
//        }
//
//        bool operator==(const SideCrossIterator& other) const {
//            return &container == &other.container && frontIndex == other.frontIndex && backIndex == other.backIndex && isFront == other.isFront;
//        }
//
//        bool operator!=(const SideCrossIterator& other) const {
//            return !(*this == other);
//        }
//    };
//
//    // Iterator class for prime numbers traversal
//    class PrimeIterator {
//    private:
//        const MagicalContainer& container;
//        size_t index;
//
//        bool isPrime(int num) const {
//            if (num <= 1)
//                return false;
//            for (int i = 2; i <= std::sqrt(num); ++i) {
//                if (num % i == 0)
//                    return false;
//            }
//            return true;
//        }
//
//    public:
//        PrimeIterator(const MagicalContainer& container) : container(container), index(0) {
//            while (index < container.size() && !isPrime(container.elements[index])) {
//                ++index;
//            }
//        }
//
//        int operator*() const {
//            return container.elements[index];
//        }
//
//        PrimeIterator& operator++() {
//            ++index;
//            while (index < container.size() && !isPrime(container.elements[index])) {
//                ++index;
//            }
//            return *this;
//        }
//
//        bool operator==(const PrimeIterator& other) const {
//            return &container == &other.container && index == other.index;
//        }
//
//        bool operator!=(const PrimeIterator& other) const {
//            return !(*this == other);
//        }
//    };
//
//    // Get an AscendingIterator pointing to the first element
//    AscendingIterator begin() const {
//        return AscendingIterator(*this);
//    }
//
//    // Get an AscendingIterator pointing to one position past the last element
//    AscendingIterator end() const {
//        return AscendingIterator(*this);
//    }
//
//    // Get a SideCrossIterator pointing to the first element
//    SideCrossIterator beginCross() const {
//        return SideCrossIterator(*this);
//    }
//
//    // Get a SideCrossIterator pointing to one position past the last element
//    SideCrossIterator endCross() const {
//        return SideCrossIterator(*this);
//    }
//
//    // Get a PrimeIterator pointing to the first prime number
//    PrimeIterator beginPrime() const {
//        return PrimeIterator(*this);
//    }
//
//    // Get a PrimeIterator pointing to one position past the last prime number
//    PrimeIterator endPrime() const {
//        return PrimeIterator(*this);
//    }
//};
//
//int main() {
//    MagicalContainer container;
//    container.addElement(1);
//    container.addElement(2);
//    container.addElement(4);
//    container.addElement(5);
//    container.addElement(14);
//
//    std::cout << "Size of container: " << container.size() << std::endl;
//
//    std::cout << "Elements in ascending order:\n";
//    for (auto it = container.begin(); it != container.end(); ++it) {
//        std::cout << *it << ' ';
//    }
//    std::cout << std::endl;
//
//    std::cout << "Elements in cross order:\n";
//    for (auto it = container.beginCross(); it != container.endCross(); ++it) {
//        std::cout << *it << ' ';
//    }
//    std::cout << std::endl;
//
//    std::cout << "Prime numbers:\n";
//    for (auto it = container.beginPrime(); it != container.endPrime(); ++it) {
//        std::cout << *it << ' ';
//    }
//    std::cout << std::endl;
//
//    container.removeElement(4);
//    std::cout << "Size of container after removing an element: " << container.size() << std::endl;
//
//    return 0;
//}