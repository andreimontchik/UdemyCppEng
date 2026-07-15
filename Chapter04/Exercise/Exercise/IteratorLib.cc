#include "IteratorLib.h"

namespace mystd
{

It next(It it, DifferenceType n)
{
    std::advance(it, n);
    return it;
}

It prev(It it, DifferenceType n)
{
    return std::prev(it, -n);
}

DifferenceType distance(It first, It last)
{
    return std::distance(first, last);
}

void advance(It &it, DifferenceType n)
{
    std::advance(it, n);
}

} // namespace mystd