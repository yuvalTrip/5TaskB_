//
// Created by yuvalbs on 5/28/23.
//

//#include "MagicalContainer.h"
#include <iostream>
#include <vector>
#include <cmath>
namespace ariel {

    class MagicalContainer {
    private:
        std::vector<int> elements;
        std::vector<int> primeIterator;
        std::vector<int> crossIterator;
        std::vector<int> ascendIterator;
    public:
        int contains(int number) const
        {
            for (std::vector<int>::size_type i=0;i<elements.size();i++) {
                if (elements[i]==number){return 1;}
            }
            return 0;
        }
        void buildCrossVector(){
//    int size_elements=elements_asc.size();
//    std::cout<<"elements_asc.size: "<<elements_asc.size()<<std::endl;

//            if (elements.size()>0) {
                if (!elements.empty()) {

//        std::cout<<"elements_asc.size>0: "<<elements_asc.size()<<std::endl;
//                First I will sort it -as needed in demo
                std::sort(elements.begin(), elements.end());
                //After the sort I will start to take one index from the start and other from the end
                std::vector<int> sideCrossArray;
////
                std::vector<int>::size_type left = 0;                            // Left pointer starting from the beginning
                std::vector<int>::size_type right = elements.size() - 1;      // Right pointer starting from the end
                //std::cout << "right: " << right << std::endl;
                // Perform side cross operation
                while (left <= right) {
                    //       std::cout << "left: " << left << " value="<<elements_asc[left]<<std::endl;


                    sideCrossArray.push_back(elements[left]);

                    if (left != right) {
                        sideCrossArray.push_back(elements[right]);
                        //          std::cout << "right: " << right << " value="<<elements_asc[right]<<std::endl;
                        right--;
                    }
                    left++;

                }
                crossIterator=sideCrossArray;

            } else {
                crossIterator = {};
            }
            //   std::cout << "currentIndex-builder: "<< currentIndex <<std::endl;

        }


        void static insertIntoSortedList(std::vector<int>& sortedList, int number) {
            std::vector<int>::size_type index = 0;
            while (index < sortedList.size() && sortedList[index] < number) {
                index++;
            }

            sortedList.push_back(0);  // Make room for the new number at the end

            for (std::vector<int>::size_type i = sortedList.size() - 1; i > index; i--) {
                sortedList[i] = sortedList[i - 1];  // Shift elements to the right
            }
            sortedList[index] = number;  // Insert the number at the correct position

        }
        // Add an element to the container
        void addElement(int element) {
            elements.push_back(element);
            if (PrimeIterator::isPrime(element)) //if this is a prime number we will add it to prime iterator
            {
                primeIterator.push_back(element);
            }
            std::sort(primeIterator.begin(), primeIterator.end());

            //add to ascending iterator
            insertIntoSortedList(ascendIterator, element);
            //add to cross iterator
            buildCrossVector();
        }

        // Remove an element from the container
        void removeElement(int element) {
            //delete from general vector
//            for (auto it = elements.begin(); it != elements.end(); ++it) {
//                if (*it == element) {
//                    elements.erase(it);
//                    std::cout<<"now the size is: "<<elements.size()<<std::endl;
////                    std::cout<<"elements.begin(): "<<elements.begin()<<std::endl;
////                    std::cout<<"elements.end(): "<<elements.end()<<std::endl;
//
//                    break;
//                }
//            }

            // Delete from general vector
            elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());

            // Delete from crossIterator
            crossIterator.erase(std::remove(crossIterator.begin(), crossIterator.end(), element), crossIterator.end());

            // Delete from primeIterator
            primeIterator.erase(std::remove(primeIterator.begin(), primeIterator.end(), element), primeIterator.end());

            // Delete from ascendIterator
            ascendIterator.erase(std::remove(ascendIterator.begin(), ascendIterator.end(), element), ascendIterator.end());

//            //delete from crossIterator
//            for (auto it = crossIterator.begin(); it != crossIterator.end(); ++it) {
//                if (*it == element) {
//                    crossIterator.erase(it);
//                }
//            }
//            //delete from primeIterator
//            for (auto it = primeIterator.begin(); it != primeIterator.end(); ++it) {
//                if (*it == element) {
//                    primeIterator.erase(it);
//                }
//            }
//            //delete from ascendIterator
//            for (auto it = ascendIterator.begin(); it != ascendIterator.end(); ++it) {
//                if (*it == element) {
//                    ascendIterator.erase(it);
//                }
//            }
        }

        // Get the size of the container
        size_t size() const {
            return elements.size();
        }

        // Iterator class for ascending order traversal
        class AscendingIterator {
        private:
            const MagicalContainer &container;
            size_t index;

        public:
            AscendingIterator(const MagicalContainer &container) : container(container), index(0) {}

            int operator*() const {
                std::cout<<"[index]: "<<index<<std::endl;

                std::cout<<"container.elements[index]: "<<container.elements[index]<<std::endl;
                return container.elements[index];
            }

            int operator++() {

                if (index+1>container.elements.size()-1)
                {
                    throw std::invalid_argument("Out of bounds!");
                }
                if(index<container.elements.size() -1){
                    index++;
                }
                return container.elements[index];

//                ++index;
//                return *this;
            }

            bool operator==(const AscendingIterator &other) const {
                return &container == &other.container && index == other.index;
            }

