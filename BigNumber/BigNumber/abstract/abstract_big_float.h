#pragma once
#include "abstract_big_number.h"
#include "abstract_big_integer.h"


namespace abstract_bignumber {
	class BigFloat : public AbstractBigNumber { //Bignumber?? ???
	private:
		// Identifier
		static const std::string name;

	protected:
		// Property
		unsigned int decimal_length;  // Length of the decimal part
		BigInteger value;

		// Protected method
		unsigned int get_redundant_zeros_in_decimal_part() const;

		// Protected virtual method
		virtual void initialize_properties();
		virtual void zero_compaction();

	public:
		// Constructor & Destructor
		BigFloat();
		BigFloat(int);
		BigFloat(long long);
		BigFloat(std::string);
		BigFloat(const BigFloat&);
		~BigFloat();

		// Public method
		unsigned int get_integer_length() const;
		unsigned int get_decimal_length() const;

		COMPARE_RESULT compare_absolute_value(const BigFloat&) const;

		// Public pure virtual method
		virtual std::string get_name() const;
		virtual char* get_string() const;
		virtual bool get_sign() const;

		virtual unsigned int get_capacity() const;
		virtual unsigned int get_length() const;

		virtual void doubling_capacity();
		virtual void shrink_to_fit();

		virtual void test() const;

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