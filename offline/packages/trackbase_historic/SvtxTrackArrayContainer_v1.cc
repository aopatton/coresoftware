#include "SvtxTrackArray.h"
#include "SvtxTrackArray_v1.h"
#include "SvtxTrackArrayContainer_v1.h"
#include <phool/PHObject.h>

#include <climits>
#include <map>


    SvtxTrackArrayContainer_v1::SvtxTrackArrayContainer_v1() {


    _clones = new TClonesArray("SvtxTrackArray_v1");

    _clones->SetOwner();
    _clones->SetName("SvtxTrackArrayContainer_v1");

    }

    SvtxTrackArrayContainer_v1::~SvtxTrackArrayContainer_v1(){

      _clones->Clear("C");
    }
    
    void SvtxTrackArrayContainer_v1::identify(std::ostream& os) const{
      os << "SvtxTrackArrayContainer_v1 of size " << size() << std::endl;
    }

    void SvtxTrackArrayContainer_v1::Reset()
  {
  // clear content of towers in the container for the next event

  for (Int_t i = 0; i < _clones->GetEntriesFast(); ++i)
  {
    TObject* obj = _clones->UncheckedAt(i);

    if (obj == nullptr)
    {
      std::cout << __PRETTY_FUNCTION__ << " Fatal access error:"
                << " _clones->GetSize() = " << _clones->GetSize()
                << " _clones->GetEntriesFast() = " << _clones->GetEntriesFast()
                << " i = " << i << std::endl;
      _clones->Print();
    }

    assert(obj);
    // same as TClonesArray::Clear() but only clear but not to erase all towers
    obj->Clear();
    obj->ResetBit(kHasUUID);
    obj->ResetBit(kIsReferenced);
    obj->SetUniqueID(0);
  }
    _clones->Clear("C");

  }


 

  

