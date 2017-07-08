#include "uhf/core/component/IActivable.hpp"
#include "toolbox/Logger.hpp"

namespace uhf {
namespace component {
		
	/////////////////////////////////////////////////////////////////////

	IActivable::IActivable()
	  : m_isActive(false)
	{
	
	}
		
	/////////////////////////////////////////////////////////////////////

	IActivable::~IActivable()
	{
		if (m_isActive) {
			MDW_LOG_WARNING("Destroying an active component ")
		}
	}	
	
	/////////////////////////////////////////////////////////////////////

	void IActivable::activate()
	{
		onActivate();
		m_isActive = true;
	}	
	
	/////////////////////////////////////////////////////////////////////

	void IActivable::passivate()
	{
		m_isActive = false;
		onPassivate();
	}	
		
}
}
