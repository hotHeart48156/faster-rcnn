
#include <daw/daw_read_file.h>
#include <daw/json/daw_json_link.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

namespace daw::cookbook_class1 {
	struct MyClass1 {
		std::string member_0;
		int member_1;
		bool member_2;
	};

	bool operator==( MyClass1 const &lhs, MyClass1 const &rhs ) {
		return std::tie( lhs.member_0, lhs.member_1, lhs.member_2 ) ==
		       std::tie( rhs.member_0, rhs.member_1, rhs.member_2 );
	}
} // namespace daw::cookbook_class1

namespace daw::json {
	template<>
	struct json_data_contract<daw::cookbook_class1::MyClass1> {
#if defined( __cpp_nontype_template_parameter_class )
		using type =
		  json_member_list<json_string<"member0">, json_number<"member1", int>,
		                   json_bool<"member2">>;
#else
		static constexpr char const member0[] = "member0";
		static constexpr char const member1[] = "member1";
		static constexpr char const member2[] = "member2";
		using type =
		  json_member_list<json_string<member0>, json_number<member1, int>,
		                   json_bool<member2>>;
#endif
		static inline auto
		to_json_data( daw::cookbook_class1::MyClass1 const &value ) {
			return std::forward_as_tuple( value.member_0, value.member_1,
			                              value.member_2 );
		}
	};
} // namespace daw::json

int main( int argc, char **argv )
#ifdef DAW_USE_JSON_EXCEPTIONS
  try
#endif
{
	if( argc <= 1 ) {
		puts( "Must supply path to cookbook_class1.json file\n" );
		exit( EXIT_FAILURE );
	}
	auto data = *daw::read_file( argv[1] );

	auto const cls = daw::json::from_json<daw::cookbook_class1::MyClass1>(
	  std::string_view( data.data( ), data.size( ) ) );

	std::string const str = daw::json::to_json( cls );
	puts( str.c_str( ) );

	auto const cls2 = daw::json::from_json<daw::cookbook_class1::MyClass1>(
	  std::string_view( str.data( ), str.size( ) ) );

}
#ifdef DAW_USE_JSON_EXCEPTIONS
catch( daw::json::json_exception const &jex ) {
	std::cerr << "Exception thrown by parser: " << jex.reason( ) << std::endl;
	exit( 1 );
}
#endif