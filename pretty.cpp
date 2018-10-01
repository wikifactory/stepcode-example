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

std::string PrettyPrintAttributeType(BASE_TYPE type) {
    std::string ret = "";
    switch(type) {
        case INTEGER_TYPE:
            ret = "INTEGER_TYPE"; break;
        case REAL_TYPE:
            ret = "REAL_TYPE"; break;
        case BOOLEAN_TYPE:
            ret = "BOOLEAN_TYPE"; break;
        case LOGICAL_TYPE:
            ret = "LOGICAL_TYPE"; break;
        case STRING_TYPE:
            ret = "STRING_TYPE"; break;
        case BINARY_TYPE:
            ret = "BINARY_TYPE"; break;
        case ENUM_TYPE:
            ret = "ENUM_TYPE"; break;
        case SELECT_TYPE:
            ret = "SELECT_TYPE"; break;
        case ENTITY_TYPE:
            ret = "ENTITY_TYPE"; break;
        case AGGREGATE_TYPE:
            ret = "AGGREGATE_TYPE"; break;
        case NUMBER_TYPE:
            ret = "NUMBER_TYPE"; break;
        case ARRAY_TYPE:
            ret = "ARRAY_TYPE"; break;
        case BAG_TYPE:
            ret = "BAG_TYPE"; break;
        case SET_TYPE:
            ret = "SET_TYPE"; break;
        case LIST_TYPE:
            ret = "LIST_TYPE"; break;
        case GENERIC_TYPE:
            ret = "GENERIC_TYPE"; break;
        case REFERENCE_TYPE:
            ret = "REFERENCE_TYPE"; break;
        case UNKNOWN_TYPE:
            ret = "UNKNOWN_TYPE"; break;
    }

    return ret;
}

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

void PrettyWrapper::PrintAssemblyTree() {
    MgrNode* node = NULL;
    SDAI_Application_instance* applicationInstance = NULL;
    for( int i = 0; i < this->instancelist->InstanceCount(); i++ ) {
        node = this->instancelist->GetMgrNode(i);
        applicationInstance = node->GetApplication_instance();

        std::cout << "EntityName: " << applicationInstance->EntityName() << std::endl;
        std::cout << "StepFileId: " << applicationInstance->StepFileId() << std::endl;
        std::cout << "Comment: " << applicationInstance->P21Comment() << std::endl;

        const EntityDescriptor* entityDescriptor = applicationInstance->getEDesc();
        std::cout << "Subtypes: " << entityDescriptor->Subtypes().EntryCount() << std::endl;
        std::cout << "Supertypes: " << entityDescriptor->Supertypes().EntryCount() << std::endl;
        std::cout << "ExplicitAttr: " << entityDescriptor->ExplicitAttr().EntryCount() << std::endl;
        std::cout << "InverseAttr: " << entityDescriptor->InverseAttr().EntryCount() << std::endl;

        int attributeCount = applicationInstance->AttributeCount();
        std::cout << "AttributeCount: " << attributeCount << std::endl;
        for( int i = 0; i < attributeCount; i++ ) {
            STEPattribute* attribute = &applicationInstance->attributes[i];
            std::cout << "Attribute" << i+1 << ":" << std::endl;
            std::cout << "\tName: " << attribute->Name() << std::endl;
            std::cout << "\tNonRefType: " << PrettyPrintAttributeType(attribute->NonRefType()) << std::endl;
            int refCount = attribute->getRefCount();
            std::cout << "\tRefCount: " << refCount << std::endl;

        }

        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    PrettyWrapper pretty;
    if( pretty.LoadFile("dm1-id-214.stp") ) {
        pretty.PrintAssemblyTree();
        std::cout << "Success!" << std::endl;
    } else {
        std::cout << "Error." << std::endl;
    }
    return 0;
}
