#include <STEPfile.h>

#include <sdai.h>

#include <Registry.h>

#include <SdaiAP242_MANAGED_MODEL_BASED_3D_ENGINEERING_MIM_LF.h>

#include <errordesc.h>

#include <string>

class PrettyWrapper {
private:
    std::string filename;
    InstMgr* instancelist;
    Registry* registry;
    STEPfile* stepfile;

public:
    PrettyWrapper();
    virtual ~PrettyWrapper();

    bool LoadFile(std::string filename);
    void PrintFileInfo();
};
