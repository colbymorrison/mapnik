/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2015 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef MAPNIK_GEOMETRY_HPP
#define MAPNIK_GEOMETRY_HPP

// mapnik
#include <mapnik/geometry/point.hpp>
#include <mapnik/geometry/line_string.hpp>
#include <mapnik/geometry/polygon.hpp>
#include <mapnik/geometry/multi_point.hpp>
#include <mapnik/geometry/multi_line_string.hpp>
#include <mapnik/geometry/multi_polygon.hpp>
//
#include <mapnik/util/variant.hpp>
// stl
#include <vector>
#include <deque>
#include <type_traits>
#include <cstddef>

namespace mapnik { namespace geometry {

template <typename T, template <typename...> class Cont = std::vector>
struct geometry_collection;

template <typename T>
struct geometry_empty
{
    using coord_type = T;
};

template <typename T>
using geometry_base = mapnik::util::variant<geometry_empty<T>,
                                            point<T>,
                                            line_string<T>,
                                            polygon<T>,
                                            multi_point<T>,
                                            multi_line_string<T>,
                                            multi_polygon<T>,
                                            geometry_collection<T> >;
template <typename T>
struct geometry : geometry_base<T>
{
    using coord_type = T;

    geometry()
        : geometry_base<T>() {} // empty

    template <typename G>
    geometry(G && geom)
        : geometry_base<T>(std::forward<G>(geom)) {}

};


template <typename T, template <typename...> class Cont>
struct geometry_collection : Cont<geometry<T>>
{
    using coord_type = T;
};

}}

#endif //MAPNIK_GEOMETRY_HPP
