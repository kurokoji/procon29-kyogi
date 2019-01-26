# kyon

第29回全国高等専門学校プログラミングコンテスト競技部門のGUIです

## 言語

- C_++(clang 6.0.0)

## ビルドと実行

```sh
./build.sh
./execute.sh
```

## 依存ライブラリ

- OpenSiv3D
- boost::asio

### Ubuntu 18.04(18.04のみ起動保証)

- ビルド済みOpenSiv3Dをダウンロード
```sh
sudo apt install gcc clang git cmake libx11-dev libxi-dev libxinerama-dev libxcursor-dev libxrandr-dev libjpeg-dev libpng-dev libgl1-mesa-dev libglu1-mesa-dev libglib2.0-dev libfreetype6-dev libturbojpeg-dev libopenal-dev libfontconfig-dev libudev-dev libboost-dev libboost-all-dev libglew-dev libbox2d-dev libgif-dev libopencv-dev
./setup.sh
```
