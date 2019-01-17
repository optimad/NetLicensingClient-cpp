#ifndef __CONVERTERS_H__
#define __CONVERTERS_H__

#include "netlicensing/constants.h"
#include "netlicensing/datatypes.h"
#include "netlicensing/entity.h"
#include "netlicensing/licensee.h"
#include "netlicensing/product.h"
#include "netlicensing/product_module.h"

namespace netlicensing {

  template<typename T>
  parameters_type toParametersList(T value);

  template<>
  inline parameters_type toParametersList<BaseEntity>(BaseEntity value) {
    parameters_type params;
    params.push_back(std::make_pair(NUMBER, value.getNumber()));
    params.push_back(std::make_pair(ACTIVE, value.getActive().toString()));
    for (const auto& prop : value.getProperties()) {
      params.push_back(prop);
    }
    return params;
  }

  template<>
  inline parameters_type toParametersList<Product>(Product value) {
    parameters_type params = toParametersList<BaseEntity>(value);
    params.push_back(std::make_pair(NAME, value.getName()));
    params.push_back(std::make_pair(VERSION, value.getVersion()));
    params.push_back(std::make_pair(LICENSEE_AUTOCREATE, value.getLicenseeAutoCreate().toString()));
    params.push_back(std::make_pair(DESCRIPTION, value.getDescription()));
    params.push_back(std::make_pair(LICENSING_INFO, value.getLicensingInfo()));

    if (!value.getDiscounts().empty()) {
      for (ProductDiscount discount : value.getDiscounts()) {
        params.push_back(std::make_pair(DISCOUNT, discount.toString()));
      }
    }
    else {
      if (value.isProductDiscountsToched()) {
        params.push_back(std::make_pair(DISCOUNT, ""));
      }
    }

    return params;
  }

  template<>
  inline parameters_type toParametersList<ProductModule>(ProductModule value) {
    parameters_type params = toParametersList<BaseEntity>(value);
    params.push_back(std::make_pair(NAME, value.getName()));
    params.push_back(std::make_pair(PRODUCT_NUMBER, value.getProductNumber()));
    params.push_back(std::make_pair(LICENSING_MODEL, value.getLicensingModel()));

    return params;
  }

  template<>
  inline parameters_type toParametersList<Licensee>(Licensee value) {
    parameters_type params = toParametersList<BaseEntity>(value);
    params.push_back(std::make_pair(NAME, value.getName()));
    return params;
  }

}  // namespace netlicensing

#endif  // __CONVERTERS_H__
