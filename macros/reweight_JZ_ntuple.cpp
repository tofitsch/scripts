// adds a new branch to the ntuple with the total weight of the event based on the weight that's already present: total_weight = weight * filter_eff * and x_sec / sum_of_weights
// sum_of_weights is taken from the cutflow histogram
// make sure to update the filter_eff and x_sec vectors below based on the AMI metadata for your sample

#include <ROOT/RDataFrame.hxx>

string const file_name_str = "user.tofitsch.TLAHistograms.oct31.mc.reco.ntuple.mc16_13TeV.3647%02d.JZ%dWithSW_%s.root";
string const cutflow_name = "cutflow_weighted";

vector<double> const filter_eff = {
  0.97536   ,
  2.4162E-02,
  9.8225E-03,
  1.1653E-02,
  0.013369  ,
  0.014529  ,
  0.0094734 ,
  0.011099  ,
  0.010156  ,
  0.012057  ,
  0.005894  ,
  0.0026734 ,
  0.00042898,
};

vector<double> const x_sec = {
  78050000000, //JZ0
  78420000000.0,
  2432800000.0,
  26452000.0,
  254610,
  4552.9,
  257.54,
  16.215,
  0.62506,
  0.019639,
  0.0011962,
  4.2263e-05,
  1.0367e-06, //JZ12
};

void reweight() {

  for(int i = 0; i <= 12; i++) {

    TFile *file_cutflow = TFile::Open(Form(file_name_str.c_str(), i, i, "cutflow.root"), "read");

    if(!file_cutflow)
      continue;

	TH1D *h_scale = static_cast<TH1D*>(file_cutflow->Get(cutflow_name.c_str()));

	double factor = x_sec.at(i) * filter_eff.at(i) / h_scale->GetBinContent(1);

    ROOT::RDataFrame data_frame("ntuple", Form(file_name_str.c_str(), i, i, "tree.root"));

    data_frame.Define("total_weight", Form("weight * %f", factor)).Snapshot("ntuple", Form("JZ%d.root", i));

  }

}
