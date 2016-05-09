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
 * temperature.h - temperature controller
 */

#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "Marlin.h"
#include "planner.h"

#if ENABLED(PID_ADD_EXTRUSION_RATE)
  #include "stepper.h"
#endif

#ifndef SOFT_PWM_SCALE
  #define SOFT_PWM_SCALE 0
#endif

class Temperature {

  public:

    int current_temperature_raw[EXTRUDERS] = { 0 };
    float current_temperature[EXTRUDERS] = { 0.0 };
    int target_temperature[EXTRUDERS] = { 0 };

    int current_temperature_bed_raw = 0;
    float current_temperature_bed = 0.0;
    int target_temperature_bed = 0;

    #if ENABLED(TEMP_SENSOR_1_AS_REDUNDANT)
      float redundant_temperature = 0.0;
    #endif

    unsigned char soft_pwm_bed;

    #if ENABLED(FAN_SOFT_PWM)
      unsigned char fanSpeedSoftPwm[FAN_COUNT];
    #endif

    #if ENABLED(PIDTEMP) || ENABLED(PIDTEMPBED)
      #define PID_dT ((OVERSAMPLENR * 12.0)/(F_CPU / 64.0 / 256.0))
    #endif

    #if ENABLED(PIDTEMP)

      #if ENABLED(PID_PARAMS_PER_EXTRUDER)

        static float Kp[EXTRUDERS], Ki[EXTRUDERS], Kd[EXTRUDERS];
        #if ENABLED(PID_ADD_EXTRUSION_RATE)
          float Kc[EXTRUDERS];
        #endif
        #define PID_PARAM(param, e) Temperature::param[e]

      #else

        static float Kp, Ki, Kd;
        #if ENABLED(PID_ADD_EXTRUSION_RATE)
          static float Kc;
        #endif
        #define PID_PARAM(param, e) Temperature::param

      #endif // PID_PARAMS_PER_EXTRUDER

      // Apply the scale factors to the PID values
      #define scalePID_i(i)   ( (i) * PID_dT )
      #define unscalePID_i(i) ( (i) / PID_dT )
      #define scalePID_d(d)   ( (d) / PID_dT )
      #define unscalePID_d(d) ( (d) * PID_dT )

    #endif

    #if ENABLED(PIDTEMPBED)
      float bedKp = DEFAULT_bedKp,
            bedKi = ((DEFAULT_bedKi) * PID_dT),
            bedKd = ((DEFAULT_bedKd) / PID_dT);
    #endif

    #if ENABLED(BABYSTEPPING)
      volatile int babystepsTodo[3] = { 0 };
    #endif

    #if ENABLED(THERMAL_PROTECTION_HOTENDS) && WATCH_TEMP_PERIOD > 0
      int watch_target_temp[EXTRUDERS] = { 0 };
      millis_t watch_heater_next_ms[EXTRUDERS] = { 0 };
    #endif

#if (defined (THERMAL_RUNAWAY_PROTECTION_PERIOD) && THERMAL_RUNAWAY_PROTECTION_PERIOD > 0) || (defined (THERMAL_RUNAWAY_PROTECTION_BED_PERIOD) && THERMAL_RUNAWAY_PROTECTION_BED_PERIOD > 0)
void thermal_runaway_protection(int *state, unsigned long *timer, float temperature, float target_temperature, int heater_id, int period_seconds, int hysteresis_degc);
static int thermal_runaway_state_machine[4]; // = {0,0,0,0};
static unsigned long thermal_runaway_timer[4]; // = {0,0,0,0};
static bool thermal_runaway = false;
#if TEMP_SENSOR_BED != 0
  static int thermal_runaway_bed_state_machine;
  static unsigned long thermal_runaway_bed_timer;
#endif
#endif

    #if ENABLED(FILAMENT_WIDTH_SENSOR)
      int current_raw_filwidth = 0;  //Holds measured filament diameter - one extruder only
    #endif

  public:

    /**
     * Static (class) methods
     */
    static float analog2temp(int raw, uint8_t e);
    static float analog2tempBed(int raw);

    /**
     * Instance Methods
     */

    Temperature();

    void init();

    /**
     * Called from the Temperature ISR
     */
    void isr();

    /**
     * Call periodically to manage heaters
     */
    void manage_heater();

    #if ENABLED(FILAMENT_WIDTH_SENSOR)
      float analog2widthFil(); // Convert raw Filament Width to millimeters
      int widthFil_to_size_ratio(); // Convert raw Filament Width to an extrusion ratio
    #endif


    //high level conversion routines, for use outside of temperature.cpp
    //inline so that there is no performance decrease.
    //deg=degreeCelsius

    FORCE_INLINE float degHotend(uint8_t extruder) { return current_temperature[extruder]; }
    FORCE_INLINE float degBed() { return current_temperature_bed; }

    #if ENABLED(SHOW_TEMP_ADC_VALUES)
    FORCE_INLINE float rawHotendTemp(uint8_t extruder) { return current_temperature_raw[extruder]; }
    FORCE_INLINE float rawBedTemp() { return current_temperature_bed_raw; }
    #endif

