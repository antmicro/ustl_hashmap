#include "ustl_hashmap.h"

#include "ustl.h"

typedef ustl::unordered_map<uint16_t, uint16_t> Map;
typedef Map::size_type size_type;

void test_full_capacity()
{
  Map map;
  for(size_type i = 0; i < map.capacity(); ++i)
  {
    ustl::cout << "Adding: " << i << '\n';
    map.insert({i, i});
  }
  for(size_type i = 0; i < map.capacity(); ++i)
  {
    ustl::cout << map[i] << '\n';
  }
}

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
  ustl::cout << "Capacity: " << hashMap.capacity() << "\n";
  test_full_capacity();
}
