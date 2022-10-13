#include <iostream>
#include "standalone/standalone_big_integer.h"
#include "standalone/standalone_big_float.h"
#include "abstract/abstract_big_integer.h"
#include "abstract/abstract_big_float.h"
#include "interface/interface_big_integer.h"
#include "interface/interface_big_float.h"
using namespace std;


const char* get_boolean_string(bool value) {
	if (value) {
		return "True";
	}
	else {
		return "False";
	}
}

void test_big_integer() {
	using namespace standalone;
	BigInteger big_integer;

	cout << "[Constructor Test]" << std::endl;
	cout << "Original BigInteger (integer: 0): " << BigInteger(0) << endl;
	cout << "Original BigInteger (string: 0): " << BigInteger(std::string("0")) << std::endl;
	cout << "Original BigInteger (string: -0): " << BigInteger(std::string("-0")) << std::endl;
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

void test_big_float() {
	using namespace standalone;
	BigFloat big_float;

	cout << "[Constructor Test]" << endl;
	cout << "Original BigFloat (integer: 0): " << BigFloat(0) << endl;
	cout << "Original BigFloat (string: 0): " << BigFloat(string("0")) << std::endl;
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

	// Subtract test
	cout << endl << "[Subtract Test]" << endl;
	cout << "1234567.899 - 1234567.890 = 0.009 -> " << BigFloat("1234567.899") - BigFloat("1234567.890") << endl;
	cout << "1234567.890 - 1234567.899 = -0.009 -> " << BigFloat("1234567.890") - BigFloat("1234567.899") << endl;
	cout << "1234567.890 - 1234567.890 = 0 -> " << BigFloat("1234567.890") - BigFloat("1234567.890") << endl;
	cout << "123456 - 2345678.9 = -2222222.9 -> " << BigFloat("123456") - BigFloat("2345678.9") << endl;
	cout << "2345678.9 - 123456 = 2222222.9 -> " << BigFloat("2345678.9") - BigFloat("123456") << endl;
	cout << "1234 - 0.1 = 1233.9 -> " << BigFloat("1234") - BigFloat("0.1") << endl;
	cout << "1234 - 1.0 = 1233 -> " << BigFloat("1234") - BigFloat("1.0") << endl;
	cout << "-1234 - (-1.0) = -1233 -> " << BigFloat("-1234") - BigFloat("-1.0") << endl;
	cout << "1234 - (-1.0) = 1235 -> " << BigFloat("1234") - BigFloat("-1.0") << endl;

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


int main(int argc, char* argv[]) {
	// Standalone test
	cout << "1. Standalone test" << endl;
	test_big_integer();
	test_big_float();

	// abstract test
	cout << "2. abstract test" << endl;
	abstract_bignumber::BigInteger abstract_big_integer;
	abstract_bignumber::BigFloat abstract_big_float;
	abstract_big_integer.test();
	abstract_big_float.test();

	// interface test
	cout << "3. interface test" << endl;
	interface_bignumber::BigInteger interface_big_integer;
	interface_bignumber::BigFloat interface_big_float;
	interface_big_integer.test();
	interface_big_float.test();

	return 0;
}