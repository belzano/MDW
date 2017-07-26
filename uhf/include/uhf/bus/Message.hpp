
#include "toolbox/Logger.hpp"
#include "toolbox/Types.hpp"
#include "toolbox/Base64.hpp"

namespace uhf {
namespace bus {

	template <class T>
	class Message {
		
	public:
		Message(T payload)
			: _payload(paylod)
		{}

		std::shared_ptr<T> get() 
		{
			return _payload;
		}

	private:
		std::shared_ptr<T> _payload;
	};

	template <class T>
	typedef std::shared_ptr<Message<T>> MessagePtr;

}
}
