#include "long_number.hpp"

using pda::LongNumber;
		
LongNumber::LongNumber() {
	length = 0;
}

LongNumber::LongNumber(const char* const str) {
	this->length = this->get_length(str);


	if (str[0] == '-')
	{
		sign = 1;
		length--;
	}

	numbers = new int[length];
	for (int i = 0; i < length; i++) 
	{
		numbers[i] = str[i+sign] - '0';
	}
}

LongNumber::LongNumber(const LongNumber& x) {
	numbers = new int[length];
    std::copy(x.numbers, x.numbers + length, numbers);
}

LongNumber::LongNumber(LongNumber&& x) {
	x.numbers = nullptr;
    x.length = 0;
    x.sign = 0;
}

LongNumber::~LongNumber() {
	if (numbers) {
        delete[] numbers;
    }
    numbers = nullptr;
    length = 0;
    sign = 0;
}

LongNumber& LongNumber::operator = (const char* const str) {
	*this = LongNumber(str);
    return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this != &x) {
        if (numbers) {
            delete[] numbers;
        }
        length = x.length;
        sign = x.sign;
        numbers = new int[length];
        std::copy(x.numbers, x.numbers + length, numbers);
    }
    return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if (this != &x) {
        if (numbers) {
            delete[] numbers;
        }
        numbers = x.numbers;
        length = x.length;
        sign = x.sign;
        x.numbers = nullptr;
        x.length = 0;
        x.sign = 1;
    }
    return *this;
}
bool LongNumber::operator == (const LongNumber& x) const {
    
    if (this->sign != x.sign){
        return 0;
    }
    if (this->length != x.length){
        return 0;
    }
    if ((this->length == x.length) && this->sign == x.sign){
        bool flag = true;
        for (int i = 0; i < length; i++){
            if (this->numbers[i] != x.numbers[i]){
                flag = false;
                break;
            }
            if (flag == true){
                return 1;
            }else{
                return 0;
            }
        }
    }
}

bool LongNumber::operator != (const LongNumber& x) const {
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
    if (this->sign > x.sign){
        return 1;
    }else if(this->sign < x.sign){
        return 0;
    }else{
        if (this->sign == -1){
            if (this->length > x.length){
                return 0;
            }else if(this->length < x.length){
                return 1;
            }else{
                bool flag = true;
                for (int i = 0; i < length; ++i){
                    if (this->numbers[i] > x.numbers[i]){
                        flag = false;
                        break;
                    }
                }
                if (flag == true){
                    return 1;
                }else{
                    return 0;
                }
            }
        }else{
            if (this->length < x.length){
                return 0;
            }else if(this->length > x.length){
                return 1;
            }else{
                bool flag = true;
                for (int i = 0; i < length; ++i){
                    if (this->numbers[i] < x.numbers[i]){
                        flag = false;
                        break;
                    }
                }
                if (flag == true){
                    return 1;
                }else{
                    return 0;
                }
            }
            
        }
    }
}

bool LongNumber::operator < (const LongNumber& x) const {
    if (x > *this) return 1;
    if (*this > x) return 0;
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	if ((this->sign) && (x.sign))
	{
		LongNumber ng{"-1"};
		return (ng * (ng * *this + ng * x));
	} else if (this->sign)
	{
		return( x - *this);
	} else if (x.sign)
	{
		return (*this - x);
	}
	

	int max_length = (x.length >= this->length)? x.length : this->length;
	                        
    
	char* buffer = new char[max_length+1];
	int cf = 0;

	for (int i = 0; i <= max_length; i++){
		if (i < this->length && i < x.length){
			buffer[i] = this->numbers[this->length-1-i]+ x.numbers[x.length-1-i] +cf;

		} else if (i < this->length) {
			buffer[i] = this->numbers[this->length-1-i] + cf;
		} else if (i < x.length) {
			buffer[i] = x.numbers[x.length-1-i] + cf;
		} else if (cf) {

			buffer[i] = cf;
			max_length = i+1;
		}
		


		cf = buffer[i] / 10;
		buffer[i] = (buffer[i] % 10) + '0';


	}

	char* res = new char[max_length + 1];
	for (int i = 0; i < max_length; i++)
	{
		res[i] = buffer[max_length - i -1];

	}
	res[max_length + 1] = '\0';

	LongNumber ans {res};
	delete[] buffer;
	delete[] res;
	return ans;
}

