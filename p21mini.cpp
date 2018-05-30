#include <sc_cf.h>
extern void SchemaInit( class Registry & );

#include <sdai.h>

#include <STEPfile.h>
#include <STEPattribute.h>

#include <ExpDict.h>
#include <Registry.h>

#include <errordesc.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

int main( int argc, char * argv[] ) {
    // the registry contains information about types present in the current schema; SchemaInit
    // is a function in the schema-specific SDAI library
    Registry  registry( SchemaInit );
    //the InstMgr holds instances that have been created or that have been loaded from a file
    InstMgr   instance_list;
    // STEPfile takes care of reading and writing Part 21 files
    STEPfile  sfile( registry, instance_list, "", false );
    // read a file, using the name from the command line
    sfile.ReadExchangeFile( argv[1] );
    // check for errors; exit if they are particularly severe
    if( sfile.Error().severity() < SEVERITY_USERMSG ) {
        sfile.Error().PrintContents( cout );
    }
    if ( sfile.Error().severity() <= SEVERITY_INCOMPLETE ) {
        exit(1);
    }
    /**************************************************
    ** do something with the data here
    ***************************************************/
    // write to "file.out", then check for write errors. The write operation overwrites any
    // errors caused by previous operations.
    sfile.WriteExchangeFile( "file.out" );
    if( sfile.Error().severity() < SEVERITY_USERMSG ) {
        sfile.Error().PrintContents( cout );
    }
}
