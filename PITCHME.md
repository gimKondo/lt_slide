### Vagrantで作る・配る・更新する開発環境

(タイトルの強制大文字化の回避に成功)

---

### 背景

元々はEC2(AWS)、GCE(GCP)を開発環境にしていたのだが…

---

しかし、数々の困難が開発者に立ちはだかる

---

構築にかかる時間

---

暗黙化されるインストールパッケージ

---

更新から置き去りにされる個人環境

---

勝手に大文字化されるタイトル
(これはGitPitchだった)

---

膨れ上がる開発費用

---

コンソールを強いられる開発者

---

### そのとき、Vagrantが立ち上がった

風の中のすば○ー

---

### EC2・GCEの問題点まとめ

- 配布が難しい
    - SSHキー
    - 個人設定
- 環境の可視化が難しい
- 環境の更新の配布が難しい
- コーディングがコンソール上に限定される
- 金がかかる(大きな金額ではないが)
- ネット接続に依存

---

### Vagrantの概要

- ホストOS(Windows、Mac等)からVMを便利に扱うツール
- VMの情報をテキストファイル(Vagrantfile)で記述可能
- ホストOSとファイルの共有可能(が、苦労するポイントあり)

---

### 今回目指す開発環境

- 配布可能な開発(実行)環境
- コードはホストOS、ゲストOS双方からアクセス可能
    - ホストOSでもゲストOS(コンソール)でもコーディング可能
- 開発環境に更新があったら簡単に配布可能

---

### 実行環境

- Vagrant上にdockerで構築
    - アプリケーションサーバ
    - DBサーバ
- Dockerは今回の話のメインではないので割愛

---

### ホスト-ゲスト間のコード共有(初期案)

- 方法1: デフォルトの共有機能(VirtualBoxのファイル共有)
    - 共有ファイルへのアクセスが遅くなる
    - 長いパス名がエラーになるケースあり
        - 例: node_modulesのパッケージ
- 方法2: rsync
    - rsyncを別途動かす必要あり
    - ホストからゲストへの一方通行の同期
        - ゲストでの変更は保持されない

---

### ホスト-ゲスト間のコード共有(暫定版)

- 基本はデフォルトの共有機能を使用
- node_moduleディレクトリはゲストOSでmount
    - `mount --bind `
    - このディレクトリ内にはホストOSからアクセスしない前提

```sh
# Vagrantfileのprovisionから抜粋
echo "*************** start mount node_modules *******************"
mkdir #{VAGRANT_HOME}/vagrant_node_modules
mkdir #{GUEST_SHARED_DIR}/#{APP_DIR}/node_modules
mount --bind #{VAGRANT_HOME}/vagrant_node_modules #{GUEST_SHARED_DIR}/#{APP_DIR}/node_modules
echo "*************** complete mount node_modules *******************"
```

### ゲストOSでの開発環境

- ホストOSとコードを共有しているので、ホストOSで開発したい人はお気に召すまま
- じゃあ、ゲストOS(コンソール)で開発したい人は？
    - (近藤のみという説もあるが)
- ゲストにSSHした段階でも十分にコーディングできる環境を構築
    - Vagrantfileのprovision

---

### ゲストOSのdotfile管理(1)

- 専用のリポジトリで管理
    - https://github.com/gimKondo/dotfiles

```sh
# install.shから抜粋
for f in .??*; do
  [ "$f" = ".git" ] && continue
  [ "$f" = "README.md" ] && continue
  if [ $# -ne 1 ]; then
    ln -snfv ~/dotfiles/"$f" ~/
  else
    ln -snfv $1/dotfiles/"$f" $1/
  fi
done
```

---

### おまけ1: .gitconfigの外部設定include

- .gitconfigの大半の設定は皆で共有したい
- しかし、userのnameやemailは個別で設定したい
- それなら、個別設定したい項目は.gitconfigから除外して、外部ファイルから取り込む
    - 外部ファイルは必要なら各自で準備

```
[include]
    path = ~/.local.gitconfig
```

---

### おまけ2: TeraTermからのアクセス

- WindowsのPowerShellは文字化け等の問題があるのでTeraTermを使用
- TeraTermからのsshはマクロを使えば一発
    - https://qiita.com/gimKondo/items/5b0e87d49ce739961e43
