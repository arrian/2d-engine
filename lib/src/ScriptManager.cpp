#include "ScriptManager.h"

#include "PythonModules.h"

ScriptManager::ScriptManager()
{
	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.insert(0, '')");
}

ScriptManager::~ScriptManager()
{
	Py_Finalize();
}

string ScriptManager::import(string import)
{
	python::object module = python::import(python::str(import));
    // TODO: do something with the module
    return "success";// TODO: return printable result
}

string ScriptManager::execute(string code)
{
    python::object result = python::exec(python::str(code));
    return "success";// TODO: return printable result
}

string ScriptManager::executeFile(string filename)
{
    python::object result = python::exec_file(python::str(filename));
    return "success";// TODO: return printable result
}

string ScriptManager::getError()
{
	PyObject *ptype, *pvalue, *ptraceback;
	PyErr_Fetch(&ptype, &pvalue, &ptraceback);

    string error;
    if(pvalue != NULL) error = python::extract<string>(pvalue);

    return error;
}

void ScriptManager::update()
{
    
}



// static int numargs=0;

// /* Return the number of arguments of the application command line */
// static PyObject*
// emb_numargs(PyObject *self, PyObject *args)
// {
//     if(!PyArg_ParseTuple(args, ":numargs"))
//         return NULL;
//     return PyLong_FromLong(numargs);
// }

// static PyMethodDef EmbMethods[] = {
//     {"numargs", emb_numargs, METH_VARARGS,
//      "Return the number of arguments received by the process."},
//     {NULL, NULL, 0, NULL}
// };

// static PyModuleDef EmbModule = {
//     PyModuleDef_HEAD_INIT, "emb", NULL, -1, EmbMethods,
//     NULL, NULL, NULL, NULL
// };

// static PyObject*
// PyInit_emb(void)
// {
//     return PyModule_Create(&EmbModule);
// }

// // To build:
// // g++ ScriptManager.cpp -L/usr/local/Cellar/python3/3.4.1/Frameworks/Python.framework/Versions/3.4/lib/python3.4/config-3.4m -ldl -framework CoreFoundation -lpython3.4m -I"/usr/local/Cellar/python3/3.4.1/Frameworks/Python.framework/Versions/3.4/include/python3.4m/" -o test
// int
// main(int argc, char *argv[])
// {
//     PyObject *pName, *pModule, *pDict, *pFunc;
//     PyObject *pArgs, *pValue;
//     int i;

//     if (argc < 3) {
//         fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
//         return 1;
//     }

//     numargs = argc;
// 	PyImport_AppendInittab("emb", &PyInit_emb);

//     Py_Initialize();
//     PyRun_SimpleString("import sys"); 
// 	PyRun_SimpleString("sys.path.insert(0, '')");

//     pName = PyUnicode_FromString(argv[1]);
//     /* Error checking of pName left out */

//     pModule = PyImport_Import(pName);
//     Py_DECREF(pName);

//     if (pModule != NULL) {
//         pFunc = PyObject_GetAttrString(pModule, argv[2]);
//         /* pFunc is a new reference */

//         if (pFunc && PyCallable_Check(pFunc)) {
//             pArgs = PyTuple_New(argc - 3);
//             for (i = 0; i < argc - 3; ++i) {
//                 pValue = PyLong_FromLong(atoi(argv[i + 3]));
//                 if (!pValue) {
//                     Py_DECREF(pArgs);
//                     Py_DECREF(pModule);
//                     fprintf(stderr, "Cannot convert argument\n");
//                     return 1;
//                 }
//                 /* pValue reference stolen here: */
//                 PyTuple_SetItem(pArgs, i, pValue);
//             }
//             pValue = PyObject_CallObject(pFunc, pArgs);
//             Py_DECREF(pArgs);
//             if (pValue != NULL) {
//                 printf("Result of call: %ld\n", PyLong_AsLong(pValue));
//                 Py_DECREF(pValue);
//             }
//             else {
//                 Py_DECREF(pFunc);
//                 Py_DECREF(pModule);
//                 PyErr_Print();
//                 fprintf(stderr,"Call failed\n");
//                 return 1;
//             }
//         }
//         else {
//             if (PyErr_Occurred())
//                 PyErr_Print();
//             fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
//         }
//         Py_XDECREF(pFunc);
//         Py_DECREF(pModule);
//     }
//     else {
//         PyErr_Print();
//         fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
//         return 1;
//     }
//     Py_Finalize();
//     return 0;
// }

