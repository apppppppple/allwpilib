// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <jni.h>

#include <wpi/jni_util.h>

#include "HALUtil.h"
#include "edu_wpi_first_hal_PowerDistributionJNI.h"
#include "hal/Ports.h"
#include "hal/PowerDistribution.h"

using namespace hal;

static_assert(edu_wpi_first_hal_PowerDistributionJNI_AUTOMATIC_TYPE ==
              HAL_PowerDistributionType::HAL_PowerDistributionType_kAutomatic);
static_assert(edu_wpi_first_hal_PowerDistributionJNI_CTRE_TYPE ==
              HAL_PowerDistributionType::HAL_PowerDistributionType_kCTRE);
static_assert(edu_wpi_first_hal_PowerDistributionJNI_REV_TYPE ==
              HAL_PowerDistributionType::HAL_PowerDistributionType_kRev);
static_assert(edu_wpi_first_hal_PowerDistributionJNI_DEFAULT_MODULE ==
              HAL_DEFAULT_POWER_DISTRIBUTION_MODULE);

extern "C" {

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    initialize
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_initialize
  (JNIEnv* env, jclass, jint module, jint type)
{
  int32_t status = 0;
  auto stack = wpi::java::GetJavaStackTrace(env, "edu.wpi.first");
  auto handle = HAL_InitializePowerDistribution(
      module, static_cast<HAL_PowerDistributionType>(type), stack.c_str(),
      &status);
  CheckStatusForceThrow(env, status);
  return static_cast<jint>(handle);
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    free
 * Signature: (I)V
 */
JNIEXPORT void JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_free
  (JNIEnv*, jclass, jint handle)
{
  HAL_CleanPowerDistribution(handle);
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    getModuleNumber
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_getModuleNumber
  (JNIEnv* env, jclass, jint handle)
{
  int32_t status = 0;
  auto result = HAL_GetPowerDistributionModuleNumber(handle, &status);
  CheckStatus(env, status, false);
  return result;
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    checkChannel
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_checkChannel
  (JNIEnv* env, jclass, jint handle, jint channel)
{
  return HAL_CheckPowerDistributionChannel(handle, channel);
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    checkModule
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_checkModule
  (JNIEnv* env, jclass, jint module, jint type)
{
  return HAL_CheckPowerDistributionModule(
      module, static_cast<HAL_PowerDistributionType>(type));
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    getType
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_getType
  (JNIEnv* env, jclass, jint handle)
{
  int32_t status = 0;
  auto result = HAL_GetPowerDistributionType(handle, &status);
  CheckStatus(env, status);
  return result;
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    getNumChannels
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_getNumChannels
  (JNIEnv* env, jclass, jint handle)
{
  int32_t status = 0;
  auto result = HAL_GetPowerDistributionNumChannels(handle, &status);
  CheckStatus(env, status);
  return result;
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    getTemperature
 * Signature: (I)D
 */
JNIEXPORT jdouble JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_getTemperature
  (JNIEnv* env, jclass, jint handle)
{
  int32_t status = 0;
  double temperature = HAL_GetPowerDistributionTemperature(handle, &status);
  CheckStatus(env, status, false);
  return temperature;
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    getVoltage
 * Signature: (I)D
 */
JNIEXPORT jdouble JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_getVoltage
  (JNIEnv* env, jclass, jint handle)
{
  int32_t status = 0;
  double voltage = HAL_GetPowerDistributionVoltage(handle, &status);
  CheckStatus(env, status, false);
  return voltage;
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    getChannelCurrent
 * Signature: (II)D
 */
JNIEXPORT jdouble JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_getChannelCurrent
  (JNIEnv* env, jclass, jint handle, jint channel)
{
  int32_t status = 0;
  double current =
      HAL_GetPowerDistributionChannelCurrent(handle, channel, &status);
  CheckStatus(env, status, false);
  return current;
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    getAllCurrents
 * Signature: (I[D)V
 */
JNIEXPORT void JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_getAllCurrents
  (JNIEnv* env, jclass, jint handle, jdoubleArray jarr)
{
  double storage[16];
  int32_t status = 0;
  // TODO fix me
  HAL_GetPowerDistributionAllChannelCurrents(handle, storage, 16, &status);
  if (!CheckStatus(env, status, false)) {
    return;
  }

  env->SetDoubleArrayRegion(jarr, 0, 16, storage);
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    getTotalCurrent
 * Signature: (I)D
 */
JNIEXPORT jdouble JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_getTotalCurrent
  (JNIEnv* env, jclass, jint handle)
{
  int32_t status = 0;
  double current = HAL_GetPowerDistributionTotalCurrent(handle, &status);
  CheckStatus(env, status, false);
  return current;
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    getTotalPower
 * Signature: (I)D
 */
JNIEXPORT jdouble JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_getTotalPower
  (JNIEnv* env, jclass, jint handle)
{
  int32_t status = 0;
  double power = HAL_GetPowerDistributionTotalPower(handle, &status);
  CheckStatus(env, status, false);
  return power;
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    getTotalEnergy
 * Signature: (I)D
 */
JNIEXPORT jdouble JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_getTotalEnergy
  (JNIEnv* env, jclass, jint handle)
{
  int32_t status = 0;
  double energy = HAL_GetPowerDistributionTotalEnergy(handle, &status);
  CheckStatus(env, status, false);
  return energy;
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    resetTotalEnergy
 * Signature: (I)V
 */
JNIEXPORT void JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_resetTotalEnergy
  (JNIEnv* env, jclass, jint handle)
{
  int32_t status = 0;
  HAL_ResetPowerDistributionTotalEnergy(handle, &status);
  CheckStatus(env, status, false);
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    clearStickyFaults
 * Signature: (I)V
 */
JNIEXPORT void JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_clearStickyFaults
  (JNIEnv* env, jclass, jint handle)
{
  int32_t status = 0;
  HAL_ClearPowerDistributionStickyFaults(handle, &status);
  CheckStatus(env, status, false);
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    setSwitchableChannel
 * Signature: (IZ)V
 */
JNIEXPORT void JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_setSwitchableChannel
  (JNIEnv* env, jclass, jint handle, jboolean enabled)
{
  int32_t status = 0;
  HAL_SetPowerDistributionSwitchableChannel(handle, enabled, &status);
  CheckStatus(env, status, false);
}

/*
 * Class:     edu_wpi_first_hal_PowerDistributionJNI
 * Method:    getSwitchableChannel
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL
Java_edu_wpi_first_hal_PowerDistributionJNI_getSwitchableChannel
  (JNIEnv* env, jclass, jint handle)
{
  int32_t status = 0;
  auto state = HAL_GetPowerDistributionSwitchableChannel(handle, &status);
  CheckStatus(env, status, false);
  return state;
}

}  // extern "C"
