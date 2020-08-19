#ifndef SUNDA_LANG_SRC_TYPE_H_
#define SUNDA_LANG_SRC_TYPE_H_

#include <cstdint>
#include <limits>

namespace Sunda {

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

// Primitive number bounds
const i8 i8_MAX = 127;
const char *const i8_MAX_S = "127";
const i8 i8_MIN = -128;
const char *const i8_MIN_S = "128";

const u8 u8_MAX = 255;
const char *const u8_MAX_S = "255";
const u8 u8_MIN = 0;
const char *const u8_MIN_S = "0";

const i16 i16_MAX = 32767;
const char *const i16_MAX_S = "32767";
const i16 i16_MIN = -32768;
const char *const i16_MIN_S = "32768";

const u16 u16_MAX = 65535;
const char *const u16_MAX_S = "65535";
const i16 u16_MIN = 0;
const char *const u16_MIN_S = u8_MIN_S;

const i32 i32_MAX = 2147483647;
const char i32_MAX_S[] = "2147483647";
const i32 i32_MIN = -2147483648;
const char i32_MIN_S[] = "2147483648";

const u32 u32_MAX = 4294967295;
const char *const u32_MAX_S = "4294967295";
const i32 u32_MIN = 0;
const char *const u32_MIN_S = u8_MIN_S;

const i64 i64_MAX = 9223372036854775807;
const char *const i64_MAX_S = "9223372036854775807";
const i64 i64_MIN = -9223372036854775808;
const char *const i64_MIN_S = "9223372036854775808";

const u64 u64_MAX = 18446744073709551615;
const char *const u64_MAX_S = "18446744073709551615";
const u64 u64_MIN = 0;
const char *const u64_MIN_S = u8_MIN_S;

}

#endif //SUNDA_LANG_SRC_TYPE_H_
