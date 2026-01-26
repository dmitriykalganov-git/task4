#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <list>
#include <cstdint>
#include <tuple>
#include <type_traits>

std::string decimal_to_ip(int64_t decimal_ip) {

	int count = std::__popcount(decimal_ip);
	std::string ss;
	if (count > 8) {
		unsigned int byte1 = (decimal_ip >> 56) & 0xFF;
		unsigned int byte2 = (decimal_ip >> 48) & 0xFF;
		unsigned int byte3 = (decimal_ip >> 40) & 0xFF;
		unsigned int byte4 = (decimal_ip >> 32) & 0xFF;
		unsigned int byte5 = (decimal_ip >> 24) & 0xFF;
		unsigned int byte6 = (decimal_ip >> 16) & 0xFF;
		unsigned int byte7 = (decimal_ip >> 8) & 0xFF;
		unsigned int byte8 = decimal_ip & 0xFF;

		ss = std::to_string(byte1)+"." 
		+ std::to_string(byte2)+ "." 
		+ std::to_string(byte3)+ "." 
		+ std::to_string(byte4)+ "." 
		+ std::to_string(byte5)+ "." 
		+ std::to_string(byte6)+ "." 
		+ std::to_string(byte7)+ "." 
		+ std::to_string(byte8);
	}
	else{
		unsigned int byte1 = (decimal_ip >> 24) & 0xFF;
		unsigned int byte2 = (decimal_ip >> 16) & 0xFF;
		unsigned int byte3 = (decimal_ip >> 8) & 0xFF;
		unsigned int byte4 = decimal_ip & 0xFF;

		ss = std::to_string(byte1)+"." 
		+ std::to_string(byte2)+ "." 
		+ std::to_string(byte3)+ "." 
		+ std::to_string(byte4);
	}
    return ss;
}
struct print_ip {

	template <
		template <typename> typename Container,
		typename Type,
			typename = std::enable_if_t<
			std::is_same_v<Container<Type>, std::vector<Type>> ||
			std::is_same_v<Container<Type>, std::list<Type>> ||
			std::is_same_v<Container<Type>, std::string> 
									>
		>
	print_ip(const Container<Type> &container) 
	{
    	for (auto iter = std::begin(container); iter != std::end(container); ++iter) {
			if (!std::is_same_v<Container<Type>, std::string>)
				if (iter != std::begin(container)) std::cout << ".";	
					std::cout << *iter;
		}
		std::cout << std::endl;
	};

	template<
		typename T,
		typename = std::enable_if_t<
			std::is_same_v<T, int8_t> ||
			std::is_same_v<T, int16_t> ||
			std::is_same_v<T, int32_t> ||
			std::is_same_v<T, int64_t>
									>
		> 
	print_ip(const T &value)
	{
		if(value == -1) {
		m_value = "255";
		}
		else
		m_value = decimal_to_ip(value);
		if((value == 0)) std::cout << m_value.substr(2, 3) << std::endl;
		else std::cout << m_value << std::endl;
	}

template <typename T>
void printElem(const T& x, int i) {
    std::cout << x;
	if (i!=3) std::cout << '.';
};

template <typename TupleT, std::size_t... Is>
void printTupleManual(const TupleT& tp) {
    (printElem(std::get<Is>(tp),Is), ...);
	std::cout << std::endl;
}

		template <
		template <typename> typename Container,
		typename... Type,
		typename = std::enable_if_t<
			std::is_same_v<Container<Type...>, std::tuple<int,int,int,int>>
									>
		>
	print_ip(const Container<Type...> &container)
	{
		printTupleManual<decltype(container), 0, 1, 2, 3>(container);
	};
	private:
	std::string m_value;
};

int main() {
print_ip( int8_t{-1} ); // 255 
print_ip( int16_t{0} ); // 0.0 
print_ip( int32_t {2130706433} ); // 127.0.0.1 
print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41 
print_ip( std::string{"Hello, World!"} ); // Hello, World! 
print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400 
print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100 
print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
	return 0;
}  