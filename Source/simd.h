#ifndef SIMD_H
#define SIMD_H

#if defined(USE_SIMD)
#include <immintrin.h>
#endif

#if defined(USE_AVX512)
typedef __m512i vepi16;
typedef __m512i vepi32;

static inline vepi16 zero_epi16(void) { return _mm512_setzero_si512(); }
static inline vepi32 zero_epi32(void) { return _mm512_setzero_si512(); }
static inline vepi16 load_epi16(const int16_t *memory_address) { return _mm512_load_si512((const __m512i *)memory_address); }
static inline vepi32 load_epi32(const int32_t *memory_address) { return _mm512_load_si512((const __m512i *)memory_address); }
static inline vepi16 load_epi16_broadcast(int num) { return _mm512_set1_epi16(num); }
static inline vepi32 load_epi32_broadcast(int num) { return _mm512_set1_epi32(num); }
// static inline void store_epi16(void *memory_address, vepi16 vector) { _mm512_store_si512(memory_address, vector); }
static inline vepi32 add_epi32(vepi32 v1, vepi32 v2) { return _mm512_add_epi32(v1, v2); }
static inline vepi16 multiply_epi16(vepi16 v1, vepi16 v2) { return _mm512_mullo_epi16(v1, v2); }
static inline vepi32 multiply_add_epi16(vepi16 v1, vepi16 v2) { return _mm512_madd_epi16(v1, v2); }
static inline vepi16 clip(vepi16 vector, int l1q) { return _mm512_min_epi16(_mm512_max_epi16(vector, zero_epi16()), load_epi16_broadcast(l1q)); }
static inline int reduce_add_epi32(vepi32 v) { return _mm512_reduce_add_epi32(v); }

#elif defined(USE_AVX2)
typedef __m256i vepi16;
typedef __m256i vepi32;

static inline vepi16 zero_epi16(void) { return _mm256_setzero_si256(); }
static inline vepi32 zero_epi32(void) { return _mm256_setzero_si256(); }
static inline vepi16 load_epi16(const int16_t *memory_address) { return _mm256_load_si256((const __m256i *)memory_address); }
static inline vepi32 load_epi32(const int32_t *memory_address) { return _mm256_load_si256((const __m256i *)memory_address); }
static inline vepi16 load_epi16_broadcast(int num) { return _mm256_set1_epi16(num); }
static inline vepi32 load_epi32_broadcast(int num) { return _mm256_set1_epi32(num); }
// static inline void store_epi16(void *memory_address, vepi16 vector) { _mm256_store_si256(memory_address, vector); }
static inline vepi32 add_epi32(vepi32 v1, vepi32 v2) { return _mm256_add_epi32(v1, v2); }
static inline vepi16 multiply_epi16(vepi16 v1, vepi16 v2) { return _mm256_mullo_epi16(v1, v2); }
static inline vepi32 multiply_add_epi16(vepi16 v1, vepi16 v2) { return _mm256_madd_epi16(v1, v2); }
static inline vepi16 clip(vepi16 vector, int l1q) { return _mm256_min_epi16(_mm256_max_epi16(vector, zero_epi16()), load_epi16_broadcast(l1q)); }

static inline int reduce_add_epi32(vepi32 vector) {
    __m128i high128 = _mm256_extracti128_si256(vector, 1);
    __m128i low128 = _mm256_castsi256_si128(vector);

    __m128i sum128 = _mm_add_epi32(high128, low128);
    __m128i high64 = _mm_unpackhi_epi64(sum128, sum128);
    __m128i sum64 = _mm_add_epi32(sum128, high64);
    __m128i high32 = _mm_shuffle_epi32(sum64, _MM_SHUFFLE(2, 3, 0, 1));
    __m128i sum32 = _mm_add_epi32(sum64, high32);

    return _mm_cvtsi128_si32(sum32);
}


#endif
#endif
