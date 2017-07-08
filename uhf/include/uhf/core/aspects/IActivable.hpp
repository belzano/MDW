#pragma once

#include "toolbox/Types.hpp"

namespace uhf {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class IActivable
    {
    public:
		IActivable();
		virtual ~IActivable();

		void activate();
		void passivate();
		bool isActive() { return m_isActive; }
		
	protected:		
		virtual void onActivate() = 0;
		virtual void onPassivate() = 0;

	private:
		bool m_isActive;
		
    };

    typedef std::shared_ptr<IActivable> IActivablePtr;
	
}
}
