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
 * Portuguese
 *
 * LCD Menu Messages
 * See also https://github.com/MarlinFirmware/Marlin/wiki/LCD-Language
 *
 */
#ifndef LANGUAGE_PT_H
#define LANGUAGE_PT_H

#define MAPPER_NON
// Define SIMULATE_ROMFONT to see what is seen on the character based display defined in Configuration.h
//#define SIMULATE_ROMFONT
#define DISPLAY_CHARSET_ISO10646_1

#define WELCOME_MSG                         MACHINE_NAME " pronto."
#define MSG_SD_INSERTED                     "Cartao inserido"
#define MSG_SD_REMOVED                      "Cartao removido"
#define MSG_MAIN                            "Menu principal"
#define MSG_AUTOSTART                       "Autostart"
#define MSG_DISABLE_STEPPERS                "Desactivar motores"
#define MSG_AUTO_HOME                       "Ir para origem"
#define MSG_LEVEL_BED_HOMING                "Indo para origem"
#define MSG_SET_HOME_OFFSETS                "Definir desvio"
#define MSG_HOME_OFFSETS_APPLIED            "Offsets applied"
#define MSG_SET_ORIGIN                      "Definir origem"
#define MSG_PREHEAT_PLA                     "Pre-aquecer PLA"
#define MSG_PREHEAT_PLA0                    " pre-aquecer PLA 1"
#define MSG_PREHEAT_PLA1                    " pre-aquecer PLA 2"
#define MSG_PREHEAT_PLA2                    " pre-aquecer PLA 3"
#define MSG_PREHEAT_PLA3                    " pre-aquecer PLA 4"
#define MSG_PREHEAT_PLA0123                 " pre-aq. PLA Tudo"
#define MSG_PREHEAT_PLA_BEDONLY             " pre-aq. PLA \002Base"
#define MSG_PREHEAT_PLA_SETTINGS            "Definicoes PLA"
#define MSG_PREHEAT_ABS                     "Pre-aquecer ABS"
#define MSG_PREHEAT_ABS0                    " pre-aquecer ABS 1"
#define MSG_PREHEAT_ABS1                    " pre-aquecer ABS 2"
#define MSG_PREHEAT_ABS2                    " pre-aquecer ABS 3"
#define MSG_PREHEAT_ABS3                    " pre-aquecer ABS 4"
#define MSG_PREHEAT_ABS0123                 " pre-aq. ABS Tudo"
#define MSG_PREHEAT_ABS_BEDONLY             " pre-aq. ABS \002Base"
#define MSG_PREHEAT_ABS_SETTINGS            "Definicoes ABS"
#define MSG_COOLDOWN                        "Arrefecer"
#define MSG_SWITCH_PS_ON                    "Ligar"
#define MSG_SWITCH_PS_OFF                   "Desligar"
#define MSG_EXTRUDE                         "Extrudir"
#define MSG_RETRACT                         "Retrair"
#define MSG_MOVE_AXIS                       "Mover eixo"
#define MSG_MOVE_X                          "Mover X"
#define MSG_MOVE_Y                          "Mover Y"
#define MSG_MOVE_Z                          "Mover Z"
#define MSG_MOVE_E                          "Mover Extrusor"
#define MSG_MOVE_01MM                       "Mover 0.1mm"
#define MSG_MOVE_1MM                        "Mover 1mm"
#define MSG_MOVE_10MM                       "Mover 10mm"
#define MSG_SPEED                           "Velocidade:"
#define MSG_NOZZLE                          "\002Nozzle:"
#define MSG_NOZZLE1                         "\002Nozzle2:"
#define MSG_NOZZLE2                         "\002Nozzle3:"
#define MSG_BED                             "\002Base:"
#define MSG_FAN_SPEED                       "Velocidade ar"
#define MSG_FLOW                            "Fluxo:"
#define MSG_FLOW0                           "Fluxo0:"
#define MSG_FLOW1                           "Fluxo1:"
#define MSG_FLOW2                           "Fluxo2:"
#define MSG_CONTROL                         "Controlo \003"
#define MSG_MIN                             "\002 Min"
#define MSG_MAX                             "\002 Max"
#define MSG_FACTOR                          "\002 Fact"
#define MSG_AUTOTEMP                        "Autotemp"
#define MSG_ON                              "On "
#define MSG_OFF                             "Off"
#define MSG_PID_P                           "PID-P"
#define MSG_PID_I                           "PID-I"
#define MSG_PID_D                           "PID-D"
#define MSG_PID_C                           "PID-C"
#define MSG_E1                              "E1"
#define MSG_E2                              "E2"
#define MSG_E3                              "E3"
#define MSG_E4                              "E4"
#define MSG_ACC                             "Acc"
#define MSG_VXY_JERK                        "Vxy-jerk"
#define MSG_VZ_JERK                         "Vz-jerk"
#define MSG_VE_JERK                         "Ve-jerk"
#define MSG_VMAX                            " Vmax "
#define MSG_X                               "x"
#define MSG_Y                               "y"
#define MSG_Z                               "z"
#define MSG_E                               "e"
#define MSG_VMIN                            "Vmin"
#define MSG_VTRAV_MIN                       "VTrav min"
#define MSG_AMAX                            "Amax "
#define MSG_A_RETRACT                       "A-retract"
#define MSG_XSTEPS                          "X passo/mm"
#define MSG_YSTEPS                          "Y passo/mm"
#define MSG_ZSTEPS                          "Z passo/mm"
#define MSG_ESTEPS                          "E passo/mm"
#define MSG_TEMPERATURE                     "Temperatura"
#define MSG_MOTION                          "Movimento"
#define MSG_VOLUMETRIC                      "Filamento"
#define MSG_VOLUMETRIC_ENABLED		          "E in mm3"
#define MSG_FILAMENT_SIZE_EXTRUDER_0        "Fil. Dia. 1"
#define MSG_FILAMENT_SIZE_EXTRUDER_1        "Fil. Dia. 2"
#define MSG_FILAMENT_SIZE_EXTRUDER_2        "Fil. Dia. 3"
#define MSG_CONTRAST                        "Contraste"
#define MSG_STORE_EPROM                     "Guardar na memoria"
#define MSG_LOAD_EPROM                      "Carregar da memoria"
#define MSG_RESTORE_FAILSAFE                "Rest. de emergen."
#define MSG_REFRESH                         "\004Recarregar"
#define MSG_WATCH                           "Monitorar   \003"
#define MSG_PREPARE                         "Preparar \x7E"
#define MSG_TUNE                            "Afinar   \x7E"
#define MSG_PAUSE_PRINT                     "Pausa impressao"
#define MSG_RESUME_PRINT                    "Retomar impressao"
#define MSG_STOP_PRINT                      "Parar impressao"
#define MSG_CARD_MENU                       "Imprimir do SD"
#define MSG_NO_CARD                         "Sem cartao SD"
#define MSG_DWELL                           "Em espera..."
#define MSG_USERWAIT                        "A espera de ordem"
#define MSG_RESUMING                        "Retomando impressao"
#define MSG_PRINT_ABORTED                   "Impressao cancelada"
#define MSG_NO_MOVE                         "Sem movimento"
#define MSG_KILLED                          "PARADA DE EMERG."
#define MSG_STOPPED                         "PARADA. "
#define MSG_CONTROL_RETRACT                 " Retrair mm:"
#define MSG_CONTROL_RETRACT_SWAP            "Troca Retrair mm:"
#define MSG_CONTROL_RETRACTF                " Retrair  V:"
#define MSG_CONTROL_RETRACT_ZLIFT           " Levantar mm:"
#define MSG_CONTROL_RETRACT_RECOVER         " DesRet +mm:"
#define MSG_CONTROL_RETRACT_RECOVER_SWAP    "Troca DesRet +mm:"
#define MSG_CONTROL_RETRACT_RECOVERF        " DesRet  V:"
#define MSG_AUTORETRACT                     " Auto Retr.:"
#define MSG_FILAMENTCHANGE                  "Trocar filamento"
#define MSG_INIT_SDCARD                     "Cartao SD inic."
#define MSG_CNG_SDCARD                      "Cartao SD trocado"
#define MSG_ZPROBE_OUT                      "Sensor fora d base"
#define MSG_POSITION_UNKNOWN                "XY antes de Z"
#define MSG_ZPROBE_ZOFFSET                  "Desvio Z"
#define MSG_BABYSTEP_X                      "Babystep X"
#define MSG_BABYSTEP_Y                      "Babystep Y"
#define MSG_BABYSTEP_Z                      "Babystep Z"
#define MSG_ENDSTOP_ABORT                   "Fim de curso"
#define MSG_END_HOUR                        "horas"
#define MSG_END_MINUTE                      "minutos"