    FORCE_INLINE float degTargetHotend(uint8_t extruder) { return target_temperature[extruder]; }
    FORCE_INLINE float degTargetBed() { return target_temperature_bed; }

    #if ENABLED(THERMAL_PROTECTION_HOTENDS) && WATCH_TEMP_PERIOD > 0
      void start_watching_heater(int e = 0);
    #endif

    #if ENABLED(THERMAL_PROTECTION_BED) && WATCH_BED_TEMP_PERIOD > 0
      void start_watching_bed();
    #endif

    FORCE_INLINE void setTargetHotend(const float& celsius, uint8_t extruder) {
      target_temperature[extruder] = celsius;
      #if ENABLED(THERMAL_PROTECTION_HOTENDS) && WATCH_TEMP_PERIOD > 0
        start_watching_heater(extruder);
      #endif
    }

    FORCE_INLINE void setTargetBed(const float& celsius) {
      target_temperature_bed = celsius;
      #if ENABLED(THERMAL_PROTECTION_BED) && WATCH_BED_TEMP_PERIOD > 0
        start_watching_bed();
      #endif
    }

    FORCE_INLINE bool isHeatingHotend(uint8_t extruder) { return target_temperature[extruder] > current_temperature[extruder]; }
    FORCE_INLINE bool isHeatingBed() { return target_temperature_bed > current_temperature_bed; }

    FORCE_INLINE bool isCoolingHotend(uint8_t extruder) { return target_temperature[extruder] < current_temperature[extruder]; }
    FORCE_INLINE bool isCoolingBed() { return target_temperature_bed < current_temperature_bed; }

    /**
     * The software PWM power for a heater
     */
    int getHeaterPower(int heater);

    /**
     * Switch off all heaters, set all target temperatures to 0
     */
    void disable_all_heaters();

    /**
     * Perform auto-tuning for hotend or bed in response to M303
     */
    #if HAS_PID_HEATING
      void PID_autotune(float temp, int extruder, int ncycles, bool set_result=false);
    #endif

    /**
     * Update the temp manager when PID values change
     */
    void updatePID();

    FORCE_INLINE void autotempShutdown() {
      #if ENABLED(AUTOTEMP)
        if (planner.autotemp_enabled) {
          planner.autotemp_enabled = false;
          if (degTargetHotend(active_extruder) > planner.autotemp_min)
            setTargetHotend(0, active_extruder);
        }
      #endif
    }

    #if ENABLED(BABYSTEPPING)

      FORCE_INLINE void babystep_axis(AxisEnum axis, int distance) {
        #if ENABLED(COREXY) || ENABLED(COREXZ)
          #if ENABLED(BABYSTEP_XY)
            switch (axis) {
              case X_AXIS: // X on CoreXY and CoreXZ
                babystepsTodo[A_AXIS] += distance * 2;
                babystepsTodo[CORE_AXIS_2] += distance * 2;
                break;
              case CORE_AXIS_2: // Y on CoreXY, Z on CoreXZ
                babystepsTodo[A_AXIS] += distance * 2;
                babystepsTodo[CORE_AXIS_2] -= distance * 2;
                break;
              case CORE_AXIS_3: // Z on CoreXY, Y on CoreXZ
                babystepsTodo[CORE_AXIS_3] += distance;
                break;
            }
          #elif ENABLED(COREXZ)
            babystepsTodo[A_AXIS] += distance * 2;
            babystepsTodo[C_AXIS] -= distance * 2;
          #else
            babystepsTodo[Z_AXIS] += distance;
          #endif
        #else
          babystepsTodo[axis] += distance;
        #endif
      }

    #endif // BABYSTEPPING

  private:

    void set_current_temp_raw();

    void updateTemperaturesFromRawValues();

    #if ENABLED(HEATER_0_USES_MAX6675)
      int read_max6675();
    #endif

    void checkExtruderAutoFans();

    float get_pid_output(int e);

    #if ENABLED(PIDTEMPBED)
      float get_pid_output_bed();
    #endif

    void _temp_error(int e, const char* serial_msg, const char* lcd_msg);
    void min_temp_error(uint8_t e);
    void max_temp_error(uint8_t e);

    #if ENABLED(THERMAL_PROTECTION_HOTENDS) || HAS_THERMALLY_PROTECTED_BED

      typedef enum TRState { TRInactive, TRFirstHeating, TRStable, TRRunaway } TRstate;

      void thermal_runaway_protection(TRState* state, millis_t* timer, float temperature, float target_temperature, int heater_id, int period_seconds, int hysteresis_degc);

      #if ENABLED(THERMAL_PROTECTION_HOTENDS)
        TRState thermal_runaway_state_machine[EXTRUDERS] = { TRInactive };
        millis_t thermal_runaway_timer[EXTRUDERS] = { 0 };
      #endif

      #if HAS_THERMALLY_PROTECTED_BED
        TRState thermal_runaway_bed_state_machine = TRInactive;
        millis_t thermal_runaway_bed_timer;
      #endif

    #endif // THERMAL_PROTECTION

};

extern Temperature thermalManager;

#endif // TEMPERATURE_H
