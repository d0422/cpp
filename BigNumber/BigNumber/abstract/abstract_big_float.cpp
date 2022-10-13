#include "abstract_big_float.h"
#include "abstract_big_integer.h"
#include <iostream>
using namespace std;

namespace abstract_bignumber {
	// Identifier
	const std::string BigFloat::name = "BigFloat";

	// Protected method
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

	// Protected virtual method
	void BigFloat::initialize_properties() {
		this->decimal_length = 0;
	}

	void BigFloat::doubling_capacity() {
		this->value.doubling_capacity();
	}

	void BigFloat::zero_compaction() {
		// Do Nothing
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

	// Public method
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

	bool BigFloat::get_sign() const {
		return this->value.get_sign();
	}

	void BigFloat::shrink_to_fit() {
		this->value.shrink_to_fit();
	}

	void BigFloat::test() const {
		BigFloat big_float;

		cout << "[Constructor Test]" << endl;
		cout << "Original BigFloat (integer: 0): " << BigFloat(0) << endl;
		cout << "Original BigFloat (string: 0): " << BigFloat(std::string("0")) << std::endl;
		cout << "Original BigFloat (string: -0): " << BigFloat(string("-0")) << std::endl;
		cout << "Original BigFloat (integer: 1234567890): " << BigFloat(1234567890) << endl;
		cout << "Original BigFloat (longlong: 123456789012345): " << BigFloat(123456789012345) << endl;
		cout << "Original BigFloat (string: 12345678901234567890): " << BigFloat(string("12345678901234567890")) << std::endl;
		cout << "Original BigFloat (integer: -1234567890): " << BigFloat(-1234567890) << endl;
		cout << "Original BigFloat (longlong: -123456789012345): " << BigFloat(-123456789012345) << endl;
		cout << "Original BigFloat (string: -12345678901234567890): " << BigFloat(string("-12345678901234567890")) << std::endl;
		cout << "Original BigFloat (string: 12345678901234567890.12345678901234567890): " << BigFloat(string("12345678901234567890.12345678901234567890")) << std::endl;
		cout << "Original BigFloat (string: -12345678901234567890.12345678901234567890): " << BigFloat(string("-12345678901234567890.12345678901234567890")) << std::endl;
		cout << "Original BigFloat (string: 0.0): " << BigFloat(string("0.0")) << std::endl;
		cout << "Original BigFloat (string: -0.0): " << BigFloat(string("-0.0")) << std::endl;
		cout << "Original BigFloat (string: -0.1): " << BigFloat(string("-0.1")) << std::endl;
		cout << "Original BigFloat (string: -1.0): " << BigFloat(string("-1.0")) << std::endl;

		cout << endl << "[I/O Test]" << endl;
		cout << "Enter a value: ";
		cin >> big_float;
		cout << "Given value: " << big_float << endl;

		cout << endl << "[Comparison Test]" << endl;
		cout << "(123.1230 == 123.123) True -> " << get_boolean_string(BigFloat("123.1230") == BigFloat("123.123")) << endl;
		cout << "(1234567890123456789.9 > 1234567890123456789.0) True -> " << get_boolean_string(BigFloat("1234567890123456789.9") > BigFloat("1234567890123456789.0")) << endl;
		cout << "(123456789012345678.99 < 123456789012345678.90) False -> " << get_boolean_string(BigFloat("123456789012345678.99") < BigFloat("123456789012345678.90")) << endl;
		cout << "(1234567890.1234567899 == 1234567890.1234567890) False -> " << get_boolean_string(BigFloat("1234567890.1234567899") == BigFloat("1234567890.1234567890")) << endl;
		cout << "(1234567890.1234567890 == 1234567890.1234567890) True -> " << get_boolean_string(BigFloat("1234567890.1234567890") == BigFloat("1234567890.1234567890")) << endl;
		cout << "(-12345.678901234567899 > 123456789012345.67890) False -> " << get_boolean_string(BigFloat("-12345.678901234567899") > BigFloat("123456789012345.67890")) << endl;
		cout << "(12345.678901234567899 > -123456789012345.67890) True -> " << get_boolean_string(BigFloat("12345.678901234567899") > BigFloat("-123456789012345.67890")) << endl;
		cout << "(-12345678901234567.899 > -12345678901234567.890) False -> " << get_boolean_string(BigFloat("-12345678901234567.899") > BigFloat("-12345678901234567.890")) << endl;
		cout << "(-12345678901234567.899 < -12345678901234567.890) True -> " << get_boolean_string(BigFloat("-12345678901234567.899") < BigFloat("-12345678901234567.890")) << endl;
		cout << "(-12345678901234567.899 >= 12345678901234567.890) False -> " << get_boolean_string(BigFloat("-12345678901234567.899") >= BigFloat("12345678901234567.890")) << endl;
		cout << "(12345678901234567.899 >= -12345678901234567.890) True -> " << get_boolean_string(BigFloat("12345678901234567.899") >= BigFloat("-12345678901234567.890")) << endl;
		cout << "(-12345678901234567.899 >= -12345678901234567.890) False -> " << get_boolean_string(BigFloat("-12345678901234567.899") >= BigFloat("-12345678901234567.890")) << endl;
		cout << "(-12345678901234567.899 <= -12345678901234567.890) True -> " << get_boolean_string(BigFloat("-12345678901234567.899") <= BigFloat("-12345678901234567.890")) << endl;

		// Add test
		cout << endl << "[Add Test]" << endl;
		cout << "1234567.890 + 1234567.899 = 2469135.789 -> " << BigFloat("1234567.899") + BigFloat("1234567.890") << endl;
		cout << "9999999999.999 + 9999999999.999 = 19999999999.998 -> " << BigFloat("9999999999.999") + BigFloat("9999999999.999") << endl;
		cout << "1234 + 78907807.809 = 78909041.809 -> " << BigFloat("1234") + BigFloat("78907807.809") << endl;
		cout << "1234 + 0 = 1234 -> " << BigFloat("1234") + BigFloat("0") << endl;
		cout << "1234 + 0.1 = 1234.1 -> " << BigFloat("1234") + BigFloat("0.1") << endl;
		cout << "1234 + 1.0 = 1235 -> " << BigFloat("1234") + BigFloat("1.0") << endl;
		cout << "-1234 - (-1.0) = -1233 -> " << BigFloat("-1234") - BigFloat("-1.0") << endl;
		cout << "1234 - (-1.0) = 1235 -> " << BigFloat("1234") - BigFloat("-1.0") << endl;

		// Subtract test
		cout << endl << "[Subtract Test]" << endl;
		cout << "1234567.899 - 1234567.890 = 0.009 -> " << BigFloat("1234567.899") - BigFloat("1234567.890") << endl;
		cout << "1234567.890 - 1234567.899 = -0.009 -> " << BigFloat("1234567.890") - BigFloat("1234567.899") << endl;
		cout << "1234567.890 - 1234567.890 = 0 -> " << BigFloat("1234567.890") - BigFloat("1234567.890") << endl;
		cout << "123456 - 2345678.9 = -2222222.9 -> " << BigFloat("123456") - BigFloat("2345678.9") << endl;
		cout << "2345678.9 - 123456 = 2222222.9 -> " << BigFloat("2345678.9") - BigFloat("123456") << endl;
		cout << "1234 - 0.1 = 1233.9 -> " << BigFloat("1234") - BigFloat("0.1") << endl;
		cout << "1234 - 1.0 = 1233 -> " << BigFloat("1234") - BigFloat("1.0") << endl;

		// (Optional)
		cout << endl << "[Multiply Test]" << endl;
		cout << "123.45 * 0 = 0 -> " << BigFloat("123.45") * BigFloat(0) << endl;
		cout << "123.45 * 678.90 = 83810.205 -> " << BigFloat("123.45") * BigFloat("678.90") << endl;
		cout << "-123.45 * 678.90 = -83810.205 -> " << BigFloat("-123.45") * BigFloat("678.90") << endl;
		cout << "-123.45 * -678.90 = 83810.205 -> " << BigFloat("-123.45") * BigFloat("-678.90") << endl;

		cout << endl << "[Divide Test]" << endl;
		cout << "678.90 / 123.45 = 5 -> " << BigFloat("678.90") / BigFloat("123.45") << endl;
		cout << "-678.90 / 123.45 = -5 -> " << BigFloat("-678.90") / BigFloat("123.45") << endl;
		cout << "-678.90 / -123.45 = 5 -> " << BigFloat("-678.90") / BigFloat("-123.45") << endl;
		cout << endl;
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

	std::ostream& abstract_bignumber::operator << (std::ostream& out, const BigFloat& big_float) {
		BigFloat instance = big_float;
		unsigned int redundant_zeros = 0;

		// Zero handling
		if (instance.value == 0) {
			out << "0";
			return out;
		}

		// Sign handling
		if (!instance.get_sign()) {
			out << std::string("-");
			instance.toggle_sign();
		}

		if (instance.decimal_length == 0) {	// e.g. 1234, 0
			out << std::string(instance.get_string(), instance.get_integer_length());
		}
		else if (instance.get_length() > instance.decimal_length) {  // e.g. 1.234
			out << std::string(instance.get_string(), instance.get_integer_length());

			// zero scan in the decimal part
			redundant_zeros = instance.get_redundant_zeros_in_decimal_part();
			if (redundant_zeros < instance.decimal_length) {
				out << "." << std::string(instance.get_string(), instance.get_integer_length(), instance.decimal_length - redundant_zeros);
			}
		}
		else {  // e.g. 0.1, 0.01, 0.11
			out << std::string("0.");
			for (unsigned zero_index = 0; zero_index < instance.decimal_length - instance.get_length(); zero_index++) {
				out << std::string("0");
			}
			out << std::string(instance.get_string(), instance.get_integer_length());
		}

		return out;
	}

	std::istream& abstract_bignumber::operator >> (std::istream& in, BigFloat& big_float) {
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