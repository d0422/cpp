#pragma once
#include <iostream>


namespace abstract_bignumber {
	class AbstractBigNumber {
	protected:
		static const int initial_capacity = 10;
		bool sign;
		unsigned int length;
		unsigned int capacity;

		// Protected method
		const char* get_boolean_string(bool) const;

		// Protected pure virtual method
		virtual void initialize_properties() = 0;
		virtual void zero_compaction() = 0;

	public:
		// Public property
		enum COMPARE_RESULT {
			COMPARE_LARGER,
			COMPARE_EQUAL,
			COMPARE_SMALLER,
		};

		// Public method
		void toggle_sign();

		// Public pure virtual method
		virtual std::string get_name() const = 0; //���� �����Լ� -> �߻�Ŭ����
		virtual char* get_string() const = 0;//���� �����Լ� -> �߻�Ŭ����
		virtual bool get_sign() const = 0;//���� �����Լ� -> �߻�Ŭ����

		virtual unsigned int get_capacity() const = 0; //���� �����Լ� -> �߻�Ŭ����
		virtual unsigned int get_length() const = 0; //���� �����Լ� -> �߻�Ŭ����

		virtual void doubling_capacity() = 0; //���� �����Լ� -> �߻�Ŭ����
		virtual void shrink_to_fit() = 0; //���� �����Լ� -> �߻�Ŭ����

		virtual void test() const = 0; //���� �����Լ� -> �߻�Ŭ����
	};
}