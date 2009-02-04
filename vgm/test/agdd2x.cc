#include <AGDD/XercesParser.hh>
#include <AGDD/IDocument.hh>
 #include <AGDD/AGDD_DocumentVisitor.hh>
#include <AGDD/AGDD_Description.hh>
#include <AGDD/AGDD_Model.hh>
#include <AGDD/AGDD_Dumper.hh>

#include <AgddGM/volumes/Factory.h>
#include <RootGM/volumes/Factory.h>
#include <TGeoManager.h>


#include <iostream>
#include <cstdlib>

using namespace std;

void usage(string msg)
{
    cerr << msg << endl;
    cerr << "usage: agdd2x file.agdd file.FORMAT\n";
    exit (1);
}

int main (int argc, char *argv[])
{
    if (argc != 3) usage("Bad command line arguments");
    cerr << "Starting...\n";


    string input = argv[1], output = argv[2];
    string::size_type dot = output.rfind(".");
    if (dot == string::npos)  usage("Bad output filename");
    string ext = output.substr(dot+1);

    const char* supported_ext[] = {
        "C", "root", /*"agdd", "gdml",*/ 0
    };

    { // sanity check for good output extension:
        bool good_ext = false;
        for (int ind=0; supported_ext[ind]; ++ind) {
            if (ext == supported_ext[ind]) { good_ext = true; break; }
        }
        if (!good_ext) {
            cerr << "Supported formats:\n";
            for (int ind=0; supported_ext[ind]; ++ind) {
                cerr << "\t." << supported_ext[ind] << endl;
            }
            usage ("Unknown output format: ." + ext);
        }
    }

    agdd::XercesParser p;
    agdd::IDocument* doc = p.Parse(argv[1]);

    agdd::AGDD_DocumentVisitor dv;

    doc->Visit(&dv);

    // have to break const, AGDD is not very const correct.
    agdd::AGDD* agdd = const_cast<agdd::AGDD*>(dv.agdd->evaluate());

    //agdd::AGDD_Dumper dumper(cout);
    //dumper.dump(agdd);

    AgddGM::Factory fact;
    if (!fact.Import(agdd)) {
	usage("AgddGM::Factory::Import failed");
    }

    if (ext == "root" || ext == "C") {
	RootGM::Factory root_fact;
	fact.SetDebug(10);
	fact.Export(&root_fact);
	if (!root_fact.Top()) {
	    cerr << "No top placement for root factory, wtf?\n";
	}

	gGeoManager->CloseGeometry();
	gGeoManager->Export(output.c_str());
	return 0;
    }

    usage("Unknown output extension: " + ext);

    return 0;
} // end of main()
