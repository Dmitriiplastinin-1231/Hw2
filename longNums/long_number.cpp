#include "long_number.hpp"



using pda::LongNumber;
		
LongNumber::LongNumber() : numbers(nullptr), length(0), sign(0) {}

LongNumber::LongNumber(const char* const str) {

	// if (str[1] == '\0' && str[0] == '0')
	// {
	// 	length = 1;
	// 	numbers = new int[length];
	// 	numbers[0] = 0;
	// 	return;
	// }

	this->length = this->get_length(str);

	
	
	if (str[0] == '-')
	{
		sign = 1;
		length--;
	}
	
	
	numbers = new int[length];
	
	int begin{sign};
	while (str[begin] == '0') begin++;
	length -= begin;
	
	for (int i = 0; i < length; i++) 
	{
		numbers[i] = str[i+begin] - '0';
	}
}

LongNumber::LongNumber(const LongNumber& x) : 
    length(x.length), sign(x.sign), numbers(new int[x.length]) {
    std::copy(x.numbers, x.numbers + length, numbers);
}

LongNumber::LongNumber(LongNumber&& x) :
	numbers(x.numbers), length(x.length), sign(x.sign) {
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
		return (ng * (ng * *this - ng * x));
	} else if (this->sign)
	{
		LongNumber ng{"-1"};
		return( x - (*this)*ng);
	} else if (x.sign)
	{
		LongNumber ng{"-1"};
		return (*this - x*ng);
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
		} else if (cf) {if (this != &x) {
			buffer[i] = cf;
			max_length = i+1;
		}
		return *this;

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
	res[max_length] = '\0';
	
	LongNumber ans {res};
	delete[] buffer;
	delete[] res;
	return ans;
}

LongNumber LongNumber::operator - (const LongNumber& x) const {

	if ((x.sign && !this->sign) || (x.sign == 0 && this->sign))
	{
		LongNumber ng{"-1"};
		return (*this + (ng * x));
	} else if (x.sign && this->sign)
	{
		LongNumber ng{"-1"};
		return(ng*((ng* *this)-(ng* x)));
	}
	
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
	std::cout << buffer[0] << std::endl;
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
  

LongNumber LongNumber::operator / (const LongNumber& x) const {
    // Проверка деления на ноль
    if (x.length == 1 && x.numbers[0] == 0) {
        throw std::runtime_error("Division by zero");
    }
    
    // Проверка если делимое равно нулю
    if (this->length == 1 && this->numbers[0] == 0) {
        return LongNumber("0");
    }
    
    // Определение знака результата
    int result_sign = this->sign ^ x.sign;
    
    // Работаем с абсолютными значениями чисел
    LongNumber dividend = this->sign ? (*this * LongNumber("-1")) : *this;
    LongNumber divisor = x.sign ? (x * LongNumber("-1")) : x;
    
    // Если делимое меньше делителя, результат 0
    if (dividend < divisor) {
        return LongNumber("0");
    }
    
    // Если числа равны, результат 1 с нужным знаком
    if (dividend == divisor) {
        LongNumber result("1");
        result.sign = result_sign;
        return result;
    }
    
    // Случай, когда делитель равен 1
    if (divisor.length == 1 && divisor.numbers[0] == 1) {
        LongNumber result = dividend;
        result.sign = result_sign;
        return result;
    }
    
    // Алгоритм длинного деления
    LongNumber quotient("0");
    LongNumber remainder("0");
    
    for (int i = 0; i < dividend.length; i++) {
        // Добавляем следующую цифру к остатку
        remainder = remainder * LongNumber("10") + LongNumber(std::to_string(dividend.numbers[i]).c_str());
        
        // Находим максимальное k, такое что divisor * k <= remainder
        int k = 0;
        LongNumber product("0");
        while (k <= 9) {
            LongNumber temp = divisor * LongNumber(std::to_string(k).c_str());
            if (temp > remainder) {
                break;
            }
            product = temp;
            k++;
        }
        k--;
        
        // Добавляем цифру к результату
        quotient = quotient * LongNumber("10") + LongNumber(std::to_string(k).c_str());
        
        // Вычитаем product из remainder
        remainder = remainder - product;
    }
    
    // Удаляем ведущие нули
    int leading_zeros = 0;
    while (leading_zeros < quotient.length && quotient.numbers[leading_zeros] == 0) {
        leading_zeros++;
    }
    
    if (leading_zeros > 0) {
        if (leading_zeros == quotient.length) {
            return LongNumber("0");
        }
        
        LongNumber trimmed;
        trimmed.length = quotient.length - leading_zeros;
        trimmed.numbers = new int[trimmed.length];
        trimmed.sign = result_sign;
        
        for (int i = 0; i < trimmed.length; i++) {
            trimmed.numbers[i] = quotient.numbers[i + leading_zeros];
        }
        
        return trimmed;
    }
    
    quotient.sign = result_sign;
    return quotient;
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
    // Проверка деления на ноль
    if (x.length == 1 && x.numbers[0] == 0) {
        throw std::runtime_error("Division by zero");
    }
    
    // Если делимое меньше делителя, остаток равен делимому
    if (*this < x) {
        return *this;
    }
    
    // Вычисляем частное
    LongNumber quotient = *this / x;
    
    // Вычисляем остаток: this - (quotient * x)
    LongNumber remainder = *this - (quotient * x);
    
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
