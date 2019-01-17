#ifndef __NETLICENSING_H__
#define __NETLICENSING_H__

#include "netlicensing/context.h"
#include "netlicensing/service.h"
#include "netlicensing/product.h"
#include "netlicensing/product_module.h"
#include "netlicensing/license_template.h"
#include "netlicensing/licensee.h"
#include "netlicensing/country.h"
#include "netlicensing/exception.h"
#include "netlicensing/validation_result.h"
#include "netlicensing/validation_parameters.h"

#ifdef __GNUC__
  #define DEPRECATED(decl) decl __attribute__ ((deprecated))
#elif defined(_MSC_VER)
  #define DEPRECATED(decl) __declspec(deprecated) decl
#else
  #pragma message("WARNING: DEPRECATED declaration for this compiler is not defined")
  #define DEPRECATED(decl) decl
#endif

namespace netlicensing {

class ProductService {
 public:
  static Product get(Context& ctx, const std::string& productNumber);
  static Product create(Context& ctx, const Product&);
  static Product update(Context& ctx, const std::string& productNumber, const Product&);
  static void del(Context& ctx, const std::string& productNumber, bool forceCascade);
  static std::list<Product> list(Context& ctx, const std::string& filter);
};

class ProductModuleService {
public:
  static ProductModule get(Context& ctx, const std::string& number);
  static ProductModule create(Context& ctx, const ProductModule&);
  static ProductModule update(Context& ctx, const std::string& number, const ProductModule&);
  static void del(Context& ctx, const std::string& number, bool forceCascade);
  static std::list<ProductModule> list(Context& ctx, const std::string& filter);
};

class LicenseTemplateService {
public:
  static LicenseTemplate get(Context& ctx, const std::string& number);
  static LicenseTemplate create(Context& ctx, const LicenseTemplate&);
  static LicenseTemplate update(Context& ctx, const std::string& number, const LicenseTemplate&);
  static void del(Context& ctx, const std::string& number, bool forceCascade);
  static std::list<LicenseTemplate> list(Context& ctx, const std::string& filter);
};

class LicenseeService {
 public:
  static Licensee create(Context& ctx, const Licensee&);
  static Licensee update(Context& ctx, const std::string& licenseeNumber, const Licensee&);
  static void del(Context& ctx, const std::string& licenseeNumber, bool forceCascade);
  static std::list<Licensee> list(Context& ctx, const std::string& filter);
  DEPRECATED(static ValidationResult validate(Context& ctx, const std::string& licenseeNumber, 
    const std::string& productNumber = std::string(),
    const std::string& licenseeName = std::string(),
    const parameters_type& validationParameters = parameters_type()));
  static ValidationResult validate(Context& ctx, const std::string& licenseeNumber,
    const ValidationParameters& validationParameters);
  static void transfer(Context& ctx, const std::string& licenseeNumber, const std::string& sourceLicenseeNumber);
};

class UtilityService {
public:
  static std::list<Country> listCountries(Context& ctx);
  //TODO(AY): add utility lists
  //static std::list<Product> listLicenseTypes(Context& ctx);
  //static std::list<Product> listLicensingModels(Context& ctx);
};


}

#endif //__NETLICENSING_H__
