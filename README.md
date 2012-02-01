QT DisplayLink Presenter
========================

Usage
-----

Connect your DisplayLink device to one of the USB ports. Start the `qtdloprez`
executable and select the `Load PDF...` in the `Presentation` menu. Select the
resolution you'd like to display the presentation in, then select the PDF
file. Please wait while ImageMagick converts your PDF into PNGs of suitable
size. When it's ready, the first page will be shown both in the window and on
the external display. You can step forward and back by pressing the Spacebar
and Backspace or using the `Presentation` menu.

Compiling
---------

1. Install the dependencies if necessary (see below).
2. Create a new directory / folder and check out the repository into it.
3. Copy `dlo_defs.h` and `libdlo.h` from the libdlo source to the directory with the source code.
4. Execute `qmake && make` which should compile everything and produce `qtdloprez`

License
-------

The whole project is licensed under MIT license.

Runtime dependencies
--------------------

 - QT4 GUI (Debian/Ubuntu package: `libqtgui4`)
 - libdlo (http://libdlo.freedesktop.org/)
 - ImageMagick (Debian/Ubuntu package: `imagemagick`)

Build dependencies
------------------

 - QT4 development files (Debian/Ubuntu package: `libqt4-dev`)
 - libdlo (http://libdlo.freedesktop.org/)
