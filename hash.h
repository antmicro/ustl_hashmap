#pragma once

#include "hash_functions.h"

//#include "ofstream.h"

#include <unistd.h>

namespace ustl {
  template<typename T>
  struct hash {
	typedef T 	argument_type;
        typedef size_t 	result_type;
	typedef argument_type*	hash_type;

	result_type operator()(argument_type value) const {
	  return Murmur264((uint8_t*)&value, sizeof(hash_type), 9901);
	}
  };


  template<>
  struct hash<uint16_t> {
	typedef uint16_t argument_type;
        typedef size_t result_type;

	result_type operator()(argument_type value) const {
	  const void* value_address = &value;
	  const uint8_t* data = static_cast<const uint8_t*>(value_address);
	  uint64_t hash = Murmur264(data, sizeof(argument_type), 9901);
// 	  cout << value << ' ' << hash << '\n';
// 	  for(size_t i = 0; i < sizeof(argument_type); ++i) cout << (int)data[i] << '\n';
	  return hash;
	}
  };
}
