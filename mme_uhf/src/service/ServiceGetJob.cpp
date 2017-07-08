
#include "ServiceGetJob.hpp"
#include "MsgJobDetails.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>

#include "toolbox/Logger.hpp"
#include "toolbox/StringUtils.hpp"

#include "uhf/kvs/component/KeyValueStorage.hpp"
#include "uhf/job/API.hpp"
#include "uhf/job/JobManager.hpp"
#include "uhf/job/Job.hpp"

#include "mme/Query.hpp"

namespace mme
{

ServiceGetJob::ServiceGetJob() : uhf::http::component::Consumer()
{ 
}

/////////////////////////////////////////////////////////////////////

int ServiceGetJob::process(uhf::http::InvocationRequestPtr )
{
	/*
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
	uhf::kvs::component::KeyValueStoragePtr kvStorage = theJob->getStorage();
	API::Query aQuery(kvStorage);
	
	// Return a JobStatus object
	MsgJobDetails reply;
	reply.setJobId(theJob->getKey());
	
	reply.getStatus().setProgression(aQuery.getState().getProgression());
	reply.getStatus().setStatus(aQuery.getState().getStatus());
	
	reply.getResult().setImage(aQuery.getOutput());
		
	reply.toJson(response);*/
    return 0;
}

}
