/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_huatai_ficc_aurora_journal_proxy_FrameNative */

#ifndef _Included_com_huatai_ficc_aurora_journal_proxy_FrameNative
#define _Included_com_huatai_ficc_aurora_journal_proxy_FrameNative
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_huatai_ficc_aurora_journal_proxy_FrameNative
 * Method:    destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_huatai_ficc_aurora_journal_proxy_FrameNative_destroy
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_huatai_ficc_aurora_journal_proxy_FrameNative
 * Method:    hasData
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_huatai_ficc_aurora_journal_proxy_FrameNative_hasData
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_huatai_ficc_aurora_journal_proxy_FrameNative
 * Method:    genTime
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_huatai_ficc_aurora_journal_proxy_FrameNative_genTime
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_huatai_ficc_aurora_journal_proxy_FrameNative
 * Method:    msgType
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_huatai_ficc_aurora_journal_proxy_FrameNative_msgType
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_huatai_ficc_aurora_journal_proxy_FrameNative
 * Method:    dataAsBytes
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_huatai_ficc_aurora_journal_proxy_FrameNative_dataAsBytes
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
