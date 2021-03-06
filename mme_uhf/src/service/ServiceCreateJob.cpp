#include "ServiceCreateJob.hpp"
#include "MsgJobDetails.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>

#include "toolbox/Logger.hpp"
#include "toolbox/StringUtils.hpp"

#include "uhf/job/API.hpp"
#include "uhf/job/JobManager.hpp"
#include "uhf/job/Job.hpp"

#include "mme/Query.hpp"

namespace mme
{

ServiceCreateJob::ServiceCreateJob() : uhf::http::component::Consumer()
{ 
}

///////////////////////////////////////////////////////////////////

int ServiceCreateJob::process(uhf::http::InvocationRequestPtr)
{
	/*
	MDW_LOG_DEBUG("CreateJob invocation:" << url << " " << urlargs.size() << " " << postargs.size());
	
	toolbox::DataPtr inputFile;
	
	// Check input file provided
	std::map<std::string, toolbox::DataPtr>::const_iterator inputParamIt;
	inputParamIt = postargs.find("input");
	if (inputParamIt == postargs.end())
	{
		response = toolbox::MakeDataPtr("No file to process.");
		return true;
	}
	inputFile = inputParamIt->second;
	
	// Get a JobManager and create a Job Id
	job::JobManager jobmgr = job::init();
	job::Job theJob = jobmgr.create();
	
	//Create the query and set the input image etc
	uhf::kvs::component::KeyValueStoragePtr kvStorage = theJob.getStorage();
	API::Query aQuery(kvStorage);
	aQuery.setInput(inputFile);
	
	aQuery.getRequestor().setHwId("undef");
	aQuery.getRequestor().setHwNativeResolution("undef");
	aQuery.getRequestor().setOsName("undef");
	aQuery.getRequestor().setOsVersion("undef");
	aQuery.getRequestor().setClientSwVersion("undef");
	aQuery.getRequestor().setClientSw("webclient");
	
	aQuery.getInputDetails().setName("undef");
	aQuery.getInputDetails().setResolution("undef");
	
	aQuery.getEvents().setQueueingTimestamp("undef");
	//aQuery.getEvents()->setTriggerTimestamp, "undef");
	//aQuery.getEvents()->setCompletionTimestamp("undef");

	aQuery.getState().setStatus("Queued");
	aQuery.getState().setProgression("0");	 
	
	/////////////////////////////////////
	// Post the the JobId for process
	//////////////////////////////////////
	jobmgr.queue(theJob);
	
	
	
	// TODO send redirect (code 301) to ServiceGetJob
	// Return a JobStatus object
	MsgJobDetails reply;
	reply.setJobId(theJob.getKey());
	
	reply.getStatus().setProgression(aQuery.getState().getProgression());
	reply.getStatus().setStatus(aQuery.getState().getStatus());
	
	reply.getResult().setImage(aQuery.getOutput());
		
	reply.toJson(response);
	* */
    return 0;
}

}

