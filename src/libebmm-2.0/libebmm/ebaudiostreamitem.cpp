#include "ebaudiostreamitem.h"
#include <QCoreApplication>
#include "ebtimegettime.h"
#include "ebvideodefine.h"

#define EB_MAX_AUDIO_FRAME_SIZE  8000

namespace entboost {

const int const_buffer_size = 32*1024;
EbAudioStreamItem::EbAudioStreamItem(mycp::bigint userId)
    : QObject(0)
    , m_userId(userId)
    , m_aacDecoder(0)
    , m_audioOutput(0)
    , m_streamOut(0)
    , m_nTimestampOfLastFrame(0)
    , m_nLastSequenceOfUpperFrame(0)
    , m_srcSampleRate(0)
    , m_srcChannels(0)
    , m_srcBitRate(0)
    , m_nPlayState(STATE_PLAY)
    , m_fnFFTcb(0)
    , m_fnFFTcb_param(0)
    , m_nHoldSize(0)

{
}

EbAudioStreamItem::~EbAudioStreamItem()
{
    close();
}

EbAudioStreamItem::pointer EbAudioStreamItem::create(mycp::bigint userId)
{
    return EbAudioStreamItem::pointer(new EbAudioStreamItem(userId));
}

bool EbAudioStreamItem::open(int srcSampleRate, int srcChannels)
{
    bool bret = false;
    if (m_aacDecoder!=0) {
        return true;
    }
    //// for test
//    srcChannels = 1;
//    srcSampleRate = 12000;
    EbAacEncoder aacEncoder(this);
    if (!aacEncoder.init(srcChannels, srcSampleRate, srcSampleRate*srcChannels)) {
        return false;
    }
    aacEncoder.stop();
    if (m_aacDecoder==0) {
        return false;
    }
    if (!m_aacDecoder->isInited()) {
        delete m_aacDecoder;
        m_aacDecoder = 0;
        return false;
    }
    QAudioFormat audioFormat;
    audioFormat.setSampleRate(srcSampleRate);
    audioFormat.setChannelCount(srcChannels);
    audioFormat.setSampleSize(16);
    audioFormat.setCodec("audio/pcm");
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    audioFormat.setSampleType(QAudioFormat::SignedInt);
    m_audioOutput = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), audioFormat);
    m_audioOutput->setBufferSize(6*1024);
    m_streamOut = m_audioOutput->start();
    return true;
}

void EbAudioStreamItem::close()
{
    if (m_aacDecoder!=0) {
        m_aacDecoder->stop();
        delete m_aacDecoder;
        m_aacDecoder = 0;
    }
    if (m_audioOutput!=0) {
        m_audioOutput->stop();
        delete m_audioOutput;
        m_audioOutput = 0;
    }
    m_streamOut = 0;
}

void EbAudioStreamItem::startPlay()
{
    m_nPlayState = STATE_PLAY;
    if (m_audioOutput!=0) {
        m_audioOutput->start();
    }
}

void EbAudioStreamItem::stopPlay()
{
    m_nPlayState = STATE_STOP;
    if (m_audioOutput!=0) {
        m_audioOutput->stop();
    }
}

void EbAudioStreamItem::setFFTCallback(FFTdataFn cb, void *userData)
{
    m_fnFFTcb = cb;
    m_fnFFTcb_param = userData;
}

void EbAudioStreamItem::enqueueFrame(mycp::bigint Id, const unsigned char *buf, unsigned int len, unsigned int ts)
{
    if (m_aacDecoder==0 || m_nPlayState!=STATE_PLAY) {
        return;
    }
    m_aacDecoder->decode(buf, len, (unsigned long)ts);
}

bool EbAudioStreamItem::isLimited()
{
    /// ??????5???????????????????????????
    return m_playVoiceList.size(false)>20?true:false;
}

