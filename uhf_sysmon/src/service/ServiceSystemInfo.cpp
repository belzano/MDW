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
#include "ServiceSystemInfo.hpp"

#include "toolbox/StringUtils.hpp"

using namespace std;

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

ServiceSystemInfo::ServiceSystemInfo() : uhf::http::component::Consumer()
{
    //string sysinfoparams[] = {"cpus", "memory", "os"}; 
	//_serviceParams = set<string>(sysinfoparams, sysinfoparams + 3);
}

//////////////////////////////////////////////////////////////////////

int ServiceSystemInfo::process(uhf::http::InvocationRequestPtr request)
{
	/*
    const char *commandcpu = "cat /proc/cpuinfo |  sed 's/\\s\\+: /:/g'";
    const char *commandmemory = "cat /proc/meminfo |  sed 's/:\\s\\+/:/g'";
    const char *commandos = "uname -a";
    FILE *fp;
    char commandout[1048];
    string line;
    ptree sysinforoot ;
    ptree sysinfo;
    ptree::iterator  ptit = sysinforoot.push_back(make_pair("sysinfo", sysinfo ));

    while (args.empty() || args.find("cpus") != args.end()) 
    {
        fp = popen(commandcpu, "r");
        if (!fp)
            break;
        ptree temp;
        string field;
        string value;
        size_t index;
        ptree::iterator pit;
        while (fgets(commandout, 1048, fp) != 0)
        {
            line = commandout;
            toolbox::eraseAllChars(line, ")( \r\n\t");
            if (strncasecmp(line.c_str(),"processor:", 10) == 0) {
                pit = ptit->second.push_back(make_pair("cpus", temp));
            }
            index = line.find(":");
            if (string::npos == index)
                continue;
            field = line.substr(0, index);
            value = line.substr(index + 1);
            pit->second.push_back(make_pair(field, value));
        }
        fclose(fp);
        break;
    }
    
    while (args.empty()  ||  args.find("memory") != args.end())
     {
        fp = popen(commandmemory, "r");
        if (!fp)
            break;
        ptree temp;
        string field;
        string value;
        size_t index;
        ptree::iterator pit = ptit->second.push_back(make_pair("memory", temp));
        while (fgets(commandout, 1048, fp) != 0)
        {
            line = commandout;
            toolbox::eraseAllChars(line, ")( \n\r\t");
            index = line.find(":");
            if (string::npos == index)
                continue;
            field = line.substr(0, index );
            value = line.substr(index + 1);
            pit->second.push_back(make_pair(field, value));
        }
        fclose(fp);
        break;
    }
    while (args.empty() || args.find("os") != args.end()) {
        fp = popen(commandos, "r");
        if (!fp)
            break;
        if (fgets(commandout, 1048, fp) == 0) {
            fclose(fp);
            break;
        }
        line = commandout;
        ptree temp;
        string field;
        string value;
        //size_t index;
        ptree::iterator pit = ptit->second.push_back(make_pair("os", temp));
        pit->second.push_back(make_pair("osdetails", line));
        fclose(fp);
        break;
    }

    //_generateOutput(&sysinforoot, type, response);
    */
    MsgSimpleString contentWrapper;
    contentWrapper.setContent("NA for the moment...");
	contentWrapper.toJson(request->answerstring);
    return 0;
}

//////////////////////////////////////////////////////////////////////

}
}
}

