#include "big_integer.h"
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
// Identifier
const std::string BigInteger::name = "BigInteger";

// Method
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
	delete(this->value_string);

	this->capacity = new_capacity;
	this->value_string = new_value_string;
}

BigInteger::COMPARE_RESULT BigInteger::compare_absolute_value(const BigInteger& big_integer) const {
	int start_index = 0;

	int length = this->length;
	int given_length = big_integer.length;

	if (length > given_length) {
		return BigInteger::COMPARE_RESULT::COMPARE_LARGER;
	}
	else if (length < given_length) {
		return BigInteger::COMPARE_RESULT::COMPARE_SMALLER;
	}
	else {
		for (int place_index = 0; place_index < length; place_index++) {
			if (this->value_string[place_index + start_index] > big_integer.value_string[place_index + start_index]) {
				return BigInteger::COMPARE_RESULT::COMPARE_LARGER;
			}
			else if (this->value_string[place_index + start_index] < big_integer.value_string[place_index + start_index]) {
				return BigInteger::COMPARE_RESULT::COMPARE_SMALLER;
			}
		}
	}
	return BigInteger::COMPARE_RESULT::COMPARE_EQUAL;
}

// Method (Interface)
BigInteger::BigInteger() {
	/* Should be implemented */
	initialize_properties();
}

BigInteger::BigInteger(int value) {
	/* Should be implemented */
	string tmp = to_string(value);
	this->capacity = tmp.size()+1;
	this->value_string = new char[capacity]();
	if (value < 0) {
		this->sign = false;
		strcpy(value_string, tmp.substr(1).c_str());
	}
	else {
		this->sign = true;
		strcpy(value_string, tmp.c_str());
	}
	this->length = strlen(value_string);
}

BigInteger::BigInteger(long long value) {
	/* Should be implemented */
	string tmp = to_string(value);
	this->capacity = tmp.size()+1;
	this->value_string = new char[capacity]();
	if (value < 0) {
		this->sign = false;
		strcpy(value_string, tmp.substr(1).c_str());
	}
	else {
		this->sign = true;
		strcpy(value_string, tmp.c_str());
	}
	this->length = strlen(value_string);

}

BigInteger::BigInteger(std::string value) {
	this->capacity = value.size()+1;
	this->value_string = new char[capacity]();
	if (value.front() == '-') {
		this->sign = false;
		strcpy(value_string, value.substr(1).c_str());
	}
	else {
		this->sign = true;
		strcpy(value_string, value.c_str());
	}
	this->length = strlen(value_string);
}

BigInteger::BigInteger(const BigInteger& big_integer) {
	this->initialize_properties();

	char* new_value_string = new char[big_integer.capacity]();
	if (new_value_string != NULL) {
		if (this->value_string != NULL) {
			delete(this->value_string);
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
		delete(this->value_string);
		this->sign = true;
		this->length = 0;
		this->capacity = 0;
	}
}

std::string BigInteger::get_name() const {
	return name;
}

char* BigInteger::get_string() const {
	return this->value_string;
}

BigInteger& BigInteger::operator = (const BigInteger& big_integer) {
	char* new_value_string = new char[big_integer.capacity]();
	if (new_value_string != NULL) {
		if (this->value_string != NULL) {
			delete(this->value_string);
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
	return !(big_integer < *this);
}

bool BigInteger::operator <= (const BigInteger& big_integer) const {
	return !(big_integer > *this);
}

BigInteger BigInteger::operator + (const BigInteger& big_integer) const {
	/* Should be implemented */
	if ((this->sign && big_integer.sign)||(!this->sign&&!big_integer.sign)) {
		string str1(this->value_string);
		string str2(big_integer.value_string);
		string ret(max(str1.size(), str2.size()) + 1, '0');
		int sum = 0;
		for (int i = 0; i < ret.size(); ++i)
		{
			if (i < str1.size()) sum += str1[str1.size() - 1 - i] - '0';
			if (i < str2.size()) sum += str2[str2.size() - 1 - i] - '0';
			ret[ret.size() - 1 - i] = sum % 10 + '0';
			sum /= 10;
		}
		if (sum) ret.insert(ret.begin(), sum + '0');
		if (ret.front() == '0') ret = ret.substr(1);

		if (this->sign && big_integer.sign) return BigInteger(ret);
		else return BigInteger("-" + ret);
	}
	else if (this->sign && !big_integer.sign) {
		return *this - BigInteger(big_integer.value_string);
	}
	else if (!this->sign && big_integer.sign) {
		return (big_integer - BigInteger(string(this->value_string)));
	}
}

BigInteger BigInteger::operator - (const BigInteger& big_integer) const {
	/* Should be implemented */
	if ((this->sign && big_integer.sign) || (!this->sign && !big_integer.sign)) {
		string str1(this->value_string);
		string str2(big_integer.value_string);
		bool sign;
		if (this->sign && big_integer.sign) {
			sign = true;
		}
		else {
			sign = false;
		}
		if (str1 < str2) {
			str1.swap(str2);
			sign = !sign;
		}
		string ret(max(str1.size(), str2.size()), '0');
		int sum = 0;
		bool flag = false;
		for (int i = 0; i < ret.size(); ++i)
		{
			if (i < str1.size()) sum += (str1[str1.size() - 1 - i] - '0');
			if (i < str2.size()) {
				if (sum < (str2[str2.size() - 1 - i] - '0')) {
					sum = sum + 10 - (str2[str2.size() - 1 - i] - '0');
					flag = true;
				}
				else {
					sum -= (str2[str2.size() - 1 - i] - '0');
				}
			}
			ret[ret.size() - 1 - i] = sum + '0';
			if (flag) sum = -1;
			else sum = 0;
			flag = false;
		}
		while (ret.front() == '0') {
			ret=ret.substr(1);
		}
		if (sign) return BigInteger(ret);
		else return BigInteger("-" + ret);
	}
	else if (this->sign && !big_integer.sign) {
		return *this + BigInteger(string(big_integer.value_string));
	}
	else if (!this->sign && big_integer.sign) {
		return  *this+ BigInteger("-" + string(big_integer.value_string));
	}
}

BigInteger BigInteger::operator * (const BigInteger& big_integer) const {
	/* Implement if you want */
	BigInteger result;

	return result;
}

BigInteger BigInteger::operator / (const BigInteger& big_integer) const {
	/* Implement if you want */
	BigInteger result;

	return result;
}

BigInteger BigInteger::operator % (const BigInteger& big_integer) const {
	/* Implement if you want */
	BigInteger result;

	return result;
}

std::ostream& operator << (std::ostream& out, const BigInteger& big_integer) {
	// Print minus sign
	if (!big_integer.sign) {
		out << std::string("-");
	}

	// Print values
	out << std::string(big_integer.get_string(), big_integer.length);
	return out;
}

std::istream& operator >> (std::istream& in, BigInteger& big_integer) {
	std::string input_string;
	in >> input_string;

	big_integer = BigInteger(input_string);

	return in;
}