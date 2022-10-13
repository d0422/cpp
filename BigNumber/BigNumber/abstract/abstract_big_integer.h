#pragma once
#include "abstract_big_number.h"


namespace abstract_bignumber {
	class BigInteger : public AbstractBigNumber {
	private:
		// Identifier
		static const std::string name;

	protected:
		char* value_string;

		// Protected method
		unsigned int get_num_of_digits(int) const;
		unsigned int get_num_of_digits(long long) const;

		// Protected virtual method
		virtual void initialize_properties();
		virtual void zero_compaction();

	public:
		// Constructor & Destructor
		BigInteger();
		BigInteger(int);
		BigInteger(long long);
		BigInteger(std::string);
		BigInteger(const BigInteger&);
		~BigInteger();

		// Public method
		COMPARE_RESULT compare_absolute_value(const BigInteger&) const;

		// Public virtual method
		virtual std::string get_name() const;
		virtual char* get_string() const;
		virtual bool get_sign() const;

		virtual unsigned int get_capacity() const;
		virtual unsigned int get_length() const;

		virtual void doubling_capacity();
		virtual void shrink_to_fit();

		virtual void test() const;

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