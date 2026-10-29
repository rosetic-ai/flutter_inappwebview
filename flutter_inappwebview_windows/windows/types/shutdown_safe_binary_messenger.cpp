#include <utility>

#include "shutdown_safe_binary_messenger.h"

namespace flutter_inappwebview_plugin
{
  ShutdownSafeBinaryMessenger::ShutdownSafeBinaryMessenger(flutter::BinaryMessenger* messenger, FlutterDesktopMessengerRef engineMessenger)
    : messenger_(messenger), engineMessenger_(engineMessenger)
  {}

  void ShutdownSafeBinaryMessenger::Send(const std::string& channel,
    const uint8_t* message,
    size_t message_size,
    flutter::BinaryReply reply) const
  {
    if (FlutterDesktopMessengerIsAvailable(engineMessenger_)) {
      messenger_->Send(channel, message, message_size, std::move(reply));
    }
  }

  void ShutdownSafeBinaryMessenger::SetMessageHandler(const std::string& channel,
    flutter::BinaryMessageHandler handler)
  {
    if (FlutterDesktopMessengerIsAvailable(engineMessenger_)) {
      messenger_->SetMessageHandler(channel, std::move(handler));
    }
  }
}
