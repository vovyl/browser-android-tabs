// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_ICE_CONNECTION_TO_HOST_H_
#define REMOTING_PROTOCOL_ICE_CONNECTION_TO_HOST_H_

#include <memory>
#include <set>
#include <string>

#include "base/callback_forward.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/sequence_checker.h"
#include "base/single_thread_task_runner.h"
#include "remoting/proto/internal.pb.h"
#include "remoting/protocol/channel_dispatcher_base.h"
#include "remoting/protocol/clipboard_filter.h"
#include "remoting/protocol/connection_to_host.h"
#include "remoting/protocol/errors.h"
#include "remoting/protocol/ice_transport.h"
#include "remoting/protocol/input_filter.h"
#include "remoting/protocol/monitored_video_stub.h"
#include "remoting/protocol/session.h"
#include "remoting/protocol/session_config.h"

namespace remoting {
namespace protocol {

class AudioDecodeScheduler;
class AudioReader;
class ClientControlDispatcher;
class ClientEventDispatcher;
class ClientVideoDispatcher;

class IceConnectionToHost : public ConnectionToHost,
                            public Session::EventHandler,
                            public IceTransport::EventHandler,
                            public ChannelDispatcherBase::EventHandler {
 public:
  IceConnectionToHost(bool use_turn_api);
  ~IceConnectionToHost() override;

  // ConnectionToHost interface.
  void set_client_stub(ClientStub* client_stub) override;
  void set_clipboard_stub(ClipboardStub* clipboard_stub) override;
  void set_video_renderer(VideoRenderer* video_renderer) override;
  void InitializeAudio(
      scoped_refptr<base::SingleThreadTaskRunner> audio_decode_task_runner,
      base::WeakPtr<AudioStub> audio_stub) override;
  void Connect(std::unique_ptr<Session> session,
               scoped_refptr<TransportContext> transport_context,
               HostEventCallback* event_callback) override;
  const SessionConfig& config() override;
  ClipboardStub* clipboard_forwarder() override;
  HostStub* host_stub() override;
  InputStub* input_stub() override;
  State state() const override;

 private:
  // Session::EventHandler interface.
  void OnSessionStateChange(Session::State state) override;

  // IceTransport::EventHandler interface.
  void OnIceTransportRouteChange(const std::string& channel_name,
                              const TransportRoute& route) override;
  void OnIceTransportError(ErrorCode error) override;

  // ChannelDispatcherBase::EventHandler interface.
  void OnChannelInitialized(ChannelDispatcherBase* channel_dispatcher) override;
  void OnChannelClosed(ChannelDispatcherBase* channel_dispatcher) override;

  // MonitoredVideoStub::EventHandler interface.
  virtual void OnVideoChannelStatus(bool active);

  void NotifyIfChannelsReady();

  // Closes the P2P connection.
  void CloseChannels();

  void SetState(State state, ErrorCode error);

  HostEventCallback* event_callback_ = nullptr;

  // Stub for incoming messages.
  ClientStub* client_stub_ = nullptr;
  ClipboardStub* clipboard_stub_ = nullptr;
  VideoRenderer* video_renderer_ = nullptr;

  std::unique_ptr<AudioDecodeScheduler> audio_decode_scheduler_;

  std::unique_ptr<Session> session_;
  std::unique_ptr<IceTransport> transport_;

  std::unique_ptr<MonitoredVideoStub> monitored_video_stub_;
  std::unique_ptr<ClientVideoDispatcher> video_dispatcher_;
  std::unique_ptr<AudioReader> audio_reader_;
  std::unique_ptr<ClientControlDispatcher> control_dispatcher_;
  std::unique_ptr<ClientEventDispatcher> event_dispatcher_;
  ClipboardFilter clipboard_forwarder_;
  InputFilter event_forwarder_;

  // Internal state of the connection.
  State state_ = INITIALIZING;
  ErrorCode error_ = OK;

  // If this is true, ICE connection will use TURN API instead of the gTalk TURN
  // services to allocate relay sessions.
  bool use_turn_api_;

 private:
  SEQUENCE_CHECKER(sequence_checker_);

  DISALLOW_COPY_AND_ASSIGN(IceConnectionToHost);
};

}  // namespace protocol
}  // namespace remoting

#endif  // REMOTING_PROTOCOL_ICE_CONNECTION_TO_HOST_H_
