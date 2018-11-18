#pragma once

#include <memory>
#include <utility>

/*
 * Simple alias so we don't have to write
 * std::unique_ptr at all places in the code
 * where we want a unique_ptr.
 */
template <typename T>
using ptr = std::unique_ptr<T>;
