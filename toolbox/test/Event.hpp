

#include "gtest/gtest.h"

#include "toolbox/event/Event.hpp"

class TestEventArgs
{

};

static int g_eventCallCount = 0;
void onEventFreeFunction(void*, TestEventArgs&)
{
	g_eventCallCount++;
}


class ListenerObject
{
public: 
	ListenerObject()
	: m_eventCallCount(0)
	{
	}
	
	void subscribe(toolbox::Event<TestEventArgs>& event)
	{
		event.subscribeMemberFunction(this, &ListenerObject::onEvent);
	}
	
	void onEvent(void*, TestEventArgs&)
	{
		m_eventCallCount++;
	}
	
	U16 m_eventCallCount;
};


TEST(ToolboxEvent, TestFreeFunction)
{
	toolbox::Event<TestEventArgs> event;
	event.subscribeFreeFunction(onEventFreeFunction);
	
	TestEventArgs args;
	event(this, args);
	
	EXPECT_EQ(1, g_eventCallCount);
}

TEST(ToolboxEvent, TestMemberFunction)
{
	ListenerObject listener;
	toolbox::Event<TestEventArgs> event;
	listener.subscribe(event);
	
	TestEventArgs args;
	event(this, args);
	
	EXPECT_EQ(1, listener.m_eventCallCount);
}
