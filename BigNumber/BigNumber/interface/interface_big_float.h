#pragma once
#include "interface_big_integer.h"
#include "interface_big_number.h"
#include "interface_testable.h"
#include "interface_vector.h"
#include <iostream>


namespace interface_bignumber {
	class BigFloat : public IBigNumber, public ITestable, public IVector
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

		// Interface implementation (IBigNumber)
		virtual bool get_sign() const;
		virtual void toggle_sign();

		// Interface implementation (IVector)
		virtual char* get_string() const;
		virtual unsigned int get_capacity() const;
		virtual unsigned int get_length() const;

		virtual void doubling_capacity();
		virtual void shrink_to_fit();

		// Interface implementation (ITestable)
		virtual void test() const;
		virtual const char* get_boolean_string(bool) const;

		// Public method
		std::string get_name() const;
		unsigned int get_integer_length() const;
		unsigned int get_decimal_length() const;
		unsigned int get_redundant_zeros_in_decimal_part() const;
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