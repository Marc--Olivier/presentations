#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

//-----------------------------------------
// test join()
//-----------------------------------------

// Append only non-pointers
template<typename TElt,
		std::enable_if_t<!std::is_pointer<TElt>::value>* = nullptr>
		//typename = std::enable_if_t<!std::is_pointer<TElt>::value>> //=> Overload does not work, see http://en.cppreference.com/w/cpp/types/enable_if
inline void appendElt(std::ostream& out, const TElt& elt, const std::string& separator) {
	out << elt << separator;
}

// Append only pointers
template<typename TElt,
		std::enable_if_t<std::is_pointer<TElt>::value>* = nullptr>
		//typename = std::enable_if_t<std::is_pointer<TElt>::value>>
inline void appendElt(std::ostream& out, const TElt& elt, const std::string& separator) {
	out << *elt << separator;
}

template<typename TContainer>
std::string join(const TContainer& container, const std::string& separator) {
	std::stringstream out;
	for(const auto& elt : container) {
		appendElt(out, elt, separator);
	}
	auto str = out.str();
	str.erase(str.size() - separator.size());
	return str;
}

void testJoin() {
	std::cout << "=======  Test Join  =======" << std::endl;
	std::vector<std::string> strs{"1", "2", "3", "4"};
	std::cout << "join strs: " << join(strs, ", ") << std::endl;
	std::vector<int> ints{5, 6, 7, 8};
	std::cout << "join ints: " << join(ints, ", ") << std::endl;
	std::vector<int*> intsPtrs{&ints[0], &ints[1], &ints[2], &ints[3]};
	std::cout << "join intsPtrs: " << join(intsPtrs, ", ") << std::endl;
}

//-----------------------------------------
// test getId()
//-----------------------------------------

class A {
public:
	A(int id) : id_(id) {}
	int id() const {return id_;}
private:
	int id_;
};

class A_old {
public:
	A_old(int id) : id_(id) {}
	int getId() const {return id_;}
private:
	int id_;
};

class A_refactored {
public:
	A_refactored(int id) : id_(id) {}
	int id() const {return id_;}
	int getId() const {return id_+1;}
private:
	int id_;
};

// See http://en.cppreference.com/w/cpp/types/void_t
namespace std {
template<typename... Ts> struct make_void { typedef void type;};
template<typename... Ts> using void_t = typename make_void<Ts...>::type;
}

// See https://github.com/CppCon/CppCon2014/blob/master/Presentations/Modern%20Template%20Metaprogramming%20-%20A%20Compendium/Modern%20Template%20Metaprogramming%20-%20A%20Compendium%20-%20Walter%20E%20Brown%20-%20CppCon%202014.pdf
// slide 36
// Test if typename T has a method id()
template<typename T, typename = void>
struct has_id : std::false_type {};

template<typename T>
struct has_id<T, std::void_t<decltype(std::declval<T>().id())>> : std::true_type {};

// getId for typenames T that have a method id()
template<typename T,
		typename std::enable_if_t<has_id<T>::value>* = nullptr>
int getId(const T& obj) {
	return obj.id();
}

// Test if typename T has a method getId()
template<typename T, typename = void>
struct has_getId : std::false_type {};

template<typename T>
struct has_getId<T, std::void_t<decltype(std::declval<T>().getId())>> : std::true_type {};

// getId for typenames T that have a method getId() but no method id()
template<typename T,
		typename std::enable_if_t<has_getId<T>::value && !has_id<T>::value>* = nullptr>
int getId(const T& obj) {
	return obj.getId();
}

void testGetId() {
	std::cout << "=======  Test getIds  =======" << std::endl;
	std::cout << "std::true_type::value = " << std::true_type::value << std::endl;
	std::cout << "std::false_type::value = " << std::false_type::value << std::endl;
	std::cout << "has_id(A(2)) = " << has_id<A>::value << std::endl;
	std::cout << "has_id(A_old(3)) = " << has_id<A_old>::value << std::endl;
	std::cout << "getId(A(4)) = " << getId(A(4)) << std::endl;
	std::cout << "getId(A_old(5)) = " << getId(A_old(5)) << std::endl;
	std::cout << "getId(A_refactored(6)) = " << getId(A_refactored(6)) << std::endl;
}

//-----------------------------------------
// main
//-----------------------------------------

int main() {
	testJoin();
	testGetId();
}
