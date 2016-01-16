#pragma once

#include <string>
#include "toolbox/Types.hpp"

namespace uhf {	

template<class V, class K=std::string>
class IKeyValueStorage
{
public:
  constexpr static const char* TypeName = "uhf::resource::IKeyValueStorage" + V::TypeName;
  
  virtual bool hasKey(const K& key) = 0;
  virtual bool set(const K& key, const T& value, U64 revision) = 0;
  virtual bool get(const K& key, T& value, U64& revision) = 0;
};

template <class V, class K=std::string>
typedef std::shared_ptr< IKeyValueStorage<V, K> > IKeyValueStoragePtr;

}
