#include "imgen/color.hpp"
#include "imgen/palette.hpp"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <vector>

namespace py = boost::python;

/** Palette Wrappers */
struct palette_wrapper : imgen::palette, py::wrapper<imgen::palette> {
    imgen::color blend(int left, int right, float proportion) {
        return this->get_override("blend")(left, right, proportion);
    }
};

/** Colour Wrappers */
typedef std::vector<imgen::color> color_vec_t;
typedef boost::gil::channel_type<imgen::color>::type channel_t;

inline void color_check_range(int index) {
    if(index < 0 || index > boost::gil::num_channels<imgen::color>()) {
        PyErr_SetString(PyExc_IndexError, "Index out of range");
        py::throw_error_already_set();
    }
}

channel_t color_getitem(imgen::color& c, int index) {
    color_check_range(index);

    return c[index];
}

void color_setitem(imgen::color& c, int index, channel_t value) {
    color_check_range(index);

    c[index] = value;
}


/** Bindings */
BOOST_PYTHON_MODULE(imgen) {
    py::class_<imgen::color>("Color", py::init<int, int, int>())
        .def("__getitem__", &color_getitem)
        .def("__setitem__", &color_setitem);

    py::class_<color_vec_t>("ColorList")
        .def(py::vector_indexing_suite<color_vec_t>());

    py::class_<palette_wrapper, boost::noncopyable>("Palette")
        .def_readwrite("colors", &imgen::palette::colors)
        .def("blend", py::pure_virtual(&imgen::palette::blend));
}
