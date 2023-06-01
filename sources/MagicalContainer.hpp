#include <iostream>
#include <vector>
#include <cmath>

namespace ariel {

    class MagicalContainer {
    private:
        std::vector<int> elements;
        std::vector<int> primeIndexIterator;//iterate over elements and save the index to a prime number
        std::vector<int>::size_type primeIndex=0;//Define index to prime numbers in elements vector
    public:
        int contains(int number) const
        {
            for (std::vector<int>::size_type i=0;i<elements.size();i++) {
                if (elements[i]==number){return 0;}
            }
            return 1;
        }


        void addElement(int element) {
            elements.push_back(element);
            //Sort 'elements' vector
            std::sort(elements.begin(), elements.end());

            // Reset the primeIndexIterator
            primeIndexIterator.clear();
            //std::cout<<" N E W  A D D ********"<<std::endl;
            //For each element we will check if this is prime number
            for (std::vector<int>::size_type i = 0; i< elements.size(); i++) {
                // std::cout<<"primeIndex: "<<primeIndex<<std::endl;

                // Access each item in the elements vector
                if (PrimeIterator::isPrime(elements[i]))//if this is a prime number
                {
                     std::cout<<"i: "<<i<<std::endl;
                     std::cout<<"elements[i]: "<<elements[i]<<std::endl;
                    primeIndexIterator.push_back(i);  // Store the index in primePointerIterator
                }
                primeIndex++;
            }
        }

        void removeElement(int element) {
            // Delete from general vector
            elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
        }

        std::vector<int>::size_type size() const {
            return elements.size();
        }

        class AscendingIterator {
        private:
            MagicalContainer& container;
            std::vector<int>::size_type index;

        public:
            AscendingIterator(MagicalContainer& container) : container(container), index(0) {}

            AscendingIterator(const AscendingIterator& other) : container(other.container), index(other.index) {}

            AscendingIterator& operator=(const AscendingIterator& other) {
                container = other.container;
                index = other.index;
                return *this;
            }

            // Default Destructor
            ~AscendingIterator() = default;

            // Move Constructor-added because of TIDY errors
            AscendingIterator(AscendingIterator&& other) noexcept
                    : container(other.container), index(other.index) {
                other.index = 0;
            }
            // Move Assignment Operator-added because of TIDY errors
            AscendingIterator& operator=(AscendingIterator&& other) noexcept {
                if (this != &other) {
                    container = other.container;
                    index = other.index;
                    other.index = 0;
                }
                return *this;
            }
            bool operator==(const AscendingIterator& other) const {
                return index == other.index;
            }

            bool operator!=(const AscendingIterator& other) const {
                return index != other.index;
            }

            bool operator>(const AscendingIterator& other) const {
                return index > other.index;
            }

            bool operator<(const AscendingIterator& other) const {
                return index < other.index;
            }

            int operator*() const {
                return container.elements[index];
            }

            AscendingIterator& operator++() {
                        std::cout << "index: "<< index <<std::endl;

                if (index>container.elements.size()-1)
                {
                    std::cout << "FALL HERE ="<<std::endl;

                    throw std::invalid_argument("Out of bounds!");
                }
                ++index;
                return *this;
            }

             AscendingIterator begin() {
                return AscendingIterator(container);
            }

             AscendingIterator end() {
                AscendingIterator iter(container);
                iter.index = container.size();
                return iter;
            }
        };

        class SideCrossIterator {
        private:
            MagicalContainer& container;
            std::vector<int>::size_type frontIndex;
            std::vector<int>::size_type backIndex;
            bool frontTurn;

        public:
            SideCrossIterator(MagicalContainer& container)
                    : container(container), frontIndex(0), backIndex(container.size() - 1), frontTurn(true) {}

            SideCrossIterator(const SideCrossIterator& other)
                    : container(other.container), frontIndex(other.frontIndex), backIndex(other.backIndex),
                      frontTurn(other.frontTurn) {}

            SideCrossIterator& operator=(const SideCrossIterator& other) {
                container = other.container;
                frontIndex = other.frontIndex;
                backIndex = other.backIndex;
                frontTurn = other.frontTurn;
                return *this;
            }

            // Default Destructor
            ~SideCrossIterator() = default;

            // Move Constructor-added because of TIDY errors
            SideCrossIterator(SideCrossIterator&& other) noexcept
                    : container(other.container), frontIndex(other.frontIndex), backIndex(other.backIndex),
            frontTurn(other.frontTurn) {
                other.frontIndex = 0;
                other.backIndex = 0;
            }

