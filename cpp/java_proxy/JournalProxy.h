//
// Created by root on 2023/8/16.
//

#ifndef JOURNAL_JOURNALPROXY_H
#define JOURNAL_JOURNALPROXY_H


#include <kungfu/yijinjing/journal/frame.h>
#include <kungfu/yijinjing/journal/journal.h>

using namespace kungfu::yijinjing;


namespace JournalProxy {
    struct FrameProxy {
        journal::frame_ptr data;
    };

    struct WriterProxy {
        journal::writer_ptr data;
    };

    struct ReaderProxy {
        journal::reader_ptr data;
    };

}

#endif //JOURNAL_JOURNALPROXY_H