#define MSG_RECTRACT                        "Retrair"
#define MSG_MAIN_WIDE                       "Menu Principal  \003"
#define MSG_PREPARE_ALT                     "Preparar \003"
#define MSG_CONTROL_ARROW                   "Controlo \x7E"
#define MSG_RETRACT_ARROW                   "Retrair \x7E"
#define MSG_STEPPER_RELEASED                "Desengatado."

#define MSG_RECTRACT                        "Retrair"
#define MSG_MAIN_WIDE                       "Menu Principal  \003"
#define MSG_PREPARE_ALT                     "Preparar \003"
#define MSG_CONTROL_ARROW                   "Controle \x7E"
#define MSG_RETRACT_ARROW                   "Retrair \x7E"
#define MSG_STEPPER_RELEASED                "Iniciado."

#ifdef DELTA_CALIBRATION_MENU
    #define MSG_DELTA_CALIBRATE             "Calibracao Delta"
    #define MSG_DELTA_CALIBRATE_X           "Calibrar X"
    #define MSG_DELTA_CALIBRATE_Y           "Calibrar Y"
    #define MSG_DELTA_CALIBRATE_Z           "Calibrar Z"
    #define MSG_DELTA_CALIBRATE_CENTER      "Calibrar Centro"
#endif // DELTA_CALIBRATION_MENU

#endif // LANGUAGE_PT_H
