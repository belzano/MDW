#include "CmdSerializeShapeSvg.hpp"

#include "QueryContext.hpp"
#include <iterator>

using namespace std;

////////////////////////////////////////////////////////////////////

//#define MMN_XML_TAG

void CmdSerializeShapeSvg::execute(QueryContext& iQueryContext, 
									std::list<std::shared_ptr<Shape> >& iShapes,
									toolbox::DataPtr ioOut )
{
	// Draw result
	CmdSerializeShapeSvg(iQueryContext.getParameters()).serialize(iShapes, ioOut);
}

////////////////////////////////////////////////////////////////////

void CmdSerializeShapeSvg::serialize( std::list<std::shared_ptr<Shape> >& iShapes,
									  toolbox::DataPtr ioData)
{
	//Logger::phase("SVG Dump");
	//Logger::cout() << " Got " << iShapes.size() 
	//				<< " shapes to draw!" << std::endl;
			
	
	int width  = _parameters._hRes;
	int height = _parameters._vRes;
	
	std::stringstream stream;
	stream >> noskipws;
	
	// svg starts
	stream << "<svg width=\""<< width <<"\" height=\""<< height <<"\" ";
	stream << "version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">";
    stream << std::endl;	 
	stream << std::endl;	  
    
    // canvas 
	//<!-- Show outline of canvas using 'rect' element -->
	//stream << "<rect width=\""<< width <<"\" height=\""<< height <<"\" ";
    //stream << "fill=\"white\" stroke=\"blue\" stroke-width=\"5\" />";
    //stream << std::endl;
    	
    stream << "<desc>Generated by Meeting Minutes Now!</desc>";
	stream << std::endl;
	stream << std::endl;
  
	// Loop on shapes and dump
	std::list<std::shared_ptr<Shape> >::const_iterator aShapeIt;
	for(aShapeIt  = iShapes.begin();
		aShapeIt != iShapes.end();
		++aShapeIt)
	{
		(*aShapeIt)->serializeAsSvg(stream, _parameters);
		stream << std::endl;
	}
  
  
  //<rect x="1000" y="1000" width="100" height="100" stroke="blue" stroke-width="5" fill="none"/>
  //<rect x="1000" y="1200" width="100" height="150" stroke="blue" stroke-width="5" fill="none"/>
  //<rect x="200" y="1500" width="200" height="200" stroke="blue" stroke-width="5" fill="none"/>
  //<rect x="1200" y="1500" width="300" height="400" stroke="blue" stroke-width="5" fill="none"/>
    
	// svg ends
	stream << "</svg>" << std::endl;	
	
	
	vector<string> V;
	std::copy(	istream_iterator<char>(stream), 
				istream_iterator<char>(), 
				back_inserter(* ioData.get()));
}
//void CmdExtractShapes::exportAsSvg(list< Shape* >& ioShapes, 
//									std::string& ioSerialized) 
//{
	//	<svg xmlns="http://www.w3.org/2000/svg" version="1.1">
	//	<rect width="300" height="100" style="fill:rgb(0,0,255);stroke-width:1;stroke:rgb(0,0,0)" />
	//	</svg>
//}