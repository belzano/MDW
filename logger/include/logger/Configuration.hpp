#pragma once

#include <string>

namespace logger{
  
class Configuration
{
public:
  virtual ~Configuration(){}

  // inactive logging level
  virtual unsigned int getInactiveLevels() = 0;
  // Tags
  virtual unsigned int getTags() = 0;

  // Files storage
  virtual std::string getWriteDirectory() = 0;
  virtual std::string getFileBaseName() = 0;
};

}


