//converts a TTree-based ntuple root file into a RNTuple-based root file

//based on: https://root.cern/doc/v632/ntpl008__import_8C.html

#include <ROOT/RNTupleDS.hxx>
#include <ROOT/RNTupleImporter.hxx>
 
using RNTuple = ROOT::Experimental::RNTuple;
using RNTupleImporter = ROOT::Experimental::RNTupleImporter;
 
char const *in_file_name = "ntuple_reco.root";
char const *tree_name = "ntuple";
char const *out_file_name = "rntuple_reco.root";
 
void ttree2rntuple()
{
   gSystem->Unlink(out_file_name);
 
   ROOT::EnableImplicitMT();
 
   auto importer = RNTupleImporter::Create(in_file_name, tree_name, out_file_name);
 
   importer->Import();
 
}
