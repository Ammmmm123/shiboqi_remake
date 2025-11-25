#include "MusicPlayer.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegularExpression>

MusicPlayer::MusicPlayer(QObject *parent)
    : QObject(parent)
    , playTimer_(new QTimer(this))
    , currentIndex_(0)
    , isPlaying_(false)
{
    initializeNoteMap();
    
    // 注意: 不再使用timeout信号,而是用singleShot
    playTimer_->setSingleShot(true);
    connect(playTimer_, &QTimer::timeout, this, &MusicPlayer::playNextNote);
}

MusicPlayer::~MusicPlayer()
{
    stop();
}

void MusicPlayer::initializeNoteMap()
{
    // 低音音名F
    noteFreqMap_["L1"] = 349;
    noteFreqMap_["L2"] = 392;
    noteFreqMap_["L3"] = 440;
    noteFreqMap_["L4"] = 466;
    noteFreqMap_["L5"] = 523;
    noteFreqMap_["L6"] = 587;
    noteFreqMap_["L7"] = 659;
    
    // 中音音名F
    noteFreqMap_["M1"] = 698;
    noteFreqMap_["M2"] = 784;
    noteFreqMap_["M3"] = 880;
    noteFreqMap_["M4"] = 932;
    noteFreqMap_["M5"] = 1047;
    noteFreqMap_["M6"] = 1175;
    noteFreqMap_["M7"] = 1319;
    
    // 高音音名F
    noteFreqMap_["H1"] = 1397;
    noteFreqMap_["H2"] = 1568;
    noteFreqMap_["H3"] = 1760;
    noteFreqMap_["H4"] = 1865;
    
    // 静音
    noteFreqMap_["0"] = 0;
}

int MusicPlayer::parseNoteName(const QString& noteName)
{
    QString trimmed = noteName.trimmed().toUpper();
    
    if (noteFreqMap_.contains(trimmed)) {
        return noteFreqMap_[trimmed];
    }
    
    return -1; // 无效音符
}

bool MusicPlayer::loadMusicFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "[音乐播放器] 无法打开文件:" << filePath;
        return false;
    }
    
    musicData_.clear();
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    
    // 查找 MyScore 数组
    QRegularExpression scoreRegex(R"(\{([^}]+)\})");
    QRegularExpressionMatchIterator it = scoreRegex.globalMatch(content);
    
    int validNotes = 0;
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        QString pairContent = match.captured(1);
        
        // 分割音符和时值
        QStringList parts = pairContent.split(',');
        if (parts.size() != 2) continue;
        
        QString noteName = parts[0].trimmed();
        QString durationStr = parts[1].trimmed();
        
        // 解析音符名称
        int frequency = parseNoteName(noteName);
        if (frequency < 0) continue;
        
        // 解析时值表达式 (例如: TT/8, TT/4+TT/8)
        int duration = evaluateDuration(durationStr);
        if (duration <= 0) continue;
        
        Note note;
        note.frequency = frequency;
        note.duration = duration;
        musicData_.append(note);
        validNotes++;
    }
    
    qDebug() << "[音乐播放器] 加载成功:" << filePath;
    qDebug() << "[音乐播放器] 音符总数:" << validNotes;
    
    return validNotes > 0;
}

void MusicPlayer::play()
{
    if (musicData_.isEmpty()) {
        qDebug() << "[音乐播放器] 没有加载音乐数据";
        return;
    }
    
    if (isPlaying_) {
        qDebug() << "[音乐播放器] 已在播放中";
        return;
    }
    
    isPlaying_ = true;
    currentIndex_ = 0;
    
    qDebug() << "[音乐播放器] 开始播放，总长度:" << musicData_.size();
    playNextNote();
}

void MusicPlayer::pause()
{
    if (!isPlaying_) return;
    
    isPlaying_ = false;
    playTimer_->stop();
    
    // 发送静音
    emit requestSetFrequency(0);
    
    qDebug() << "[音乐播放器] 已暂停";
}

void MusicPlayer::stop()
{
    pause();
    currentIndex_ = 0;
    emit progressUpdated(0, musicData_.size());
    qDebug() << "[音乐播放器] 已停止";
}

int MusicPlayer::evaluateDuration(const QString& expr)
{
    // 解析时值表达式,例如 "TT/8", "TT/4+TT/8"
    QString trimmed = expr.trimmed();
    
    // TT = 2000ms
    const int TT = 2000;
    
    // 替换TT为实际数值
    QString processed = trimmed;
    processed.replace("TT", QString::number(TT));
    
    // 处理加法
    QStringList addParts = processed.split('+');
    int result = 0;
    
    for (const QString& part : addParts) {
        QString p = part.trimmed();
        
        // 处理除法
        if (p.contains('/')) {
            QStringList divParts = p.split('/');
            if (divParts.size() == 2) {
                bool ok1, ok2;
                int numerator = divParts[0].trimmed().toInt(&ok1);
                int denominator = divParts[1].trimmed().toInt(&ok2);
                if (ok1 && ok2 && denominator != 0) {
                    result += numerator / denominator;
                }
            }
        } else {
            // 直接是数字
            bool ok;
            int val = p.toInt(&ok);
            if (ok) {
                result += val;
            }
        }
    }
    
    return result;
}

void MusicPlayer::playNextNote()
{
    if (!isPlaying_) return;
    
    if (currentIndex_ >= musicData_.size()) {
        // 播放完成,循环播放
        currentIndex_ = 0;
        qDebug() << "[音乐播放器] 循环播放";
    }
    
    Note currentNote = musicData_[currentIndex_];
    
    // 发送频率设置请求
    emit requestSetFrequency(currentNote.frequency);
    
    // 更新进度
    emit progressUpdated(currentIndex_ + 1, musicData_.size());
    
    currentIndex_++;
    
    // 根据当前音符的时值设置下一次触发时间
    playTimer_->start(currentNote.duration);
}
