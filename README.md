# SpriteToBmp

Arduino(M5Stick-C) Library for encoding TFT_eSprite to Windows Bitmap using base64.

# Example

- Upload `examples/serial_write.cpp` to M5Stick-C.
- Decode images with bellow commnad.
```console
$ pio device monitor -b 115200 | grep -e "==== BMP:" | sed -e "s/==== BMP://" | awk '/[a-zA-Z0-9+\/=]/{ decode ="base64 -i -d | convert bmp:- example" NR ".png "; print $0 | decode ; close(decode) }' RS="---- cut ----"
```
- Quit monitor when `Ctrl-C` displayed on M5Stick-C
- `.png` files has been saved on host pc.
![]()