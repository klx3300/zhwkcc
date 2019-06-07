#include "stdlibs.hpp"
#include "../format/log.hpp"

using namespace std;

StdLibrary::StdLibrary(){
    {
        // io.println
        FunctionSignature io_prln;
        io_prln.namespc = 0;
        io_prln.funcid = 0;
        io_prln.return_type.push_back(NewTypeSignature(VTYPE_INTEGER));
        list<TypeSignature> lt;
        lt.push_back(NewTypeSignature(VTYPE_STRING));
        io_prln.param_types.push_back(lt);
        libfuncs["io.println"] = io_prln;
        qLogDebug("Generator: registered standard library function io.println.\n");
    }
}


FunctionSignature StdLibrary::getfunc(string nsname, string fname, bool& succ){
    auto libiter = libfuncs.find(nsname + "." + fname);
    if(libiter == libfuncs.end()){
        succ = false;
        return FunctionSignature();
    }
    succ = true;
    return libiter->second;
}
