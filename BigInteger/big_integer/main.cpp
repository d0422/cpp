#include <iostream>
#include "big_integer.h"
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
	BigInteger big_integer;

	// Constructor test
	cout << "[Constructor Test]" << endl;
	cout << "Original BigInteger (integer: 1234567890): " << BigInteger(1234567890) << endl;
	cout << "Original BigInteger (longlong: 123456789012345): " << BigInteger(123456789012345) << endl;
	cout << "Original BigInteger (string: 12345678901234567890): " << BigInteger(string("12345678901234567890")) << std::endl;
	cout << "Original BigInteger (integer: -1234567890): " << BigInteger(-1234567890) << endl;
	cout << "Original BigInteger (longlong: -123456789012345): " << BigInteger(-123456789012345) << endl;
	cout << "Original BigInteger (string: -12345678901234567890): " << BigInteger(string("-12345678901234567890")) << std::endl;
	// I&O test
	cout << endl << "[I/O Test]" << endl;
	cout << "Enter a value: ";
	cin >> big_integer;
	cout << "Given value: " << big_integer << endl;
	// Comparison test
	cout << endl << "[Comparison Test]" << endl;
	cout << "(12345678901234567899 > 12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567899") > BigInteger("12345678901234567890")) << endl;
	cout << "(12345678901234567899 < 12345678901234567890) False -> " << get_boolean_string(BigInteger("12345678901234567899") < BigInteger("12345678901234567890")) << endl;
	cout << "(12345678901234567899 == 12345678901234567890) False -> " << get_boolean_string(BigInteger("12345678901234567899") == BigInteger("12345678901234567890")) << endl;
	cout << "(12345678901234567890 == 12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567890") == BigInteger("12345678901234567890")) << endl;
	cout << "(-12345678901234567899 > 12345678901234567890) False -> " << get_boolean_string(BigInteger("-12345678901234567899") > BigInteger("12345678901234567890")) << endl;
	cout << "(12345678901234567899 > -12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567899") > BigInteger("-12345678901234567890")) << endl;
	cout << "(-12345678901234567899 > -12345678901234567890) False -> " << get_boolean_string(BigInteger("-12345678901234567899") > BigInteger("-12345678901234567890")) << endl;
	cout << "(-12345678901234567899 < -12345678901234567890) True -> " << get_boolean_string(BigInteger("-12345678901234567899") < BigInteger("-12345678901234567890")) << endl;
	// Add test
	cout << endl << "[Add Test]" << endl;
	cout << "1234567890 + 1234567899 = 2469135789 -> " << BigInteger(12345676899) + BigInteger(12345676890) << endl;
	cout << "-1234567890+ -1234567899 = -2469135789 -> " << BigInteger(-12345676899) + BigInteger(-12345676890) << endl;
	cout << "-1234567899 + 1234567890 = -9 -> " << BigInteger(-12345676899) + BigInteger(12345676890) << endl;
	cout << "1234567899 + -1234567890 = 9 -> " << BigInteger(12345676899) + BigInteger(-12345676890) << endl;

	cout << endl << "[Subtract Test]" << endl;
	cout << "1234567899 - 1234567890 = 9 -> " << BigInteger(12345676899) - BigInteger(12345676890) << endl;
	cout << "1234567890 - 1234567899 = -9 -> " << BigInteger(12345676890) - BigInteger(12345676899) << endl;
	cout << "-75--85=10 -> " << BigInteger(-75) - BigInteger(-85) << endl;
	cout << "75-85=-10-> " << BigInteger(75) - BigInteger(85) << endl;
	cout << "-75-85=-160 -> " << BigInteger(-75) - BigInteger(85) << endl;
	cout << "75--85=160 -> " << BigInteger(75) - BigInteger(-85) << endl;

}

int main(int argc, char* argv[]) {
	// Test BigInteger class
	test_big_integer();

	return 0;
}