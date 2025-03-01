#ifndef G4EVAL_SVTXEVALUATOR_H
#define G4EVAL_SVTXEVALUATOR_H

//===============================================
/// \file SvtxEvaluator.h
/// \brief Compares reconstructed tracks to truth particles
/// \author Michael P. McCumber (revised SVTX version)
//===============================================

#include <fun4all/SubsysReco.h>

#include <TMatrixFfwd.h>
#include <TMatrixT.h>
#include <TMatrixTUtils.h>

#include <string>

class PHCompositeNode;
class PHTimer;
class TrkrCluster;
class SvtxEvalStack;
class TFile;
class TNtuple;
class SvtxTrack;
class SvtxVertexMap;
class GlobalVertexMap;

// class TrkrClusterContainer;

/// \class SvtxEvaluator
///
/// \brief Compares reconstructed tracks to truth particles
///
/// Plan: This module will trace the reconstructed tracks back to
/// the greatest contributor Monte Carlo particle and then
/// test one against the other.
///
class SvtxEvaluator : public SubsysReco
{
 public:
  SvtxEvaluator(const std::string &name = "SVTXEVALUATOR",
                const std::string &filename = "g4eval.root",
                const std::string &trackmapname = "SvtxTrackMap",
                unsigned int nlayers_maps = 3,
                unsigned int nlayers_intt = 8,
                unsigned int nlayers_tpc = 48,
                unsigned int nlayers_mms = 2);
  ~SvtxEvaluator() override;

  int Init(PHCompositeNode *topNode) override;
  int InitRun(PHCompositeNode *topNode) override;
  int process_event(PHCompositeNode *topNode) override;
  int End(PHCompositeNode *topNode) override;
  //  void do_primaries(bool b);

  void set_strict(bool b) { _strict = b; }
  void set_use_initial_vertex(bool use_init_vtx) { _use_initial_vertex = use_init_vtx; }
  void set_use_genfit_vertex(bool use_genfit_vtx) { _use_genfit_vertex = use_genfit_vtx; }
  void do_info_eval(bool b) { _do_info_eval = b; }
  void do_vertex_eval(bool b) { _do_vertex_eval = b; }
  void do_gpoint_eval(bool b) { _do_gpoint_eval = b; }
  void do_g4hit_eval(bool b) { _do_g4hit_eval = b; }
  void do_hit_eval(bool b) { _do_hit_eval = b; }
  void do_cluster_eval(bool b) { _do_cluster_eval = b; }
  void do_g4cluster_eval(bool b) { _do_g4cluster_eval = b; }
  void do_gtrack_eval(bool b) { _do_gtrack_eval = b; }
  void do_track_eval(bool b) { _do_track_eval = b; }
  void do_gseed_eval(bool b) { _do_gseed_eval = b; }

  void do_track_match(bool b) { _do_track_match = b; }
  void do_eval_light(bool b) { _do_eval_light = b; }
  void do_vtx_eval_light(bool b) { _do_vtx_eval_light = b; }
  void scan_for_embedded(bool b) { _scan_for_embedded = b; }
  void scan_for_primaries(bool b) { _scan_for_primaries = b; }
  
 private:
  unsigned int _ievent = 0;
  unsigned int _iseed = 0;
  float m_fSeed = NAN;
  // eval stack
  SvtxEvalStack *_svtxevalstack = nullptr;

  TMatrixF calculateClusterError(TrkrCluster *c, float &clusphi);
  void get_dca(SvtxTrack *track, GlobalVertexMap *vertexmap,
               float &dca3dxy, float &dca3dz,
               float &dca3dxysigma, float &dca3dzsigma);
  // TrkrClusterContainer *cluster_map{nullptr};

  //----------------------------------
  // evaluator output ntuples

  bool _strict = false;
  bool _use_initial_vertex = true;
  bool _use_genfit_vertex = false;
  unsigned int _errors = 0;

  bool _do_info_eval = true;
  bool _do_vertex_eval = true;
  bool _do_gpoint_eval = true;
  bool _do_g4hit_eval = true;
  bool _do_hit_eval = true;
  bool _do_cluster_eval = true;
  bool _do_g4cluster_eval = true;
  bool _do_gtrack_eval = true;
  bool _do_track_eval = true;
  bool _do_gseed_eval = false;

  bool _do_track_match = true;
  bool _do_eval_light = true;
  bool _do_vtx_eval_light = true;
  bool _scan_for_embedded = false;
  bool _scan_for_primaries = false;

  unsigned int _nlayers_maps = 3;
  unsigned int _nlayers_intt = 4;
  unsigned int _nlayers_tpc = 48;
  unsigned int _nlayers_mms = 2;

  TNtuple *_ntp_info = nullptr;
  TNtuple *_ntp_vertex = nullptr;
  TNtuple *_ntp_gpoint = nullptr;
  TNtuple *_ntp_g4hit = nullptr;
  TNtuple *_ntp_hit = nullptr;
  TNtuple *_ntp_cluster = nullptr;
  TNtuple *_ntp_g4cluster = nullptr;
  TNtuple *_ntp_gtrack = nullptr;
  TNtuple *_ntp_track = nullptr;
  TNtuple *_ntp_gseed = nullptr;

  // evaluator output file
  std::string _filename;
  // Track map name
  std::string _trackmapname;
  TFile *_tfile = nullptr;

  PHTimer *_timer = nullptr;

  // output subroutines
  void fillOutputNtuples(PHCompositeNode *topNode);  ///< dump the evaluator information into ntuple for external analysis
  void printInputInfo(PHCompositeNode *topNode);     ///< print out the input object information (debugging upstream components)
  void printOutputInfo(PHCompositeNode *topNode);    ///< print out the ancestry information for detailed diagnosis
 
};

#endif  // G4EVAL_SVTXEVALUATOR_H
