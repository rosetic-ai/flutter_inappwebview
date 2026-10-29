#ifndef FLUTTER_INAPPWEBVIEW_PLUGIN_SHUTDOWN_SAFE_BINARY_MESSENGER_H_
#define FLUTTER_INAPPWEBVIEW_PLUGIN_SHUTDOWN_SAFE_BINARY_MESSENGER_H_

#include <string>

#include <flutter/binary_messenger.h>
#include <flutter_messenger.h>

namespace flutter_inappwebview_plugin
{
  // ~FlutterWindowsEngine detaches the messenger from the engine before it destroys plugins,
  // so channel calls made from plugin destructors would dereference a null engine.
  class ShutdownSafeBinaryMessenger : public flutter::BinaryMessenger
  {
  public:
    ShutdownSafeBinaryMessenger(flutter::BinaryMessenger* messenger, FlutterDesktopMessengerRef engineMessenger);

    void Send(const std::string& channel,
      const uint8_t* message,
      size_t message_size,
      flutter::BinaryReply reply) const override;

    void SetMessageHandler(const std::string& channel,
      flutter::BinaryMessageHandler handler) override;

  private:
    flutter::BinaryMessenger* messenger_;
    FlutterDesktopMessengerRef engineMessenger_;
  };
}

#endif //FLUTTER_INAPPWEBVIEW_PLUGIN_SHUTDOWN_SAFE_BINARY_MESSENGER_H_
