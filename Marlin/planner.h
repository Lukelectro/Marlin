/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * planner.h
 *
 * Buffer movement commands and manage the acceleration profile plan
 *
 * Derived from Grbl
 * Copyright (c) 2009-2011 Simen Svale Skogsrud
 */

#ifndef PLANNER_H
#define PLANNER_H

#include "Marlin.h"

#if ENABLED(AUTO_BED_LEVELING_FEATURE)
  #include "vector_3.h"
#endif

class Planner;
extern Planner planner;

/**
 * struct block_t
 *
 * A single entry in the planner buffer.
 * Tracks linear movement over multiple axes.
 *
 * The "nominal" values are as-specified by gcode, and
 * may never actually be reached due to acceleration limits.
 */
typedef struct {

  unsigned char active_extruder;            // The extruder to move (if E move)

  // Fields used by the bresenham algorithm for tracing the line
  long steps[NUM_AXIS];                     // Step count along each axis
  unsigned long step_event_count;           // The number of step events required to complete this block

  long accelerate_until,                    // The index of the step event on which to stop acceleration
       decelerate_after,                    // The index of the step event on which to start decelerating
       acceleration_rate;                   // The acceleration rate used for acceleration calculation

  unsigned char direction_bits;             // The direction bit set for this block (refers to *_DIRECTION_BIT in config.h)

  // Advance extrusion
  #if ENABLED(LIN_ADVANCE)
    bool use_advance_lead;
    int e_speed_multiplier8; // Factorised by 2^8 to avoid float
  #elif ENABLED(ADVANCE)
    long advance_rate;
    volatile long initial_advance;
    volatile long final_advance;
    float advance;
  #endif

  // Fields used by the motion planner to manage acceleration
  float nominal_speed,                               // The nominal speed for this block in mm/sec
        entry_speed,                                 // Entry speed at previous-current junction in mm/sec
        max_entry_speed,                             // Maximum allowable junction entry speed in mm/sec
        millimeters,                                 // The total travel of this block in mm
        acceleration;                                // acceleration mm/sec^2
  unsigned char recalculate_flag,                    // Planner flag to recalculate trapezoids on entry junction
                nominal_length_flag;                 // Planner flag for nominal speed always reached

  // Settings for the trapezoid generator
  unsigned long nominal_rate,                        // The nominal step rate for this block in step_events/sec
                initial_rate,                        // The jerk-adjusted step rate at start of block
                final_rate,                          // The minimal rate at exit
                acceleration_steps_per_s2;           // acceleration steps/sec^2

  #if FAN_COUNT > 0
    unsigned long fan_speed[FAN_COUNT];
  #endif

  #if ENABLED(BARICUDA)
    unsigned long valve_pressure, e_to_p_pressure;
  #endif

  volatile char busy;

} block_t;

#define BLOCK_MOD(n) ((n)&(BLOCK_BUFFER_SIZE-1))

class Planner {

  public:

#if defined(ENABLE_AUTO_BED_LEVELING) || defined(MESH_BED_LEVELING)
void plan_buffer_line(float x, float y, float z, const float &e, float feed_rate, const uint8_t &extruder);

#ifdef ENABLE_AUTO_BED_LEVELING
  #include "vector_3.h"
  // this holds the required transform to compensate for bed level
  extern matrix_3x3 plan_bed_level_matrix;
  // Add a new linear movement to the buffer. x, y and z is the signed, absolute target position in 
  // millimaters. Feed rate specifies the speed of the motion.
  void plan_buffer_line(float x, float y, float z, const float &e, float feed_rate, const uint8_t &extruder);

  /**
   * Set the planner positions. Used for G92 instructions.
   * Multiplies by axis_steps_per_unit[] to set stepper positions.
   * Clears previous speed values.
   */
  void plan_set_position(float x, float y, float z, const float &e);
  #ifndef DELTA
    // Get the position applying the bed level matrix if enabled
    vector_3 plan_get_position();
  #endif
#else
void plan_buffer_line(const float &x, const float &y, const float &z, const float &e, float feed_rate, const uint8_t &extruder);
#endif  // ENABLE_AUTO_BED_LEVELING || MESH_BED_LEVELING

// Set position. Used for G92 instructions.
#if defined(ENABLE_AUTO_BED_LEVELING) || defined(MESH_BED_LEVELING)
void plan_set_position(float x, float y, float z, const float &e);
#else
void plan_set_position(const float &x, const float &y, const float &z, const float &e);
#endif // ENABLE_AUTO_BED_LEVELING || MESH_BED_LEVELING

void plan_set_e_position(const float& e);

//===========================================================================
//============================= public variables ============================
//===========================================================================

extern millis_t minsegmenttime;
extern float max_feedrate[NUM_AXIS]; // Max speeds in mm per minute
extern float axis_steps_per_unit[NUM_AXIS];
extern unsigned long max_acceleration_units_per_sq_second[NUM_AXIS]; // Use M201 to override by software
extern float minimumfeedrate;
extern float acceleration;         // Normal acceleration mm/s^2  DEFAULT ACCELERATION for all printing moves. M204 SXXXX
extern float retract_acceleration; // Retract acceleration mm/s^2 filament pull-back and push-forward while standing still in the other axes M204 TXXXX
extern float travel_acceleration;  // Travel acceleration mm/s^2  DEFAULT ACCELERATION for all NON printing moves. M204 MXXXX
extern float max_xy_jerk;          // The largest speed change requiring no acceleration
extern float max_z_jerk;
extern float max_e_jerk;
extern float mintravelfeedrate;
extern unsigned long axis_steps_per_sqr_second[NUM_AXIS];

#if ENABLED(AUTOTEMP)
  extern bool autotemp_enabled;
  extern float autotemp_max;
  extern float autotemp_min;
  extern float autotemp_factor;
#endif

};

#endif // PLANNER_H
