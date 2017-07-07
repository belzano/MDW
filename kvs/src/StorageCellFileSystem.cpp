
#include "toolbox/StorageCellFileSystem.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "toolbox/Logger.hpp"

namespace toolbox
{

/////////////////////////////////////////////////////////////////////

StorageCellFileSystem::StorageCellFileSystem(const std::string& rootPath)
{
	_rootPath = rootPath;
}

/////////////////////////////////////////////////////////////////////

bool StorageCellFileSystem::dataExists(const DataKey & hashkey)
{
	std::ifstream file(_rootPath + hashkey);
	
	return (file.is_open());
}

/////////////////////////////////////////////////////////////////////

bool StorageCellFileSystem::dataSet(const DataKey & hashkey, DataPtr data)
{
	//MDW_LOG_DEBUG("Writing data file" << _rootPath << hashkey << " ("<< data->size() <<")");
	
	boost::filesystem::path directory(_rootPath);
	
	if (! boost::filesystem::exists(directory) )
		boost::filesystem::create_directory(directory);
    
    boost::filesystem::path filepath = directory / hashkey;
	std::ofstream file(filepath.string());
	file.write(data->data(), data->size()); 
	return true;
}     

/////////////////////////////////////////////////////////////////////

DataPtr StorageCellFileSystem::dataGet(const DataKey & hashkey)
{
	//MDW_LOG_DEBUG("Reading data file" << _rootPath << hashkey << " ");
	
	std::ifstream file(_rootPath + hashkey);
	
	// if no file
	if (! file.is_open())
		return DataPtr((Data*)NULL);
	
	file >> std::noskipws;
	DataPtr data(new Data());
	std::copy(  std::istream_iterator<char>(file), 
				std::istream_iterator<char>(), 
				std::back_inserter(* data.get()));

	return data;
 }

///////////////////////////////////////////////////////////////////// 
/*
bool StorageCellFileSystem::propertySet(const PropertyGroup& iGroup, const PropertyKey & iKey, const PropertyValue& iVal)
{
	//MDW_LOG_DEBUG("Writing property file" << _rootPath << "" << iKey << " :"<< iVal <<" ");
	
	boost::filesystem::path directory(_rootPath);
	
	if (! boost::filesystem::exists(directory) )
		boost::filesystem::create_directory(directory);
    
    directory /= iGroup;
	if (! boost::filesystem::exists(directory) )
		boost::filesystem::create_directory(directory);
		
    boost::filesystem::path filepath = directory / iKey;
	std::ofstream file(filepath.string());
	file << iVal;
	
	return true;
}

/////////////////////////////////////////////////////////////////////

bool StorageCellFileSystem::propertyGet(const PropertyGroup& iGroup, const PropertyKey & iKey, PropertyValue& iVal)
{
	boost::filesystem::path filename = _rootPath;
	filename /= iGroup;
	filename /= iKey;
	
	std::ifstream file(filename.string());
	
	// if no file
	if (! file.is_open())
		return false;
	
	file >> std::noskipws;
	
	iVal.clear();
	std::copy(  std::istream_iterator<char>(file), 
				std::istream_iterator<char>(), 
				std::back_inserter(iVal));

	return true;
}
*/
/////////////////////////////////////////////////////////////////////
        
}