            bool operator!=(const AscendingIterator &other) const {
                return !(*this == other);
            }

            // Get an AscendingIterator pointing to the first element
//            AscendingIterator begin() const {
//                return AscendingIterator(*this);
//            }

             const int * begin() {
//                std::cout<<"container.ascendIterator.size(): "<<container.ascendIterator.size()<<std::endl;
                if (container.ascendIterator.empty()) {
                    return NULL;
                }
//                else{
//                    std::cout<<"container.ascendIterator[0]: "<<container.ascendIterator[0]<<std::endl;
                    return &(container.ascendIterator[0]);
//                }
            }
            // Get an AscendingIterator pointing to one position past the last element
            const int * end(){
                if (container.ascendIterator.empty()) {
                    return NULL;
                }
//                else{
                    return &container.ascendIterator[container.ascendIterator.size()-1]+1;

//                }
            }
        };
//            AscendingIterator end() const {
//                return AscendingIterator(*this);
//            }
        // Iterator class for cross order traversal
        class SideCrossIterator {
        private:
            const MagicalContainer &container;
            size_t frontIndex;
            size_t backIndex;
            size_t currentIndex=0;
            bool isFront;

        public:
            SideCrossIterator(const MagicalContainer &container) : container(container), frontIndex(0),
                                                                   backIndex(container.size() - 1), isFront(true) {}

            int operator*() const {
                if (isFront) {
                    return container.elements[frontIndex];
                }
//                else {
                    return container.elements[backIndex];
//                }
            }

//            SideCrossIterator &operator++() {
//                if (isFront) {
//                    ++frontIndex;
//                } else {
//                    --backIndex;
//                }
//                isFront = !isFront;
//                return *this;
//            }
            int operator++(){//just iterate ovel the crossIterator
                if (currentIndex+1>container.crossIterator.size()-1)
                {
                    throw std::invalid_argument("Out of bounds!");
                }
                if(currentIndex<container.crossIterator.size() -1){
                    currentIndex++;
                }
                return container.crossIterator[currentIndex];
            }

            bool operator==(const SideCrossIterator &other) const {
                return &container == &other.container && frontIndex == other.frontIndex &&
                       backIndex == other.backIndex && isFront == other.isFront;
            }

            bool operator!=(const SideCrossIterator &other) const {
                return !(*this == other);
            }

            // Get a SideCrossIterator pointing to the first element
//            SideCrossIterator begin() const {
//                return SideCrossIterator(*this);
//            }
            const int * begin() {
//                std::cout<<"container.ascendIterator.size(): "<<container.ascendIterator.size()<<std::endl;
                if (container.crossIterator.empty()) {
                    return NULL;
                }
//                else{
//                    std::cout<<"container.ascendIterator[0]: "<<container.ascendIterator[0]<<std::endl;
                    return &(container.crossIterator[0]);
//                }
            }

            // Get a SideCrossIterator pointing to one position past the last element
//            SideCrossIterator end() const {
//                return SideCrossIterator(*this);
//            }
            const int * end(){
                if (container.crossIterator.empty()) {
                    return NULL;
                }
//                else{
                    return &container.crossIterator[container.crossIterator.size()-1]+1;

//                }
            }

        };

        // Iterator class for prime numbers traversal
        class PrimeIterator {
        private:
            const MagicalContainer &container;
            size_t index;
            size_t currentIndex=0;


        public:
            static bool isPrime(int num) {
                if (num <= 1)
                {return false;}
                for (int i = 2; i <= std::sqrt(num); ++i) {
                    if (num % i == 0)
                    { return false;}
                }
                return true;
            }

            PrimeIterator(const MagicalContainer &container) : container(container), index(0) {
                while (index < container.size() && !isPrime(container.elements[index])) {
                    ++index;
                }
            }

            int operator*() const {
                return container.elements[index];
            }

//            PrimeIterator &operator++() {
//                ++index;
//                while (index < container.size() && !isPrime(container.elements[index])) {
//                    ++index;
//                }
//                return *this;
//            }
            int operator++(){//just iterate ovel the crossIterator
                if (currentIndex+1>container.primeIterator.size()-1)
                {
                    throw std::invalid_argument("Out of bounds!");
                }
                if(currentIndex<container.primeIterator.size() -1){
                    currentIndex++;
                }
                return container.primeIterator[currentIndex];
            }

            bool operator==(const PrimeIterator &other) const {
                return &container == &other.container && index == other.index;
            }

            bool operator!=(const PrimeIterator &other) const {
                return !(*this == other);
            }

            // Get a PrimeIterator pointing to the first prime number
//            PrimeIterator begin() const {
//                return PrimeIterator(*this);
//            }
            const int * begin() {
//                std::cout<<"container.ascendIterator.size(): "<<container.ascendIterator.size()<<std::endl;
                if (container.primeIterator.empty()) {
                    return NULL;
                }
//                else
//                {
//                    std::cout<<"container.ascendIterator[0]: "<<container.ascendIterator[0]<<std::endl;
                    return &(container.primeIterator[0]);
//                }
            }
            // Get a PrimeIterator pointing to one position past the last prime number
//            PrimeIterator end() const {
//                return PrimeIterator(*this);
//            }
            const int * end(){
                if (container.primeIterator.empty()) {
                    return NULL;
                }
//                else{
                    return &container.primeIterator[container.primeIterator.size()-1]+1;

//                }
            }
        };






    };
}

