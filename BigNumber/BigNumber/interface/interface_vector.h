#pragma once


namespace interface_bignumber {
	class IVector {
	public:
		virtual char* get_string() const = 0;
		virtual unsigned int get_capacity() const = 0;
		virtual unsigned int get_length() const = 0;

		virtual void doubling_capacity() = 0;
		virtual void shrink_to_fit() = 0;
	};
}