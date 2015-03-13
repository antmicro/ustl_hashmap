#pragma once

#include "memblock.h"
#include "umultimap.h"
#include "hash.h"

namespace ustl {
  template<
      class Key,
      class T,
      class Hash = hash<Key>,
      class KeyEqual = equal_to<Key>
  > 
  class unordered_map {
  public:
    typedef Key 	key_type;
    typedef T 		mapped_type;
    typedef KeyEqual	key_comparer;
    typedef pair<const Key, T>		value_type;
    typedef memblock::size_type		size_type;
    typedef memblock::difference_type	difference_type;
    typedef value_type&		reference;
    typedef const value_type&	const_reference;
    typedef const key_type&	const_key_ref;
    typedef value_type*		pointer;
    typedef const value_type*	const_pointer;
    typedef pointer		iterator;
    typedef const_pointer	const_iterator;
    typedef ::ustl::reverse_iterator<iterator>	reverse_iterator;
    typedef ::ustl::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef pair<iterator,bool>	insertrv_t;
    typedef const unordered_map<Key, T, Hash, KeyEqual>&	crself_t;
  public:
    unordered_map();
    unordered_map(size_type bucket_count);
    inline mapped_type&		operator[] (const_key_ref key);
    //inline const_reference 	operator[] (const_key_ref key) const;
    insertrv_t			insert (const_reference v);
    inline const_iterator	find (const_key_ref k) const;
    inline iterator		find (const_key_ref k)	{ return const_cast<iterator> (const_cast<crself_t>(*this).find (k)); }
    inline iterator		begin ()	{ assert(false); /* "Iterating over unordered_map is not implemented." */ };
    inline const_iterator	end () const	{ return (const_iterator)_buckets.end(); };
    inline iterator		end () 		{ return const_cast<iterator> (const_cast<crself_t>(*this).end ()); };
    inline size_type		bucket_count() const 	{ return _buckets.size(); };
  protected:
    typedef vector<value_type>	bucket_type;
    typedef size_type		bucket_key;
    typedef vector<bucket_type>	bucket_container;
    typedef typename bucket_container::iterator		bucket_iterator;
    typedef typename bucket_container::const_iterator	bucket_const_itr;
  protected:
    inline size_type bucket(const_key_ref key) const 	{ return _hash(key) % bucket_count(); };


  private:
    bucket_container _buckets;
    Hash _hash;
    key_comparer _key_comparer;
  };

  template<class Key, class T, class Hash, class KeyEqual>
  unordered_map<Key, T, Hash, KeyEqual>::unordered_map() : unordered_map(4)
  {    
  }

  template<class Key, class T, class Hash, class KeyEqual>
  unordered_map<Key, T, Hash, KeyEqual>::unordered_map(size_type bucket_count) : _buckets(bucket_count), _hash(), _key_comparer()
  {    
  }
  
  template<class Key, class T, class Hash, class KeyEqual>
  typename unordered_map<Key, T, Hash, KeyEqual>::const_iterator unordered_map<Key, T, Hash, KeyEqual>::find(const_key_ref key) const
  {
    const bucket_key& bucket_idx = bucket(key);
    const bucket_type& _bucket = _buckets[bucket_idx];
    for(size_type i = 0; i < _bucket.size(); ++i) {
      if( _key_comparer(key, _bucket[i].first) ) return _bucket.iat(i);
    }
    const_iterator _end = end();
    return _end;
  }
  
  template<class Key, class T, class Hash, class KeyEqual>
  typename unordered_map<Key, T, Hash, KeyEqual>::mapped_type& unordered_map<Key, T, Hash, KeyEqual>::operator[](const_key_ref key)
  {
    //TODO: make c++11 compilant version with emplace
    return (insert( make_pair( key, T() ) ).first)->second;
  }
  
  template<class Key, class T, class Hash, class KeyEqual>
  typename unordered_map<Key, T, Hash, KeyEqual>::insertrv_t unordered_map<Key, T, Hash, KeyEqual>::insert(const_reference v)
  {
    iterator element_itr = find(v.first);
    iterator _end = end();
    bool inserted = (element_itr == _end);
    if(inserted){
      _buckets[bucket(v.first)].push_back(v);
      element_itr = _buckets[bucket(v.first)].end()-1;
    }
    return make_pair(element_itr, inserted);
  }
}
