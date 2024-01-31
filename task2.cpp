#include <iostream>
// Recursive template metaprogramming to calculate powers
template <int n, int k>
struct Power {
    static constexpr int value = n * Power<n, k - 1>::value;
};
// Base case for recursion of powers 
template <int n>
struct Power<n, 0> {
    static constexpr int value = 1; // n^0 = 1
};
// Recursive template metaprogramming to calculate sum F(n,k)
template <int n, int k>
struct PowerSum {
    static constexpr int value = Power<n, k>::value + PowerSum<n, k - 1>::value;
};
// Base case for recursion of sum of F(n,k)
template <int n>
struct PowerSum<n, 0> {
    static constexpr int value = 0; 
};
// Meta-function to calculate the sum F(n,k)
template <int n, int k>
struct SumSequence {
    static constexpr int value = PowerSum<n, k>::value;
};
int main() {
    constexpr int result = SumSequence<3, 3>::value  ; 
    std::cout << "Sum of F(n,k): " << result << '\n';
    return 0;
}
