#pragma once

#include "util.h"
#include "lasting_effect.h"
#include "furniture_type.h"
#include "creature_id.h"

#define SIMPLE_PREDICATE(Name) \
  struct Name { \
    SERIALIZE_EMPTY()\
  }

struct CreaturePredicate;

namespace CreaturePredicates {
SIMPLE_PREDICATE(Enemy);
SIMPLE_PREDICATE(Automaton);
SIMPLE_PREDICATE(Hidden);
SIMPLE_PREDICATE(Indoors);
SIMPLE_PREDICATE(Night);
SIMPLE_PREDICATE(AIAfraidOf);
SIMPLE_PREDICATE(InTerritory);
SIMPLE_PREDICATE(Spellcaster);
SIMPLE_PREDICATE(Humanoid);
SIMPLE_PREDICATE(PopLimitReached);

struct HatedBy {
  LastingEffect SERIAL(effect);
  SERIALIZE_ALL(effect)
};

struct Ingredient {
  string SERIAL(name);
  SERIALIZE_ALL(name)
};

struct Attacker {
  HeapAllocated<CreaturePredicate> SERIAL(pred);
  SERIALIZE_ALL(pred)
};

struct Name {
  string SERIAL(name);
  HeapAllocated<CreaturePredicate> SERIAL(pred);
  SERIALIZE_ALL(name, pred)
};

struct Flag {
  string SERIAL(name);
  SERIALIZE_ALL(name)
};

struct Unlocked {
  UnlockId SERIAL(id);
  SERIALIZE_ALL(id)
};

struct Health {
  double SERIAL(from);
  double SERIAL(to);
  SERIALIZE_ALL(from, to)
};

struct Not {
  HeapAllocated<CreaturePredicate> SERIAL(pred);
  SERIALIZE_ALL(pred)
};

struct And {
  vector<CreaturePredicate> SERIAL(pred);
  SERIALIZE_ALL(pred)
};

struct Or {
  vector<CreaturePredicate> SERIAL(pred);
  SERIALIZE_ALL(pred)
};

struct Distance {
  optional<int> SERIAL(min);
  optional<int> SERIAL(max);
  SERIALIZE_ALL(min, max)
};

#define CREATURE_PREDICATE_LIST\
  X(Enemy, 0)\
  X(Automaton, 1)\
  X(LastingEffect, 2)\
  X(CreatureStatus, 3)\
  X(BodyMaterial, 4)\
  X(HatedBy, 5)\
  X(Ingredient, 6)\
  X(Hidden, 7)\
  X(Flag, 8)\
  X(Unlocked, 9)\
  X(Name, 10)\
  X(Night, 11)\
  X(Indoors, 12)\
  X(Attacker, 13)\
  X(FurnitureType, 14)\
  X(Not, 15)\
  X(And, 16)\
  X(Or, 17)\
  X(Health, 18)\
  X(CreatureId, 19)\
  X(Distance, 20)\
  X(AIAfraidOf, 21)\
  X(InTerritory, 22)\
  X(Spellcaster, 23)\
  X(Humanoid, 24)\
  X(PopLimitReached, 25)

#define VARIANT_NAME CreaturePredicate
#define VARIANT_TYPES_LIST CREATURE_PREDICATE_LIST

#include "gen_variant.h"

#undef VARIANT_TYPES_LIST
#undef VARIANT_NAME

template <class Archive>
void serialize(Archive& ar1, CreaturePredicate&);

}
class Position;
struct CreaturePredicate : CreaturePredicates::CreaturePredicate {
  using CreaturePredicates::CreaturePredicate::CreaturePredicate;
  bool apply(Position, const Creature* attacker) const;
  string getName() const;
  string getNameInternal(bool negated = false) const;
};
