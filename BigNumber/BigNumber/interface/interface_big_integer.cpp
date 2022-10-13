#include "interface_big_integer.h"
#include <iostream>
using namespace std;

namespace interface_bignumber {
	// Identifier
	const std::string BigInteger::name = "BigInteger";

	// Protected method
	void BigInteger::initialize_properties() {
		this->sign = true;
		this->length = 0;
		this->capacity = 0;
		this->value_string = new char[this->initial_capacity]();
		if (this->value_string != NULL) {
			this->capacity = this->initial_capacity;
			this->length = 0;
		}
	}

	void BigInteger::doubling_capacity() {
		int new_capacity = this->capacity * 2;
		char* new_value_string = new char[new_capacity]();
		if (new_value_string == NULL) return;

		memcpy(new_value_string, this->value_string, this->length);
		delete[] this->value_string;

		this->capacity = new_capacity;
		this->value_string = new_value_string;
	}

	void BigInteger::toggle_sign() {
		this->sign ^= 1;	// XOR toggling
	}

	void BigInteger::zero_compaction() {
		unsigned int new_length = 0;
		unsigned int left_compact_point = 0;

		// Check the left zeros
		for (unsigned int place_index = 0; place_index < this->length; place_index++) {
			if (this->value_string[place_index] != '0') {
				left_compact_point = place_index;
				break;
			}
		}

		// Check new length
		if (left_compact_point == 0) {
			return;
		}
		new_length = this->length - left_compact_point;

		// Set new string
		char* new_value_string = new char[new_length]();
		if (new_value_string == NULL) return;

		memcpy(new_value_string, this->value_string + left_compact_point, new_length);
		delete[] this->value_string;

		this->value_string = new_value_string;
		this->length = new_length;
		this->capacity = new_length;
	}

	unsigned int BigInteger::get_num_of_digits(int value) const {
		long long long_value = value;
		unsigned int num_of_digits = this->get_num_of_digits(long_value);

		return num_of_digits;
	}

	unsigned int BigInteger::get_num_of_digits(long long value) const {
		unsigned int num_of_digits = 0;

		// Exception handling for zero value
		if (value == 0) {
			num_of_digits = 1;
		}
		// Normal case
		else {
			// Convert into absolute value
			if (value < 0) {
				value *= -1;
			}

			// Count the number of digits
			for (; value > 0; num_of_digits++) {
				value /= 10;
			}
		}

		return num_of_digits;
	}

	BigInteger::COMPARE_RESULT BigInteger::compare_absolute_value(const BigInteger& big_integer) const {
		unsigned int length = this->length;
		unsigned int given_length = big_integer.length;

		if (length > given_length) {
			return BigInteger::COMPARE_LARGER;
		}
		else if (length < given_length) {
			return BigInteger::COMPARE_SMALLER;
		}
		else {
			for (unsigned int place_index = 0; place_index < length; place_index++) {
				if (this->value_string[place_index] > big_integer.value_string[place_index]) {
					return BigInteger::COMPARE_LARGER;
				}
				else if (this->value_string[place_index] < big_integer.value_string[place_index]) {
					return BigInteger::COMPARE_SMALLER;
				}
			}
		}
		return BigInteger::COMPARE_RESULT::COMPARE_EQUAL;
	}

	// Interface (Method)
	BigInteger::BigInteger() {
		this->initialize_properties();
	}

	BigInteger::BigInteger(int value) : BigInteger(static_cast<long long>(value)) {}

	BigInteger::BigInteger(long long value) : BigInteger() {
		unsigned int num_of_digits = this->get_num_of_digits(value);

		while (this->capacity < num_of_digits) {
			this->doubling_capacity();
		}

		// Set the length
		this->length = num_of_digits;

		// Check negativity
		if (value < 0) {
			this->sign = false;
			value *= -1;
		}

		// Fill the value_string
		unsigned int number = 0;
		for (unsigned int place_index = 0; place_index < num_of_digits; place_index++) {
			number = value % 10;
			this->value_string[num_of_digits - place_index - 1] = number + '0';
			value /= 10;
		}
	}

