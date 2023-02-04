#include "number.h"

const uint2022_t zero = from_uint(0);
const uint2022_t one = from_uint(1);
const uint2022_t two = from_uint(2);
const uint2022_t three = from_uint(3);
const uint2022_t four = from_uint(4);
const uint2022_t five = from_uint(5);
const uint2022_t six = from_uint(6);
const uint2022_t seven = from_uint(7);
const uint2022_t eight = from_uint(8);
const uint2022_t nine = from_uint(9);
const uint2022_t ten = from_uint(10);

const int uint2022_t_size = 2022;

int to_int(const uint2022_t &value) {
  int ans = 0;
  for (int i = 0; i < uint2022_t_size; i++) {
    ans = ans + value.get(i) * (1 << i);
  }
  return ans;
}

uint2022_t from_uint(uint32_t i) {
  uint2022_t num;
  int j = 0;
  while ((i != 0) && (j < uint2022_t_size)) {
    num.put(j, i % 2);
    i /= 2;
    j++;
  }
  return num;
}

uint2022_t operator+(const uint2022_t &lhs, const uint2022_t &rhs) {
  uint2022_t sum;
  uint8_t left = 0;
  for (int i = 0; i < uint2022_t_size; i++) {
    uint8_t part_sum = lhs.get(i) + rhs.get(i) + left;
    sum.put(i, part_sum % 2);
    left = part_sum / 2;
  }
  return sum;
}

uint2022_t operator-(const uint2022_t &lhs, const uint2022_t &rhs) {
  uint2022_t diff;
  int left = 0;
  for (int i = 0; i < uint2022_t_size; i++) {
    int part_diff = int(lhs.get(i)) - int(rhs.get(i)) + int(left);
    switch (part_diff) {
      case (-2):diff.put(i, 0);
        left = -1;
        break;
      case (-1):diff.put(i, 1);
        left = -1;
        break;
      case (0):diff.put(i, 0);
        left = 0;
        break;
      case (1):diff.put(i, 1);
        left = 0;
        break;
      default:
        std::cout << "ERROR" << int(lhs.get(i)) << int(rhs.get(i)) << int(left) << "||" << int(part_diff) << std::endl;
    }
  }
  return diff;
}

uint2022_t operator*(const uint2022_t &lhs, const uint2022_t &rhs) {
  uint2022_t mul;
  uint8_t left = 0;
  for (int i = 0; i < uint2022_t_size; i++) {
    int part_mul = left;
    for (int j = 0; j <= i; j++) {
      part_mul += lhs.get(j) * rhs.get(i - j);
    }
    mul.put(i, part_mul % 2);
    left = part_mul / 2;
  }
  return mul;
}

/*
uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t counter;
    uint2022_t left_arg = lhs;
    uint2022_t right_arg = rhs;
    while (left_arg >= right_arg) {
        left_arg = (left_arg - right_arg);
        counter = counter + one;
    }
    return counter;
}*/

int meaningful_part(const uint2022_t &arg) {
  for (int i = uint2022_t_size - 1; i > -1; i--) {
    if (arg.get(i) == 1) {
      return i;
    }
  }
  return 0;
}

uint2022_t pow_2(const uint2022_t &arg, int i) {
  uint2022_t ans;
  for (int j = i; i < uint2022_t_size; i++) {
    ans.put(j, arg.get(j - i));
  }
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t &rhs) {
  uint2022_t left = lhs;
  uint2022_t ans;
  for (int i = (uint2022_t_size - 2) - meaningful_part(rhs); i > -1; i--) {
    if (left >= pow_2(rhs, i)) {
      ans.put(i, 1);
      left = left - pow_2(rhs, i);
    }
  }
  return ans;
}

bool operator==(const uint2022_t &lhs, const uint2022_t &rhs) {
  bool ans = true;
  for (int i = 0; i < uint2022_t_size; i++) {
    if (lhs.get(i) != rhs.get(i)) {
      ans = false;
      break;
    }
  }
  return ans;
}

bool operator!=(const uint2022_t &lhs, const uint2022_t &rhs) {
  return (!(lhs == rhs));
}

bool operator<=(const uint2022_t &lhs, const uint2022_t &rhs) {
  bool ans = true;
  for (int i = (uint2022_t_size - 1); i > -1; i--) {
    if (lhs.get(i) > rhs.get(i)) {
      ans = false;
      break;
    }
    if (lhs.get(i) < rhs.get(i)) {
      ans = true;
      break;
    }
  }
  return ans;
}

bool operator>=(const uint2022_t &lhs, const uint2022_t &rhs) {
  return ((!(lhs <= rhs)) || (lhs == rhs));
}

uint2022_t from_string(const char *buff) {
  int end = 0;
  uint2022_t ans;
  while (buff[end] != '\0') {
    ans = (ans * ten) + from_uint(buff[end] - '0');
    end++;
  }
  return ans;
}

std::ostream &operator<<(std::ostream &stream, const uint2022_t &value) {
  uint2022_t num = value;
  if (num <= nine) {
    if (num == zero) {
      stream << "0";
    } else if (num == one) {
      stream << "1";
    } else if (num == two) {
      stream << "2";
    } else if (num == three) {
      stream << "3";
    } else if (num == four) {
      stream << "4";
    } else if (num == five) {
      stream << "5";
    } else if (num == six) {
      stream << "6";
    } else if (num == seven) {
      stream << "7";
    } else if (num == eight) {
      stream << "8";
    } else if (num == nine) {
      stream << "9";
    }
  } else {
    stream << num / ten << (num - ((num / ten) * ten));
  }
  return stream;
}
