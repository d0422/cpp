#pragma once


namespace interface_bignumber {
	class ITestable {
	public:
		virtual void test() const = 0;
		virtual const char* get_boolean_string(bool) const = 0;
	};
}