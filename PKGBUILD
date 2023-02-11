# Maintainer: Jose Riha <jose1711 gmail com>
# Maintainer: Sebastian J. Bronner <waschtl@sbronner.com>
# Maintainer: Kevin Stolp <kevinstolp@gmail.com>
# Contributor: Patrick Jackson <PatrickSJackson gmail com>
# Contributor: Christoph Vigano <mail@cvigano.de>

pkgname=st
pkgver=0.9
pkgrel=1
pkgdesc='A simple virtual terminal emulator for X.'
arch=('i686' 'x86_64' 'armv7h' 'aarch64')
license=('MIT')
depends=(libxft)
url=https://st.suckless.org
source=(
https://dl.suckless.org/$pkgname/$pkgname-$pkgver.tar.gz
terminfo.patch
README.terminfo.rst
st-copyurl-multiline-20220221-0.8.5.diff
st-blinking_cursor-20211116-2f6e597.diff
config.h
)
sha256sums=(
            'f36359799734eae785becb374063f0be833cf22f88b4f169cd251b99324e08e7'
            'f9deea445a5c6203a0e8e699f3c3b55e27275f17fb408562c4dd5d649edeea23'
            '0ebcbba881832adf9c98ce9fe7667c851d3cc3345077cb8ebe32702698665be2'
            'SKIP'
            'SKIP'
            'SKIP'
            )
_sourcedir=$pkgname-$pkgver
_makeopts="--directory=$_sourcedir"

prepare() {
    patch --directory="$_sourcedir" --strip=0 < terminfo.patch
    cd $srcdir/$pkgname-$pkgver
    patch -p1 < "$srcdir/st-copyurl-multiline-20220221-0.8.5.diff"
    patch -p1 < "$srcdir/st-blinking_cursor-20211116-2f6e597.diff"

    [ -e "${srcdir}/config.h" ] && cp "${srcdir}/config.h" "${srcdir}/${pkgname}-${pkgver}"

}

build() {
  make $_makeopts X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  local installopts='--mode 0644 -D --target-directory'
  local shrdir="$pkgdir/usr/share"
  local licdir="$shrdir/licenses/$pkgname"
  local docdir="$shrdir/doc/$pkgname"
  make $_makeopts PREFIX=/usr DESTDIR="$pkgdir" install
  install $installopts "$licdir" "$_sourcedir/LICENSE"
  install $installopts "$docdir" "$_sourcedir/README"
  install $installopts "$docdir" README.terminfo.rst
  install $installopts "$shrdir/$pkgname" "$_sourcedir/st.info"
}