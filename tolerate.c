#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>
#include <stdio.h>
#include <stdlib.h>

PyObject *return_values(PyObject *self, PyObject *args) {
    PyArrayObject *arr;
    double tol;
    PyArg_ParseTuple(args, "Od", &arr, &tol);
    
    if (PyErr_Occurred()) {
        return NULL;
    }

    if (!PyArray_Check(arr) || PyArray_TYPE(arr) != NPY_DOUBLE) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a double precision NumPy array");
        return NULL;
    }

    int axis = 0;
    //npy_intp dim = PyArray_DIMS(arr);
    int64_t size = PyArray_SIZE(arr);
    npy_intp dim[] = { [0] = size };
    double *data = PyArray_DATA(arr);

    PyArray_AsCArray((PyObject **)&arr, &data, dim, 1, PyArray_DescrFromType(NPY_DOUBLE));

    PyArray_Sort(arr,axis,NPY_QUICKSORT);
    
    double dtol = tol * tol;
    double diff;

    for (int i = 0; i < size - 1; ++i) {
        diff = data[i] - data[i+1];
        diff *= diff; 
        if (diff <= dtol) {
            data[i+1] = data[i];
        }
    }

    PyArray_Free((PyObject *) arr,data);

    arr = (PyArrayObject *) PyArray_SimpleNewFromData(1,dim, NPY_DOUBLE,data);

    return PyArray_Return(arr);
}

static PyMethodDef methods[] = {
    {"return_values", return_values, METH_VARARGS, "Returns unique values within tolerance"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef tolerate = {
    PyModuleDef_HEAD_INIT,
    "tolerate",
    "This module returns the unique values of an array within a specified tolerance",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_tolerate() {
    PyObject *module = PyModule_Create(&tolerate);
    import_array();
    return module;
}