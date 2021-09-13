# linux-keywatcher

A keywatcher, that sends a network request to `http://10.10.10.10:4444/toggle-usb-switch` when RSHIFT is pressed.

Code inspired by [SCOTPAUL/keylog](https://github.com/SCOTPAUL/keylog).

* Hardcoded to use "Apple Magic Keyboard" as input source (see main.c).
* Uses `/usr/bin/curl` binary.
