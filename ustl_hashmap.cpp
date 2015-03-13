#include "ustl_hashmap.h"

#include "ustl.h"

int main() {
  ustl::cout << "Hello!\n";
  ustl::hash< uint16_t > hash;
  ustl::hash< uint32_t > hash2;
  ustl::cout << hash(1) % 4 << '\n';
  ustl::cout << hash(1) % 4 << '\n';
  ustl::cout << hash2(1337) << '\n';
  ustl::cout << hash2(1337) << '\n';
  
  ustl::unordered_map<uint16_t, uint16_t> hashMap;
  hashMap.insert({1, 2});
  hashMap.insert({1337, 987});
  ustl::cout << hashMap[1] << '\n';
  ustl::cout << hashMap[1337] << '\n';
}
