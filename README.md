# Introduction
K4Oxygen is a variant of KDE4 Oxygen widget theme, released from KDE dependencies and supported both for Qt4 and Qt5.

It is based on oxygen-transparent for KDE4 (as of commit [aa154d4](https://github.com/KDE/oxygen-transparent/commit/aa154d4e2f930258a9f094014103078a91003180)), but currently has some **limitations**:

* no window decorations implementation (it'd depend on KDE anyway, and the code would likely be different for KDE4 and KF5)
* no configuration utility
* translucency in Qt5 version is in experimental stage

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
## Making K4Oxygen current Qt theme
* Qt4: You can choose current theme using `qtconfig` (or, on some distros, `qtconfig-qt4`)
* Qt5: Qt5 doesn't provide a standard utility to set its theme, but you can either try `qt5ct` utility, or set a global environment variable `QT_STYLE_OVERRIDE` to `k4oxygen`.

## Style settings
In a KDE session K4Oxygen should pick the Oxygen and global KDE settings automatically with no user intervention.

In a non-KDE session you can set non-default settings by editing `oxygenrc` and `kdeglobals` files. These files are searched as follows:

1. If `kde4-config --path config` works, its output paths are used
2. Otherwise, the path is set to `$HOME/.config/k4oxygen` (or `$XDG_CONFIG_HOME/k4oxygen`, if `XDG_CONFIG_HOME` is set).

If you've edited `oxygenrc` or `kdeglobals`, you can force configuration reloading using these commands (`TypeOfChange` is a parameter):

    dbus-send --type=signal /KGlobalSettings org.kde.KGlobalSettings.notifyChange int32:TypeOfChange int32:0  # for kdeglobals
    dbus-send --type=signal /OxygenStyle org.kde.Oxygen.Style.reparseConfiguration # for oxygenrc

Here `TypeOfChange` for `kdeglobals` is one of the following (the ones supported):

* 0 — means Palette Changed
* 1 — means Font Changed
* 3 — means Settings Changed

These commands simulate the signals sent by KDE's *System Settings* utility.
