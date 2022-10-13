#include "abstract_big_number.h"

namespace abstract_bignumber {
	// Protected method
	const char* AbstractBigNumber::get_boolean_string(bool value) const {
		if (value) {
			return "True";
		}
		else {
			return "False";
		}
	} //부호를 얻는 getter

	// Public method
	void AbstractBigNumber::toggle_sign() {
		this->sign ^= 1;	// XOR toggling
	} //부호 변환하는 함수
}