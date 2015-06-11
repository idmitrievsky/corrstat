//
//  acopula.h
//  corrstat
//
//  Created by Ivan Dmitrievsky on 10/06/15.
//  Copyright (c) 2015 Иван Дмитриевский. All rights reserved.
//

#ifndef corrstat_acopula_h
#define corrstat_acopula_h

#include "copula.h"

namespace cst {

class acopula_t : public copula_t {
public:
  acopula_t(size_t dim) : copula_t(dim) {}

  virtual num_t call(vec_t x) {
    num_t a(0);

    check(x);

    for (size_t i = 0; i < _dim; ++i) {
      a += gen(x[i]);
    }

    return inv_gen(a);
  }

  virtual num_t gen(num_t x) const = 0;
  virtual num_t inv_gen(num_t x) const = 0;
};
}

#endif