#include "standalone_big_float.h"
#include "standalone_big_integer.h"
#include <iostream>

namespace standalone {
	// Identifier
	const std::string BigFloat::name = "BigFloat";

	// Protected method
	void BigFloat::initialize_properties() {
		this->decimal_length = 0;
	}

	void BigFloat::doubling_capacity() {
		this->value.doubling_capacity();
	}

	void BigFloat::toggle_sign() {
		this->value.toggle_sign();
	}

	BigFloat::COMPARE_RESULT BigFloat::compare_absolute_value(const BigFloat& big_float) const {
		BigInteger base_integer;
		unsigned int gap = 0;

		// Value with the larger length of integer part is more larger.
		if (this->decimal_length > big_float.decimal_length) {
			return BigFloat::COMPARE_LARGER;
		}
		else if (this->decimal_length < big_float.decimal_length) {
			return BigFloat::COMPARE_SMALLER;
		}

		// Comparison of different length values
		if (this->get_length() > big_float.get_length()) {
			gap = this->get_length() - big_float.get_length();
			base_integer = big_float.value << gap;  // Make the same length
			if (this->value.compare_absolute_value(base_integer) == BigInteger::COMPARE_LARGER) {
				return BigFloat::COMPARE_LARGER;
			}
			else {
				BigFloat::COMPARE_SMALLER;
			}
		}
		else if (this->get_length() < big_float.get_length()) {
			gap = big_float.get_length() - this->get_length();
			base_integer = this->value << gap;  // Make the same length
			if (base_integer.compare_absolute_value(big_float.value) == BigInteger::COMPARE_LARGER) {
				return BigFloat::COMPARE_LARGER;
			}
			else {
				BigFloat::COMPARE_SMALLER;
			}
		}

		// Comparison of same length values
		switch (this->value.compare_absolute_value(big_float.value)) {
		case BigInteger::COMPARE_LARGER:
			return BigFloat::COMPARE_LARGER;
		case BigInteger::COMPARE_EQUAL:
			return BigFloat::COMPARE_EQUAL;
		case BigInteger::COMPARE_SMALLER:
			return BigFloat::COMPARE_SMALLER;
		}
	}

	// Constructor & Destructor
	BigFloat::BigFloat() {
		this->initialize_properties();
	}

	BigFloat::BigFloat(int value) : BigFloat(static_cast<long long>(value)) {}

	BigFloat::BigFloat(long long value) : BigFloat() {
		this->value = value;
		this->decimal_length = 0;
	}

	BigFloat::BigFloat(std::string value) : BigFloat() {
		// Find decimal point
		unsigned int decimal_point = value.find('.');
		if (decimal_point > value.length()) {  // If not exist, pass to BigInteger
			this->value = value;
			this->decimal_length = 0;
		}
		else {  // If exist, remove the decimal point
			value.erase(decimal_point, 1);
			this->value = value;
			this->decimal_length = value.length() - decimal_point;
		}

		// Remove the redundant zeros in the decimal part
		unsigned int redundant_zeros = this->get_redundant_zeros_in_decimal_part();
		if (redundant_zeros > 0) {
			this->value = this->value >> redundant_zeros;
			this->decimal_length -= redundant_zeros;
		}
	}

	BigFloat::BigFloat(const BigFloat& big_float) : BigFloat() {
		this->decimal_length = big_float.decimal_length;
		this->value = big_float.value;
	}

	BigFloat::~BigFloat() {}

	// Public methods
	std::string BigFloat::get_name() const {
		return name;
	}

	char* BigFloat::get_string() const {
		return this->value.get_string();
	}

	unsigned int BigFloat::get_capacity() const {
		return this->value.get_capacity();
	}

	unsigned int BigFloat::get_length() const {
		return this->value.get_length();
	}

	unsigned int BigFloat::get_integer_length() const {
		if (this->get_length() > this->decimal_length) {
			return this->get_length() - this->decimal_length;	// e.g. 123.4 -> 4 - 1
		}
		else {
			return 1;	// e,g, 0.001 -> 1
		}
	}

	unsigned int BigFloat::get_decimal_length() const {
		return this->decimal_length;
	}

	unsigned int BigFloat::get_redundant_zeros_in_decimal_part() const {
		unsigned int redundant_zeros = 0;

		// Exception handling
		if (this->decimal_length == 0) {	// e.g. 1234
			return 0;
		}
		if (this->get_length() < this->get_decimal_length()) {	// e.g. 0.1, 0.01
			return 0;
		}

		// Calculate
		for (unsigned int zero_index = 0; zero_index < this->decimal_length; zero_index++) {
			if (this->value[this->get_length() - 1 - zero_index] == '0') {
				redundant_zeros++;
			}
			else {
				break;
			}
		}

		return redundant_zeros;
	}

	bool BigFloat::get_sign() const {
		return this->value.get_sign();
	}

	void BigFloat::shrink_to_fit() {
		this->value.shrink_to_fit();
	}

	// Operators
	BigFloat& BigFloat::operator = (const BigFloat& big_float) {
		this->decimal_length = big_float.decimal_length;
		this->value = big_float.value;

		return *this;
	}