	BigInteger::BigInteger(std::string value) : BigInteger() {
		bool zero_flag = false;

		// Check negativity
		if (value[0] == '-') {
			this->sign = false;
			value = value.substr(1, value.length() - 1);
		}

		// Zero check
		zero_flag = true;
		for (unsigned int place_index = 0; place_index < value.length(); place_index++) {
			if (value[place_index] != '0') {
				zero_flag = false;
			}
		}

		if (zero_flag) {
			this->sign = true;
			this->length = 1;
			this->value_string[0] = '0';
			this->zero_compaction();
			return;
		}

		while (this->capacity < value.length()) {
			this->doubling_capacity();
		}

		memcpy(this->value_string, value.c_str(), value.length());
		this->length = static_cast<unsigned int>(value.length());

		this->zero_compaction();
	}

	BigInteger::BigInteger(const BigInteger& big_integer) : BigInteger() {
		char* new_value_string = new char[big_integer.capacity]();
		if (new_value_string != NULL) {
			if (this->value_string != NULL) {
				delete[] this->value_string;
				this->sign = true;
				this->length = 0;
				this->capacity = 0;
			}

			this->value_string = new_value_string;
			memcpy(this->value_string, big_integer.get_string(), big_integer.capacity);
			this->sign = big_integer.sign;
			this->length = big_integer.length;
			this->capacity = big_integer.capacity;
		}
	}

	BigInteger::~BigInteger() {
		if (this->value_string != NULL) {
			delete[] this->value_string;
			this->sign = true;
			this->length = 0;
			this->capacity = 0;
		}
	}

	// Public method
	std::string BigInteger::get_name() const {
		return name;
	}

	char* BigInteger::get_string() const {
		return this->value_string;
	}

	bool BigInteger::get_sign() const {
		return this->sign;
	}

	unsigned int BigInteger::get_capacity() const {
		return this->capacity;
	}

	unsigned int BigInteger::get_length() const {
		return this->length;
	}

	void BigInteger::shrink_to_fit() {
		if (this->capacity == this->length) {
			return;
		}

		char* new_value_string = new char[this->length]();
		if (new_value_string == NULL) return;

		memcpy(new_value_string, this->value_string, this->length);
		delete[] this->value_string;
		this->value_string = new_value_string;
		this->capacity = this->length;
	}

