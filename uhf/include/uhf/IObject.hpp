#pragma once

#include <memory>

namespace  uhf {
      
    class IObject
    {
    public:
		IObject();
		virtual ~IObject();
    };

    typedef std::shared_ptr<IObject> IObjectPtr;
}