            // Move Assignment Operator-added because of TIDY errors
            SideCrossIterator& operator=(SideCrossIterator&& other) noexcept {
                if (this != &other) {
                    container = other.container;
                    frontIndex = other.frontIndex;
                    backIndex = other.backIndex;
                    frontTurn = other.frontTurn;
                    other.frontIndex = 0;
                    other.backIndex = 0;
                }
                return *this;
            }
            bool operator==(const SideCrossIterator& other) const {
//                std::cout << "frontIndex ="<<frontIndex<<" other.frontIndex="<<other.frontIndex << " backIndex="<<backIndex<<" other.backIndex="<<other.backIndex<<std::endl;
//                if (frontIndex==backIndex)
//                {
//                    return false;
//                }
                 return frontIndex == other.frontIndex && backIndex == other.backIndex;

//                return frontIndex == other.frontIndex && backIndex == other.backIndex && frontTurn == other.frontTurn;

            }

            bool operator!=(const SideCrossIterator& other) const {
                return !(*this == other);
            }

            bool operator>(const SideCrossIterator& other) const {
                return (frontIndex > other.frontIndex && backIndex > other.backIndex) ||
                       (frontIndex > other.frontIndex && !other.frontTurn) ||
                       (!frontTurn && backIndex > other.backIndex);
            }

            bool operator<(const SideCrossIterator& other) const {
                return (frontIndex < other.frontIndex && backIndex < other.backIndex) ||
                       (frontIndex < other.frontIndex && other.frontTurn) ||
                       (frontTurn && backIndex < other.backIndex);
            }

            std::vector<int>::value_type operator*() const {
                if (frontTurn) {
                    return container.elements[frontIndex];
                }
                return container.elements[backIndex];

            }

                SideCrossIterator& operator++() {
                    std::cout << "frontIndex ="<<frontIndex<<std::endl;
                    std::cout << "backIndex ="<<backIndex<<std::endl;
                    std::cout << "container.size ="<<container.size()<<std::endl;
                    std::cout << "frontIndex = container.size()/2+container.size()%2 "<< container.size()/2+container.size()%2 <<std::endl;
                    std::cout << "backIndex = container.size()/2-(1-container.size()%2) "<< container.size()/2-(1-container.size()%2) <<std::endl;

                    //if (frontIndex>=backIndex+1)
                    if(frontIndex == container.size()/2+container.size()%2 && backIndex == container.size()/2-(1-container.size()%2))
                    {
                        throw std::runtime_error("Out of bounds!");
                    }
                    if (frontTurn  ) {
                    ++frontIndex;

                } else {
                    --backIndex;

                }
                frontTurn = !frontTurn;
                return *this;
            }

             SideCrossIterator begin() {
                return SideCrossIterator(container);
            }

             SideCrossIterator end() {
                SideCrossIterator iter(container);
                iter.frontIndex = container.size()/2+container.size()%2;
                //iter.backIndex = static_cast<std::vector<int>::size_type>(-1);
                 iter.backIndex = container.size()/2-(1-container.size()%2);
                return iter;
            }
        };
        class PrimeIterator {
//            const MagicalContainer &container;
//            size_t index;
            MagicalContainer& container;
            std::vector<int>::size_type index;
//
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
            PrimeIterator(MagicalContainer& container) : container(container), index(0) {
                while (index < container.size() && !isPrime(static_cast<int>(container.elements[index]))) {
                    ++index;
                }
            }

            PrimeIterator(const PrimeIterator& other) : container(other.container), index(other.index) {}
            PrimeIterator& operator=(const PrimeIterator& other) {
                container = other.container;
                index = other.index;
                return *this;
            }
            // Default Destructor
            ~PrimeIterator() = default;

            // Move Constructor-Added because of tidy errors
            PrimeIterator(PrimeIterator&& other) noexcept
                    : container(other.container), index(other.index) {
                other.index = 0;
            }

            // Move Assignment Operator-Added because of tidy errors
            PrimeIterator& operator=(PrimeIterator&& other) noexcept {
                if (this != &other) {
                    container = other.container;
                    index = other.index;
                    other.index = 0;
                }
                return *this;
            }

