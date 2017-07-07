#pragma once

#include "toolbox/Types.hpp"
#include "opencv2/highgui/highgui.hpp"


namespace Grayscale
{
	typedef U8 Value;
	
	static const Value Black = 0;
	static const Value Gray  = 128;	
	static const Value White = 255;
}

namespace Color
{
	typedef cv::Scalar Value;
	
	static const Value Black( 0, 0, 0 );
	static const Value White( 255, 255, 255 );	
	static const Value Blue( 255, 0, 0 );
	static const Value Green( 0, 255, 0 );
	static const Value Red( 0, 0, 255 );
}
