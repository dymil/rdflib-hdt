#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "hdt_document.hpp"

namespace py = pybind11;

struct Pet {
    Pet(const std::string &name) : name(name) { }
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }

    std::string name;
};

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(hdt, m) {
    m.doc() = "pyHDT module enables to load and query HDT files with ease";

    py::class_<HDTDocument>(m, "HDTDocument", "An HDTDocument enables to load an query and HDT file with ease. Indexes are automatically generated if missing.")
      .def(py::init(&HDTDocument::create))
      .def("get_file_path", &HDTDocument::getFilePath, "Get the path to the HDT file currently loaded")
      .def("search_triples", &HDTDocument::search,
          "Search for RDF triples matching the triple pattern { subject predicate object }, with an optional limit and offset.\nUse empty strings (\"\") to indicate variables.",
          py::arg("subject"), py::arg("predicate"), py::arg("object"), py::arg("limit") = 0, py::arg("offset") = 0)
      .def("__repr__", &HDTDocument::python_repr);

}
