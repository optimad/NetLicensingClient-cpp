#include <iostream>
#include "netlicensing/context.h"
#include "netlicensing/service.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello, this is NetLicensing demo client\n";

  // check context direct call 
  std::list<std::pair<std::string, std::string> > params;
  params.push_back(std::make_pair("licenseeNumber", "1"));
  params.push_back(std::make_pair("licenseTemplateNumber", "1"));
  params.push_back(std::make_pair("active", "true"));
  params.push_back(std::make_pair("number", "1"));
  params.push_back(std::make_pair("name", "lic"));

  netlicensing::Context ctx;
  ctx.set_base_url("https://go.netlicensing.io/core/v2/rest/");
  ctx.set_username("demo");
  ctx.set_password("demo");
  std::string res = ctx.post("license", params);
  std::cout << "license check answer: " << res << std::endl;
  return 0;
}