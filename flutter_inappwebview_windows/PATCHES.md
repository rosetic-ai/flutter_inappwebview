# Vendored: flutter_inappwebview_windows 0.7.0-beta.3

Source: https://pub.dev/packages/flutter_inappwebview_windows/versions/0.7.0-beta.3

## Applied patches

1. https://github.com/pichillilorenzo/flutter_inappwebview/pull/2768
   (commit `8ee862eec097cae5a7bbea735c66aa0e08fa0ea1`) — creates the hidden
   WebView2 host windows as `WS_CHILD` of the Flutter window instead of
   separate top-level windows, so clicking inside an `InAppWebView` no longer
   triggers a focus fight that blurs HTML inputs / closes dropdowns
   (upstream issue: https://github.com/pichillilorenzo/flutter_inappwebview/issues/2736).

2. `lib/src/in_app_webview/custom_platform_view.dart` — stop the webview's
   Flutter `FocusNode` from ever acquiring focus (`autofocus: false`,
   `canRequestFocus: false`, drop the pointer-down `requestFocus()` + 50ms
   retry). The node is inert in this plugin version (empty `onFocusChange`,
   no key handlers), but acquiring Flutter focus while the WebView2 window
   holds Win32 focus makes the framework call
   `requestViewFocusChange(state: focused)` (see `_scopeFocusChangeListener`
   in Flutter's `widgets/view.dart`), which natively re-focuses the Flutter
   HWND and blurs the HTML element the user just clicked. Not upstreamed yet.

3. `windows/in_app_webview/` — reply to the `addWebMessageListener` platform
   channel call only after the CDP `Page.addScriptToEvaluateOnNewDocument`
   registration completes (threads the existing `addScriptToWebView`
   completion handler through `addUserOnlyScript`). Previously the Dart
   `await controller.addWebMessageListener(...)` resolved while registration
   was still in flight, so a `loadUrl` issued right after could create the
   first document before the script was registered — the `jsObjectName`
   object (e.g. `parentChannel`) then never appears in that document and
   page-to-Dart `postMessage` is silently lost, because document-start
   scripts are never injected retroactively. Awaiting registration matches
   Android/iOS, where it is synchronous. Also adds a missing early `return`
   in the null-webview guard of `UserContentController::addScriptToWebView`,
   which otherwise fell through to a null dereference. Not upstreamed yet.
