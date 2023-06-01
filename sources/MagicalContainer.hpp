#include <iostream>
#include <vector>
#include <cmath>

namespace ariel {

    class MagicalContainer {
    private:
        std::vector<int> elements;

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

                    if (frontIndex>=backIndex+1)
                    {
                        throw std::invalid_argument("Out of bounds!");
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
        private:
            MagicalContainer& container;
            std::vector<int>::size_type index;

            bool static isPrime(int number) {
                if (number < 2) {
                    return false;
                }
                for (int i = 2; i <= std::sqrt(number); ++i) {
                    if (number % i == 0) {
                        return false;
                    }
                }
                return true;
            }

        public:
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
            bool operator==(const PrimeIterator& other) const {
                return index == other.index;
            }

            bool operator!=(const PrimeIterator& other) const {
                return index != other.index;
            }

            bool operator>(const PrimeIterator& other) const {
                return index > other.index;
            }

            bool operator<(const PrimeIterator& other) const {
                return index < other.index;
            }

            int operator*() const {
                return container.elements[index];
            }

            PrimeIterator& operator++() {
                ++index;
                while (index < container.size() && !isPrime(container.elements[index])) {
                    ++index;
                }
                return *this;
            }

            PrimeIterator begin() {
                return PrimeIterator(container);
            }

            PrimeIterator end() {
                PrimeIterator iter(container);
                iter.index = container.size();
                return iter;
            }
        };
    };

}  // namespace ariel