/**
 ** This file is part of the G-TimeTracker project.
 ** Copyright 2015-2016 Nikita Krupenko <krnekit@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef DATASYNCER_H
#define DATASYNCER_H

#include <QObject>
#include <QUrl>
#include <QDateTime>

class QThread;

class TimeLogHistory;
class DataSyncerWorker;

class DataSyncer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    Q_PROPERTY(bool notifySync MEMBER m_notifySync NOTIFY notifySyncChanged)
    Q_PROPERTY(bool notifyNextSync MEMBER m_notifyNextSync NOTIFY notifyNextSyncChanged)
    Q_PROPERTY(bool autoSync MEMBER m_autoSync WRITE setAutoSync NOTIFY autoSyncChanged)
    Q_PROPERTY(int syncCacheSize MEMBER m_syncCacheSize WRITE setSyncCacheSize NOTIFY syncCacheSizeChanged)
    Q_PROPERTY(int syncCacheTimeout MEMBER m_syncCacheTimeout WRITE setSyncCacheTimeout NOTIFY syncCacheTimeoutChanged)
    Q_PROPERTY(QUrl syncPath MEMBER m_syncPath WRITE setSyncPath NOTIFY syncPathChanged)
public:
    explicit DataSyncer(TimeLogHistory *history, QObject *parent = 0);
    virtual ~DataSyncer();

    void init(const QString &dataPath);
    void pack(const QDateTime &start = QDateTime::currentDateTimeUtc());

    bool isRunning() const;

    void setAutoSync(bool autoSync);
    void setSyncCacheSize(int syncCacheSize);
    void setSyncCacheTimeout(int syncCacheTimeout);
    void setSyncPath(const QUrl &syncPathUrl);
    void setNoPack(bool noPack);

signals:
    void isRunningChanged(bool newIsRunning) const;
    void notifySyncChanged(bool newNotifySync) const;
    void notifyNextSyncChanged(bool newNotifyNextSync) const;
    void autoSyncChanged(bool newAutoSync) const;
    void syncCacheSizeChanged(int newSyncCacheSize) const;
    void syncCacheTimeoutChanged(int newSyncCacheTimeout) const;
    void syncPathChanged(const QUrl &newSyncPath) const;
    void error(const QString &errorText) const;
    void synced(QPrivateSignal);

public slots:
    void sync(const QDateTime &start = QDateTime::currentDateTimeUtc());

private slots:
    void syncError(const QString &errorText);
    void syncFinished();
    void syncStarted();
    void syncStopped();

private:
    void setIsRunning(bool isRunning);
    bool m_isRunning;
    bool m_notifySync;
    bool m_notifyNextSync;
    bool m_autoSync;
    int m_syncCacheSize;
    int m_syncCacheTimeout;
    QUrl m_syncPath;
    QThread *m_thread;
    DataSyncerWorker *m_worker;
};

#endif // DATASYNCER_H
