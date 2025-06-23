//
// Created by root on 2023/8/16.
//


#include "com_huatai_ficc_aurora_journal_proxy_ReaderNative.h"
#include "JournalProxy.h"
#include "kungfu/yijinjing/journal_wrapper.h"
#include "utils.h"


JNIEXPORT void JNICALL Java_com_huatai_ficc_aurora_journal_proxy_ReaderNative_destroy
        (JNIEnv *, jclass, jlong pReader) {
    auto *readerProxy = (JournalProxy::ReaderProxy *) pReader;
    delete readerProxy;
}

JNIEXPORT jlong JNICALL Java_com_huatai_ficc_aurora_journal_proxy_ReaderNative_createReader
        (JNIEnv *, jclass, jboolean lazy) {
    auto readerProxy = new JournalProxy::ReaderProxy();
    readerProxy->data = journal::create_reader(lazy);
    return (long) readerProxy;
}

JNIEXPORT jint JNICALL Java_com_huatai_ficc_aurora_journal_proxy_ReaderNative_join
        (JNIEnv *env, jclass, jlong pReader, jstring home, jstring name, jlong fromTime, jint ps, jint destId) {
    auto *readerProxy = (JournalProxy::ReaderProxy *) pReader;
    return journal::reader_join(readerProxy->data,
                                jstringToStdString(env, home),
                                jstringToStdString(env, name),
                                fromTime,
                                (data::page_size) ps,
                                destId);
}

JNIEXPORT void JNICALL Java_com_huatai_ficc_aurora_journal_proxy_ReaderNative_disJoin
        (JNIEnv *, jclass, jlong pReader, jint location_uid) {
    auto *readerProxy = (JournalProxy::ReaderProxy *) pReader;
    readerProxy->data->disjoin(location_uid);
}

JNIEXPORT jboolean JNICALL Java_com_huatai_ficc_aurora_journal_proxy_ReaderNative_dataAvailable
        (JNIEnv *, jclass, jlong pReader) {
    auto *readerProxy = (JournalProxy::ReaderProxy *) pReader;
    return readerProxy->data->data_available();
}

JNIEXPORT void JNICALL Java_com_huatai_ficc_aurora_journal_proxy_ReaderNative_seekToTime
        (JNIEnv *, jclass, jlong pReader, jlong nanoTime) {
    auto *readerProxy = (JournalProxy::ReaderProxy *) pReader;
    return readerProxy->data->seek_to_time(nanoTime);
}

JNIEXPORT jlong JNICALL Java_com_huatai_ficc_aurora_journal_proxy_ReaderNative_currentFrame
        (JNIEnv *, jclass, jlong pReader) {
    auto *readerProxy = (JournalProxy::ReaderProxy *) pReader;
    auto frame = readerProxy->data->current_frame();
    if (frame) {
        auto pFrame = new JournalProxy::FrameProxy();
        pFrame->data = frame;
        return (long) pFrame;
    } else {
        return 0;
    }
}

JNIEXPORT void JNICALL Java_com_huatai_ficc_aurora_journal_proxy_ReaderNative_next
        (JNIEnv *, jclass, jlong pReader) {
    auto *readerProxy = (JournalProxy::ReaderProxy *) pReader;
    readerProxy->data->next();
}
