
#include "qspice-helper.h"
#include "qspice-port-channel.h"

void QSpiceHelper::port_data(SpicePortChannel *spiceportchannel,
                             gpointer          arg1,
                             gint              arg2,
                             gpointer          user_data)
{
    // emitted when data is available for receiving from port
    Q_UNUSED(spiceportchannel)
    QSpicePortChannel *_port = static_cast<QSpicePortChannel*>(user_data);
    if ( nullptr==_port ) return;
    emit _port->portData(arg1, size_t(arg2));
}

void QSpiceHelper::port_event(SpicePortChannel *spiceportchannel,
                              gint              arg1,
                              gpointer          user_data)
{
    Q_UNUSED(spiceportchannel)
    QSpicePortChannel *_port = static_cast<QSpicePortChannel*>(user_data);
    if ( nullptr==_port ) return;
    emit _port->portEvent(arg1);
}

void QSpicePortChannel::initCallbacks()
{
    g_signal_connect(gobject, "port-data",
                     GCallback(QSpiceHelper::port_data), this);
    g_signal_connect(gobject, "port-event",
                     GCallback(QSpiceHelper::port_event), this);
}

void QSpicePortChannel::sendEventToPort(quint8 event)
{
#if SPICE_GTK_CHECK_VERSION(0, 35, 0)
    spice_port_channel_event(
#else
    spice_port_event(
#endif
                static_cast<SpicePortChannel*>(gobject),
                guint8(event));
}

void QSpicePortChannel::writeBuffToPort(const void *buff, size_t _size)
{
#if SPICE_GTK_CHECK_VERSION(0, 35, 0)
    spice_port_channel_write_async(
#else
    spice_port_write_async(
#endif
                static_cast<SpicePortChannel*>(gobject),
                buff,
                _size,
                nullptr,
                GAsyncReadyCallback(writeFinishToPort),
                this);
}

void QSpicePortChannel::writeFinishToPort(void *_port, void *_res, void *_errs)
{
    GAsyncResult *result = static_cast<GAsyncResult*>(_res);
    GError **errors = static_cast<GError**>(_errs);
#if SPICE_GTK_CHECK_VERSION(0, 35, 0)
    long ssize = spice_port_channel_write_finish(
#else
    long ssize = spice_port_write_finish(
#endif
                static_cast<SpicePortChannel*>(_port),
                result,
                errors);
    //QSpicePortChannel *obj = static_cast<QSpicePortChannel*>(
    //            g_async_result_get_user_data(result));
    size_t count = sizeof(errors)/sizeof(*errors);
    for ( uint i = 0; i<count; i++ ) {
        if ( nullptr==errors[i] ) continue;
        qDebug()<<errors[i]->code<< QString::fromUtf8(errors[i]->message);
    };
}
