#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>

#include <stdint.h>
#include <boost/regex.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "MsgSimpleString.hpp"
#include "ServiceProcInfo.hpp"

using std::vector;
using boost::property_tree::ptree;
using std::make_pair;
using boost::lexical_cast;
using boost::bad_lexical_cast;
using boost::format;
using boost::regex_search;
using boost::match_default;
using boost::match_results;
using boost::regex;

namespace uhf {
namespace sysmon {
namespace component {
	
//////////////////////////////////////////////////////////////////////

ServiceProcInfo::ServiceProcInfo() : uhf::http::component::Consumer()
{
    //string processinfoparams[] = {"percentmemory", "percentcpu" }; 
	//_serviceParams = set<string>(processinfoparams, processinfoparams + 2);
}

//////////////////////////////////////////////////////////////////////

int ServiceProcInfo::process(uhf::http::InvocationRequestPtr request)
{
	/*
    const char *command = "ps auxef | tail -n +2 |awk ' { printf \"%s %s %s %s \", $1, $2, $3, $3 ; for (i = 11; i <= NF; i++) {printf \"%s \", $i }  print \"\" }  ' ";
    char line[8096];
    FILE *fp = popen(command, "r");

    if (!fp) {
        return false;
    }

    string read_line;
    ptree prcinforoot ;
    ptree prcinfo;
    string::const_iterator start, end;
    match_results<string::const_iterator > what;
    ptree::iterator  ptit = prcinforoot.push_back(make_pair("prcinfo", prcinfo ));
    ptree::iterator pit;
    regex expression("(.*?) (.*?) (.*?) (.*?) (.*)");  
    ptree temp;
    bool percentcpu = false;
    bool percentmemory = false; 

    if (args.find("percentcpu") != args.end()) {
        percentcpu = true;
    }
    if (args.find("percentmemory") != args.end()) {
        percentmemory = true;
    }

    while (fgets(line, 8096, fp) != 0){
        read_line = line;
        start = read_line.begin();
        end = read_line.end();
        if (!regex_search(start, end, what, expression, match_default)){
            continue;
        }
        if (what.size() != 6){
            continue;
        }   
        pit = ptit->second.push_back(make_pair("process", temp));
        pit->second.push_back(make_pair("owner", string(what[1].first, what[1].second)));
        pit->second.push_back(make_pair("processid", string(what[2].first, what[2].second)));
        if (percentcpu)
            pit->second.push_back(make_pair("percentcpu", string(what[3].first, what[3].second)));
        if (percentmemory)
            pit->second.push_back(make_pair("percentmemory", string(what[4].first, what[4].second)));
        pit->second.push_back(make_pair("processcommand", string(what[5].first, what[5].second)));
    }
    fclose(fp);   
    */ 
    //_generateOutput(&prcinforoot, type, response);
    //std::cout << response << std::endl;
    MsgSimpleString contentWrapper;
    contentWrapper.setContent("NA for the moment...");
	contentWrapper.toJson(request->answerstring);
	
    return 0;
}

//////////////////////////////////////////////////////////////////////

}
}
}
