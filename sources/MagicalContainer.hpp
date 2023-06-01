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
                if (elements[i]==number){return true;}
            }
            return false;
        }

        void addElement(int element) {
            elements.push_back(element);
            //Sort 'elements' vector
            std::sort(elements.begin(), elements.end());
        }

        void removeElement(int element) {
            for (auto it = elements.begin(); it != elements.end(); ++it) {
                if (*it == element) {
                    elements.erase(it);
                    break;
                }
            }
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

            bool operator==(const SideCrossIterator& other) const {
                std::cout << "frontIndex ="<<frontIndex<<" other.frontIndex="<<other.frontIndex << " backIndex="<<backIndex<<" other.backIndex="<<other.backIndex<<std::endl;
                return frontIndex == other.frontIndex && backIndex == other.backIndex;
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
                } else {
                    return container.elements[backIndex];
                }
            }

            SideCrossIterator& operator++() {
                if (frontTurn) {
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
                iter.frontIndex = container.size();
                //iter.backIndex = static_cast<std::vector<int>::size_type>(-1);
                 iter.backIndex = 0;
                return iter;
            }
        };

        class PrimeIterator {
        private:
            MagicalContainer& container;
            std::vector<int>::size_type index;

            bool isPrime(int number) const {
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