bool EbAudioStreamItem::write(const EbAudioBuffer::pointer &audioBufferIn)
{
    if (m_aacDecoder==0) {
        return false;
    }

    if (isLimited()) {
        return false;
    }

    if (m_audioList.size()<100) {
        audioBufferIn->expire_ts = timeGetTime() + 1200;	// 3000; //800~1200ms
        m_audioList.add(audioBufferIn);
        return true;
    }
    else {
        return false;
    }

//    if (audioBufferIn->ts <= m_nTimestampOfLastFrame && (m_nTimestampOfLastFrame - audioBufferIn->ts <0xFFFF)) {
//        return false;
//    }
//    /// reset the expired time.
//    audioBufferIn->expire_ts = timeGetTime() + 1200;	// 3000; //800~1200ms
//    if (m_audioList.empty()) {
//        m_audioList.add(audioBufferIn);
//    }
//    else {
//        /// sort ascending
//        bool bfound = false;
//        EbAudioBuffer::pointer pAudioBuffer1;
//        {
//            BoostWriteLock wtlock(m_audioList.mutex());
//            CLockList<EbAudioBuffer::pointer>::iterator iter = m_audioList.begin();
//            for (;iter!=m_audioList.end();iter++) {
//                pAudioBuffer1 = (*iter);
//                if ( pAudioBuffer1->ts > audioBufferIn->ts) {
//                    bfound = true;
//                    break;
//                }
//                else if ((audioBufferIn->ts - pAudioBuffer1->ts) > 0xFFFF0000) {
//                    bfound = true;
//                    break;
//                }
//            }
//            if (bfound)
//                m_audioList.insert(iter, audioBufferIn);
//            else
//                m_audioList.push_back( audioBufferIn);
//        }
//    }
//    return true;
}

void EbAudioStreamItem::playBuffer(EbAudioBuffer::pointer &pOutBuffer)
{
    /// ????????????????????????????????????????????????.
//    if (isLimited() || m_audioList.empty()) {
//        return;
//    }

    writeVoiceData();

    EbAudioBuffer::pointer pAudioBuffer;
    if (m_audioList.front(pAudioBuffer)) {
        pOutBuffer = pAudioBuffer;
        /// ???????????????????????????
        if (pAudioBuffer->expire_ts > timeGetTime()) {
            enqueueFrame(pAudioBuffer->ssrc, pAudioBuffer->data, pAudioBuffer->len, pAudioBuffer->ts);
        }
//        bool bfound = false;
//        /// ????????????.
//        if (m_nLastSequenceOfUpperFrame == 0 ||
//            (unsigned short)(m_nLastSequenceOfUpperFrame + 1) == (unsigned short)pAudioBuffer->seq) {
//            bfound = true;
//            m_nLastSequenceOfUpperFrame = (unsigned short)pAudioBuffer->seq;
//            m_nTimestampOfLastFrame = pAudioBuffer->ts;
//            pOutBuffer = pAudioBuffer;
//            m_audioList.popfront();
//        }
//        else if (pAudioBuffer->expire_ts < timeGetTime()) {
//            /// ????????????
//            /// bfound = true;
//            m_nLastSequenceOfUpperFrame = (unsigned short)pAudioBuffer->seq;
//            m_nTimestampOfLastFrame = pAudioBuffer->ts;
//            pOutBuffer = pAudioBuffer;
//            m_audioList.popfront();
//        }
//        /// ????????????????????????????????????.
//        if (bfound) {
//            enqueueFrame(pAudioBuffer->ssrc, pAudioBuffer->data, pAudioBuffer->len, pAudioBuffer->ts);
//        }
    }
}

void EbAudioStreamItem::writeVoiceData(void)
{
    if (m_audioOutput!=0 && m_audioOutput->state()!=QAudio::StoppedState) {
//        if (m_audioOutput->state()==QAudio::SuspendedState) {
//            m_audioOutput->resume();
//        }
        EbVoiceBuffer::pointer pVoiceBuffer;
        /// ????????????????????????
        int writeSize = 0;
        while (writeSize<m_audioOutput->bytesFree() && m_playVoiceList.front(pVoiceBuffer)) {
            if ((writeSize+pVoiceBuffer->m_size)>=m_audioOutput->bytesFree()) {
                /// ??????????????????
                m_playVoiceList.pushfront(pVoiceBuffer);
                break;
            }
            m_streamOut->write((const char*)pVoiceBuffer->m_data, (qint64)pVoiceBuffer->m_size);
            writeSize += pVoiceBuffer->m_size;
            if (writeSize+pVoiceBuffer->m_size>m_audioOutput->bytesFree()) {
                break;
            }
        }

//        int chunks = m_audioOutput->bytesFree()/m_audioOutput->periodSize();
//        while (chunks!=0) {
//            int writeSize = 0;
//            while (m_playVoiceList.front(pVoiceBuffer)) {
//                if ((writeSize+pVoiceBuffer->m_size)>=m_audioOutput->periodSize()) {
//                    /// ??????????????????
//                    m_playVoiceList.pushfront(pVoiceBuffer);
//                    break;
//                }
//                m_streamOut->write((const char*)pVoiceBuffer->m_data, (qint64)pVoiceBuffer->m_size);
//                writeSize += pVoiceBuffer->m_size;
//                if (writeSize+pVoiceBuffer->m_size>m_audioOutput->periodSize()) {
//                    break;
//                }
//            }
//           --chunks;
//        }
    }
}

