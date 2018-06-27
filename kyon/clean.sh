#!/bin/sh

# OS check
if [ "$(uname)" == 'Darwin' ]; then
  OS='Mac'
elif [ "$(expr substr $(uname -s) 1 5)" == 'Linux' ]; then
  OS='Linux'
elif [ "$(expr substr $(uname -s) 1 10)" == 'MINGW32_NT' ]; then                                                                                           
  OS='Cygwin'
else
  echo "Your platform ($(uname -a)) is not supported."
  exit 1
fi

if [ "$OS" == "Mac" ]; then
  cd ./siv3d_v0.2.6_macOS/kyon/kyon/
  xcodebuild clean
  cd ../../../
elif [ "$OS" == "Linux" ]; then
  cd ./siv3d_v0.2.3_alpha_Linux/kyon/build/
  rm -r CMakeCache.txt CMakeFiles Makefile cmake_install.cmake kyon
  cd ../../../
fi

echo "Your platform is ""${OS}"". clean succeeded."
