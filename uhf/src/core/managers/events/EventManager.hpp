#pragma once

#include <memory>
#include <set>

//
// Framework base
////////////////////////////////////////
	
template <class EventType>
class EventListener
{
	public:
		virtual void OnEventReceived(const EventType& event) = 0;
};

////////////////////////////////////////

template <class EventRegistry>
class EventManager
{
	public:
		template<class EventType>
		void triggerEvent(const EventType& event)
		{
			std::set< std::shared_ptr<EventListener<EventType>> >* listeners = nullptr;
			_eventsRegistry.getListeners(listeners);
			typename std::set< std::shared_ptr<EventListener<EventType>> >::iterator listenerIt;
			for(listenerIt  = listeners->begin();
				listenerIt != listeners->end();
				++listenerIt)
			{
				(*listenerIt)->OnEventReceived(event);
			}
		}
		
		template<class EventType>
		void registerListener(std::shared_ptr<EventListener<EventType>> listener)
		{
			std::set< std::shared_ptr<EventListener<EventType>> >* listeners = nullptr;
			_eventsRegistry.getListeners(listeners);				
			listeners->insert(listener); 
		}
		
		template<class EventType>
		void deregisterListener(std::shared_ptr<EventListener<EventType>> listener)
		{
			std::set< std::shared_ptr<EventListener<EventType>> >* listeners = nullptr;
			_eventsRegistry.getListeners(listeners);				
			listeners->remove(listener);
		}
					
	protected:
		EventRegistry _eventsRegistry;
};


//
// Logger implementation

namespace logger
{	
	
	class ConfigurationUpdatedEvent 
	{
		
	};
	
	///////////////////////////////////////

#define REGISTER_EVENT(eventType)													\
std::set< std::shared_ptr<EventListener<eventType>> > m_Listeners##eventType ;		\
void getListeners(std::set< std::shared_ptr<EventListener<eventType>> >*& listeners)\
{ listeners = & m_Listeners##eventType ; }

	class EventListenerRegistry
	{
		public:
			REGISTER_EVENT(ConfigurationUpdatedEvent)
	};
	
	///////////////////////////////////////
	
	class EventManager : public ::EventManager<EventListenerRegistry>
	{
		public:
			static EventManager& Instance();
	};
	
}
