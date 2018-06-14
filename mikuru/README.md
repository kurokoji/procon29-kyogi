# mikuru

第29回全国高専プログラミングコンテスト競技部門のQRコードリーダです

## ビルドと実行

``` sh
mkdir build
cd build
cmake ..
make
./mikuru
```

## 依存ライブラリ

- OpenCV
- ZBar

### Mac(brew)

``` sh
brew install opencv zbar
```

### Ubuntu 18.04(apt)

``` sh
sudo apt install libopencv-dev libzbar-dev zbar-tools
```
