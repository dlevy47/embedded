#pragma once

#include "crt/print.hh"
#include "std/assert.hh"
#include "types.hh"

namespace crt {

template <typename HAL>
struct CRT: public crt::print::Print<HAL> {
};

}
