#include <iostream>
// Main template
template <typename T>
struct RemovePointer {
    using type = T;
};
// Specialization for pointers
template <typename T>
struct RemovePointer<T*> {
    using type = T;
};
// Template to remove all modifiers
template <typename T>
struct RemoveAllModifiers {
    using type = T;
};
// Specializations for references, const
template <typename T>
struct RemoveAllModifiers<T&> {
    using type = T;
};
template <typename T>
struct RemoveAllModifiers<const T> {
    using type = T;
};
// Check if two types are the same
template <typename T, typename U>
struct IsSame {
    static constexpr bool value = 0;
};
template <typename T>
struct IsSame<T, T> {
    static constexpr bool value = 1;
};
int main() {
    std::cout << IsSame<typename RemovePointer<int>::type, int>::value << std::endl;        // Output: 1 -> true
    std::cout << IsSame<typename RemovePointer<int*>::type, int>::value << std::endl;       // Output: 1 -> true
    std::cout << IsSame<typename RemoveAllModifiers<int>::type, int>::value << std::endl;   // Output: 1 -> true
    std::cout << IsSame<typename RemoveAllModifiers<int&>::type, int>::value << std::endl;  // Output: 1 -> true
    return 0;
}
