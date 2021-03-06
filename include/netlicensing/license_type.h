#ifndef __LICENSE_TYPES_H__
#define __LICENSE_TYPES_H__

#include <list>

#include "netlicensing/constants.h"
#include "netlicensing/entity.h"

namespace netlicensing {

  class LicenseType {
  private:
    String_t name_i;

  public:
    LicenseType() : name_i() { }

    void setName(const String_t& name) {
      name_i = name;
    }

    const String_t& getName() const {
      return name_i;
    }

    std::string toString() const {
      std::string name(getName());

      std::stringstream ss;
      ss << "LicenseType [";
      ss << NAME << ": " << name;
      ss << "]";
      return ss.str();
    }

  };

}

#endif // __LICENSE_TYPES_H__
