//
// Created by root on 2023/8/16.
//

#include "com_huatai_ficc_aurora_journal_proxy_FrameNative.h"
#include "JournalProxy.h"

JNIEXPORT void JNICALL Java_com_huatai_ficc_aurora_journal_proxy_FrameNative_destroy
        (JNIEnv *, jclass, jlong pFrame) {
    auto *frameProxy = (JournalProxy::FrameProxy *) pFrame;
    delete frameProxy;
}

JNIEXPORT jboolean JNICALL Java_com_huatai_ficc_aurora_journal_proxy_FrameNative_hasData
        (JNIEnv *, jclass, jlong pFrame) {
    auto *frameProxy = (JournalProxy::FrameProxy *) pFrame;
    return frameProxy->data->has_data();
}

JNIEXPORT jlong JNICALL Java_com_huatai_ficc_aurora_journal_proxy_FrameNative_genTime
        (JNIEnv *, jclass, jlong pFrame) {
    auto *frameProxy = (JournalProxy::FrameProxy *) pFrame;
    return frameProxy->data->gen_time();
}

JNIEXPORT jint JNICALL Java_com_huatai_ficc_aurora_journal_proxy_FrameNative_msgType
        (JNIEnv *, jclass, jlong pFrame) {
    auto *frameProxy = (JournalProxy::FrameProxy *) pFrame;
    return frameProxy->data->msg_type();
}

JNIEXPORT jbyteArray JNICALL Java_com_huatai_ficc_aurora_journal_proxy_FrameNative_dataAsBytes
        (JNIEnv *env, jclass, jlong pFrame) {
    auto *frameProxy = (JournalProxy::FrameProxy *) pFrame;
    auto data_length = frameProxy->data->data_length();
    auto pData = frameProxy->data->data_as_bytes();

    jbyteArray result;
    result = env->NewByteArray(data_length);
    env->SetByteArrayRegion(result, 0, data_length, (jbyte *) pData);

    return result;
}
