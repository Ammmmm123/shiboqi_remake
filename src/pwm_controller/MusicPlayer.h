#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QString>
#include <QMap>

/**
 * @brief 音符结构体
 */
struct Note {
    int frequency;  // 频率 (Hz)
    int duration;   // 时值 (ms)
};

/**
 * @brief 音乐播放器类
 * 
 * 解析音乐文本文件并通过PWM控制器播放音乐
 */
class MusicPlayer : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    explicit MusicPlayer(QObject *parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~MusicPlayer();
    
    /**
     * @brief 加载音乐文件
     * @param filePath 音乐文件路径
     * @return true=成功, false=失败
     */
    bool loadMusicFile(const QString& filePath);
    
    /**
     * @brief 开始播放
     */
    void play();
    
    /**
     * @brief 暂停播放
     */
    void pause();
    
    /**
     * @brief 停止播放
     */
    void stop();
    
    /**
     * @brief 检查是否正在播放
     * @return true=正在播放, false=未播放
     */
    bool isPlaying() const { return isPlaying_; }
    
    /**
     * @brief 获取当前播放进度
     * @return 当前音符索引
     */
    int getCurrentIndex() const { return currentIndex_; }
    
    /**
     * @brief 获取音乐总长度
     * @return 音符总数
     */
    int getTotalLength() const { return musicData_.size(); }
    
    /**
     * @brief 解析音符名称
     * @param noteName 音符名称字符串
     * @return 频率值,失败返回-1
     */
    int parseNoteName(const QString& noteName);

signals:
    /**
     * @brief 请求设置PWM频率信号
     * @param frequency 频率值（Hz）
     */
    void requestSetFrequency(int frequency);
    
    /**
     * @brief 播放完成信号
     */
    void playbackFinished();
    
    /**
     * @brief 播放进度更新信号
     * @param current 当前索引
     * @param total 总数
     */
    void progressUpdated(int current, int total);

private slots:
    /**
     * @brief 播放下一个音符
     */
    void playNextNote();

private:
    /**
     * @brief 初始化音符频率映射表
     */
    void initializeNoteMap();
    
    /**
     * @brief 解析时值表达式
     * @param expr 时值表达式字符串 (例如: "TT/8", "TT/4+TT/8")
     * @return 时值(毫秒)
     */
    int evaluateDuration(const QString& expr);

private:
    QTimer *playTimer_;              ///< 播放定时器
    QVector<Note> musicData_;        ///< 音乐数据（音符+时值序列）
    int currentIndex_;               ///< 当前播放索引
    bool isPlaying_;                 ///< 是否正在播放
    QMap<QString, int> noteFreqMap_; ///< 音符到频率的映射表
};

#endif // MUSIC_PLAYER_H
