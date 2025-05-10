#include "long_number.hpp"



using naa::LongNumber;
		
LongNumber::LongNumber() : numbers(nullptr), length(0), sign(0) {}

LongNumber::LongNumber(const char* const str) {
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
    if (length == 1 && numbers[0] == 0) {
        return LongNumber("0");
    }

    // Определение знака результата
    int result_sign = sign ^ x.sign;

    // Создаем копии для работы с абсолютными значениями
    LongNumber dividend = *this;
    dividend.sign = 0;
    LongNumber divisor = x;
    divisor.sign = 0;

    // Если делимое меньше делителя
    if (dividend < divisor) {
        return LongNumber("0");
    }

    // Если числа равны
    if (dividend == divisor) {
        LongNumber result("1");
        result.sign = result_sign;
        return result;
    }

    // Специальный случай: деление на 1
    if (divisor.length == 1 && divisor.numbers[0] == 1) {
        dividend.sign = result_sign;
        return dividend;
    }

    // Инициализация результата
    LongNumber result("0");
    LongNumber current("0");

    // Основной цикл деления
    for (int i = 0; i < dividend.length; i++) {
        current = current * LongNumber("10");
        current = current + LongNumber(std::to_string(dividend.numbers[i]).c_str());

        // Находим цифру для частного
        int digit = 0;
        LongNumber multiple("0");
        while (digit <= 9) {
            LongNumber temp = divisor * LongNumber(std::to_string(digit).c_str());
            if (temp > current) {
                break;
            }
            multiple = temp;
            digit++;
        }
        digit--;

        // Добавляем цифру к результату
        result = result * LongNumber("10") + LongNumber(std::to_string(digit).c_str());

        // Вычитаем из текущего остатка
        current = current - multiple;
    }

    // Удаление ведущих нулей
    int leading_zeros = 0;
    while (leading_zeros < result.length && result.numbers[leading_zeros] == 0) {
        leading_zeros++;
    }

    if (leading_zeros > 0) {
        if (leading_zeros == result.length) {
            return LongNumber("0");
        }

        LongNumber trimmed;
        trimmed.length = result.length - leading_zeros;
        trimmed.numbers = new int[trimmed.length];
        trimmed.sign = result_sign;

        for (int i = 0; i < trimmed.length; i++) {
            trimmed.numbers[i] = result.numbers[i + leading_zeros];
        }

        return trimmed;
    }

    result.sign = result_sign;
    return result;
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
    // Проверка деления на ноль
    if (x.length == 1 && x.numbers[0] == 0) {
        throw std::runtime_error("Division by zero");
    }

    // Если делимое меньше делителя
    if (*this < x) {
        return *this;
    }

    // Вычисляем частное
    LongNumber quotient = *this / x;

    // Вычисляем остаток
    LongNumber remainder = *this - (quotient * x);

    // Корректировка знака остатка
    remainder.sign = sign; // Остаток сохраняет знак делимого
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
namespace naa {
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
