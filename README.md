aese is An ANSI Escape Sequences Emulator
=========================================

何が出来る？
------------

Windows標準のターミナル、いわゆる、「コマンドプロンプト」は、ANSIエスケープシーケンスをサポートしていません。

aeseコマンドは Windows API でANSIエスケープシーケンスを再現します。

下記の機能を実装しています。

1. 標準出力を受け取りエスケープシーケンスを取り除く
2. 文字属性の再現(部分的)
3. カーソルの移動の再現(未実装)

使い方
------

    echo ^[[43maaa^[[0m|aese

^[ は CTRL + [ と入力します。コードは 0x1B です。

ライセンス
----------

Copyright(c) 2013 sharkpp All rights reserved.

このプログラムは、The MIT License の元で公開されています。
