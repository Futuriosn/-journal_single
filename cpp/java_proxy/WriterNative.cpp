//
// Created by root on 2023/8/16.
//

#include "com_huatai_ficc_aurora_journal_proxy_WriterNative.h"
#include "JournalProxy.h"
#include "kungfu/yijinjing/journal_wrapper.h"
#include "utils.h"

JNIEXPORT jlong JNICALL Java_com_huatai_ficc_aurora_journal_proxy_WriterNative_createWriter
        (JNIEnv *env, jclass, jstring home, jstring name, jint ps, jint destId, jboolean lazy) {
    auto wr = journal::create_writer(jstringToStdString(env, home),
                                     jstringToStdString(env, name),
                                     (data::page_size) ps,
                                     destId,
                                     lazy);
    auto writeProxy = new JournalProxy::WriterProxy();
    writeProxy->data = wr;
    return (long) writeProxy;
}

JNIEXPORT void JNICALL Java_com_huatai_ficc_aurora_journal_proxy_WriterNative_destroy
        (JNIEnv *, jclass, jlong pWriter) {
    auto *writerProxy = (JournalProxy::WriterProxy *) pWriter;
    delete writerProxy;
}

JNIEXPORT void JNICALL Java_com_huatai_ficc_aurora_journal_proxy_WriterNative_writeBytesWithTime
        (JNIEnv *env, jclass, jlong pWriter, jlong genTime, jint msgType, jbyteArray data, jint length) {
    auto *writerProxy = (JournalProxy::WriterProxy *) pWriter;
    auto *pBuffer = reinterpret_cast<char *>(env->GetByteArrayElements(data, nullptr));
    writerProxy->data->write_bytes_with_time(genTime, msgType, pBuffer, length);
}

JNIEXPORT void JNICALL Java_com_huatai_ficc_aurora_journal_proxy_WriterNative_writeBytes
(JNIEnv *env, jclass, jlong pWriter, jint msgType, jbyteArray data, jint length, jlong triggerTime) {
auto *writerProxy = (JournalProxy::WriterProxy *) pWriter;
auto *pBuffer = reinterpret_cast<char *>(env->GetByteArrayElements(data, nullptr));
writerProxy->data->write_bytes(msgType, pBuffer, length, triggerTime);
}