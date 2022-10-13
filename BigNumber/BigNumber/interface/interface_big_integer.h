#pragma once
#include <iostream>
#include "interface_big_number.h"
#include "interface_testable.h"
#include "interface_vector.h"


namespace interface_bignumber {
	class BigInteger : public IBigNumber, public ITestable, public IVector //IBigNumber, ITestable, IVector를 모두 상속하여 구현함
	{
	private:
		// Identifier
		static const std::string name;

	protected:
		// Protected property
		bool sign;
		unsigned int length;
		unsigned int capacity;
		char* value_string;

		// Protected method
		void initialize_properties();
		void zero_compaction();

		unsigned int get_num_of_digits(int) const;
		unsigned int get_num_of_digits(long long) const;

	public:
		// Constructor & Destructor
		BigInteger();
		BigInteger(int);
		BigInteger(long long);
		BigInteger(std::string);
		BigInteger(const BigInteger&);
		~BigInteger();

		// Public property
		enum COMPARE_RESULT {
			COMPARE_LARGER,
			COMPARE_EQUAL,
			COMPARE_SMALLER,
		};

		// Interface implementation (IBigNumber)
		virtual bool get_sign() const;
		virtual void toggle_sign();

		// Interface implementation (IVector) -> IVector 구현
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
		COMPARE_RESULT compare_absolute_value(const BigInteger&) const;

		// Operator
		BigInteger& operator = (const BigInteger&);
		BigInteger& operator = (std::string);
		bool operator == (const BigInteger&) const;
		bool operator != (const BigInteger&) const;
		bool operator > (const BigInteger&) const;
		bool operator < (const BigInteger&) const;
		bool operator >= (const BigInteger&) const;
		bool operator <= (const BigInteger&) const;

		BigInteger operator + (const BigInteger&) const;
		BigInteger operator - (const BigInteger&) const;
		BigInteger operator * (const BigInteger&) const;
		BigInteger operator / (const BigInteger&) const;
		BigInteger operator % (const BigInteger&) const;
		BigInteger operator << (unsigned int) const;
		BigInteger operator >> (unsigned int) const;

		const char operator [] (unsigned int) const;

		friend std::ostream& operator << (std::ostream&, const BigInteger&);
		friend std::istream& operator >> (std::istream&, BigInteger&);
	};
}