void EbAudioStreamItem::onEncodeInitOk(const unsigned char *decodeSCData, int size)
{
    if (m_aacDecoder==0) {
        m_aacDecoder = new EbAacDecoder(this);
    }
    if (!m_aacDecoder->isInited()) {
        m_aacDecoder->init(decodeSCData, size);
    }
}

void EbAudioStreamItem::onDecodeOk(const unsigned char *data, int size, unsigned long param)
{
    if (EbAacEncoder::DetectSilence(data, size)!=0) {
        /// ???????????????
        if (m_nHoldSize>0 && m_nHoldSize>=m_holdVoiceList.size())
        {
            /// 1??????
            const size_t nBeginIndex = m_holdVoiceList.size()-m_nHoldSize+1;
            size_t nCurrentIndex = 0;
            BoostReadLock rdLock(m_holdVoiceList.mutex());
            CLockList<EbVoiceBuffer::pointer>::iterator pIter = m_holdVoiceList.begin();
            for (; pIter!=m_holdVoiceList.end(); pIter++) {
                if ((++nCurrentIndex)<nBeginIndex) {
                    continue;
                }
                EbVoiceBuffer::pointer pVoiceBuffer = *pIter;
                m_playVoiceList.add(pVoiceBuffer);
                if (m_fnFFTcb!=0 && pVoiceBuffer->m_size>0) {
                    m_fnFFTcb(m_userId, (const char*)pVoiceBuffer->m_data, pVoiceBuffer->m_size, m_fnFFTcb_param);
                }
            }
            m_nHoldSize = 0;
        }
        EbVoiceBuffer::pointer pVoiceBuffer = EbVoiceBuffer::create(data, size);
        pVoiceBuffer->m_userId = this->m_userId;
        const unsigned int ts = (unsigned int)param;
        pVoiceBuffer->m_timestamp = ts;
        m_playVoiceList.add(pVoiceBuffer);
        if (m_fnFFTcb!=0 && pVoiceBuffer->m_size>0) {
            m_fnFFTcb(m_userId, (const char*)pVoiceBuffer->m_data, pVoiceBuffer->m_size, m_fnFFTcb_param);
        }
    }
    else {
        /// ????????????????????????????????????????????????????????????????????????????????????????????????
        EbVoiceBuffer::pointer pHoldBuffer;
        if (m_holdVoiceList.size()<6 || !m_holdVoiceList.front(pHoldBuffer)) {
            pHoldBuffer = EbVoiceBuffer::create();
            pHoldBuffer->m_data = new unsigned char[EB_MAX_AUDIO_FRAME_SIZE];
//            pHoldBuffer->m_pBuffer = new short[EB_MAX_AUDIO_FRAME_SIZE];
        }
        const unsigned int ts = (unsigned int)param;
        pHoldBuffer->m_timestamp = ts;
        pHoldBuffer->m_userId = m_userId;
        pHoldBuffer->m_size = MIN(EB_MAX_AUDIO_FRAME_SIZE, size);
        memcpy(pHoldBuffer->m_data, data, pHoldBuffer->m_size);
        m_holdVoiceList.add(pHoldBuffer);
        if (m_nHoldSize<(int)m_holdVoiceList.size()) {
            m_nHoldSize++;
        }
    }
}

}   /// namespace entboost
