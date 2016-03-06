## Prerequisites

* [Visual C++ Redistributable for Visual Studio 2015 Update 1](https://www.microsoft.com/en-US/download/details.aspx?id=49984) (x86)
* Kindred Spirits on the Roof
* 屋上の百合霊さん

## Instruction

「Kindred Spirits on the Roof」と「屋上の百合麗さん」が共に起動している状態でこのアプリの「Push」と書かれたボタンを押すと、一方で行ったマウス・キーボードの操作が他方にも影響するようになります。このアプリを終了するとその状態が解除されるほか、キーボードの「S」を押している間はマウス操作は他方に影響しません。

## Download

https://pinterior.github.io/yuri2/yuri2.zip

## FAQ

### 英語版を起動後、日本語版が起動しない

同時起動防止用の仕組みが、他言語版にも作用しています。[ProcessExplorer](https://technet.microsoft.com/en-us/sysinternals/processexplorer.aspx)を管理者権限で起動して、
先に起動した方のプロセスを選び `\Sessions\1\BaseNamedObjects\RSCRIPT` という名前の`Mutant`を`Close Handle`してやればもう片方が起動できる状態になります。

### 操作していない側のメッセージが表示されない

サイレントモードをOFFに。

## Build environment

* Visual Studio 2015 Professional Update 1
* [WTL 9.1 build 5321 Final](http://wtl.sourceforge.net/)
