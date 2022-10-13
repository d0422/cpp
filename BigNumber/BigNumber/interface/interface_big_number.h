#pragma once
#include <iostream>

namespace interface_bignumber {
	class IBigNumber {
	public:
		static const int initial_capacity = 10;

		virtual bool get_sign() const = 0;
		virtual void toggle_sign() = 0;
	};
}