	bool BigFloat::operator == (const BigFloat& big_float) const {
		if (this->get_integer_length() != big_float.get_integer_length()) {
			return false;
		}

		if (this->value != big_float.value) {
			return false;
		}

		return true;
	}

	bool BigFloat::operator > (const BigFloat& big_float) const {
		BigFloat::COMPARE_RESULT compare_result;

		// If sign is the same
		if (this->get_sign() == big_float.get_sign()) {
			// Compare two absolute values
			compare_result = this->compare_absolute_value(big_float);

			// Compare two positive values
			if (this->get_sign()) {
				if (compare_result == this->COMPARE_LARGER) {
					return true;
				}
				else {
					return false;
				}
			}
			// Compare two negative values
			else {
				if (compare_result == this->COMPARE_SMALLER) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		// No need to compare
		else {
			if (this->get_sign()) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	bool BigFloat::operator < (const BigFloat& big_float) const {
		return (big_float > *this);
	}

	bool BigFloat::operator >= (const BigFloat& big_float) const {
		return !(big_float > *this);
	}

	bool BigFloat::operator <= (const BigFloat& big_float) const {
		return !(big_float < *this);
	}

	BigFloat BigFloat::operator + (const BigFloat& big_float) const {
		BigFloat result;

		BigInteger gap_filled_integer;
		unsigned int gap = 0;

		if (this->decimal_length > big_float.decimal_length) {
			// Make the same length
			gap = this->decimal_length - big_float.decimal_length;
			gap_filled_integer = big_float.value;
			gap_filled_integer = gap_filled_integer << gap;

			// Calculate
			result.value = this->value + gap_filled_integer;
			result.decimal_length = this->decimal_length;
		}
		else if (this->decimal_length < big_float.decimal_length) {
			// Make the same length
			gap = big_float.decimal_length - this->decimal_length;
			gap_filled_integer = this->value;
			gap_filled_integer = gap_filled_integer << gap;

			// Calculate
			result.value = big_float.value + gap_filled_integer;
			result.decimal_length = big_float.decimal_length;
		}
		else {
			// Calculate
			result.value = this->value + big_float.value;
			result.decimal_length = this->decimal_length;
		}

		return result;
	}

	BigFloat BigFloat::operator - (const BigFloat& big_float) const {
		BigFloat result;

		BigInteger gap_filled_integer;
		unsigned int gap = 0;

		if (this->decimal_length > big_float.decimal_length) {
			// Make the same decimal length
			gap = this->decimal_length - big_float.decimal_length;
			gap_filled_integer = big_float.value;
			gap_filled_integer = gap_filled_integer << gap;

			// Calculate
			result.value = this->value - gap_filled_integer;
			result.decimal_length = this->decimal_length;
		}
		else if (this->decimal_length < big_float.decimal_length) {
			// Make the same decimal length
			gap = big_float.decimal_length - this->decimal_length;
			gap_filled_integer = this->value;
			gap_filled_integer = gap_filled_integer << gap;

			// Calculate
			result.value = gap_filled_integer - big_float.value;
			result.decimal_length = big_float.decimal_length;
		}
		else {
			// Calculate
			result.value = this->value - big_float.value;
			result.decimal_length = this->decimal_length;
		}

		return result;
	}

	BigFloat BigFloat::operator * (const BigFloat& big_float) const {
		BigFloat result;
		/* Should be implemented */

		return result;
	}

	BigFloat BigFloat::operator / (const BigFloat& big_float) const {
		BigFloat result;
		/* Should be implemented */

		return result;
	}

	std::ostream& standalone::operator << (std::ostream& out, const BigFloat& big_float) {
		BigFloat instance = big_float;
		unsigned int redundant_zeros = 0;

		// Zero handling
		if (instance == 0) {
			out << "0";
			return out;
		}

		// Sign handling
		if (!instance.get_sign()) {
			out << std::string("-");
			instance.toggle_sign();
		}

		if (instance.get_decimal_length() == 0) {	// e.g. 1234, 0
			out << std::string(instance.get_string(), instance.get_integer_length());
		}
		else if (instance.get_length() > instance.get_decimal_length()) {  // e.g. 1.234
			out << std::string(instance.get_string(), instance.get_integer_length());

			// zero scan in the decimal part
			redundant_zeros = instance.get_redundant_zeros_in_decimal_part();
			if (redundant_zeros < instance.get_decimal_length()) {
				out << "." << std::string(instance.get_string(), instance.get_integer_length(), instance.get_decimal_length() - redundant_zeros);
			}
		}
		else {  // e.g. 0.1, 0.01, 0.11
			out << std::string("0.");
			for (unsigned zero_index = 0; zero_index < instance.get_decimal_length() - instance.get_length(); zero_index++) {
				out << std::string("0");
			}
			out << std::string(instance.get_string(), instance.get_integer_length());
		}

		return out;
	}

	std::istream& standalone::operator >> (std::istream& in, BigFloat& big_float) {
		unsigned int begin_index = 0;
		std::string input_string;
		in >> input_string;

		for (unsigned int place_index = 0; place_index < input_string.length(); place_index++) {
			if (input_string[place_index] == ' ') {
				begin_index++;
			}
			else {
				break;
			}
		}

		big_float = BigFloat(input_string.substr(begin_index));

		return in;
	}
}