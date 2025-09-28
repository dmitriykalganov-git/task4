#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <list>
#include <cstdint>
#include <tuple>

std::string decimal_to_ip(int64_t decimal_ip) {

	int count = std::__popcount(decimal_ip);
	std::string ss;
	if (count > 8) {
		int8_t byte1 = (decimal_ip >> 56) & 0xFF;
		int8_t byte2 = (decimal_ip >> 48) & 0xFF;
		int8_t byte3 = (decimal_ip >> 40) & 0xFF;
		int8_t byte4 = (decimal_ip >> 32) & 0xFF;
		int8_t byte5 = (decimal_ip >> 24) & 0xFF;
		int8_t byte6 = (decimal_ip >> 16) & 0xFF;
		int8_t byte7 = (decimal_ip >> 8) & 0xFF;
		int8_t byte8 = decimal_ip & 0xFF;

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
		int8_t byte1 = (decimal_ip >> 24) & 0xFF;
		int8_t byte2 = (decimal_ip >> 16) & 0xFF;
		int8_t byte3 = (decimal_ip >> 8) & 0xFF;
		int8_t byte4 = decimal_ip & 0xFF;

		ss = std::to_string(byte1)+"." 
		+ std::to_string(byte2)+ "." 
		+ std::to_string(byte3)+ "." 
		+ std::to_string(byte4);
	}
    return ss;
}
struct print_ip {
/*	template <typename TT,
		typename Fake =
			typename std::enable_if<
				!std::is_same<typename std::remove_reference<TT>::type,
					int8_t>::value &&
				!std::is_same<typename std::remove_reference<TT>::type,
					int16_t>::value &&
				!std::is_same<typename std::remove_reference<TT>::type,
					int32_t>::value &&
				!std::is_same<typename std::remove_reference<TT>::type,
					int64_t>::value
					,
					void>::type
				>
	print_ip(TT &&value) : m_value{std::forward<TT>(value)} 
	{
      //    std::cout << value << std::endl;
		  std::cout << value << std::endl;
	};
*/

	template <
		template <typename> typename Container,
		typename Type,
		typename = std::enable_if_t<
			std::is_same_v<Container<Type>, std::vector<Type>> ||
			std::is_same_v<Container<Type>, std::list<Type>>
									>
		>
	print_ip(const Container<Type> &container) 
	{
     for (auto iter = std::begin(container); iter != std::end(container); ++iter) {
		if (iter != std::begin(container)) std::cout << ".";
			std::cout << *iter;
	}
	std::cout << std::endl;
	};
	
	print_ip(std::string &&value)     
	{
		std::cout << value << std::endl;
	};

	print_ip(int64_t &&value)     
	{
		if(value == -1) {
			m_value = "255";
		}
		else
		m_value = decimal_to_ip(value);
		std::cout << m_value << std::endl;
	};

	print_ip(std::tuple<int,int,int,int> &&value)      
	{
		std::apply([](auto &... x){(..., static_cast<void>(std::cout << x << "."));}, value);
		std::cout << std::endl;
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
//
print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400 
print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100 
print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
	return 0;
}