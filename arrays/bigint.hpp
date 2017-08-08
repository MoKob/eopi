#ifndef EOPI_ARRAYS_BIGINT_HPP_
#define EOPI_ARRAYS_BIGINT_HPP_

#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <vector>

#include <string>

namespace eopi {
namespace arrays {
class BigInt {
    const static std::uint8_t constexpr WIDTH = 9;
    const static std::int64_t constexpr CARRY_FROM = 1000000000;

   public:
    friend std::ostream& operator<<(std::ostream& os, BigInt const& value) {
        os << value.digits.back();

        // set leading zeros to true, filling with `0` up to width
        for (std::size_t i = 1; i < value.digits.size(); ++i)
        {
            os << std::setw(WIDTH) << std::setfill('0');
            os << value.digits[value.digits.size() - i - 1];
        }

        return os;
    };

    BigInt& operator++() {
        if (digits.back() < 0) {
            for (std::size_t i = 0; i < digits.size(); ++i) {
                if (std::abs(digits[i]) > 0) {
                    if (digits[i] < 0)
                        digits[i]++;
                    else
                        digits[i]--;
                    // removed last digit?
                    if (digits[i] == 0 && i + 1 == digits.size())
                        digits.pop_back();
                    return *this;
                } else {
                    digits[i] = CARRY_FROM - 1;
                }
            }
        } else {
            for (std::size_t i = 0; i < digits.size(); ++i) {
                if (digits[i] + 1 < CARRY_FROM) {
                    digits[i]++;
                    return *this;
                } else {
                    digits[i] = 0;
                }
            }
            digits.push_back(1);
        }
        return *this;
    }

    BigInt& operator+=(BigInt const& other) {
        digits.resize(std::max(digits.size(), other.digits.size()));
        std::int64_t carry = 0;
        for (std::size_t i = 0; i < other.digits.size(); ++i) {
            digits[i] = digits[i] + other.digits[i] + carry;
            carry = digits[i] / CARRY_FROM;
            digits[i] %= CARRY_FROM;
        }
        return *this;
    }

    friend BigInt operator+(BigInt lhs, BigInt const& rhs) {
        return lhs += rhs;
    }

    // multiply by an int
    friend BigInt operator*(BigInt lhs, std::int32_t rhs){
        std::int64_t carry = 0;
        for( auto &digit : lhs.digits )
        {
            digit = digit * rhs + carry;
            carry = digit / CARRY_FROM;
            if( digit < 0 )
            {
                if( carry )
                    digit = std::abs(digit) % CARRY_FROM;
            }
            else
                digit %= CARRY_FROM;
        }
        if( carry )
            lhs.digits.push_back(carry);
        return lhs;
    }

    friend BigInt operator*(BigInt const& lhs, BigInt const& rhs) {
        // ensure less work
        if( lhs.digits.size() < rhs.digits.size() )
            return rhs * lhs;

        BigInt result(0);
        auto sign = lhs.digits.back() * rhs.digits.back() < 0 ? -1 : 1;



        // can treat all digits as aboslute values now

        result.digits.back() *= sign;
        return result;
    }

    BigInt(std::int32_t value) {
        digits.push_back(value % CARRY_FROM);
        if (value >= CARRY_FROM) digits.push_back(value / CARRY_FROM);
    }

    BigInt(std::string const& str_digits) {
        std::uint8_t current_digit = 0;
        std::uint32_t value = 0;
        std::uint32_t pow = 1;
        for (auto itr = str_digits.rbegin();
             itr != str_digits.rend() && *itr != '-'; ++itr) {
            if (current_digit == WIDTH) {
                current_digit = 0;
                digits.push_back(value);
                value = 0;
                pow = 1;
            }
            value += pow * (*itr - '0');
            pow *= 10;
            ++current_digit;
        }
        digits.push_back(value);

        // store sign
        if (str_digits.front() == '-') digits.back() = -digits.back();
    }

   private:
    std::vector<std::int64_t> digits;
};
}  // namespace arrays
}  // namespace eopi

#endif  // EOPI_ARRAYS_BIGINT_HPP_
