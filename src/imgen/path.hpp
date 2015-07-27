#ifndef IMGEN_PATH_HPP_
#define IMGEN_PATH_HPP_

#include "imgen/point.hpp"
#include "imgen/image.hpp"

#include <cairo/cairo.h>
#include <format.h>

#include <array>
#include <exception>
#include <utility>
#include <vector>

namespace imgen {

struct path {
    enum operation_type {
        MOVE_TO = CAIRO_PATH_MOVE_TO,
        LINE_TO = CAIRO_PATH_LINE_TO,
        CURVE_TO = CAIRO_PATH_CURVE_TO,
    };

    typedef point<double> point_t;
    typedef std::pair<operation_type, std::vector<point_t>> operation_t;

    void move_to(point_t point)
    {
        add_operation(MOVE_TO, { std::move(point) });
    }

    void line_to(point_t point)
    {
        add_operation(LINE_TO, { std::move(point) });
    }

    void curve_to(std::array<point_t, 3>&& points)
    {
        add_operation(CURVE_TO, std::vector<point_t>(
            std::make_move_iterator(points.begin()),
            std::make_move_iterator(points.end())
        ));
    }

    void curve_to(const std::array<point_t, 3>& points)
    {
        add_operation(CURVE_TO, std::vector<point_t>(
            points.begin(), points.end()
        ));
    }

    void draw(context& ctx) const;

private:
    std::vector<operation_t> operations;

    void add_operation(operation_type op, std::vector<point_t> points);
};

} // namespace imgen

#endif // IMGEN_PATH_HPP_