            int operator*() const {
               // std::cout<<"container.elements[index]: "<<container.elements[index]<<std::endl;

             //   std::cout<<"[index]: "<<index<<std::endl;
               // std::cout<<"container.primeIndexIterator[index]: "<<container.primeIndexIterator[index]<<std::endl;

               // std::cout<<"container.primeIndexIterator[index]: "<<container.primeIndexIterator[index]<<std::endl;
                std::vector<int>::size_type temp_indexPrime = static_cast<std::vector<int>::size_type>(container.primeIndexIterator[index]);
             //   std::cout<<"[temp_indexPrime]: "<<temp_indexPrime<<std::endl;
              //  std::cout<<"container.elements[temp_indexPrime: "<<container.elements[temp_indexPrime]<<std::endl;
//                temp_indexPrime++;
//                std::vector<int>::size_type temp_indexPrime=container.primeIndexIterator[index];
                return container.elements[temp_indexPrime];
                //return container.elements[index];
            }

            bool operator>(const PrimeIterator& other) const {
                return index > other.index;
            }

            bool operator<(const PrimeIterator& other) const {
                return index < other.index;
            }
            bool operator==(const PrimeIterator& other) const {
                return index == other.index;
            }

            bool operator!=(const PrimeIterator& other) const {
                return index != other.index;
            }

            PrimeIterator& operator++() {
               // std::cout<<"im in operator ++ "<<std::endl;

                if (index >= container.primeIndexIterator.size()) {
                    throw std::invalid_argument("Out of bounds!");
                }
                if (index < container.primeIndexIterator.size()) {
                    ++index;
                }
                //std::cout<<"[index++]: "<<index<<std::endl;
               // std::cout<<"[container.primeIndexIterator.size()]"<<container.primeIndexIterator.size()<<std::endl;
                return *this;//returns a reference to the updated AscendIterator object.
            }

            PrimeIterator begin() {
                PrimeIterator iter(container);
                std::cout<<"[begin index]: "<<iter.index<<std::endl;
                return iter;
            }

            PrimeIterator end() {
                PrimeIterator iter(container);
                iter.index = container.primeIndexIterator.size();
                std::cout<<"[end index]: "<<iter.index<<std::endl;
                return iter;
            }

        };

//        class XPrimeIterator {
//        private:
//            MagicalContainer& container;
//            std::vector<int>::size_type index;
//
//            bool static isPrime(int number) {
//                if (number < 2) {
//                    return false;
//                }
//                for (int i = 2; i <= std::sqrt(number); ++i) {
//                    if (number % i == 0) {
//                        return false;
//                    }
//                }
//                return true;
//            }
//
//        public:
//            PrimeIterator(const MagicalContainer &container) : container(container), index(0) {
//                while (index < container.size() && !isPrime(container.elements[index])) {
//                    ++index;
//                }
//            }
//
//            PrimeIterator(const PrimeIterator& other) : container(other.container), index(other.index) {}
//
//            PrimeIterator& operator=(const PrimeIterator& other) {
//                container = other.container;
//                index = other.index;
//                return *this;
//            }
//            // Default Destructor
//            ~PrimeIterator() = default;
//
//            // Move Constructor-Added because of tidy errors
//            PrimeIterator(PrimeIterator&& other) noexcept
//                    : container(other.container), index(other.index) {
//                other.index = 0;
//            }
//
//            // Move Assignment Operator-Added because of tidy errors
//            PrimeIterator& operator=(PrimeIterator&& other) noexcept {
//                if (this != &other) {
//                    container = other.container;
//                    index = other.index;
//                    other.index = 0;
//                }
//                return *this;
//            }
//            bool operator==(const PrimeIterator& other) const {
//                return index == other.index;
//            }
//
//            bool operator!=(const PrimeIterator& other) const {
//                return index != other.index;
//            }
//
//            bool operator>(const PrimeIterator& other) const {
//                return index > other.index;
//            }
//
//            bool operator<(const PrimeIterator& other) const {
//                return index < other.index;
//            }
//
//            int operator*() const {
//                return container.elements[index];
//            }
//
//            PrimeIterator& operator++() {
//                ++index;
//                while (index < container.size() && !isPrime(container.elements[index])) {
//                    ++index;
//                }
//                return *this;
//            }
//
//            PrimeIterator begin() {
//                return PrimeIterator(container);
//            }
//
//            PrimeIterator end() {
//                PrimeIterator iter(container);
//                iter.index = container.size();
//                return iter;
//            }
//        };
    };

}  // namespace ariel