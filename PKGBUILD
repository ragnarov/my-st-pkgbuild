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
## https://dl.suckless.org/$pkgname/$pkgname-$pkgver.tar.gz
source=(
    "${pkgname}-${pkgver}::git+https://github.com/ragnarov/my-st-build"
    config.h
)
sha256sums=(
    'SKIP'
    'SKIP'
)
_sourcedir=$pkgname-$pkgver
_makeopts="--directory=$_sourcedir"

prepare() {
    cd $srcdir/$pkgname-$pkgver

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
  install $installopts "$docdir" "$_sourcedir/README.terminfo.rst"
  install $installopts "$shrdir/$pkgname" "$_sourcedir/st.info"
}
