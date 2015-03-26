#pragma once

typedef uint64_t u64;
typedef uint8_t u8;

#ifdef __SIZEOF_INT128__
__extension__ typedef unsigned __int128 u128;

inline u64 CrapWow64( const u8 *key, u64 len, u64 seed ) {
  const u64 m = 0x95b47aa3355ba1a1, n = 0x8a970be7488fda55;
  #define cwfold( a, b, lo, hi ) { p = (u64)(a) * (u128)(b); lo ^= (u64)p; hi ^= (u64)(p >> 64); }
  #define cwmixa( in ) { cwfold( in, m, k, h ); }
  #define cwmixb( in ) { cwfold( in, n, h, k ); }

  const u64 *key8 = (const u64 *)key;
  u64 h = len, k = len + seed + n;
  u128 p;

  while ( len >= 16 ) { cwmixb(key8[0]) cwmixa(key8[1]) key8 += 2; len -= 16; }
  if ( len >= 8 ) { cwmixb(key8[0]) key8 += 1; len -= 8; }
  if ( len ) { cwmixa( key8[0] & ( ( (u64)1 << ( len * 8 ) ) - 1 ) ) }
  cwmixb( h ^ (k + n) )
  return k ^ h;
}
#endif

inline u64 Murmur264( const u8 *key, u64 len, u64 seed ) {
  const u64 m = 0xc6a4a7935bd1e995;
  const u8 r = 47;
  u64 h = len + seed;

  for ( ; len >= 8; len -= 8, key += 8 ) {
          u64 k = *(u64 *)key * m;
          k ^= k >> r; 
          k *= m;
          h = ( h * m ) ^ k;
  }

  switch ( len & 7 ) {
          case 7: h ^= u64(key[6]) << 48;
          case 6: h ^= u64(key[5]) << 40;
          case 5: h ^= u64(key[4]) << 32;
          case 4: h ^= u64(key[3]) << 24;
          case 3: h ^= u64(key[2]) << 16;
          case 2: h ^= u64(key[1]) << 8;
          case 1: h ^= u64(key[0]);
          h *= m;
  }

  h ^= h >> r;
  h *= m;
  h ^= h >> r;
  return h;
}
