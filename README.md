# janet-base16
Base 16 encoding/decoding of buffers.

# Quick examples
```
(import base16)
(base16/encode @"\x12\x34")
"1234"
(base16/decode "1234")
@"\x12\x34"
```
