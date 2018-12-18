# nagato

第29回全国高等専門学校プログラミングコンテスト競技部門のソルバです

## 言語

- D(ldc2 1.12.0)

## ビルドと実行

```sh
dub --compiler=ldc2 --build=release --
```

## 依存ライブラリ

- nephele

## Mac(brew)

```sh
brew install ldc
```

## Ubuntu 18.04*

**※ aptで入れたldcでは動かないので注意**

```sh
curl -fsS https://dlang.org/install.sh | bash -s ldc
```

の後，言われたとおりにpath通す
