//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <string>

// template<> struct char_traits<char32_t>

// static char_type* move(char_type* s1, const char_type* s2, size_t n);

#include <string>
#include <cassert>

int main()
{
#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
    char32_t s1[] = {1, 2, 3};
    assert(std::char_traits<char32_t>::move(s1, s1+1, 2) == s1);
    assert(s1[0] == char32_t(2));
    assert(s1[1] == char32_t(3));
    assert(s1[2] == char32_t(3));
    s1[2] = char32_t(0);
    assert(std::char_traits<char32_t>::move(s1+1, s1, 2) == s1+1);
    assert(s1[0] == char32_t(2));
    assert(s1[1] == char32_t(2));
    assert(s1[2] == char32_t(3));
#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS
}
