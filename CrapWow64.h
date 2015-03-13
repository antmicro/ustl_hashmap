#pragma once

typedef uint64_t u64;
typedef uint8_t u8;
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