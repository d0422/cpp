#pragma once
#include "standalone_big_integer.h"
#include <string>
#include <istream>
#include <ostream>


namespace standalone {
	class BigFloat
	{
	private:
		// Identifier
		static const std::string name;

	protected:
		// Static Property
		static const int initial_capacity = 10;

		// Property
		unsigned int decimal_length;  // Length of the decimal part
		BigInteger value;

		// Protected method
		void initialize_properties();

	public:
		// Constructor & Destructor
		BigFloat();
		BigFloat(int);
		BigFloat(long long);
		BigFloat(std::string);
		BigFloat(const BigFloat&);
		~BigFloat();

		// Public property
		enum COMPARE_RESULT {
			COMPARE_LARGER,
			COMPARE_EQUAL,
			COMPARE_SMALLER,
		};

		// Public method
		std::string get_name() const;
		char* get_string() const;
		bool get_sign() const;
		void toggle_sign();

		unsigned int get_capacity() const;
		unsigned int get_length() const;
		unsigned int get_integer_length() const;
		unsigned int get_decimal_length() const;
		unsigned int get_redundant_zeros_in_decimal_part() const;

		void shrink_to_fit();
		void doubling_capacity();

		COMPARE_RESULT compare_absolute_value(const BigFloat&) const;

		// Operator
		BigFloat& operator = (const BigFloat&);
		bool operator == (const BigFloat&) const;
		bool operator > (const BigFloat&) const;
		bool operator < (const BigFloat&) const;
		bool operator >= (const BigFloat&) const;
		bool operator <= (const BigFloat&) const;

		BigFloat operator + (const BigFloat&) const;
		BigFloat operator - (const BigFloat&) const;
		BigFloat operator * (const BigFloat&) const;
		BigFloat operator / (const BigFloat&) const;

		friend std::ostream& operator << (std::ostream&, const BigFloat&);
		friend std::istream& operator >> (std::istream&, BigFloat&);
	};
}