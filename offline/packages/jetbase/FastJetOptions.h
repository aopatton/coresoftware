#ifndef JETBASE_FASTJETOPTIONS
#define JETBASE_FASTJETOPTIONS

#include "Jet.h"

#include <ostream>
#include <vector>

// This is a structure that the FastJetAlgo class uses for its optoins. The users
// can initialize it as a double-brace enclosed list which is a mix of
// Something like this:
//
// FastJetOptions fj_opt {{ Jet::ALGO::ANTIKT, DO_SOFTDROP, SD_BETA, 0.0, SD_ZCUT 0.1, JET_R, 0.4 }};
// jet_reco_obj->add_algo(new FastJetAlgo(fj_opt), "AntiKt_Tower_r04");
// /* can also update it */
// jet_reco_obj->add_algo(new FastJetAlgo(fj_opt({{JET_R,0.5}}), "AntiKt_Tower_r05");

enum FastJetOptEnum
{
    JET_R         // required
  , JET_MIN_PT    // optional, not set
  , JET_MAX_ETA   // optional, not set

  , CONSTITUENT_MIN_PT // optional, not set

  , DO_SOFTDROP   // optional; off
  , SD_BETA       // defaults to 0
  , SD_ZCUT       // defaults to 0
  , SD_JET_MIN_PT // defaults to 5.

  , CALC_AREA     // optional, is off
  , GHOST_AREA    // defaults to 0.01
  , GHOST_MAX_RAP // defaults to 5 or JET_MAX_ETA+JET_R

  , CALC_RhoMedDens    // optional; default off
  , CUT_RhoMedNHardest // optional; default 2
  , NONE 

  , SAVE_JET_COMPONENTS      // optional; default true (I think this is what is hitting the e- spectra)
  , DONT_SAVE_JET_COMPONENTS // set save_jet_components to false

  , VERBOSITY // optional 
};

struct FastJetOptItem
{  // All the things you can feed into FastJetAlgo
  FastJetOptEnum opt{FastJetOptEnum::NONE};
  bool is_opt{false};

  float val{0.};
  bool is_val{false};

  Jet::ALGO algo{};
  bool is_algo{false};

  FastJetOptItem(float _val)
    : val{_val}
    , is_val{true} {};
  FastJetOptItem(Jet::ALGO _algo)
    : algo{_algo}
    , is_algo{true} {};
  FastJetOptItem(FastJetOptEnum _opt)
    : opt{_opt}
    , is_opt{true} {};
};

struct FastJetOptions
{
  FastJetOptions(){};
  FastJetOptions(const std::vector<FastJetOptItem>& _vitem) { update(_vitem); };
  FastJetOptions& update(std::vector<FastJetOptItem>);
  FastJetOptions& operator()(const std::vector<FastJetOptItem>& _vitem) { return update(_vitem); };

  void print(std::ostream& os = std::cout);

  float next_val(int& i, std::vector<FastJetOptItem>&);
  float jet_R = 0.4;
  Jet::ALGO algo = Jet::ALGO::ANTIKT;

  bool  use_jet_max_eta = false;
  float jet_max_eta     = 0;
  /* bool  handset_maxeta              = false; // If user uses jet_max_eta, then cut_edge_eta won't reset eta at all */
  /* bool  cut_edge_eta                = false; */

  bool  use_jet_min_pt = false;
  float jet_min_pt     = 0;

  bool  use_constituent_min_pt = false;
  float constituent_min_pt     = 0.;

  bool  save_jet_components    = true;

  bool  doSoftDrop                  = false;
  float SD_beta                     = 0;
  float SD_zcut                     = 0;
  float SD_jet_min_pt               = 5.;

  bool  calc_area                   = false;
  float ghost_area                  = 0.01;
  float ghost_max_rap               = 0; // will default to min(jet_max_eta+Jet_R., 5)

  bool  calc_jetmedbkgdens          = false;
  float nhardestcut_jetmedbkgdens   = 2;
  float etahardestcut_jetmedbkgdens = 0.; // will default to jet_max_eta or ghost_max_rap
  /* float rhoMedEtaNHardCut           = 0.; */

  int   verbosity                   = 0;

  // for convenience when running FastJetAlgo
  bool  use_jet_selection           = false; // set when initialized
  void initialize();  // updates run with the first call
};

#endif
