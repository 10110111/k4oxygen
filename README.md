# Introduction
K4Oxygen is a variant of KDE4 Oxygen widget theme, released from KDE dependencies and supported both for Qt4 and Qt5.

It is based on oxygen-transparent for KDE4 (as of commit [aa154d4](https://github.com/KDE/oxygen-transparent/commit/aa154d4e2f930258a9f094014103078a91003180)), but currently has some **limitations**:

* no window decorations implementation (it'd depend on KDE anyway, and the code would likely be different for KDE4 and KF5)
* no configuration utility
* transparency is broken on Qt5

The theme does read Oxygen and global KDE settings similarly to how oxygen-gtk does it.

# Installation
You can install it using the following commands

    mkdir build
    cd build
    cmake .. -DQT_VERSION=5
    make
    sudo make install

Similarly, for Qt4 version replace `-DQT_VERSION=5` with `-DQT_VERSION=4`.

# Configuration
In a KDE session K4Oxygen should pick the Oxygen and global KDE settings automatically with no user intervention.

In a non-KDE session you can set non-default settings by editing `oxygenrc` and `kdeglobals` files. These files are searched as follows:

1. If `kde4-config --path config` works, its output paths are used
2. Otherwise, the path is set to `$HOME/.config/k4oxygen` (or `$XDG_CONFIG_HOME/k4oxygen`, if `XDG_CONFIG_HOME` is set).

If you've edited `oxygenrc` or `kdeglobals`, you can force configuration reloading using these commands:

    dbus-send --type=signal /KGlobalSettings org.kde.KGlobalSettings.notifyChange  # for kdeglobals
    dbus-send --type=signal /OxygenStyle org.kde.Oxygen.Style.reparseConfiguration # for oxygenrc

These commands simulate the signals sent by KDE's *System Settings* utility.
