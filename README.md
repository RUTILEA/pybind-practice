# pybind-practice

## 動作方法
- mod.cppのビルド:`make build`
- main.pyでmod.cpp内の関数を実行:`make test`
- 両方実行:`make all` 


## 備考
ビルドにはとりあえずMakefileを用いているが
実際に運用する際はcmakeを使うことが予想されるので
以下のドキュメントを参照されたし
https://pybind11.readthedocs.io/en/stable/compiling.html#building-with-cmake