	void BigInteger::test() const {
		BigInteger big_integer;

		cout << "[Constructor Test]" << endl;
		cout << "Original BigInteger (integer: 0): " << BigInteger(0) << endl;
		cout << "Original BigInteger (string: 0): " << BigInteger(string("0")) << std::endl;
		cout << "Original BigInteger (string: -0): " << BigInteger(string("-0")) << std::endl;
		cout << "Original BigInteger (integer: 1234567890): " << BigInteger(1234567890) << endl;
		cout << "Original BigInteger (longlong: 123456789012345): " << BigInteger(123456789012345) << endl;
		cout << "Original BigInteger (string: 12345678901234567890): " << BigInteger(string("12345678901234567890")) << std::endl;
		cout << "Original BigInteger (integer: -1234567890): " << BigInteger(-1234567890) << endl;
		cout << "Original BigInteger (longlong: -123456789012345): " << BigInteger(-123456789012345) << endl;
		cout << "Original BigInteger (string: -12345678901234567890): " << BigInteger(string("-12345678901234567890")) << std::endl;

		cout << endl << "[I/O Test]" << endl;
		cout << "Enter a value: ";
		cin >> big_integer;
		cout << "Given value: " << big_integer << endl;

		cout << endl << "[Comparison Test]" << endl;
		cout << "(12345678901234567899 > 12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567899") > BigInteger("12345678901234567890")) << endl;
		cout << "(12345678901234567899 < 12345678901234567890) False -> " << get_boolean_string(BigInteger("12345678901234567899") < BigInteger("12345678901234567890")) << endl;
		cout << "(12345678901234567899 == 12345678901234567890) False -> " << get_boolean_string(BigInteger("12345678901234567899") == BigInteger("12345678901234567890")) << endl;
		cout << "(12345678901234567890 == 12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567890") == BigInteger("12345678901234567890")) << endl;
		cout << "(-12345678901234567899 > 12345678901234567890) False -> " << get_boolean_string(BigInteger("-12345678901234567899") > BigInteger("12345678901234567890")) << endl;
		cout << "(12345678901234567899 > -12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567899") > BigInteger("-12345678901234567890")) << endl;
		cout << "(-12345678901234567899 > -12345678901234567890) False -> " << get_boolean_string(BigInteger("-12345678901234567899") > BigInteger("-12345678901234567890")) << endl;
		cout << "(-12345678901234567899 < -12345678901234567890) True -> " << get_boolean_string(BigInteger("-12345678901234567899") < BigInteger("-12345678901234567890")) << endl;
		cout << "(-12345678901234567899 >= 12345678901234567890) False -> " << get_boolean_string(BigInteger("-12345678901234567899") >= BigInteger("12345678901234567890")) << endl;
		cout << "(12345678901234567899 >= -12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567899") >= BigInteger("-12345678901234567890")) << endl;
		cout << "(-12345678901234567899 >= -12345678901234567890) False -> " << get_boolean_string(BigInteger("-12345678901234567899") >= BigInteger("-12345678901234567890")) << endl;
		cout << "(-12345678901234567899 <= -12345678901234567890) True -> " << get_boolean_string(BigInteger("-12345678901234567899") <= BigInteger("-12345678901234567890")) << endl;

		// Add test
		cout << endl << "[Add Test]" << endl;
		cout << "1234567890 + 1234567899 = 2469135789 -> " << BigInteger(1234567899) + BigInteger(1234567890) << endl;
		cout << "9999999999999 + 9999999999999 = 19999999999998 -> " << BigInteger(9999999999999) + BigInteger(9999999999999) << endl;
		cout << "1234 + 78907807809 = 78907809043 -> " << BigInteger(1234) + BigInteger(78907807809) << endl;
		cout << "1234 + 0 = 1234 -> " << BigInteger(1234) + BigInteger(0) << endl;

		// Subtract test
		cout << endl << "[Subtract Test]" << endl;
		cout << "1234567899 - 1234567890 = 9 -> " << BigInteger(1234567899) - BigInteger(1234567890) << endl;
		cout << "1234567890 - 1234567899 = -9 -> " << BigInteger(1234567890) - BigInteger(1234567899) << endl;
		cout << "1234567890 - 1234567890 = 0 -> " << BigInteger(1234567890) - BigInteger(1234567890) << endl;
		cout << "123456 - 23456789 = -23333333 -> " << BigInteger(123456) - BigInteger(23456789) << endl;
		cout << "23456789 - 123456 = 23333333 -> " << BigInteger(23456789) - BigInteger(123456) << endl;
		cout << "-23456789 - 123456 = -23580245 -> " << BigInteger(-23456789) - BigInteger(123456) << endl;
		cout << "-23456789 - (-123456) = -23333333 -> " << BigInteger(-23456789) - BigInteger(-123456) << endl;
		cout << "23456789 - (-123456) = 23580245 -> " << BigInteger(23456789) - BigInteger(-123456) << endl;

		// Shift test
		cout << endl << "[Shift Test]" << endl;
		cout << "1234567890 << 3 = 1234567890000 -> " << (BigInteger(1234567890) << 3) << endl;
		cout << "1234567890 >> 3 = 1234567 -> " << (BigInteger(1234567890) >> 3) << endl;
		cout << "0 << 3 = 0 -> " << (BigInteger(0) << 3) << endl;
		cout << "1 >> 3 = 0 -> " << (BigInteger(1) >> 3) << endl;

		// (Optional)
		cout << endl << "[Multiply Test]" << endl;
		cout << "12345 * 0 = 0 -> " << BigInteger(12345) * BigInteger(0) << endl;
		cout << "12345 * 67890 = 838102050 -> " << BigInteger(12345) * BigInteger(67890) << endl;
		cout << "-12345 * 67890 = -838102050 -> " << BigInteger(-12345) * BigInteger(67890) << endl;
		cout << "-12345 * -67890 = 838102050 -> " << BigInteger(-12345) * BigInteger(-67890) << endl;

		cout << endl << "[Divide Test]" << endl;
		cout << "67890 / 12345 = 5 -> " << BigInteger(67890) / BigInteger(12345) << endl;
		cout << "-67890 / 12345 = -5 -> " << BigInteger(-67890) / BigInteger(12345) << endl;
		cout << "-67890 / -12345 = 5 -> " << BigInteger(-67890) / BigInteger(-12345) << endl;

		cout << endl << "[Remainder Test]" << endl;
		cout << "67890 % 12345 = 6156 -> " << BigInteger(67890) % BigInteger(12345) << endl;
		cout << "-67890 % 12345 = 6180 -> " << BigInteger(-67890) % BigInteger(12345) << endl;
		cout << "-67890 % -12345 = -6165 -> " << BigInteger(-67890) % BigInteger(-12345) << endl;
		cout << endl;
	}

	const char* BigInteger::get_boolean_string(bool value) const {
		if (value) {
			return "True";
		}
		else {
			return "False";
		}
	}

	// Operator
	BigInteger& BigInteger::operator = (const BigInteger& big_integer) {
		char* new_value_string = new char[big_integer.capacity]();
		if (new_value_string != NULL) {
			if (this->value_string != NULL) {
				delete[] this->value_string;
				this->sign = true;
				this->length = 0;
				this->capacity = 0;
			}

			this->value_string = new_value_string;
			memcpy(this->value_string, big_integer.get_string(), big_integer.capacity);
			this->sign = big_integer.sign;
			this->length = big_integer.length;
			this->capacity = big_integer.capacity;
		}

		return *this;
	}

	BigInteger& BigInteger::operator = (std::string value) {
		bool zero_flag = false;

		// Check negativity
		if (value[0] == '-') {
			this->sign = false;
			value = value.substr(1, value.length() - 1);
		}

		// Zero check
		zero_flag = true;
		for (unsigned int place_index = 0; place_index < value.length(); place_index++) {
			if (value[place_index] != '0') {
				zero_flag = false;
			}
		}

		if (zero_flag) {
			this->sign = true;
			this->length = 1;
			this->value_string[0] = '0';
			this->zero_compaction();
			return *this;
		}

		while (this->capacity < value.length()) {
			this->doubling_capacity();
		}

		memcpy(this->value_string, value.c_str(), value.length());
		this->length = static_cast<unsigned int>(value.length());

		this->zero_compaction();

		return *this;
	}

	bool BigInteger::operator == (const BigInteger& big_integer) const {
		if (this->length != big_integer.length) {
			return false;
		}

		if (this->sign != big_integer.sign) {
			return false;
		}

		for (unsigned int place_index = 0; place_index < big_integer.length; place_index++) {
			if (this->value_string[place_index] != big_integer.value_string[place_index]) {
				return false;
			}
		}

		return true;
	}

	bool BigInteger::operator != (const BigInteger& big_integer) const {
		return !(*this == big_integer);
	}

	bool BigInteger::operator > (const BigInteger& big_integer) const {
		BigInteger::COMPARE_RESULT compare_result;

		// If sign is the same
		if (this->sign == big_integer.sign) {
			// Compare two absolute values
			compare_result = this->compare_absolute_value(big_integer);

			// Compare two positive values
			if (this->sign) {
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
			if (this->sign) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	bool BigInteger::operator < (const BigInteger& big_integer) const {
		return (big_integer > *this);
	}

	bool BigInteger::operator >= (const BigInteger& big_integer) const {
		return !(big_integer > *this);
	}

	bool BigInteger::operator <= (const BigInteger& big_integer) const {
		return !(big_integer < *this);
	}

	BigInteger BigInteger::operator + (const BigInteger& big_integer) const {
		BigInteger result;

		// Redirecting to subtraction
		if (this->sign != big_integer.sign) {
			if (this->sign) {	// Positive
				result = big_integer;
				result.toggle_sign();
				return *this - result;
			}
			else {	// Negative
				result = *this;
				result.toggle_sign();
				return result - *this;
			}
		}

		// Set new base length
		unsigned int new_length = this->length;
		if (big_integer.length > new_length) {
			new_length = big_integer.length;
		}
		new_length += 1;

		// Initialize result value
		while (result.capacity < new_length) {
			result.doubling_capacity();
		}
		result.length = new_length;
		result.sign = this->sign;

		// Calculate
		for (unsigned int place_index = 0; place_index < this->length; place_index++) {
			result.value_string[new_length - place_index - 1] += this->value_string[this->length - place_index - 1] - '0';
		}

		for (unsigned int place_index = 0; place_index < big_integer.length; place_index++) {
			result.value_string[new_length - place_index - 1] += big_integer.value_string[big_integer.length - place_index - 1] - '0';
		}

		// Carry and adjust
		for (unsigned int place_index = 0; place_index < new_length - 1; place_index++) {
			if (result.value_string[new_length - place_index - 1] >= 10) {
				result.value_string[new_length - place_index - 1] -= 10;
				result.value_string[new_length - place_index - 2] += 1;
			}
			result.value_string[new_length - place_index - 1] += '0';
		}
		result.value_string[0] += '0';

		// Zero compaction
		result.zero_compaction();

		return result;
	}

	BigInteger BigInteger::operator - (const BigInteger& big_integer) const {
		BigInteger result;

		// Redirecting to addition
		if (this->sign != big_integer.sign) {
			if (this->sign) {	// Positive
				result = big_integer;
				result.toggle_sign();
				return *this + result;
			}
			else {	// Negative
				result = big_integer;
				result.toggle_sign();
				return result + *this;
			}
		}

		// Value Comparison
		BigInteger::COMPARE_RESULT compare_result;
		const BigInteger* bigger_value = NULL;
		const BigInteger* smaller_value = NULL;

		compare_result = this->compare_absolute_value(big_integer);
		if (compare_result == BigInteger::COMPARE_EQUAL) {
			return BigInteger(0);
		}
		else if (compare_result == BigInteger::COMPARE_LARGER) {
			result.sign = this->get_sign();
			bigger_value = this;
			smaller_value = &big_integer;
		}
		else {
			result.sign = big_integer.get_sign() ^ 1;  // XOR toggling
			bigger_value = &big_integer;
			smaller_value = this;
		}

		// Initialize result value
		while (result.capacity < bigger_value->length) {
			result.doubling_capacity();
		}
		result.length = bigger_value->length;

		// Calculate
		for (unsigned int place_index = 0; place_index < bigger_value->length; place_index++) {
			result.value_string[result.length - place_index - 1] += (bigger_value->value_string[bigger_value->length - place_index - 1] - '0');
		}

		for (unsigned int place_index = 0; place_index < smaller_value->length; place_index++) {
			result.value_string[result.length - place_index - 1] -= (smaller_value->value_string[smaller_value->length - place_index - 1] - '0');
		}

		// Borrow and adjust
		for (unsigned int place_index = 0; place_index < result.length - 1; place_index++) {
			if (result.value_string[result.length - place_index - 1] < 0) {
				result.value_string[result.length - place_index - 1] += 10;
				result.value_string[result.length - place_index - 2] -= 1;
			}
			result.value_string[result.length - place_index - 1] += '0';
		}
		result.value_string[0] += '0';

		// Zero compaction
		result.zero_compaction();

		return result;
	}

	BigInteger BigInteger::operator * (const BigInteger& big_integer) const {
		BigInteger result;
		/* Should be implemented */

		return result;
	}

	BigInteger BigInteger::operator / (const BigInteger& big_integer) const {
		BigInteger result;
		/* Should be implemented */

		return result;
	}

	BigInteger BigInteger::operator % (const BigInteger& big_integer) const {
		BigInteger result;
		/* Should be implemented */

		return result;
	}

	BigInteger BigInteger::operator << (unsigned int shift_amount) const {
		BigInteger result = *this;

		if (result == 0) {
			return BigInteger(0);
		}

		if (result.capacity < result.length + shift_amount) {
			result.doubling_capacity();
		}

		for (unsigned int place_index = 0; place_index < shift_amount; place_index++) {
			result.value_string[result.length + place_index] = '0';
		}
		result.length += shift_amount;

		result.shrink_to_fit();

		return result;
	}

	BigInteger BigInteger::operator >> (unsigned int shift_amount) const {
		BigInteger result = *this;

		if (shift_amount >= result.length) {
			return BigInteger(0);
		}

		for (unsigned int place_index = 0; place_index < shift_amount; place_index++) {
			result.value_string[result.length - 1 - place_index] = 0;
		}
		result.length -= shift_amount;

		result.shrink_to_fit();

		return result;
	}

	const char BigInteger::operator [] (unsigned int index) const {
		return this->value_string[index];
	}

	std::ostream& interface_bignumber::operator << (std::ostream& out, const BigInteger& big_integer) {
		// Print minus sign
		if (!big_integer.get_sign()) {
			out << std::string("-");
		}

		// Print values
		out << std::string(big_integer.get_string(), big_integer.get_length());
		return out;
	}

	std::istream& interface_bignumber::operator >> (std::istream& in, BigInteger& big_integer) {
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

		big_integer = BigInteger(input_string.substr(begin_index));

		return in;
	}
}