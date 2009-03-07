// ==========================================================================
// Dedmonwakeen's Raid DPS/TPS Simulator.
// Send questions to natehieter@gmail.com
// ==========================================================================

#include "simcraft.h"

// ==========================================================================
// Rating
// ==========================================================================

namespace { // ANONYMOUS NAMESPACE ==========================================

// rating_60 =================================================================

static rating_t& rating_60()
{
  static rating_t r;

  if( r.spell_haste == 0 )
  {
    r.spell_haste       = 1000;
    r.spell_hit         =  800;
    r.spell_crit        = 1400;
    r.attack_haste      = 1000;
    r.attack_hit        = 1000;
    r.attack_crit       = 1400;
    r.expertise         = 1000;
    r.armor_penetration =  376;
  }

  return r;
}

// rating_70 =================================================================

static rating_t& rating_70()
{
  static rating_t r;

  if( r.spell_haste == 0 )
  {
    r.spell_haste       = 1576;
    r.spell_hit         = 1262;
    r.spell_crit        = 2208;
    r.attack_haste      = 1576;
    r.attack_hit        = 1576;
    r.attack_crit       = 2208;
    r.expertise         = 1576;
    r.armor_penetration =  592;
  }

  return r;
}

// rating_80 =================================================================

static rating_t& rating_80()
{
  static rating_t r;

  if( r.spell_haste == 0 )
  {
    r.spell_haste       = 3279;
    r.spell_hit         = 2623;
    r.spell_crit        = 4591;
    r.attack_haste      = 3279;
    r.attack_hit        = 3279;
    r.attack_crit       = 4591;
    r.expertise         = 3279;
    r.armor_penetration = 1232;
  }

  return r;
}

} // ANONYMOUS NAMESPACE =====================================================

// rating_t::init ============================================================

void rating_t::init( int level )
{
  rating_t& r_60 = rating_60();
  rating_t& r_70 = rating_70();
  rating_t& r_80 = rating_80();

  spell_haste       = interpolate( level, r_60.spell_haste,       r_70.spell_haste,       r_80.spell_haste       );
  spell_hit         = interpolate( level, r_60.spell_hit,         r_70.spell_hit,         r_80.spell_hit         );
  spell_crit        = interpolate( level, r_60.spell_crit,        r_70.spell_crit,        r_80.spell_crit        );
  attack_haste      = interpolate( level, r_60.attack_haste,      r_70.attack_haste,      r_80.attack_haste      );
  attack_hit        = interpolate( level, r_60.attack_hit,        r_70.attack_hit,        r_80.attack_hit        );
  attack_crit       = interpolate( level, r_60.attack_crit,       r_70.attack_crit,       r_80.attack_crit       );
  expertise         = interpolate( level, r_60.expertise,         r_70.expertise,         r_80.expertise         );
  armor_penetration = interpolate( level, r_60.armor_penetration, r_70.armor_penetration, r_80.armor_penetration );
}

// rating_t::interpolate ======================================================

double rating_t::interpolate( int    level,
			      double val_60,
			      double val_70,
			      double val_80 )
{
  if( level <= 60 )
  {
    return val_60;
  }
  else if( level == 70 )
  {
    return val_70;
  }
  else if( level >= 80 )
  {
    return val_80;
  }
  else if( level < 70 )
  {
    // Assume linear progression for now.
    double adjust = ( level - 60 ) / 10.0;
    return val_60 + adjust * ( val_70 - val_60 );
  }
  else // ( level < 80 )
  {
    // Assume linear progression for now.
    double adjust = ( level - 70 ) / 10.0;
    return val_70 + adjust * ( val_80 - val_70 );
  }
  assert(0);
  return 0;
}
