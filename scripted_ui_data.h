#pragma once

#include "stdafx.h"
#include "util.h"
#include "view_index.h"
#include "pretty_archive.h"

struct ScriptedUIData;

namespace ScriptedUIDataElems {

using Label = string;
struct Callback {
  function<void()> fun;
  template <class Archive> void serialize(Archive& ar1, const unsigned int) {
    FATAL << "Can't deserialize Callback";
  }
};
struct Record {
  map<string, ScriptedUIData> SERIAL(elems);
  SERIALIZE_ALL(elems)
};
using List = vector<ScriptedUIData>;
using ::ViewIdList;

#define VARIANT_TYPES_LIST\
  X(Label, 0)\
  X(ViewIdList, 1)\
  X(Callback, 2)\
  X(Record, 3)\
  X(List, 4)

#define VARIANT_NAME ScriptedUIDataImpl
#include "gen_variant.h"
#include "gen_variant_serialize.h"
#define DEFAULT_ELEM "Record"
inline
#include "gen_variant_serialize_pretty.h"
#undef DEFAULT_ELEM
#undef VARIANT_TYPES_LIST
#undef VARIANT_NAME

}

struct ScriptedUIData : ScriptedUIDataElems::ScriptedUIDataImpl {
  using ScriptedUIDataImpl::ScriptedUIDataImpl;
};

struct ScriptedUIState {
  double scrollPos;
  optional<int> scrollButtonHeld;
};