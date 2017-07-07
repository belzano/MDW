#include "ServiceGetJob.hpp"
#include "MsgJobDetails.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>

#include "toolbox/Logger.hpp"
#include "toolbox/StringUtils.hpp"

#include "job/API.hpp"
#include "job/JobManager.hpp"
#include "job/Job.hpp"

#include "mme/Query.hpp"

using namespace WTF;

ServiceGetJob::ServiceGetJob() : ServiceTemplate<ServiceGetJob>()
{ 
}

/////////////////////////////////////////////////////////////////////

bool ServiceGetJob::process(const std::string MDW_DEBUG_ONLY(url),
						 const std::map<std::string, std::string>& urlargs, 			 
						 const std::map<std::string, toolbox::DataPtr>& MDW_DEBUG_ONLY(postargs),
						 toolbox::DataPtr& response)
{
	MDW_LOG_DEBUG("ServiceGetJob invocation:"<< url << " " 	<< urlargs.size() << " " << postargs.size());
	
	// Check input file provided
	std::map<std::string, std::string>::const_iterator inputParamIt;
	inputParamIt = urlargs.find("id");
	if (inputParamIt == urlargs.end())
	{
		response = toolbox::MakeDataPtr("No jobId provided.");
		return true;
	}
	
	// Get a JobManager
	job::JobManager jobmgr = job::init();
	
	// Create a Job Id
	job::JobPtr theJob = jobmgr.get(inputParamIt->second);
	
	// TODO handle case job is null
	
	// wrap as a query to exploit
	API::Query aQuery(theJob->getStorage());
	
	// Return a JobStatus object
	MsgJobDetails reply;
	reply.setJobId(theJob->getKey());
	
	reply.getStatus().setProgression(aQuery.getState().getProgression());
	reply.getStatus().setStatus(aQuery.getState().getStatus());
	
	reply.getResult().setImage(aQuery.getOutput());
		
	reply.toJson(response);
    return true;
}