LongNumber LongNumber::operator - (const LongNumber& x) const {

	// if ((x.sign && !this->sign) || (x.sign == 0 && this->sign))
	// {
	// 	LongNumber ng{"-1"};
	// 	return (*this + (ng * x));
	// } else if (x.sign && this->sign)
	// {
	// 	LongNumber ng{"-1"};
	// 	return(ng*((ng* *this)-(ng* x)));
	// }
	
	if (*this < x)
	{
		LongNumber ng {"-1"};
		LongNumber copy = *this;
		return (x - copy);
	}
	int cf = 0;
	char* buffer = new char[this->length];
	for (int i = 0; i < this->length; i++){
		if (x.length < i) {
			buffer[i] = this->numbers[this->length - 1 - i] - cf;
		}else{
			buffer[i] = this->numbers[this->length - 1 - i] - x.numbers[x.length - 1 - i] - cf;
		}
		cf = 0;
		if (buffer[i] < 0){
			cf = 1;
			buffer[i] += 10;
		}
		buffer[i] += '0';
	}
	
	int new_length = this->length;
	for (int i = 0; (i < this->length) && (buffer[this->length - i -1] == '0'); i++)
	{
		new_length--;
	}
	char* res = new char[new_length+1];
	for (int i = 0; i < new_length; i++)
	{
		res[i] = buffer[this->length - i -1];
	}
	res[new_length] = '\0';

	LongNumber ans {res};
	delete[] buffer;
	delete[] res;
	return ans;
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	int max_buffer_length = this->length + x.length;
	int* buffer = new int[max_buffer_length]();
	int result_length = 0;
  
	int sign = this->sign ^ x.sign;
  
	for (int i = 0; i < this->length; i++) {
	  for (int j = 0; j < x.length; j++) {
		buffer[i + j] += this->numbers[this->length - 1 - i] * x.numbers[x.length - 1 - j];
		result_length = i + j + 1;
		if (buffer[i + j] >= 10) {
		  buffer[i + j + 1] += buffer[i + j] / 10;
		  buffer[i + j] %= 10;
		  ++result_length;
		}
	  }
	}
  
	if (sign) {
	  result_length++;
	}
	char* res = new char[result_length + 1];
	if (sign) {
	  res[0] = '-';
	  for (int i = 1; i < result_length; i++) {
		res[i] = buffer[result_length - 1 - i] + '0';
	  }
	} else {
	  for (int i = 0; i < result_length; i++) {
		res[i] = buffer[result_length - 1 - i] + '0';
	  }
	}
	res[result_length] = '\0';
  
	LongNumber ans{res};
	delete[] buffer;
	delete[] res;
	return ans;
}
  

LongNumber LongNumber::operator/(const LongNumber& x) const {
    if (x.length == 1 && x.numbers[0] == 0) {
        throw std::runtime_error("Division by zero");
    }
    
    LongNumber dividend(*this);
    dividend.sign = 1;
    LongNumber divisor(x);
    divisor.sign = 1;
    
    if (dividend < divisor) {
        return LongNumber("0");
    }
    
    LongNumber quotient;
    quotient.sign = sign * x.sign;
    quotient.length = length;
    quotient.numbers = new int[quotient.length]{};
    
    LongNumber current;
    for (int i = length - 1; i >= 0; i--) {
        current = current * LongNumber("10") + LongNumber(std::to_string(numbers[i]).c_str());
        
        int digit = 0;
        while (current > divisor || current == divisor) {
            current = current - divisor;
            digit++;
        }
        
        quotient.numbers[i] = digit;
    }
    
    // Удаление ведущих нулей
    while (quotient.length > 1 && quotient.numbers[quotient.length-1] == 0) {
        quotient.length--;
    }
    
    return quotient;
}

LongNumber LongNumber::operator%(const LongNumber& divisor) const {
    if (divisor == LongNumber("0")) {
        throw std::runtime_error("Division by zero");
    }
    
    LongNumber dividend = *this;
    dividend.sign = 1;
    LongNumber abs_divisor = divisor;
    abs_divisor.sign = 1;
    LongNumber remainder;
    for (int i = dividend.length - 1; i >= 0; i--) {
        remainder = remainder * LongNumber("10") + LongNumber(std::to_string(dividend.numbers[i]).c_str());
        while (remainder > abs_divisor || remainder == abs_divisor) {
            remainder = remainder - abs_divisor;
        }
    }

    if (this->is_negative() && remainder != LongNumber("0")) {
        remainder = abs_divisor - remainder;
    }
    
    return remainder;
}

int LongNumber::get_digits_number() const noexcept {
	return (length);
}

int LongNumber::get_rank_number(int rank) const {
	return (numbers[length - rank]);
}

bool LongNumber::is_negative() const noexcept {
	return (this->sign);
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	int length = 0;
	while (str[length] != '\0') length++;
	return length;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace pda {
	std::ostream& operator << (std::ostream &os, const LongNumber& x)
	{
		if (x.sign)
		{
			os << '-';
		}
		for (int i = 0; i < x.length; i++)
		{
			os << x.numbers[i];
		}
		return os;
	}
}
