#pragma once

#include <string>
#include <list>
#include <memory>

namespace toolbox
{
	/////////////////////////////////////////////////////////////////////
	
	template<class TEventArgs>
	class EventHandler
	{
		public:
			virtual void operator()(void*, TEventArgs& ) = 0;
	};

	// TODO handler should be a weak pointer
	template<class TEventArgs, class THandlerType>
	class EventHandlerMemberFunction: public EventHandler<TEventArgs>
	{	
		public:
			typedef  void (THandlerType::*handlerCallback)(void* sender, TEventArgs& eventArgs);
		
			EventHandlerMemberFunction(THandlerType* handler, handlerCallback callback)
			: m_handler(handler)
			, m_callback(callback)
			{}
			
			void operator()(void* sender, TEventArgs& eventArgs) override
			{
				((*m_handler).*(m_callback))(sender, eventArgs);
			}
			
			THandlerType* m_handler;
			handlerCallback m_callback;
	};	
	
	template<class TEventArgs>
	class EventHandlerFreeFunction: public EventHandler<TEventArgs>
	{	
		public:
			typedef  void (*handlerCallback)(void* sender, TEventArgs& eventArgs);
		
			EventHandlerFreeFunction(handlerCallback callback)
			: m_callback(callback)
			{}
			
			void operator()(void* sender, TEventArgs& eventArgs) override
			{
				(*m_callback)(sender, eventArgs);
			}
			
			handlerCallback m_callback;
	};

	/////////////////////////////////////////////////////////////////////
	
	template<class TEventArgs>
	class Event
	{
		typedef std::list< EventHandler<TEventArgs>* > EventHandlers;
		
		public:
			// TODO forbid copy operator
			// TODO const eventArgs
		
			void operator()(void* sender, TEventArgs& args)
			{
				for(auto iter : m_eventHandlers)
				{
					(*iter)(sender, args);
				}
			}
			
			template<class THandlerType>
			void subscribeMemberFunction(THandlerType* handler, void (THandlerType::*cbk)(void*, TEventArgs&) )
			{
				//EventHandlers::iterator iter = std::find(m_callbacks.begin(), m_callbacks.end(), cbk);
				//if( iter == m_callbacks.end())
				EventHandler<TEventArgs>* evtHandler = new EventHandlerMemberFunction<TEventArgs, THandlerType>(handler, cbk);
				m_eventHandlers.push_back(evtHandler);
			}
			
			void subscribeFreeFunction(void (*cbk)(void*, TEventArgs&) )
			{
				//EventHandlers::iterator iter = std::find(m_callbacks.begin(), m_callbacks.end(), cbk);
				//if( iter == m_callbacks.end())
				EventHandler<TEventArgs>* evtHandler = new EventHandlerFreeFunction<TEventArgs>(cbk);
				m_eventHandlers.push_back(evtHandler);
			}
			
			template<class THandlerType>
			void unSubscribe(THandlerType* handler, void (THandlerType::*cbk)(void*, TEventArgs&) )
			{
				EventHandler<TEventArgs>* evtHandler = new EventHandlerMemberFunction<TEventArgs, THandlerType>(handler, cbk);
				typename EventHandlers::iterator iter = std::find(m_eventHandlers.begin(), m_eventHandlers.end(), evtHandler);
				if(m_eventHandlers.end() == iter)
					return;
				m_eventHandlers.erase(iter);	
			}
			
		private:
			EventHandlers m_eventHandlers;
	};

}



	




