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
#include "ServiceDiskInfo.hpp"

#include "toolbox/StringUtils.hpp"

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

ServiceDiskInfo::ServiceDiskInfo() : uhf::http::component::Consumer()
{
    //string diskinfoparamas[] = {"totalparts", "spaceinfo" }; 
	//_serviceParams = set<string>(diskinfoparamas, diskinfoparamas + 2); 
}

//////////////////////////////////////////////////////////////////////

int ServiceDiskInfo::process(uhf::http::InvocationRequestPtr request)
{
	/*
    const char *command = "df | sed 's/ \\+/ /g'  | tail -n +2 ";
    char line[255];
    vector<string> tokens;
    int i = 0,j;
    bool spaceinfo = false;
    bool totalparts = false;
    uint64_t totalspace = 0;
    uint64_t usedspace = 0;
    int32_t partnum = 0;

    FILE *fp = popen(command, "r");
    if (!fp){
        return false;
    }
    std::string response = "";
    while (fgets(line, 255, fp) != 0){
        response += string(line);
    }
    fclose(fp);

    if (args.find("spaceinfo") != args.end()) {
        spaceinfo = true;
    }
    if (args.find("totalparts") != args.end()) {
        totalparts = true;
    }


    toolbox::split( response, " \t\n", tokens); 
    
    j = tokens.size();
    ptree diskinforoot ;
    ptree diskinfo;

    ptree::iterator  ptit = diskinforoot.push_back(make_pair("diskinfo", diskinfo ));
    ptree::iterator pit ;
    while (i < j) {
        {
            ptree temp;
            pit = ptit->second.push_back(make_pair("FileSystem", temp));
        }
        pit->second.push_back(make_pair("Name", tokens[i++]));
        try {
            if (spaceinfo) {
                totalspace += lexical_cast<uint64_t>(tokens[i]);
            }
            pit->second.push_back(make_pair("Size", tokens[i++]));
            usedspace += lexical_cast<uint64_t>(tokens[i]);
            pit->second.push_back(make_pair("Used", tokens[i++]));

        } catch ( bad_lexical_cast& e) {
        }
        pit->second.push_back(make_pair("Avail", tokens[i++]));
        pit->second.push_back(make_pair("PercentUse", tokens[i++]));
        pit->second.push_back(make_pair("MountedOn", tokens[i++]));
        partnum++;
    }

    if (spaceinfo) {
        ptree temp;
        format fmter("%1%");
        pit = ptit->second.push_back(make_pair("SpaceInfo", temp));
        fmter % totalspace;
        pit->second.push_back(make_pair("TotalSpace", fmter.str()));
        fmter.clear();
        fmter % usedspace;
        pit->second.push_back(make_pair("UsedSpae", fmter.str()));
        fmter.clear();

    }

    if (totalparts) {
        ptree temp;
        format fmter("%1%");
        fmter % partnum;
        ptit->second.push_back(make_pair("TotalParts", fmter.str()));
        fmter.clear();
    }
*/
    //_generateOutput(&diskinforoot, type, response);
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


