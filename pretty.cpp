#include "pretty.h"

PrettyWrapper::PrettyWrapper()
    : registry(NULL), stepfile(NULL)
{
    int ownsInstanceMemory = 1;
    instancelist = new InstMgr(ownsInstanceMemory);
}

PrettyWrapper::~PrettyWrapper() {
    delete instancelist;
    delete stepfile;
    delete registry;
}

bool PrettyWrapper::LoadFile(std::string filename) {
    this->registry = new Registry(SchemaInit);
    this->stepfile = new STEPfile(*registry, *instancelist);

    this->filename = filename;
    try {
        this->stepfile->ReadExchangeFile(this->filename.c_str());
    } catch( std::exception &e ) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

#define ANSI_RED "\033[1;31m"
#define ANSI_RESET "\033[0m"

void PrettyWrapper::PrintFileInfo() {
    std::cout << "Registry::GetEntityCnt: " << this->registry->GetEntityCnt() << std::endl;
    std::cout << "InstMgr::InstanceCount: " << this->instancelist->InstanceCount() << std::endl;
    std::cout << "InstMgr::OwnsInstances: " << this->instancelist->OwnsInstances() << std::endl;
    std::cout << "InstMgr::MaxFileId: " << this->instancelist->MaxFileId() << std::endl;

    MgrNode* node = NULL;
    SDAI_Application_instance* applicationInstance = NULL;
    std::map<std::string, int> entityCounts;
    for( int i = 0; i < this->instancelist->InstanceCount(); i++ ) {
        node = this->instancelist->GetMgrNode(i);
        applicationInstance = node->GetApplication_instance();
        std::string name = applicationInstance->EntityName();
        if( entityCounts.find(name) == entityCounts.end() ) {
            entityCounts[name] = 1;
        } else {
            entityCounts[name] = entityCounts[name] + 1;
        }
    }

    std::cout << std::endl;

    const Schema* schema = this->registry->NextSchema();
    while( schema != NULL ) {
        std::cout << "Schema::Name: " << schema->Name() << std::endl;
        std::cout << "Schema::Entities::EntryCount: " << schema->Entities()->EntryCount() << std::endl;
        std::cout << "Schema::Types::EntryCount: " << schema->Types()->EntryCount() << std::endl;

        // const EntityDescriptor* entity = this->registry->NextEntity();
        // while( entity != NULL ) {
        //     std::string name = entity->Name();
        //     if( entityCounts.find(name) == std::end(entityCounts) ) {
        //         std::cout << name << std::endl;
        //     } else {
        //         int count = entityCounts[name];
        //         std::cout << ANSI_RED << name << ": " << count << ANSI_RESET << std::endl;
        //     }
        //     entity = this->registry->NextEntity();
        // }

        schema = this->registry->NextSchema();
    }

    std::cout << std::endl;

    for( auto const it : entityCounts ) {
        std::cout << it.first << ": " << it.second << std::endl;
    }

    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    PrettyWrapper pretty;
    if( pretty.LoadFile("dm1-id-214.stp") ) {
        pretty.PrintFileInfo();
        std::cout << "Success!" << std::endl;
    } else {
        std::cout << "Error." << std::endl;
    }
    return 0;
}
