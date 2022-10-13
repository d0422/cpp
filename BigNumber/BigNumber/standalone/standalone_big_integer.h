#pragma once
#include <string>
#include <istream>
#include <ostream>


namespace standalone {
	class BigInteger
	{
	private:
		// Identifier
		static const std::string name;

	protected:
		// Static Property
		static const int initial_capacity = 10;

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

		// Public method
		std::string get_name() const;
		char* get_string() const;
		bool get_sign() const;
		void toggle_sign();

		unsigned int get_capacity() const;
		unsigned int get_length() const;

		void doubling_capacity();
		void shrink_to_fit();

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