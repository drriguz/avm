#ifndef _AVM_CLASS_PATH_CLASS_LOADER_H_
#define _AVM_CLASS_PATH_CLASS_LOADER_H_

#include <string>

#include "class_loader.h"

namespace avm {

class ClasspathClassLoader: public ClassLoader {
public:
    ClasspathClassLoader(const std::string &classpath);
    virtual ~ClasspathClassLoader();
public:
    virtual void loadClass(const std::string &className, JavaClass &out);
private:
    std::string getClassFilePath(const std::string &className) const;
protected:
    const std::string _classpath;
};
}
#endif
