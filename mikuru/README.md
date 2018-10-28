# mikuru

第29回全国高等専門学校プログラミングコンテスト競技部門のQRコードリーダです

## 言語

- C_++(clang 6.0.0)

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
- Boost

### Mac(brew)

``` sh
brew install opencv zbar boost
```

### Ubuntu 18.04(apt)

``` sh
sudo apt install libopencv-dev libzbar-dev zbar-tools libboost-dev
```
