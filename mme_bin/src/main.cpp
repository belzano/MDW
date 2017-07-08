
#include <vector>
#include <dirent.h>
#include <iostream>
#include <fstream>

#include "toolbox/Macros.hpp"

#include "toolbox/ExecutionContext.hpp"
#include "toolbox/StringUtils.hpp"
#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"

#include "uhf/kvs/component/KeyValueStorage.hpp"
//#include "toolbox/StorageCellLocalMemory.hpp"
//#include "toolbox/StorageCellFileSystem.hpp"


#include "mme/Query.hpp"


using namespace std;

/////////////////////////////////////////////////////////////////////
	
int listFiles(const std::string& iDir, std::vector<std::string>& ioFiles)	
{
	DIR *dpdf;
	struct dirent *epdf;

	dpdf = opendir(iDir.c_str());
	if (dpdf != NULL)
	{
		;
		while ( (epdf=readdir(dpdf)) )
		{
			// Skip . .. and hidden files
			if (epdf->d_name[0] == '.')
				continue;
				
			ioFiles.push_back(iDir + epdf->d_name);
//			std::cout << "\t" << epdf->d_name << std::endl;
		}
	}
	
	return ioFiles.size();
}

/////////////////////////////////////////////////////////////////////

int main (int argc, char* argv[])
{
	std::vector<std::string> files;	
	if (argc > 1)
	{
		for(int i = 1; i < argc; ++i)
			files.push_back(argv[i]);
	}
	else
	{
		// List files
		MDW_LOG_INFO("Looking for files to process");
		std::string inputDir = toolbox::ExecutionContext::instance().getDirDataTestIn();
		listFiles(inputDir, files);
		if (files.empty())
		{
			MDW_LOG_INFO("No file to process: exiting");
			exit(0);
		}
	}
		
	// Process files
	for (uint i = 0; i < files.size(); ++i)	
	{
		MDW_LOG_INFO("About to process " << files[i]);
		toolbox::ScopedChrono aProcessChrono("Processing overall");
		
		std::string filenamebase = toolbox::split(files[i], '/').back();
		std::string filenamenoext = toolbox::split(filenamebase, '/')[0];
		
		// Create a query with memory storage in release mode (for perf debug)
		uhf::kvs::component::KeyValueStoragePtr testStorage;
#ifdef MDW_DEBUG
		//std::string dataRootPath = toolbox::ExecutionContext::instance().getDirData() + "/" + filenamenoext +"/";
		//testStorage = toolbox::StorageCellPtr( (toolbox::StorageCell*) new toolbox::StorageCellFileSystem(dataRootPath) );
#else
		//testStorage = toolbox::StorageCellPtr( (toolbox::StorageCell*) new toolbox::StorageCellLocalMemory() );
#endif
		
		API::Query aQuery(testStorage);
		
		// Set input data from file name
		aQuery.setInput(files[i]);

		// Process query
		aQuery.process();

		// Release mode: cellStorage is a volatile instance, and we d like to check the result 
#ifndef MDW_DEBUG		

		// Get output
		toolbox::DataPtr result = aQuery.getOutput( toolbox::Image::svg,
													toolbox::Image::sameAsInput );
		
		// get output data to file
		std::string outFileName = toolbox::ExecutionContext::instance().getDirData();
		outFileName += "result_" + filenamenoext + ".svg";
		
		std::ofstream FILE(outFileName, ios::out | std::ofstream::binary);
		std::copy(  result->begin(), 
					result->end(), 
					ostreambuf_iterator<char>(FILE));
		FILE.close();
#endif

	}
}


