#pragma once

#include <string>
#include "toolbox/Types.hpp"
#include "toolbox/PtreeHelper.hpp"
#include "toolbox/ObjectModelHelpers.hpp"

namespace WTF
{		
	class BusMessage
	{
		public:
		
			typedef std::string Type;
		
			BusMessage(const char* iType)
				: m_type(iType) {}
		
			Type getType() const {return m_type; }
			
			toolbox::DataPtr toBinaryStream() const;
			void fromBinaryStream(toolbox::DataPtr);

			virtual void serializeCustom(toolbox::DataPtr) const {}
			virtual void deserializeCustom(toolbox::Data&) {}
			virtual void run() {}
			
		private:
			Type m_type;
	};
	
	/////////////////////////////////////////////////////////////////////
		
	template <class T>	
	class BusMessageJson : public BusMessage, toolbox::PtreeDocument<T>
	{
		public:
		virtual void serializeCustom(toolbox::DataPtr ioData) const 
		{
			toolbox::PtreeDocument<T>::toJson(ioData);	
		}
		
		virtual void deserializeCustom(toolbox::Data& iData) 
		{
			toolbox::PtreeDocument<T>::fromJson(iData);
		}

	};
	
}
