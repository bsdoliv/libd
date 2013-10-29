/****************************************************************************
**
** Copyright (C) 2013 Andre Oliveira
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#ifndef DTCPSERVER_H
#define DTCPSERVER_H

#include "daemon.h"
#include "abstractsocket.h"
#include "hostaddress.h"

#include <sys/types.h>
#include <inttypes.h>

D_BEGIN_NAMESPACE

class TcpServerPrivate;
class TcpConnection;
class ConnectionData;
class TcpServer : public Daemon
{
public:
    explicit TcpServer();
    virtual ~TcpServer();

    virtual void run();

    bool listen(const HostAddress &address = HostAddress::Any, uint16_t port = 0);
    void close();

    bool isListening() const;

    void setMaxConnections(int numConnections);
    int maxConnections() const;

    uint16_t port() const;
    HostAddress address() const;

    qintptr socketDescriptor() const;
    bool setSocketDescriptor(qintptr socketDescriptor);

//    bool waitForNewConnection(int msec = 0, bool *timedOut = 0);
    bool hasConnections() const;

    AbstractSocket::SocketError serverError() const;
    QString errorString() const;
    virtual void newConnection(TcpConnection * c) = 0;
    void closeConnection(ConnectionData * data);

private:
    friend class TcpServerPrivate;
    TcpServerPrivate *d;

#if 0
    void pauseAccepting();
    void resumeAccepting();
#endif

#if 0
protected:
    virtual void incomingConnection(qintptr handle);
    void addPendingConnection(QTcpSocket* socket);

Q_SIGNALS:
    void acceptError(QAbstractSocket::SocketError socketError);
#endif
};

D_END_NAMESPACE

#endif // DTCPSERVER_H
