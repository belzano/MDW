#include "ShapeHandlerRegistry.hpp"


#include "ShapeLine.hpp"
#include "ShapeArrow.hpp"
#include "ShapeCross.hpp"

#include "ShapeText.hpp"
#include "ShapeArc.hpp"

#include "ShapeCircle.hpp"
#include "ShapeEllipse.hpp"

#include "ShapeRectangle.hpp"


//////////////////////////////////////////////////////////////////////

ShapeHandlerRegistry* 		ShapeHandlerRegistry::instance 			= new ShapeHandlerRegistry();	
ClosedShapeHandlerRegistry* ClosedShapeHandlerRegistry::instance 	= new ClosedShapeHandlerRegistry();	

/////////////////////////////////////////////////////////////////////

void ShapeHandlerRegistryBase::registerHandler( std::shared_ptr<const ShapeHandler> iHandler)
{
	push_back(iHandler);
}

/////////////////////////////////////////////////////////////////////

ClosedShapeHandlerRegistry::ClosedShapeHandlerRegistry() 
{
	// register handlers for each shape	
	registerHandler(std::shared_ptr<const ShapeHandler>( new ShapeCircleHandler() ) );
	registerHandler(std::shared_ptr<const ShapeHandler>( new ShapeEllipseHandler() ) );
	registerHandler(std::shared_ptr<const ShapeHandler>( new ShapeRectangleHandler() ) );
}
	
//////////////////////////////////////////////////////////////////

ShapeHandlerRegistry::ShapeHandlerRegistry() 
{
	// register handlers for each shape
	
	registerHandler(std::shared_ptr<const ShapeHandler>( new ShapeLineHandler() ) );
	registerHandler(std::shared_ptr<const ShapeHandler>( new ShapeArrowHandler() ) );
//	registerHandler(std::shared_ptr<const ShapeHandler>( new ShapeCrossHandler() ) );

//	registerHandler(std::shared_ptr<const ShapeHandler>( new ShapeTextHandler() ) );	
	
	registerHandler(std::shared_ptr<const ShapeHandler>( new ShapeCircleHandler() ) );
	registerHandler(std::shared_ptr<const ShapeHandler>( new ShapeEllipseHandler() ) );
	
	registerHandler(std::shared_ptr<const ShapeHandler>( new ShapeRectangleHandler() ) );
}
	
//////////////////////////////////////////////////////////////////



