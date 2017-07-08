#pragma once

#include "uhf/http/InvocationRequest.hpp"
#include "uhf/http/component/Consumer.hpp"
#include <set>

using std::string;
using std::set;

namespace mme 
{

class ServiceCreateJob : public uhf::http::component::Consumer
{   
public:

    ServiceCreateJob();
    
    int process(uhf::http::InvocationRequestPtr query) override;

};

}

//WTF_SERVICE_REGISTRATION( ServiceCreateJob )
