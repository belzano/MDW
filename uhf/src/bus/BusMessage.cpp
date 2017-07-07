#include "uhf/bus/BusMessage.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"

#include <sstream>
#include <vector>
#include <iterator>


////////////////////////////////////////////////////////////

namespace WTF
{
	toolbox::DataPtr BusMessage::toBinaryStream() const
	{
		toolbox::DataPtr theData(new toolbox::Data);
		
		// push type size
		U64 size = m_type.size();
		char* memptr = (char*) & size;
		theData->push_back(memptr[0]);
		theData->push_back(memptr[1]);
		theData->push_back(memptr[2]);
		theData->push_back(memptr[3]);
		// push type
		theData->insert(theData->end(), m_type.begin(), m_type.end());
		
		// custom type if any
		serializeCustom(theData);
		
		return theData;
	}
	
	void BusMessage::fromBinaryStream(toolbox::DataPtr iData)
	{
		U64 size = 0;
		char* memptr = (char*) & size;
		memptr[0] = iData->at(0);
		memptr[1] = iData->at(1);
		memptr[2] = iData->at(2);
		memptr[3] = iData->at(3);
		
		m_type.insert(m_type.begin(), iData->begin()+4, iData->begin()+4+size);

		// Yes, there's a copy...
		toolbox::Data customPart(iData->begin() + 4 + size + 1, iData->end());
		deserializeCustom(customPart);
	}
}
