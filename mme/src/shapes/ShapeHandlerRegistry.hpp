#pragma once

#include <memory>
#include <list>

#include "ShapeHandler.hpp"

class Parameters;
class ConnectedSet;

//////////////////////////////////////////////////////////////////////

typedef std::list< std::shared_ptr<const ShapeHandler> >  ShapeHandlerSet;

//////////////////////////////////////////////////////////////////////

class ShapeHandlerRegistryBase : public ShapeHandlerSet
{
	public:	 	
	 	void registerHandler( std::shared_ptr<const ShapeHandler>  );
};

//////////////////////////////////////////////////////////////////////

class ShapeHandlerRegistry : public ShapeHandlerRegistryBase
{
	public:		
		ShapeHandlerRegistry();
 	
		static ShapeHandlerRegistry* instance;
};

//////////////////////////////////////////////////////////////////

class ClosedShapeHandlerRegistry : public ShapeHandlerRegistryBase
{
	public:
		ClosedShapeHandlerRegistry();
		
		static ClosedShapeHandlerRegistry* instance;	
};

//////////////////////////////////////////////////////////////////

